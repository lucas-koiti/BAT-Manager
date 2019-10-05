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
void arrive(Directions dir);
void car_exit(BAT* current_car);
char enum_to_chr(Directions dir);
char chr_to_enum(char dir);


// Functions down below
BAT* new_car(int number, Directions dir){
    BAT* car = malloc(sizeof(BAT));
    car->dir = dir;
    car->car_number = number + 1;
    return car;
}

void arrive(Directions dir){
    BAT* current_car = new_car(total_car_number, dir);
    total_car_number++;
    printf("BAT %d %c chegou no cruzamento\n", current_car->car_number, enum_to_chr(current_car->dir));
    switch (current_car->dir){
        case NORTH:
            push(priority_queue[0], current_car);
            break;
        case EAST:
            push(priority_queue[1], current_car);
            break;
        case SOUTH:
            push(priority_queue[2], current_car);
            break;
        case WEST:
            push(priority_queue[3], current_car);
            break;
    }
}

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

void cross(BAT* current_car){
    pthread_mutex_lock(&mutex);
    sleep(1);
    car_exit(current_car);
    pthread_mutex_unlock(&mutex);
}

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

#define EXP1_STRUCTS_H

#endif //EXP1_STRUCTS_H
