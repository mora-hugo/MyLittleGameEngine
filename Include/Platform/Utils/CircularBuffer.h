#pragma once

#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;
template <typename T>
class CircularBuffer {
private:
    vector<T> buffer;
    int head;
    int tail;
    int capacity;

public:
    CircularBuffer(int capacity)
    {
        this->capacity = capacity;
        this->head = 0;
        this->tail = 0;
        buffer.resize(capacity);
    }

    void push_back(T element)
    {
        buffer[head] = element;
        head = (head + 1) % capacity;
        if (head == tail) {
            tail = (tail + 1) % capacity;
        }
    }

    void pop_front()
    {
        if (empty()) {
            throw out_of_range("Buffer is empty");
        }
        tail = (tail + 1) % capacity;
    }

    bool empty() const { return head == tail; }

    bool full() const
    {
        return (head + 1) % capacity == tail;
    }

    int size() const
    {
        if (head >= tail) {
            return head - tail;
        }
        return capacity - (tail - head);
    }

    //[] operator
    T& operator[](int index)
    {
        if (index >= size()) {
            throw out_of_range("Index out of range");
        }
        return buffer[(tail + index) % capacity];
    }
};
