#pragma once

#include <QQueue>
#include <QMutex>

template<typename T>
class threadSafeQueue
{

public:
    threadSafeQueue();
    ~threadSafeQueue();
    int size();
    bool empty();
    void clear();
    T front();
    T pop();
    void push(T value);

private:
    QMutex mutex;
    QQueue<T>* queue;

};

