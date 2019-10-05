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
pthread_t dir_array[4];
Queue* priority_queue[4];

int total_car_number = 0;


void* queue_start(void* arg){
    Directions* dir_ptr = (Directions*) arg;
    Directions queue_dir = *dir_ptr;
    int i = 0;
    pthread_cond_signal(&cond_array[0]);
    printf("[QUEUE %c]I am going to wait for the carty cars!\n", enum_to_chr(queue_dir));
//    Waiting for permission to make carts go
    while(i != 3){
        pthread_cond_wait(&cond_array[queue_dir], &mutex_array[queue_dir]);
        i++;
        printf("[QUEUE %c] CART WENT VROOM VROOM\n", enum_to_chr(queue_dir));
        pthread_cond_signal(&cond_array[0]);
    }
    printf("[QUEUE %c]I am done! Bye Bye...\n", enum_to_chr(queue_dir));
    pthread_exit(NULL);
}

void* BAT_manager(char* dir_string){
    printf("[BATMAN]Starting BATMAN with - %s", dir_string);
    Directions dir =  NORTH;
    pthread_create(&dir_array[0], NULL, queue_start, &dir);
    pthread_cond_wait(&cond_array[0], &mutex_array[0]);
    dir = EAST;
    pthread_create(&dir_array[1], NULL, queue_start, &dir);
    pthread_cond_wait(&cond_array[0], &mutex_array[0]);
    dir = SOUTH;
    pthread_create(&dir_array[2], NULL, queue_start, &dir);
    pthread_cond_wait(&cond_array[0], &mutex_array[0]);
    dir = WEST;
    pthread_create(&dir_array[3], NULL, queue_start, &dir);
    pthread_cond_wait(&cond_array[0], &mutex_array[0]);

    printf("[BATMAN] Threads created, now carty cars!\n");
    char current_dir = dir_string[0];
    Directions enum_current_dir;
    int i = 0;
    while (current_dir != '\n'){
        enum_current_dir = chr_to_enum(current_dir);
        pthread_cond_signal(&cond_array[enum_current_dir]);
        pthread_cond_wait(&cond_array[0], &mutex_array[0]);
        i++;
        current_dir = dir_string[i];
    }
    printf("[BATMAN] MORTAL, I AM D O N E!\n");
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

    Queue* north = create_queue();
    Queue* east = create_queue();
    Queue* south = create_queue();
    Queue* west = create_queue();

    priority_queue[0] = north;
    priority_queue[1] = east;
    priority_queue[2] = south;
    priority_queue[3] = west;

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
