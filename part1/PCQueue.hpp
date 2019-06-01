#ifndef _QUEUEL_H
#define _QUEUEL_H
#include "Headers.hpp"
#include "Semaphore.hpp"
// Single Producer - Multiple Consumer queue
template <typename T>class PCQueue
{

public:

    PCQueue();
    ~PCQueue();

	// Blocks while queue is empty. When queue holds items, allows for a single
	// thread to enter and remove an item from the front of the queue and return it. 
	// Assumes multiple consumers.
	T pop(); 

	// Allows for producer to enter with *minimal delay* and push items to back of the queue.
	// Hint for *minimal delay* - Allow the consumers to delay the producer as little as possible.  
	// Assumes single producer 
	void push(const T& item);

private:
	// Add your class memebers here
	std::queue<T> q;
    pthread_mutex_t consumers_lock;
    Semaphore avail_items;
};
// Recommendation: Use the implementation of the std::queue for this exercise


template <typename T>
PCQueue<T>::PCQueue() {
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK);

    pthread_mutex_t error_check_mutex;
    pthread_mutex_init(&error_check_mutex, &attr);
    this->consumers_lock = error_check_mutex;

    pthread_mutexattr_destroy(&attr);

    this->avail_items = new Semaphore();
}

template <typename T>
PCQueue<T>::~PCQueue() {
    pthread_mutex_destroy(this->consumers_lock);
    delete this->avail_items;
}

template <typename T>
T PCQueue<T>::pop() {
    avail_items.down();
    pthread_mutex_lock(&this->consumers_lock);
    T temp = q.front();
    q.pop();
    pthread_mutex_unlock(&this->consumers_lock);

    return temp;
}

template <typename T>
void PCQueue<T>::push(const T& item) {
    q.push(item);
    avail_items.up();
}

// TODO: maybe needs some more changes. push_all? delating the producer?

#endif