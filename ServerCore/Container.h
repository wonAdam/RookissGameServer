#pragma once

#include "Types.h"
#include "Allocator.h"
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <string>

template<typename Type>
using xVector = std::vector<Type, STLAllocator<Type>>;

template<typename Type, typename Container = xDeque<Type>>
using xQueue = std::queue<Type, Container>;

template<typename Type, typename Container = xDeque<Type>>
using xStack = std::stack<Type, Container>;

template<typename Type, typename Container = xVector<Type>, typename Pred = less<typename Container::value_type>> 
using xPriorityQueue = std::priority_queue<Type, Container, Pred>;

template<typename Type>
using xList = std::list<Type, STLAllocator<Type>>;

template<typename Type>
using xDeque = std::deque<Type, STLAllocator<Type>>;

template<typename Key, typename Value, typename Pred = std::less<Key>>
using xMap = std::map<Key, Value, Pred, STLAllocator<std::pair<Key, Value>>>;

template<typename Key, typename Value, typename Hasher = hash<Key>, typename KeyEq = equal_to<Key>>
using xHashMap = std::unordered_map<Key, Value, Hasher, KeyEq, STLAllocator<std::pair<Key, Value>>>;

template<typename Key, typename Pred = std::less<Key>>
using xSet = std::set<Key, Pred, STLAllocator<Key>>;

template<typename Key, typename Hasher = hash<Key>, typename KeyEq = equal_to<Key>>
using xHashSet = std::unordered_set<Key, Hasher, KeyEq, STLAllocator<Key>>;

using xString = std::basic_string<char, std::char_traits<char>, STLAllocator<char>>;

using xWString = std::basic_string<wchar_t, std::char_traits<wchar_t>, STLAllocator<wchar_t>>;

