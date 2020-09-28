//
// Created by researcher on 9/28/20.
//

//
// Created by researcher on 9/8/20.
//

#include <boost/test/unit_test.hpp>
#include "processor.h"

#include <chrono>

using namespace std::chrono_literals;
using namespace queue_processor;

BOOST_AUTO_TEST_CASE(test_run){
    QueueProcessor<int, int, unique, sequential> processor;
    std::vector<std::thread> producers;
    std::atomic<int> total_count = 0;
    constexpr size_t countConsumers = 3;
    constexpr size_t countItems = 100;

    auto consumer = [&](const int& id, const int& val){
        ++total_count;
    };

    auto producer = [&](size_t count, int key){
        for(size_t i = 0; i != count; ++i){
            processor.queue(key, i);
        }
    };

    processor.start();

    processor.subscribe(0, consumer);
    processor.subscribe(1, consumer);
    processor.subscribe(2, consumer);

    for(auto i = 0; i != countConsumers; ++i ){
        producers.emplace_back(producer, countItems, i);
    }

    for(auto &th : producers){
        th.join();
    }


    while(total_count != countItems*countConsumers)
        continue;


    BOOST_CHECK_EQUAL(true, true);
}

BOOST_AUTO_TEST_CASE(test_register_subscribers) {
    QueueProcessor<int, int, unique, sequential> processor;
    auto consumer = [&](const int& id, const int& val){

    };

    processor.start();

    std::this_thread::sleep_for(3s);
    for(auto i = 0; i != 1000; ++i )
        processor.subscribe(i, consumer);


    BOOST_CHECK_EQUAL(true, true);
}


BOOST_AUTO_TEST_CASE(test_consumer_process) {
    QueueProcessor<int, int, unique, sequential> processor;
    size_t limit = 10;
    std::atomic<int> consumerCount{0};
    std::vector<int> values;
    int key = 1;
    std::vector checkSequence({0,1,2,3,4,5,6,7,8,9});

    auto consumer = [&](const int &id, const int &val) {
        values.push_back(val);
        ++consumerCount;
    };

    auto producer = [&](size_t count, int key){
        for(size_t i = 0; i != count; ++i){
            processor.queue(key, i);
        }
    };

    processor.subscribe(key, consumer);
    processor.start();

    auto producerThread = std::thread(producer, limit, key);

    producerThread.join();

    while(consumerCount != limit)
        continue;

    BOOST_CHECK_EQUAL_COLLECTIONS(values.begin(), values.end(), checkSequence.begin(), checkSequence.end());
}

