#ifndef HECATE_BAG_H
#define HECATE_BAG_H
#include <cstdlib>
#include <cstring>
#include <stdexcept>

namespace hecate {

typedef unsigned int size_type;

template<class T>
class Bag {
public:
	Bag() {
		init(16);
	}

	Bag(size_type capacity) {
		init(capacity);
	}

	~Bag() {
	}

	T erase(size_type index) {
		if(index > bag_size)
			throw std::out_of_range();
	}

	bool erase(T o) {
		for (int i = 0; i < bag_size; i++) {
			T o1 = data[i];

			if (o == o1) {
				data[i] = data[--bag_size]; // overwrite item to remove with last
				// element
				data[bag_size] = NULL; // null last element, so gc can do its work
				return true;
			}
		}

		return false;
	}

	bool erase(Bag<T> bag) {
	}

	T eraseLast() {
		if(bag_size > 0) {
			T o = data[--bag_size];
			data[bag_size] = NULL;
			return o;
		}

		return NULL;

	}

	T &at(size_type index) {
		if(index > bag_size)
			throw std::out_of_range("index out of range");
		return data[index];
	}

	const T &at(size_type index) const {
		if(index > bag_size)
			throw std::out_of_range("index out of range");
		return data[index];
	}

	T &operator[](size_type index) {
		if(index > bag_size)
			throw std::out_of_range("index out of range");
		return data[index];
	}

	const T &operator[](size_type index) const {
		if(index > bag_size)
			throw std::out_of_range("index out of range");
		return data[index];
	}

	bool contains(T o) {
		for(int i = 0; bag_size > i; i++) {
			if(o == data[i]) {
				return true;
			}
		}

		return false;
	}

	size_type size() {
		return bag_size;
	}

	size_type capacity() {
		return bag_capacity;
	}

	bool empty() {
		return bag_size == 0;
	}

	void add(T o) {
		if(bag_size == bag_capacity) {
			grow();
		}

		data[bag_size++] = o;
	}

	void add(const Bag<T> &items) {
		for(int i = 0; items.size() > i; i++) {
			add(items.at(i));
		}
	}

	void set(size_type index, T o) {
		if(index >= bag_capacity) {
			grow(index*2);
		}

		data[index] = o;
		bag_size = index+1;
	}

	void clear() {
		memset(data, 0, sizeof(T) * bag_capacity);

		bag_size = 0;
	}

private:
	void grow() {
		grow((bag_capacity*3)/2+1);
	}

	void grow(int newCapacity) {
		T *old_data = data;
		data = new T[newCapacity];
		memcpy(data, old_data, bag_capacity);
		bag_capacity = newCapacity;
		delete [] old_data;
	}

	void init(size_type capacity) {
		bag_size = 0;
		bag_capacity = capacity;
		data = new T[capacity];
	}

	size_type bag_size;
	size_type bag_capacity;
	T *data;
};

}

#endif
