//
// Created by sharo on 6/1/2019.
//

#ifndef OS234123_EX3_GAMETHREAD_H
#define OS234123_EX3_GAMETHREAD_H

#include "Thread.hpp"

class GameThread : Thread {
protected:
    void thread_workload();
};


#endif //OS234123_EX3_GAMETHREAD_H
