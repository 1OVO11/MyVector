#pragma once
#include<utility>
#include <cstddef> 
using namespace std;

template<typename T>
class MyVector
{
   private:
   T* data;
   size_t m_size;
   size_t m_capacity;
   public:

   MyVector() : data(nullptr), m_size(0),m_capacity(0) {};

   ~MyVector()
   {
    delete[] data;
   }

   void reserve(size_t new_capacity)
   {
    if(new_capacity <= m_capacity)
    {
        return;
    }
    else
    {
        T* new_data = new T[new_capacity];
        for(size_t i = 0; i<m_size;i++)
        {
            new_data[i] = std::move(data[i]);
        }
        delete[] data;
        data=new_data;
        m_capacity=new_capacity;
    }

   }
   void push_back(const T& value)
    {
        if(m_size >= m_capacity)
        {
            reserve(m_capacity == 0 ? 1 : m_capacity * 2);
        }
        data[m_size] = value;
        m_size++;
        
    }

    void push_back(T&& value)
    {
        if(m_size >= m_capacity)
        {
            reserve(m_capacity == 0 ? 1 :m_capacity * 2);
        }

        data[m_size] = std::move(value);
        m_size++;

    }
    template<typename... Args>
    void emplace_back(Args&&... args)
    {
        if(m_size >= m_capacity)
        {
            reserve(m_capacity == 0 ? 1 : m_capacity * 2);
        }
        new(data + m_size) T(std::forward<Args>(args)...);
        m_size++;
    }

    void pop_back()
    {
        if(m_size > 0)
        {
            m_size--;
        }
    }

    size_t size() const
    {
        return m_size;
    }

    size_t capacity() const
    {
        return m_capacity;
    }

};