#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <mutex>

using namespace std;

vector<int> vec;

mutex mtx;
void push()
{
    for (int i = 0; i < 10; ++i) {
        mtx.lock();
        cout << "Push "<< i << endl;
        vec.push_back(i);
        this_thread::sleep_for(std::chrono::milliseconds(500));
        mtx.unlock();
    }
}

void pop(){
    int count = 0;
    while (count < 10) {
        mtx.lock();
        if (!vec.empty()) {
            count++;
            int val = vec.back();
            vec.pop_back();
            cout << "Pop " << val << endl;
            this_thread::sleep_for(std::chrono::milliseconds(500));
        }    
        mtx.unlock();
     
    }
}

int main() {
    thread threadPush(push);
    thread threadPop(pop);

    if (threadPush.joinable())
        threadPush.join();

    if (threadPop.joinable())
        threadPop.join();

}
