#include "threadsafequeue.h"

template<typename T>
threadSafeQueue<T>::threadSafeQueue()
{
    queue = new QQueue<T>;
}

template<typename T>
threadSafeQueue<T>::~threadSafeQueue() {
    delete queue;
}

template<typename T>
int threadSafeQueue<T>::size() {
    return queue->size();
}

template<typename T>
void threadSafeQueue<T>::clear() {
    mutex.lock();
    queue->clear();
    mutex.unlock();
}

template<typename T>
bool threadSafeQueue<T>::empty()  {
    return queue->empty();
}

template<typename T>
T threadSafeQueue<T>::front() {
    return queue->front();
}

template<typename T>
void threadSafeQueue<T>::pop() {
    mutex.lock();
    queue->pop_front();
    mutex.unlock();
}

template<typename T>
void threadSafeQueue<T>::push(T value) {
    mutex.lock();
    queue->push_back(value);
    mutex.unlock();
}
