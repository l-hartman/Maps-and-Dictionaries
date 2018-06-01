#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdexcept>
#include <string>


// Define an exception type that can be thrown by dictionary implementations
class DictionaryException: public std::runtime_error {
public:
    DictionaryException(std::string msg=""): runtime_error(msg) {}
};

// Key-value dictionary abstract class
template<class K, class V>
class Dictionary {
    public:
        // Virtual destructor
        virtual ~Dictionary() { }

        // Add a given key, value pair to the dictionary.  If key is already
        // a key in the dictionary, REPLACE the associated value.
        virtual void add(K key, V value) = 0;

        // Return the value associated with the given key.  If the key doesn't
        // exist, throws an exception of class DictionaryException
        virtual V getValue(K key) const = 0;

        // Return the key associated with the given value.  In the case where
        // multiple values are equal to the passed-in value, returning any
        // associated key is correct.  If no values are equal to value,
        // throws an exception of class DictionaryException.
        virtual K getKey(V value) const = 0;

        // Remove the given key and associated value from the dictionary.  In
        // the case where key doesn't exist, this function throws an exception
        // of class DictionaryException.
        virtual void remove(K key) = 0;

        // Display the dictionary on standard output, indicating what keys are
        // associated with what values.  The order of keys can be in any order.
        virtual void display() const = 0;

        // Return the number of key-value pairs in this dictionary.
        virtual int size() const = 0;

        // Returns true if the key exists and false otherwise.
        virtual bool keyExists(K key) const = 0;
};

#endif