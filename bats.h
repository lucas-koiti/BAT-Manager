//
// Created by ferragut on 28/09/2019.
//
#ifndef EXP1_STRUCTS_H
#include <ctype.h>
#include "queue.h"
#include <unistd.h>

typedef enum  possible_directions{
    NORTH = 1,
    SOUTH,
    EAST,
    WEST
} Directions;

typedef struct batStruct{
    Directions dir;
    int car_number;
}BAT;

// Functions Prototype
BAT* new_car(int number, Directions dir);
void car_exit(BAT* current_car);
char enum_to_chr(Directions dir);
char chr_to_enum(char dir);


// Functions that creates a new car
BAT* new_car(int number, Directions dir){
    BAT* car = malloc(sizeof(BAT));
    car->dir = dir;
    car->car_number = number;
    return car;
}

// Function that triggers everytime a car exits
void car_exit(BAT* current_car){
    printf("BAT %d %c saiu do cruzamento\n", current_car->car_number, enum_to_chr(current_car->dir));
    switch (current_car->dir){
        case NORTH:
            pop(priority_queue[0]);
            break;
        case EAST:
            pop(priority_queue[1]);
            break;
        case SOUTH:
            pop(priority_queue[2]);
            break;
        case WEST:
            pop(priority_queue[3]);
            break;
    }
}

// Function that triggers everytime a car crosses
void cross(BAT* current_car){
    pthread_mutex_lock(&mutex);
    sleep(1);
    car_exit(current_car);
    pthread_mutex_unlock(&mutex);
}

// Transforms a enum Directions to a char
char enum_to_chr(Directions dir){
    char chr_dir;
    switch (dir){
        case NORTH:
            chr_dir = 'N';
            break;
        case EAST:
            chr_dir = 'E';
            break;
        case SOUTH:
            chr_dir = 'S';
            break;
        case WEST:
            chr_dir = 'W';
            break;
    }
    return chr_dir;
}

// Transforms a char to a Direction Enum
char chr_to_enum(char dir){
    Directions enum_dir;
    dir = toupper(dir);
    switch (dir){
        case 'N':
            enum_dir = NORTH;
            break;
        case 'E':
            enum_dir = EAST;
            break;
        case 'S':
            enum_dir = SOUTH;
            break;
        case 'W':
            enum_dir = WEST;
            break;
    }
    return enum_dir;
}

int int_to_enum(int dir){
    Directions enum_dir;
    switch (dir){
        case 1:
            enum_dir = NORTH;
            break;
        case 'E':
            enum_dir = EAST;
            break;
        case 'S':
            enum_dir = SOUTH;
            break;
        case 'W':
            enum_dir = WEST;
            break;
    }
    return enum_dir;
}

#define EXP1_STRUCTS_H

#endif //EXP1_STRUCTS_H
