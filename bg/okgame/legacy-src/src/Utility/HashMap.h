#pragma once
#include "bobtypes.h"
class Logger;
#include <unordered_map>
#include <memory>
#include "Logger.h"
#include "ArrayList.h"


template <typename K, typename V> class HashMap
{
public:
	static Logger log;

	std::unordered_map<K, V> m;

	HashMap<K, V>() {
	}
	~HashMap<K, V>() {
	}

	// Java API Compatibility

	V put(K k, V v) {
		V previousValue = V();
		auto it = m.find(k);
		if (it != m.end()) {
			previousValue = it->second;
			it->second = v;
		} else {
			m.insert({k, v});
		}
		return previousValue;
	}

	// Java remove(Object key) returns V
	V remove(K k) {
		V value = V();
		auto it = m.find(k);
		if (it != m.end()) {
			value = it->second;
			m.erase(it);
		}
		return value;
	}

	// Alias for remove(K) to match existing code
	void removeAt(K k) {
		remove(k);
	}

	void removeAllValues(V v) {
		for (auto it = m.begin(); it != m.end(); ) {
			if (it->second == v) {
				it = m.erase(it);
			} else {
				++it;
			}
		}
	}

	bool containsKey(K k) {
		return m.find(k) != m.end();
	}

	bool containsValue(V v) {
		for (auto const& [key, val] : m) {
			if (val == v) return true;
		}
		return false;
	}

	void clear() {
		m.clear();
	}

	bool isEmpty() {
		return m.empty();
	}

	int size() {
		return (int)m.size();
	}

	V get(K k) {
		auto it = m.find(k);
		if (it != m.end()) {
			return it->second;
		}
		// Return default (nullptr for pointers)
		return V();
	}

	K getFirstKey(V v) {
		for (auto const& [key, val] : m) {
			if (val == v) return key;
		}
		return K();
	}

	// Returns ArrayList instead of Collection, matching C++ style usage
	ArrayList<V> getAllValues() {
		ArrayList<V> list;
		for (auto const& [key, val] : m) {
			list.add(val);
		}
		return list;
	}

	// Java API alias
	ArrayList<V> values() {
		return getAllValues();
	}

	ArrayList<K> keySet() {
		ArrayList<K> list;
		for (auto const& [key, val] : m) {
			list.add(key);
		}
		return list;
	}

};

template <typename K, typename V>
Logger HashMap<K,V>::log = Logger("HashMap");
