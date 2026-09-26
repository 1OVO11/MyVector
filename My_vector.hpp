#pragma once
#include <cassert>
#include <cstddef>
#include <utility>

template <typename T> class MyVector {
private:
  T *data;
  size_t m_size;
  size_t m_capacity;

  // 销毁 [start, end) 区间内的所有对象，不释放内存
  void destroy_range(T *start, T *end) {
    for (T *p = start; p != end; ++p) {
      p->~T();
    }
  }

public:
  // 默认构造：空容器
  MyVector() : data(nullptr), m_size(0), m_capacity(0) {};

  // 析构函数：销毁所有元素，释放底层内存
  ~MyVector() {
    destroy_range(data, data + m_size);
    operator delete(data);
  }

  // 禁用拷贝构造、拷贝赋值
  MyVector(const MyVector &) = delete;
  MyVector &operator=(const MyVector &) = delete;

  // 预分配底层内存，扩容。不会缩小容量，不改变元素数量
  void reserve(size_t new_capacity) {
    if (new_capacity <= m_capacity)
      return;

    // 分配原始内存，只分配内存，不构造任何对象
    T *new_data = static_cast<T *>(operator new(new_capacity * sizeof(T)));

    // 将旧缓冲区的元素拷贝到新内存
    for (size_t i = 0; i < m_size; i++) {
      new (&new_data[i]) T(data[i]); // placement new，调用拷贝构造
    }

    // 销毁旧缓冲区中的有效对象
    destroy_range(data, data + m_size);
    operator delete(data);

    data = new_data;
    m_capacity = new_capacity;
  }

  // 在容器尾部插入元素（左值版本）
  void push_back(const T &value) {
    if (m_size >= m_capacity) {
      reserve(m_capacity == 0 ? 1 : m_capacity * 2);
    }
    new (data + m_size) T(value);
    m_size++;
  }

  // 原位构造元素，直接在容器内存上创建对象，减少拷贝开销
  template <typename... Args> void emplace_back(Args &&...args) {
    if (m_size >= m_capacity) {
      reserve(m_capacity == 0 ? 1 : m_capacity * 2);
    }
    new (data + m_size) T(std::forward<Args>(args)...);
    m_size++;
  }

  // 删除末尾元素，只调用析构，不释放容量
  void pop_back() {
    assert(m_size > 0); // 空容器禁止pop_back
    --m_size;
    data[m_size].~T();
  }

  // 获取当前存储的元素个数
  size_t size() const { return m_size; }

  // 获取底层缓冲区总容量
  size_t capacity() const { return m_capacity; }

  // 判断容器是否为空
  bool empty() const { return m_size == 0; }

  // 清空所有元素，不释放底层内存
  void clear() {
    destroy_range(data, data + m_size);
    m_size = 0;
  }

  // 下标访问，非const版本，带越界断言
  T &operator[](size_t idx) {
    assert(idx < m_size);
    return data[idx];
  }

  // 下标访问，const版本，带越界断言
  const T &operator[](size_t idx) const {
    assert(idx < m_size);
    return data[idx];
  }
};
