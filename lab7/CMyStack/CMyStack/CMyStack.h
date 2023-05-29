#pragma once

constexpr size_t MAX_STACK_SIZE = std::numeric_limits<size_t>::max();

template<typename T>
class CMyStack
{
public:
    CMyStack()
    {
    }

    ~CMyStack() noexcept
    {
        Clear();
    }

    CMyStack(const CMyStack<T>& other)
    {
        if (!other.m_top)
        {
            return;
        }

        CMyStack tempStack;

        MyItem* tempOtherItem = other.m_top;
        tempStack.m_top = new MyItem(*tempOtherItem);
        MyItem* tempItem = tempStack.m_top;

        while (tempOtherItem->next)
        {
            tempOtherItem = tempOtherItem->next;
            tempItem->next = new MyItem(*tempOtherItem);
            tempItem = tempItem->next;
            ++m_size;
        }

        std::swap(m_top, tempStack.m_top);
        std::swap(m_size, tempStack.m_size);
    }

    CMyStack(CMyStack<T>&& other)noexcept
        :m_top(other.m_top)
        , m_size(other.m_size)
    {
        other.m_top = nullptr;
        other.m_size = 0;
    }

    void Push(const T& el)
    {
        if (MAX_STACK_SIZE == m_size)
        {
            throw std::runtime_error("stack already has max size");
        }

        MyItem* tempItem = new MyItem({ el, m_top });
        m_top = tempItem;
        ++m_size;
    }

    T Top()const
    {
        if (!m_top)
        {
            throw std::runtime_error("stack is empty");
        }

        return m_top->value;
    }

    void Pop()
    {
        if (!m_top)
        {
            throw std::runtime_error("stack is empty");
        }

        MyItem* tempItem = m_top;
        m_top = m_top->next;
        delete tempItem;
    }

    size_t Size()const
    {
        return m_size;
    }

    void Clear()
    {
        if (m_top)
        {
            while (m_top->next)
            {
                MyItem* tempItem = m_top;
                m_top = m_top->next;
                delete tempItem;
            }
            delete m_top;
        }
        m_top = nullptr;
        m_size = 0;
    }
    
    bool Empty() const
    {
        return m_size == 0;
    }

    CMyStack<T>& operator=(const CMyStack<T>& other)
    {
        if (this == &other) return *this;

        CMyStack tempStack(other);

        std::swap(m_top, tempStack.m_top);
        std::swap(m_size, tempStack.m_size);

        return *this;
    }

    CMyStack<T>& operator=(CMyStack<T>&& other)noexcept
    {
        if (this == &other) return *this;

        CMyStack tempStack(std::move(other));

        std::swap(m_top, tempStack.m_top);
        std::swap(m_size, tempStack.m_size);

        return *this;
    }

private:

    struct MyItem
    {
        T value;
        MyItem* next;
    };

    MyItem* m_top = nullptr;

    size_t m_size = 0;
};


