//
// Created by sharo on 6/2/2019.
//
#include "Thread.hpp"

Thread::Thread(uint thread_id) : m_thread_id(thread_id) {}

// Returns true if the thread was successfully started, false if there was an error starting the thread
// Creates the internal thread via pthread_create
bool Thread::start() {
    int output = pthread_create(&this->m_thread, nullptr, entry_func, this);
    return output == 0;
}

// Will not return until the internal thread has exited.
void Thread::join() {
    pthread_join(this->m_thread, nullptr);
}

// Returns the user identifier
uint Thread::thread_id() {
    return m_thread_id;
}

void* Thread::entry_func(void* thread) {
    ((Thread *)thread)->thread_workload();
    return nullptr;
}

