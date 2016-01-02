#include <thread>
#include <iostream>

using namespace std;

void showMessage() {
}

int main() {
    thread t1(showMessage);
    thread t2(showMessage);
    thread t3(showMessage);
   
    thread::id id1 = t1.get_id();
    thread::id id2 = t2.get_id();
    thread::id id3 = t3.get_id();
    
    if (t1.joinable()){
        t1.join();
        cout << "Thread with id " << id1 << " is terminated" << endl;
    }

    if (t2.joinable()){
        t2.join();
        cout << "Thread with id " << id2 << " is terminated" << endl;
    }

    if (t3.joinable()){
        t3.join();
        cout << "Thread with id " << id3 << " is terminated" << endl;
    }
    
    return 0;
}
