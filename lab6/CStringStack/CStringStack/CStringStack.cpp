#include "CStringStack.h"
#include <stdexcept>
#include <numeric>

const size_t MAX_STACK_SIZE = std::numeric_limits<size_t>::max();

CStringStack::CStringStack()
{
}

CStringStack::~CStringStack() noexcept
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

CStringStack::CStringStack(const CStringStack& other)
{
    if (!other.m_top)
    {
        return;
    }

    if (!source.m_top)
    {
        m_top = nullptr;
        m_size = 0;
        return;
    }

    CStringStack tempStack;

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

CStringStack::CStringStack(CStringStack&& other)noexcept
    :m_top(other.m_top)
    ,m_size(other.m_size)
{
    other.m_top = nullptr;
    other.m_size = 0;
}

void CStringStack::Push(const std::string& str)
{
    if (MAX_STACK_SIZE == m_size)
    {
        throw std::runtime_error("stack already had max size");
    }
    
    MyItem* tempItem = new MyItem({ str, m_top });
    m_top = tempItem;
    ++m_size;
}

std::string CStringStack::Top()const
{
    if (!m_top)
    {
        throw std::runtime_error("stack is empty");
    }

    return m_top->value;
}

void CStringStack::Pop()
{
    if (!m_top)
    {
        throw std::runtime_error("stack is empty");
    }

    MyItem* tempItem = m_top;
    m_top = m_top->next;
    delete tempItem;
}

size_t CStringStack::Size()const
{
    return m_size;
}

CStringStack& CStringStack::operator=(const CStringStack& other)
{
    if (this == &other) return *this;

    CStringStack tempStack(other);

    std::swap(m_top, tempStack.m_top);
    std::swap(m_size, tempStack.m_size);

    return *this;
}

CStringStack& CStringStack::operator=(CStringStack&& other)noexcept
{
    if (this == &other) return *this;

    CStringStack tempStack(std::move(other));

    std::swap(m_top, tempStack.m_top);
    std::swap(m_size, tempStack.m_size);

    return *this;
}