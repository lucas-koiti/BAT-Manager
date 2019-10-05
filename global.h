//
// Created by ferragut on 05/10/2019.
//

#ifndef EXP1_GLOBAL_H

// Global variables
pthread_mutex_t mutex;
pthread_cond_t cond_array[5];
pthread_t dir_array[4];
int bit_mask[4];

int total_car_number = 0;
int done = 0;

#define EXP1_GLOBAL_H

#endif //EXP1_GLOBAL_H
