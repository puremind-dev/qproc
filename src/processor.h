//
// Created by researcher on 9/28/20.
//

#ifndef QUEUEPROCESSOR_PROCESSOR_H
#define QUEUEPROCESSOR_PROCESSOR_H


#include "traits.h"
#include "queue.h"

#include <deque>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <functional>


namespace queue_processor {

    template<typename Key, typename Value>
    using Consumer = std::function<void(const Key &, const Value &)>;

    template<typename Key, typename Value, typename KeyOrder = unique, typename ValueOrder = sequential>
    class QueueProcessor {
        using ConsumerContainer = typename ConsumerOrderTraits<Key, Consumer<Key, Value>, KeyOrder>::type;


        static const size_t MaxCapacity = 1000;

        std::mutex operGuard;
        ConsumerContainer consumers;
        Queue<Key,Value, ValueOrder> queues;

        std::condition_variable cv;

        bool isStopped{true};
        std::unique_ptr<std::thread> processThread;
    public:

        explicit QueueProcessor(size_t capacity = MaxCapacity)
                : queues(capacity){
        }

        ~QueueProcessor() {
            stop();
        }

        QueueProcessor(const QueueProcessor &) = delete;
        QueueProcessor &operator=(const QueueProcessor &) = delete;


        bool subscribe(const Key &key, const Consumer<Key, Value> &consumer) {
            bool state{false};
            {
                std::lock_guard<std::mutex> lck(operGuard);
                state = consumers.insert({key, consumer}).second;
            }

            cv.notify_one();

            return  state;
        }

        void unsubscribe(const Key &key) {
            {
                std::lock_guard<std::mutex> lck(operGuard);
                consumers.erase(key);
            }

            cv.notify_one();
        }

        void queue(const Key &key, const Value &value) {
            {
                std::lock_guard<std::mutex> lck(operGuard);
                queues.queue(key, value);
            }

            cv.notify_one();
        }

        void start() {
            if (isStopped) {
                isStopped = false;
                processThread = std::make_unique<std::thread>(&QueueProcessor::process, this);
            }
        }

        void stop() {
            if (!isStopped) {
                isStopped = true;
                cv.notify_one();
                processThread->join();
            }
        }

    private:
        void process() {

            while (!isStopped) {
                std::unique_lock<std::mutex> lckC(operGuard);
                cv.wait(lckC, [&]() { return (isStopped || (!queues.empty() && !consumers.empty())); });

                if (isStopped) {
                    break;
                }

                processItem();
            }
        }

        void processItem() {
            for(const auto & [id, operation] : consumers) {
                if (auto value = queues.deque(id); value) {
                    operation(id, *value);
                }
            }
        }
    };
}

#endif //QUEUEPROCESSOR_PROCESSOR_H
