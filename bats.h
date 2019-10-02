//
// Created by ferragut on 28/09/2019.
//
#include "queue.h"

#ifndef EXP1_STRUCTS_H

//typedef enum  possible_directions{
//    NORTH = 'n',
//    SOUTH = 's',
//    EAST = 'e',
//    WEST = 'w'
//} Directions;

typedef struct BATStruct{
    char direction;
    int car_number;
    pthread_t* thread_id;
} BAT ;


BAT* new_BAT(char direction, int car_number, pthread_t* thread_id){
    BAT* new_car_BAT = malloc(sizeof(BAT));
    new_car_BAT->direction = direction;
    new_car_BAT->car_number = car_number;
    new_car_BAT->thread_id = thread_id;
    return new_car_BAT;
}
#define EXP1_STRUCTS_H

#endif //EXP1_STRUCTS_H
