//#include "CMyStack.h"
//#include <stdexcept>
//#include <numeric>
//
//const size_t MAX_STACK_SIZE = std::numeric_limits<size_t>::max();
//
//template<typename T>
//CMyStack<T>::CMyStack()
//{
//}
//
//template<typename T>
//CMyStack<T>::~CMyStack() noexcept
//{
//    DeleteStack(*this);
//}
//
//template<typename T>
//CMyStack<T>::CMyStack(const CMyStack<T>& other)
//{
//    if (!other.m_top)
//    {
//        return;
//    }
//
//    CopyStack(other);
//}
//
//template<typename T>
//CMyStack<T>::CMyStack(CMyStack<T>&& other)noexcept
//    :m_top(other.m_top)
//    , m_size(other.m_size)
//{
//    other.m_top = nullptr;
//    other.m_size = 0;
//}
//
//template<typename T>
//void CMyStack<T>::Push(const T& str)
//{
//    if (MAX_STACK_SIZE == m_size)
//    {
//        throw std::runtime_error("stack already had max size");
//    }
//
//    MyItem* tempItem = new MyItem({ str, m_top });
//    m_top = tempItem;
//    ++m_size;
//}
//
//template<typename T>
//T CMyStack<T>::Top()const
//{
//    if (!m_top)
//    {
//        throw std::runtime_error("stack is empty");
//    }
//
//    return m_top->value;
//}
//
//template<typename T>
//void CMyStack<T>::Pop()
//{
//    if (!m_top)
//    {
//        throw std::runtime_error("stack is empty");
//    }
//
//    MyItem* tempItem = m_top;
//    m_top = m_top->next;
//    delete tempItem;
//}
//
//template<typename T>
//size_t CMyStack<T>::Size()const
//{
//    return m_size;
//}
//
//template<typename T>
//CMyStack<T>& CMyStack<T>::operator=(const CMyStack<T>& other)
//{
//    if (this == &other) return *this;
//
//    DeleteStack(*this);
//
//    if (!other.m_top)
//    {
//        return *this;
//    }
//
//    CopyStack(other);
//
//    return *this;
//}
//
//template<typename T>
//CMyStack<T>& CMyStack<T>::operator=(CMyStack<T>&& other)noexcept
//{
//    if (this == &other) return *this;
//    std::swap(m_top, other.m_top);
//    std::swap(m_size, other.m_size);
//
//    DeleteStack(other);
//
//    return *this;
//}
//
//template<typename T>
//void CMyStack<T>::DeleteStack(CMyStack<T>& other)
//{
//    if (other.m_top)
//    {
//        while (other.m_top->next)
//        {
//            MyItem* tempItem = other.m_top;
//            other.m_top = other.m_top->next;
//            delete tempItem;
//        }
//        delete other.m_top;
//    }
//    other.m_top = nullptr;
//    m_size = 0;
//}
//
//template<typename T>
//void CMyStack<T>::CopyStack(const CMyStack<T>& source)
//{
//    if (!source.m_top)
//    {
//        m_top = nullptr;
//        m_size = 0;
//        return;
//    }
//
//    CMyStack<T> backupStack;
//    backupStack.m_top = m_top;
//    backupStack.m_size = m_size;
//    try
//    {
//        MyItem* tempOtherItem = source.m_top;
//        m_top = new MyItem(*tempOtherItem);
//        MyItem* tempItem = m_top;
//
//        while (tempOtherItem->next)
//        {
//            tempOtherItem = tempOtherItem->next;
//            tempItem->next = new MyItem(*tempOtherItem);
//            tempItem = tempItem->next;
//            ++m_size;
//        }
//    }
//    catch (const std::bad_alloc&)
//    {
//        DeleteStack(*this);
//        m_top = backupStack.m_top;
//        m_size = backupStack.m_size;
//        throw;
//    }
//}
