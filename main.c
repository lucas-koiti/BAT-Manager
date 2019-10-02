#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "bats.h"
#include "queue.h"

pthread_mutex_t mutex_array[5];
pthread_cond_t cond_array[5];

int total_car_number = 0;


void* BAT_manager(char* arg){
    printf("[BATMAN]I am DONE!...\n");
    return NULL;

}

void initialize_thread_array(){
    pthread_mutex_t main_mutex, north_queue_mutex, east_queue_mutex, south_queue_mutex, west_queue_mutex;
    pthread_cond_t main, north_queue, east_queue, south_queue, west_queue;
    pthread_mutex_init(&main_mutex, NULL);
    pthread_mutex_init(&north_queue_mutex, NULL);
    pthread_mutex_init(&east_queue_mutex, NULL);
    pthread_mutex_init(&south_queue_mutex, NULL);
    pthread_mutex_init(&west_queue_mutex, NULL);
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
    mutex_array[0] = main_mutex;
    mutex_array[1] = north_queue_mutex;
    mutex_array[2] = east_queue_mutex;
    mutex_array[3] = south_queue_mutex;
    mutex_array[4] = west_queue_mutex;

}

int main() {
    printf("Starting program!\n");
    char    *buffer;
    size_t  n = 1024;
    buffer = malloc(n);
    initialize_thread_array();

    // While an empty line is not read, continue reading
    while(getline(&buffer, &n, stdin) != 1){
        BAT_manager(buffer);
    }
    printf("Bye Bye!\n");
    return 0;
}