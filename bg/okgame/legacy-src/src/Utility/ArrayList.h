#pragma once
#include "bobtypes.h"
class Logger;
#include <vector>
#include <algorithm>
#include "Logger.h"



template <typename E> class Vector
{
public:
	static void removeAt(vector<E> &v,int index)
	{
		auto it = v.begin();
		advance(it, index);
		v.erase(it);
	}
};

class Integer
{
public:
	int i;
	Integer(int i) { this->i = i; }
	int value() { return i; }
//	static int parseInt(string s)
//	{
//		return stoi(s);
//	}

};
//
//bool stob(string s)
//{
//	return 0 != stoi(s);
//}
class BobBoolean
{
public:
	//Parses the string argument as a boolean. The boolean returned represents the value true if the string argument is not null and is equal, ignoring case, to the string "true". 
	//Example: Boolean.parseBoolean("True") returns true.
	//Example: Boolean.parseBoolean("yes") returns false.
	static bool parseBoolean(string s)
	{
		std::transform(s.begin(), s.end(), s.begin(), ::tolower);
		if (s == "true")return true;
		return false;
	}
};
//
//class Float
//{
//	static float parseFloat(string s)
//	{
//		return stof(s);
//	}
//
//};



template <typename E> class ArrayList
{
public:
	static Logger log;

	ArrayList<E>() {}
	ArrayList<E>(int size) { v.reserve(size); }
	~ArrayList<E>() {}

	// Java API Compatibility

	bool add(E e) {
		v.push_back(e);
		return true;
	}

	void add(int index, E element) {
		if (index >= 0 && index <= (int)v.size()) {
			v.insert(v.begin() + index, element);
		} else {
			log.error("Index out of bounds in add(index, element)");
		}
	}

	bool addAll(const ArrayList<E>& c) {
		if (c.isEmpty()) return false;
		v.insert(v.end(), c.v.begin(), c.v.end());
		return true;
	}

	void clear() {
		v.clear();
	}

	bool contains(const E& e) const {
		return std::find(v.begin(), v.end(), e) != v.end();
	}

	// Alias for contains to match some Java Map usages if mixed up, but mostly for compatibility
	bool containsValue(const E& e) const {
		return contains(e);
	}

	E get(int index) {
		if (index < 0 || index >= size()) {
			log.error("Index out of bounds in get()");
			// Return default constructed object. For pointers this is nullptr.
			return E();
		}
		return v[index];
	}

	int indexOf(const E& e) const {
		auto it = std::find(v.begin(), v.end(), e);
		if (it != v.end()) {
			return (int)std::distance(v.begin(), it);
		}
		return -1;
	}

	bool isEmpty() const {
		return v.empty();
	}

	E removeAt(int index) {
		if (index < 0 || index >= size()) {
			log.error("Index out of bounds in removeAt()");
			return E();
		}
		E el = v[index];
		v.erase(v.begin() + index);
		return el;
	}

	// Java remove(Object) removes the first occurrence
	bool remove(const E& e) {
		auto it = std::find(v.begin(), v.end(), e);
		if (it != v.end()) {
			v.erase(it);
			return true;
		}
		return false;
	}

	E set(int index, E element) {
		if (index < 0 || index >= size()) {
			log.error("Index out of bounds in set()");
			return E();
		}
		E old = v[index];
		v[index] = element;
		return old;
	}

	int size() const {
		return (int)v.size();
	}

	// Helpers
	void insert(int index, E e) { // Alias for add(index, e)
		add(index, e);
	}

	void deleteAll() {
		clear();
	}

	void removeAll(const ArrayList<E>& c) {
		for (int i = 0; i < c.size(); i++) {
			E e = c.v[i]; // Access directly to avoid const issues with get() if get wasn't const
			// Remove all occurrences or just first? Java removeAll removes all occurrences of elements in c.
			// But standard remove(Object) removes first.
			// Let's use std::remove_if for efficiency if needed, or just loop.
			// Simple implementation:
			while(remove(e));
		}
	}

	vector<E> v;

	bool operator==(const ArrayList<E>& rhs) const;
	bool operator!=(const ArrayList<E>& rhs) const;


	template <typename Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & BOOST_SERIALIZATION_NVP(v);
	}


};

//BOOST_CLASS_VERSION(template <typename E> ArrayList<E>, 1)
//BOOST_CLASS_TRACKING(ArrayList, boost::serialization::track_never)


template <typename E>
Logger ArrayList<E>::log = Logger("ArrayList");

template <typename E>
bool ArrayList<E>::operator==(const ArrayList<E>& rhs) const
{
	return this->v == rhs.v;
}

template <typename E>
bool ArrayList<E>::operator!=(const ArrayList<E>& rhs) const
{
	return !(*this == rhs);
}
