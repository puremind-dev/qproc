//
// Created by researcher on 9/28/20.
//

#include <boost/test/unit_test.hpp>
#include "processor.h"

using namespace std::chrono_literals;
using namespace queue_processor;

BOOST_AUTO_TEST_CASE(test_append_subscriber){
    QueueProcessor<int, int, unique, sequential> processor;

    bool appendState = processor.subscribe(1, [](const int&, const int & ){});
    bool appendState2 = processor.subscribe(1, [](const int&, const int & ){});

    BOOST_CHECK_EQUAL(appendState, true);
    BOOST_CHECK_EQUAL(appendState2, false);
}


BOOST_AUTO_TEST_CASE(test_call_subscriber){
    QueueProcessor<int, int, unique, sequential> processor;
    int result = -1;
    int checkValue = 1;

    processor.subscribe(1, [&](const int&, const int & val){
        result = val;
    });
    processor.start();

    processor.queue(1, checkValue);

    std::this_thread::sleep_for(3s);
    processor.stop();

    BOOST_CHECK_EQUAL(result, checkValue);
}

