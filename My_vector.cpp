#include "My_vector.hpp"
#include <iostream>
#include <string>
using namespace std;

int main()
{
    MyVector<string> vec;
    cout << "initial size:" << vec.size() << ", capacity:" << vec.capacity() << endl;

    vec.push_back("hello1");
    vec.emplace_back("hello2");
    vec.push_back(string("hello3"));

    cout << "after insert size:" << vec.size() << ", capacity:" << vec.capacity() << endl;
    vec.pop_back();
    cout << "after pop_back size:" << vec.size() << ", capacity:" << vec.capacity() << endl;
    return 0;
}