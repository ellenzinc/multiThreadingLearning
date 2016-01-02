#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

mutex mtx;
condition_variable cv; //condition variable for critical section
bool ready = false;
int current = 0;


void print_num(int num, int max) {
    unique_lock<mutex> lck(mtx);
    while(num != current || !ready) { cv.wait(lck); }
    current = (current+1) % max;
    cout << "Thread: ";
    cout << num+1 << "/" << max;
    cout << " current count i: ";
    cout << current << endl;

    cv.notify_all();
}


void run() {
    unique_lock<mutex> lck(mtx);
    ready = true;
    cv.notify_all();
}


int main() {
    int threadnum = 15;
    thread threads[15];
    
    for (int id = 0; id < threadnum; id++) {
        threads[id] = thread(print_num, id, threadnum);
    }

    cout << "\nRunning " << threadnum;
    cout << " in parallel: \n" << endl;

    run();
    
    for (int id = 0; id < threadnum; id++) {
        threads[id].join();
    }

    cout << "\n Completed semaphore example! \n";
    cout << endl;

    return 0;
}
