#include "My_vector.hpp"
#include <iostream>
#include <string>
using namespace std;

int main() {
  MyVector<string> vec;
  cout << "initial size:" << vec.size() << ", capacity:" << vec.capacity()
       << endl;

  vec.push_back("hello1");
  vec.emplace_back("hello2");
  vec.push_back(string("hello3"));

  cout << "after insert size:" << vec.size() << ", capacity:" << vec.capacity()
       << endl;

  // 遍历打印元素，验证下标访问
  cout << "elements: ";
  for (size_t i = 0; i < vec.size(); ++i) {
    cout << vec[i] << " ";
  }
  cout << endl;

  vec.pop_back();
  cout << "after pop_back size:" << vec.size()
       << ", capacity:" << vec.capacity() << endl;
  cout << "elements: ";
  for (size_t i = 0; i < vec.size(); ++i) {
    cout << vec[i] << " ";
  }
  cout << endl;

  // 测试clear
  vec.clear();
  cout << "after clear size:" << vec.size() << ", capacity:" << vec.capacity()
       << endl;
  cout << "empty? " << (vec.empty() ? "yes" : "no") << endl;

  return 0;
}
