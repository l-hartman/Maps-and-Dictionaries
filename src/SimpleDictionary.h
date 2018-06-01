#ifndef SIMPLEDICTIONARY_H
#define SIMPLEDICTIONARY_H

#include <iostream>
#include <cassert>

#include "Dictionary.h"

using namespace std;

// Implementation of the Dictionary class, backed by an unsorted array with
// a given maximum size.  Most operations are O(n)
template<class K, class V>
class SimpleDictionary: public Dictionary<K,V> {
    public:
        // Create a dictionary with a given maximum number of elements
        SimpleDictionary(int num = 1000) {
            keys = new K[num];
            values = new V[num];
            maxSize = num;
            count = 0;
        }

        // Simple destructor
        ~SimpleDictionary() {
            delete[] keys;
            keys = nullptr;
            delete[] values;
            values = nullptr;
        }

        // Copy constructor
        SimpleDictionary(const SimpleDictionary &other) {
            maxSize = other.maxSize;
            count = other.count;
            keys = new K[maxSize];
            values = new V[maxSize];
            for (int i=0; i<count; i++) {
                keys[i] = other.keys[i];
                values[i] = other.values[i];
            }
        }

        SimpleDictionary& operator=(const SimpleDictionary &other) {
            // Check to avoid self-assignment
            if (this == &other) {
                return *this;
            }
            
            // Perform destructor operations
            delete[] keys;
            keys = nullptr;
            delete[] values;
            values = nullptr;

            // Perform copy constructor operations
            maxSize = other.maxSize;
            count = other.count;
            keys = new K[maxSize];
            values = new V[maxSize];
            for (int i=0; i<count; i++) {
                keys[i] = other.keys[i];
                values[i] = other.values[i];
            }

            // Return reference to this
            return *this;
        }

        // Add elements to the dictionary, adding to the end of the array
        void add(K key, V value) override {
            // Check to make sure there is room to add elements
            if (count >= maxSize) {
                throw DictionaryException("Dictionary full; can't add item");
            }
            for (int i=0; i<count; i++) {
                if (keys[i] == key) {
                    values[i] = value;
                    return;
                }
            }
            keys[count] = key;
            values[count] = value;
            count++;
        }

        // Return the value associated with the given key.  If the key is not
        // found, throws an exception
        V getValue(K key) const override {
            for (int i=0; i<count; i++) {
                if (keys[i] == key) {
                    return values[i];
                }
            }
            throw DictionaryException("Key doesn't exist");
        }

        // Return a key associated with the given value.  If no keys have value
        // associated with them, throws an exception
        K getKey(V value) const override {
            for (int i=0; i<count; i++) {
                if (values[i] == value) {
                    return keys[i];
                }
            }
            throw DictionaryException("Value doesn't exist");
        }

        // Returns true if the key exists, and false otherwise
        bool keyExists(K key) const override {
            for (int i=0; i<count; i++) {
                if (keys[i] == key) {
                    return true;
                }
            }
            return false;
        }

        // Removes a key/value pair from the dictionary.  If key can't be found,
        // an exception is thrown.
        void remove(K key) override {
            // find the index of the key
            for (int i=0; i<count; i++) {
                if (keys[i] == key) {
                    keys[i] = keys[count - 1];
                    values[i] = values[count - 1];
                    count--;
                    return;
                }
            }
            throw DictionaryException("Unable to remove element");
        }

        // Displays the dictionary on standard output
        void display() const override {
            cout << "Dictionary: ";
            for (int i=0; i<count; i++) {
                cout << keys[i] << "->" << values[i];
                if (i != count-1) {
                    cout << ", ";
                } 
            }
            cout << endl;
        }

        // Returns the number of elements in the dictionary
        int size() const override {
            return count;
        }

        K keyAtIndex(int index) const {
            return keys[index];
        }

    private:
        // Array of keys
        K *keys;

        // Array of values.  Index i in keys corresponds to index i in values
        V *values;

        // Maximum number of elements that can be stored in the dictionary
        int maxSize;

        // Number of elements currently stored in the dictionary
        int count;
};

#endif