#pragma once
#include "bobtypes.h"
#include "HashMap.h"
#include <mutex>

template <typename K, typename V> class Hashtable
{
public:
	// Wrapper around HashMap with synchronization
	HashMap<K, V> map;
	std::recursive_mutex mtx;

	Hashtable() {}
	~Hashtable() {}

	V put(K k, V v) {
		std::lock_guard<std::recursive_mutex> lock(mtx);
		return map.put(k, v);
	}

	V remove(K k) {
		std::lock_guard<std::recursive_mutex> lock(mtx);
		return map.remove(k);
	}

	void removeAt(K k) {
		std::lock_guard<std::recursive_mutex> lock(mtx);
		map.removeAt(k);
	}

	void removeAllValues(V v) {
		std::lock_guard<std::recursive_mutex> lock(mtx);
		map.removeAllValues(v);
	}

	bool containsKey(K k) {
		std::lock_guard<std::recursive_mutex> lock(mtx);
		return map.containsKey(k);
	}

	bool containsValue(V v) {
		std::lock_guard<std::recursive_mutex> lock(mtx);
		return map.containsValue(v);
	}

	void clear() {
		std::lock_guard<std::recursive_mutex> lock(mtx);
		map.clear();
	}

	bool isEmpty() {
		std::lock_guard<std::recursive_mutex> lock(mtx);
		return map.isEmpty();
	}

	int size() {
		std::lock_guard<std::recursive_mutex> lock(mtx);
		return map.size();
	}

	V get(K k) {
		std::lock_guard<std::recursive_mutex> lock(mtx);
		return map.get(k);
	}

	K getFirstKey(V v) {
		std::lock_guard<std::recursive_mutex> lock(mtx);
		return map.getFirstKey(v);
	}

	ArrayList<V> getAllValues() {
		std::lock_guard<std::recursive_mutex> lock(mtx);
		return map.getAllValues();
	}

	ArrayList<V> values() {
		std::lock_guard<std::recursive_mutex> lock(mtx);
		return map.values();
	}

	ArrayList<K> keySet() {
		std::lock_guard<std::recursive_mutex> lock(mtx);
		return map.keySet();
	}
};
