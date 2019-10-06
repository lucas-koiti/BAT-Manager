#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "bats.h"
#include "queue.h"
#include "global.h"

void initialize_thread_array();
void BAT_manager_init();
void* BAT_manager(char* dir_string);
void* queue_thread(void* arg);
void check_for_conflict();
void check_for_new_cars();

int main() {
    char    *buffer;
    size_t  n = 1024;
    buffer = malloc(n);
    initialize_thread_array();

    // While an empty line is not read, continue reading
    while(getline(&buffer, &n, stdin) != 1){
        BAT_manager(buffer);
    }
    return 0;
}

// Main function for the BAT manager
void* BAT_manager(char* dir_string){
    int i = 0;
//    Putting all the cars in their respective queues
    char current_dir = dir_string[0];
    BAT* current_car;
    Directions enum_current_dir;
    while(current_dir != '\n'){
        enum_current_dir = chr_to_enum(current_dir);
        current_car = new_car(++total_car_number, enum_current_dir);
        push(priority_queue[enum_current_dir-1], current_car);
        current_dir = dir_string[++i];
    }
//    Init BAT queues and vars
    BAT_manager_init();
//    BAT main loop, done is set by check_for_conflicts
    while(!done){
        check_for_new_cars();
        check_for_conflict();
    }
    return NULL;

}

/*  BATMAN function that checks for conflicts or if the process is done
 * TODO: Conflict == 1, let that one car pass
 * TODO: Conflict > 1, solve the conflict, consider starvation
 * */
void check_for_conflict(){
    pthread_mutex_lock(&mutex);

//    There is only a direct conflict if the sum of the bits is bigger than one
    int conflict = bit_mask[0] + bit_mask[1] + bit_mask[2] + bit_mask[3];

    // If there are no cars (conflict == 0), we are done
    if (conflict == 0){
        // Check if there are no more cars left to deal with
        int empty = 0;
        for(int i = 0; i<0; i++){
            empty += priority_queue[i]->size;
        }
        if (empty == 0 ){
            done = 1;
        }
    }
    // If only one car wants to pass
    else if (conflict == 1){
        for(int i = 0; i<4; i++){
            if (bit_mask[i]){
                pthread_cond_signal(&cond_array[i+1]);
            }
        }
    }
//    If there is a conflict
//    TODO: For each bit in the bitmask, try to signal the best queue
//      Wait for possible starvation (global var)
//      If no starvation, return from function (only one car pass for each conflict)
//      If there is starvation, try to find next queue
//      Worst case, signal goes to the same queue, but now it accepts (because only one pass is admitted for each queue)
    else{
    }
    pthread_mutex_unlock(&mutex);
}

// Function that is triggred everytime a car arrives
void arrive(BAT* car, int index){
    bit_mask[index] = 1;
    printf("BAT %d %c chegou no cruzamento\n", car->car_number, enum_to_chr(car->dir));
}


/*  Checks if there are any cars that want to cross
 * */
void check_for_new_cars(){
    for(int i = 0; i<4; i++){
        if(priority_queue[i]->size != 0){
            pthread_mutex_lock(&mutex);
            if (bit_mask[i] == 0){
                BAT* car = (BAT*)peek(priority_queue[i]);
                arrive(car, i);
            }
            pthread_mutex_unlock(&mutex);
        }
    }
}


/*  Function that deals with each queue's logic
 * */
void* queue_thread(void* arg){
    Directions* dir_ptr = (Directions*) arg;
    Directions queue_dir = *dir_ptr;
    Queue* queue = priority_queue[queue_dir-1];
    free(dir_ptr);
//    While this thread's queue is not empty

    while(queue->size != 0){
        BAT* current_car = (BAT*)peek(queue);
//        Waiting for permission to cross
        pthread_cond_wait(&cond_array[queue_dir], &mutex);
        cross(current_car);
    }
    pthread_exit(NULL);
}

void BAT_manager_init(){
    Directions* arg_dir;
    for(int i = 0; i<4; i++){
        bit_mask[i] = 0;
        arg_dir = malloc(sizeof(Directions));
        *arg_dir = (Directions) i+1;
        pthread_create(&dir_array[i], NULL, queue_thread, arg_dir);
    }
}

void initialize_thread_array(){
    pthread_mutex_t main_mutex;
    pthread_cond_t main, north_queue, east_queue, south_queue, west_queue;

    pthread_mutex_init(&main_mutex, NULL);
    pthread_cond_init(&main, NULL);
    pthread_cond_init(&north_queue, NULL);
    pthread_cond_init(&east_queue, NULL);
    pthread_cond_init(&south_queue, NULL);
    pthread_cond_init(&west_queue, NULL);

    cond_array[0] = main;
    cond_array[1] = north_queue;
    cond_array[2] = east_queue;
    cond_array[3] = south_queue;
    cond_array[4] = west_queue;
    mutex = main_mutex;

    Queue* north = create_queue();
    Queue* east = create_queue();
    Queue* south = create_queue();
    Queue* west = create_queue();

    priority_queue[0] = north;
    priority_queue[1] = east;
    priority_queue[2] = south;
    priority_queue[3] = west;

}
