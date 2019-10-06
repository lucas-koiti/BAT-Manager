//
// Created by ferragut on 05/10/2019.
//

#ifndef EXP1_GLOBAL_H

// Global variables
pthread_mutex_t mutex;
pthread_cond_t cond_array[5];
pthread_cond_t batman, north_queue, east_queue, south_queue, west_queue;
pthread_t dir_array[4];
pthread_attr_t attr;


int car_crossed = 0;
int should_cross[4] = {0,0,0,0};
int bit_mask[4];
int total_car_number = 0;
int done = 0;
int starved = 0;
int K = 2;

#define EXP1_GLOBAL_H

#endif //EXP1_GLOBAL_H
