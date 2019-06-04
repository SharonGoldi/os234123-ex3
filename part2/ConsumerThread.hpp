//
// Created by sharo on 6/1/2019.
//

#ifndef OS234123_EX3_CONSUMERTHREAD_H
#define OS234123_EX3_CONSUMERTHREAD_H

#include "Thread.hpp"
#include "tiles.hpp"
#include "PCQueue.hpp"


class ConsumerThread : public Thread {
private:
    PCQueue<tile_job>* jobs_queue;
    vector<tile_record>* m_tile_hist;
    pthread_mutex_t* lock;
    uint* done_thread_counter;

protected:
    void thread_workload();
    int calc_live_neighbors(int row, int col, bool_mat* curr_field, uint field_height, uint field_width);

public:
    ConsumerThread(uint thread_id, PCQueue<tile_job>* jobs_queue, vector<tile_record>* m_tile_hist, pthread_mutex_t* lock, uint* done_thread_counter);
    ~ConsumerThread() = default;
};


#endif //OS234123_EX3_CONSUMERTHREAD_H
