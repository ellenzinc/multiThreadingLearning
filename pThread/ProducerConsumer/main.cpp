#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "Thread.h"
#include "wqueue.h"

using namespace std;

class WorkItem {
public:
    WorkItem(const char* message, int number)
        : m_message(message), m_number(number) {}
    ~WorkItem() {}

    const char* getMessage() {
        return m_message.c_str();
    }
    int getNumber() {
        return m_number;
    }

private:
    string m_message;
    int m_number;
};


class ConsumerThread: public Thread {
public:
    ConsumerThread(wqueue<WorkItem*>& queue): m_queue(queue) {}

    void* run() {
        for (int i = 0;; i++) {
            printf("thread %lu, loop %d = waiting for item...\n",
                   (long unsigned int)self(), i);
            WorkItem *item = (WorkItem*)m_queue.remove();
            printf("thread %lu, loop %d - got one item \n",
                   (long unsigned int)self(), i);
            printf("thread %lu, loop %d - item: message - %s, number - %d\n", 
                   (long unsigned int)self(), i, item->getMessage(), 
                   item->getNumber());
            delete item;
        }
        return NULL;
    }
private:
    wqueue<WorkItem*> &m_queue;
};

int main(int argc, char** argv) {
    if ( argc != 2) {
        printf("usage: %s <iterations>\n", argv[0]);
        exit(-1);
    }
    
    int iterations = atoi(argv[1]);

    wqueue<WorkItem*> queue;
    ConsumerThread* thread1 = new ConsumerThread(queue);
    ConsumerThread* thread2 = new ConsumerThread(queue);
    thread1->start();
    thread2->start();
    
    WorkItem *item;
    for (int i = 0; i < iterations; i++) {
        item = new WorkItem("abc", 123);
        queue.add(item);
        item = new WorkItem("def", 456);
        queue.add(item);
        item = new WorkItem("ghi", 789);
        queue.add(item);
        sleep(1);
    }
    
    //sleep(1);
    //printf("Enter Ctrl-C to end the program...\n");
    while(queue.size()> 0);
    printf("done\n");
    return 0;
}
