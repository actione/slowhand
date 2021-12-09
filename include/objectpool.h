#pragma once
#include <list>

/*
user keys:
    const int size = 1024
    Pool<Object> pool(size);
    Object a = pool.Get();  // get a object;
    pool.free(a);    // recycle a object
*/

template<typename T>
class Pool
{
public:

public:
    Pool(int size)
    {
        T* objects = new T[size];
        for (int i = 0; i < size; i++)
        {
            m_ptrFreeNode.push_back(objects[i]);
        }
    }

    ~Pool()
    {
        for (auto ptrItem : m_ptrFreeNode)
        {
            delete ptrItem;
            ptrItem = nullptr;
        }

        for (auto ptrItem : m_ptrUsedNode)
        {
            delete ptrItem;
            ptrItem = nullptr;
        }
    }

    T* Get()
    {
        if (m_ptrFreeNode.size() == 0)
        {
            return nullptr;  // error. how to deal with it?
        }

        auto ptrObject = m_ptrFreeNode.pop_back();
        m_ptrUsedNode.push_back(ptrObject);

        return ptrObject;
    }

    int Free(T* object)
    {
        m_ptrFreeNode.push_front(object);
        m_ptrUsedNode.remove(object);

        return 0;
    }

private:

   std::list<T*> m_ptrFreeNode;
   std::list<T*> m_ptrUsedNode;
};