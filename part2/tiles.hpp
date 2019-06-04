//
// Created by sharo on 6/4/2019.
//

#ifndef OS234123_EX3_TILES_H
#define OS234123_EX3_TILES_H

#include "Headers.hpp"

struct tile_record {
    double tile_compute_time; // Compute time for the tile
    uint thread_id; // The thread responsible for the compute
};

struct tile_job {
    bool_mat* curr_field;
    bool_mat* next_field;

    uint start_row;
    uint end_row;

    uint field_height;
    uint field_width;

    bool is_end_of_game;
};

#endif //OS234123_EX3_TILES_H
