//
// Created by sharo on 6/1/2019.
//

#include "ConsumerThread.hpp"

void ConsumerThread::thread_workload() {
    // TODO: implement
    while (true) {
        // ?

        // pop job from queue
        tile_job* tj = jobs_queue.pop();

        // start timer
        auto tile_start = std::chrono::system_clock::now();

        // execute job
        for (int i = tj->start_row; i <= tj->end_row; i++) {
            for (int j = 0; j < tj->field_width; j++) {
                int live_neighbors = calc_live_neighbors(i, j);

                (*tj->next_field)[i][j] = (live_neighbors == 3) ||
                                          (live_neighbors == 2 &&
                                           (*tj->curr_field)[i][j] == 1);
            }
        }

        // stop timer
        auto tile_end = std::chrono::system_clock::now();

        // append duration to shared tile history vector, along with the thread's id
        //
        tile_record record;
        record.tile_compute_time = (double)std::chrono::duration_cast<std::chrono::microseconds>(tile_end - tile_start).count();
        record.thread_id = m_thread_id;
        // TODO: add lock or whatsapp sol
        m_tile_hist->push_back(record);
    }
}
