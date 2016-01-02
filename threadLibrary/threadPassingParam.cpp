#include <iostream>
#include <thread>

using namespace std;

void printSomeValues(int val, const char* str, double dval) {
    cout << val << " " << str << " "<< dval << " " << endl;
}

class myFunctorParam {
public:
    void operator()(int *arr, int length) {
        cout << "An array of length " << length << " is passed to thread" << endl;
        for (int i = 0; i < length; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    void changeSign(int *arr, int length) {
        cout << "An array of length " << length << " is passed to thread" << endl;
        for (int i = 0; i < length; i++) 
            cout << arr[i] << " ";
        cout << "Change sign of all elements of the initial array" << endl;
        for (int i = 0; i < length; i++) {
            arr[i] *= -1;
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    const char *str = "Hello";
    thread paramPass(printSomeValues, 5, str, 3.2);
    if (paramPass.joinable())
        paramPass.join();

    int arr[5] = {1,3,5,7,9};
    //myFunctorParam objParamPass;
    thread test(myFunctorParam(), arr, 5);
    if (test.joinable())
        test.join();

    myFunctorParam objParamPass;
    int arr2[5] = {-1, 3, 5, -7, 0};
    thread testPublic(&myFunctorParam::changeSign, &objParamPass, arr2, 5);
    if (testPublic.joinable())
        testPublic.join();
    return 0;
}
