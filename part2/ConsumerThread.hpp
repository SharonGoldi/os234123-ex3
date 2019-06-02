//
// Created by sharo on 6/1/2019.
//

#ifndef OS234123_EX3_CONSUMERTHREAD_H
#define OS234123_EX3_CONSUMERTHREAD_H

#include "Thread.hpp"

class ConsumerThread : public Thread {
protected:
    void thread_workload();
};


#endif //OS234123_EX3_CONSUMERTHREAD_H
