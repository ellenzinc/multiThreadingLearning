#include <thread>
#include <iostream>

using namespace std;


class myFunctor {
public:
    void operator()(){
        cout << "This is my function object" << endl;
    }
    void publicFunction() {
        cout << "public function of myFunctor class is called" << endl;
    }
};

void threadFunc() {
    cout << "Welcomm to multithreading" << endl;
}

int main() {
    thread funcTest1(threadFunc);
    funcTest1.detach(); // this function detach a thread from the parent thread
    if (funcTest1.joinable()) {
        // main is blocked until funcTest1 is finished.
        funcTest1.join();
    } else {
        cout << "funcTest1 is detached" << endl;
    }

    myFunctor myFunc;
    thread functorTest(myFunc);
    if (functorTest.joinable())
        functorTest.join();

    thread publicFunctionTest(&myFunctor::publicFunction, myFunc);
    if (publicFunctionTest.joinable())
        publicFunctionTest.join();
    return 0;
}
