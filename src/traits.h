//
// Created by researcher on 9/28/20.
//

#ifndef QUEUEPROCESSOR_TRAITS_H
#define QUEUEPROCESSOR_TRAITS_H
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <set>
#include <deque>


namespace queue_processor {

    struct ordered {};

    struct unique_hash {};

    struct non_unique_hash{};

    struct unique {};

    struct sequential {};

    template<typename Key, typename Value, typename Order>
    struct ConsumerOrderTraits {
        static_assert(
                std::is_same<Order, unique>::value ||
                std::is_same<Order, unique_hash>::value,
                "Unknown order type or type does not supports");

        typedef std::unordered_map <Key, Value> type;
    };

    template<typename Key, typename Value>
    struct ConsumerOrderTraits<Key, Value, unique_hash> {
        typedef std::unordered_map <Key, Value> type;
    };

    template<typename Key, typename Value>
    struct ConsumerOrderTraits<Key, Value, unique> {
        typedef std::map <Key, Value> type;
    };

    template<typename Key, typename Order>
    struct ValueOrderTraits {
        static_assert(
                       std::is_same<Order, sequential>::value ||
                       std::is_same<Order, ordered>::value ||
                       std::is_same<Order, non_unique_hash>::value,
                       "Unknown order type or type does not supports");

        typedef std::deque <Key> type;
    };

    template<typename Key>
    struct ValueOrderTraits<Key, non_unique_hash> {
        typedef std::unordered_multiset <Key> type;
    };

    template<typename Key>
    struct ValueOrderTraits<Key, sequential> {
        typedef std::deque <Key> type;
    };

    template<typename Key>
    struct ValueOrderTraits<Key, ordered> {
        typedef std::multiset <Key> type;
    };
}

#endif //QUEUEPROCESSOR_TRAITS_H
