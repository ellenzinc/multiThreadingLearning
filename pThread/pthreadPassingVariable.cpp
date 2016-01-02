#include <pthread.h>
#include <iostream>

using namespace std;

const int NUM_THREADS = 8;
const char *messages1[NUM_THREADS];

struct thread_data {
    int thread_id;
    int sum;
    const char *message;
};

thread_data thread_data_array[NUM_THREADS];

void *PrintHello (void *threadarg) {
    int taskid, sum;
    const char *hello_msg;
    thread_data *my_data;
    
    sleep(1);
    my_data = (thread_data *) threadarg;
    taskid = my_data->thread_id;
    sum = my_data->sum;
    hello_msg = my_data->message;
    printf("Thread %d: %s Sum=%d\n", taskid, hello_msg, sum);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    pthread_t threads[NUM_THREADS];
    int *taskids[NUM_THREADS];
    int rc, t, sum;

    sum = 0;
    messages1[0] = "English: Hello World!";
    messages1[1] = "French: Bonjour,le monde!";
    messages1[2] = "Spanish: Hola al mundo";
    messages1[3] = "Klingon: Nuq neH!";
    messages1[4] = "German: Guten Tag, Welt!"; 
    messages1[5] = "Russian: Zdravstvytye, mir!";
    messages1[6] = "Japan: Sekai e konnichiwa!";
    messages1[7] = "Latin: Orbis, te saluto!";

    for (t = 0; t < NUM_THREADS; t++) {
        sum = sum +t;
        thread_data_array[t].thread_id = t;
        thread_data_array[t].sum = sum;
        thread_data_array[t].message = messages1[t];
        rc = pthread_create(&threads[t], NULL, PrintHello, (void*)&thread_data_array[t]);
        if (rc) {
            printf("Error: return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }
    pthread_exit(NULL);
}
