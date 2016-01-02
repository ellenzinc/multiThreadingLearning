#include <iostream>
#include <pthread.h>

const int NUM_THREADS = 5;

void *printHello(void *threadid) {
    long tid;
    tid = (long) threadid;
    printf("Hello World! it's me, thread #%ld!\n", tid);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;
    for (t = 0; t < NUM_THREADS; t++) {
        printf("In main: creating thread %ld\n", t);
        rc = pthread_create(&threads[t], NULL, printHello, (void*) t);
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }
    
    pthread_exit(NULL);
}
