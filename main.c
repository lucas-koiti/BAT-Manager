#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "bats.h"
#include "queue.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

Queue* queue_array[4];
int total_car_number = 0;

void* BAT_behaviour(void* arg){
    BAT* car_ptr = (BAT*)arg;
    BAT car = *car_ptr;
    printf("BAT %d %c chegou no cruzamento\n", car.car_number, toupper(car.direction));
    pthread_mutex_lock(&mutex);
    printf("[BAT %d %c] I AM DOING STUFF MKAY...\n", car.car_number, toupper(car.direction));
    sleep(1);
    printf("BAT %d %c saiu no cruzamento\n", car.car_number, toupper(car.direction));
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void* BAT_manager(char* arg){
//  TODO:Criar threads de filas (4)
//  TODO:Para cada char da string, criar novo carro, \

    Queue* queueN = create_queue();
    queue_array[0] = queueN;
    Queue* queueE = create_queue();
    queue_array[1] = queueE;
    Queue* queueS = create_queue();
    queue_array[2] = queueS;
    Queue* queueW = create_queue();
    queue_array[3] = queueW;
    char* directions_string =  arg;
    char current_direction = directions_string[0];
    int car_number = 0;
    while (current_direction != '\n'){
        pthread_t* new_car_thread = malloc(sizeof(pthread_t));
        car_number++;
        total_car_number++;
        pthread_mutex_lock(&mutex);
        BAT* new_car_BAT = new_BAT(current_direction, total_car_number, new_car_thread);
        pthread_mutex_unlock(&mutex);
        pthread_create(new_car_thread, NULL, BAT_behaviour, new_car_BAT);
        current_direction = directions_string[car_number];
    }
    printf("[BATMAN]I am DONE!...\n");
    return NULL;

}

int main() {
    printf("Starting program!\n");
    char    *buffer;
    size_t  n = 1024;
    buffer = malloc(n);

    // While an empty line is not read, continue reading
    while(getline(&buffer, &n, stdin) != 1){
//        pthread_t batman;
//        pthread_create(&batman, NULL, BAT_manager, buffer);
        BAT_manager(buffer);
    }
    printf("Bye Bye!\n");
    return 0;
}