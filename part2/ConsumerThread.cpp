//
// Created by sharo on 6/1/2019.
//

#include "ConsumerThread.hpp"
#include <pthread.h>

void ConsumerThread::thread_workload() {
    // TODO: implement
    bool is_end_of_game = false;
    while (!is_end_of_game) {
        // ?

        // pop job from queue
        tile_job tj = jobs_queue->pop();
        is_end_of_game = tj.is_end_of_game;
        if (is_end_of_game) {
            return;
        }

        // start timer
        auto tile_start = std::chrono::system_clock::now();

        // execute job
        for (int i = tj.start_row; i <= tj.end_row; i++) {
            for (int j = 0; j < tj.field_width; j++) {
                int live_neighbors = calc_live_neighbors(i, j, tj.curr_field,  tj.field_height,  tj.field_width);

                (*tj.next_field)[i][j] = (live_neighbors == 3) ||
                                          (live_neighbors == 2 &&
                                           (*tj.curr_field)[i][j] == 1);
            }
        }

        // stop timer
        auto tile_end = std::chrono::system_clock::now();

        // append duration to shared tile history vector, along with the thread's id
        tile_record record;
        record.tile_compute_time = (double)std::chrono::duration_cast<std::chrono::microseconds>(tile_end - tile_start).count();
        record.thread_id = m_thread_id;

        pthread_mutex_lock(lock);
        m_tile_hist->push_back(record);
        (*done_thread_counter)++;
        pthread_mutex_unlock(lock);
    }
}

ConsumerThread::ConsumerThread(uint thread_id, PCQueue<tile_job> *jobs_queue, vector<tile_record> *m_tile_hist,
                               pthread_mutex_t *lock, uint *done_thread_counter) :
                               Thread(thread_id), jobs_queue(jobs_queue), m_tile_hist(m_tile_hist), lock(lock), done_thread_counter(done_thread_counter) {}

int ConsumerThread::calc_live_neighbors(int row, int col, bool_mat* curr_field, uint field_height, uint field_width) {

    int live_neighbors_counter = 0;

    for (int i = row - 1; i <= row + 1; i++) {
        for (int j = col - 1; j <= col +1; j++) {
            if (i >= 0 && i < field_height && j >= 0 && j < field_width) {
                live_neighbors_counter += (*curr_field)[i][j];
            }
        }
    }
    return live_neighbors_counter - (*curr_field)[row][col];
}
