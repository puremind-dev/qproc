//
// Created by researcher on 9/28/20.
//

#include <boost/test/unit_test.hpp>
#include "queue.h"

using namespace queue_processor;

BOOST_AUTO_TEST_CASE(test_empty_seq) {
    Queue<int, int, sequential> queues(2);

    queues.queue(1, 2);
    queues.queue(1, 1);

    BOOST_CHECK_EQUAL(queues.empty(), false);
    BOOST_CHECK_EQUAL(*queues.deque(1), 2);
    BOOST_CHECK_EQUAL(queues.empty(), false);
    BOOST_CHECK_EQUAL(*queues.deque(1), 1);
    BOOST_CHECK_EQUAL(queues.empty(), true);
}

BOOST_AUTO_TEST_CASE(test_reach_limit_capcity_seq) {
    Queue<int, int, sequential> queues(2);

    BOOST_CHECK_EQUAL(queues.queue(1, 1), true);
    BOOST_CHECK_EQUAL(queues.queue(1, 1), true);
    BOOST_CHECK_EQUAL(queues.queue(1, 2), false);
}

BOOST_AUTO_TEST_CASE(test_order_seq) {
    Queue<int, int, sequential> queues(3);

    queues.queue(1, 2);
    queues.queue(1, 1);
    queues.queue(1, 2);

    BOOST_CHECK_EQUAL(*queues.deque(1), 2);
    BOOST_CHECK_EQUAL(*queues.deque(1), 1);
    BOOST_CHECK_EQUAL(*queues.deque(1), 2);
}

BOOST_AUTO_TEST_CASE(test_duplicate_values_seq) {
    Queue<int, int, sequential> queues(2);

    queues.queue(1, 1);
    queues.queue(1, 1);

    BOOST_CHECK_EQUAL(*queues.deque(1), 1);
    BOOST_CHECK_EQUAL(*queues.deque(1), 1);
}

BOOST_AUTO_TEST_CASE(test_empty_ordered) {
    Queue<int, int, ordered> queues(3);

    queues.queue(1, 2);
    queues.queue(1, 1);
    queues.queue(1, 1);

    BOOST_CHECK_EQUAL(queues.empty(), false);
    BOOST_CHECK_EQUAL(*queues.deque(1), 1);
    BOOST_CHECK_EQUAL(queues.empty(), false);
    BOOST_CHECK_EQUAL(*queues.deque(1), 1);
    BOOST_CHECK_EQUAL(queues.empty(), false);
    BOOST_CHECK_EQUAL(*queues.deque(1), 2);
    BOOST_CHECK_EQUAL(queues.empty(), true);
}

BOOST_AUTO_TEST_CASE(test_reach_limit_capcity_ordered) {
    Queue<int, int, ordered> queues(2);

    BOOST_CHECK_EQUAL(queues.queue(1, 1), true);
    BOOST_CHECK_EQUAL(queues.queue(1, 1), true);
    BOOST_CHECK_EQUAL(queues.queue(1, 2), false);
}

BOOST_AUTO_TEST_CASE(test_order_ordered) {
    Queue<int, int, ordered> queues(3);

    queues.queue(1, 2);
    queues.queue(1, 1);
    queues.queue(1, 2);

    BOOST_CHECK_EQUAL(*queues.deque(1), 1);
    BOOST_CHECK_EQUAL(*queues.deque(1), 2);
    BOOST_CHECK_EQUAL(*queues.deque(1), 2);
}

BOOST_AUTO_TEST_CASE(test_duplicate_values_ordered) {
    Queue<int, int, ordered> queues(2);

    queues.queue(1, 1);
    queues.queue(1, 1);

    BOOST_CHECK_EQUAL(*queues.deque(1), 1);
    BOOST_CHECK_EQUAL(*queues.deque(1), 1);
}
