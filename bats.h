//
// Created by ferragut on 28/09/2019.
//
#include "queue.h"

#ifndef EXP1_STRUCTS_H

typedef enum  possible_directions{
    NORTH = 1,
    SOUTH,
    EAST,
    WEST
} Directions;

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
