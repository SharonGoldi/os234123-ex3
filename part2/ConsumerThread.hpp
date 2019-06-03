//
// Created by sharo on 6/1/2019.
//

#ifndef OS234123_EX3_CONSUMERTHREAD_H
#define OS234123_EX3_CONSUMERTHREAD_H

#include "Thread.hpp"
#include "Game.hpp"

class ConsumerThread : public Thread {
private:
    PCQueue<tile_job*>* jobs_queue;
    vector<tile_record>* m_tile_hist;
protected:
    void thread_workload();
};


#endif //OS234123_EX3_CONSUMERTHREAD_H
