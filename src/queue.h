//
// Created by researcher on 9/28/20.
//

#ifndef QUEUEPROCESSOR_QUEUE_H
#define QUEUEPROCESSOR_QUEUE_H

#include "traits.h"
#include <cassert>

namespace queue_processor{
    template<typename T, typename = std::void_t<>>
    struct is_hashable : std::false_type {
    };

    template<typename T>
    struct is_hashable<T,
            std::void_t < decltype(std::declval < std::hash < T >> ()(std::declval<T>()))>> : std::true_type {
    };

    template<typename Key, typename Value, typename ValueOrder>
    class Queue{
        using ValueContainer = typename ValueOrderTraits<Value, ValueOrder>::type;
        using QueueContainer = typename std::conditional_t<is_hashable<Key>::value, std::unordered_map < Key, ValueContainer>,
                                                                                    std::map <Key, ValueContainer>>;

        const size_t capacityOfValues{0};
        QueueContainer queues;
    public:
        explicit Queue(size_t capacity)
        : capacityOfValues(capacity) {
                assert(capacity != 0);
        }

        bool empty() const {
            return queues.empty();
        }

        bool queue(const Key &key, const Value &value) {
            auto & queue = queues[key];
            return insert(queue, value);
        }

        std::optional <Value> deque(const Key &id) {
            std::optional <Value> result;

            if (auto queue = queues.find(id); queue != queues.end()) {
                result = *(queue->second.begin());
                clean(queue);
            }

            return result;
        }
    private:
        bool insert(ValueContainer & container, const Value & value){
            if(container.size() == capacityOfValues){
                return false;
            }

            if constexpr (std::is_same < ValueContainer, std::deque < Value >> ::value) {
                container.emplace_back(value);
            }else{
                container.insert(value);
            }

            return true;
        }

        void clean(typename QueueContainer::iterator &itQueue){
            if (itQueue->second.size() == 1) {
                queues.erase(itQueue);
            } else{
                itQueue->second.erase(itQueue->second.begin());
            }
        }
    };
}

#endif //QUEUEPROCESSOR_QUEUE_H
