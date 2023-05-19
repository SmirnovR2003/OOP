#include "CStringStack.h"
#include <stdexcept>
#include <numeric>

const size_t MAX_STACK_SIZE = std::numeric_limits<size_t>::max();

CStringStack::CStringStack()
{
}

CStringStack::~CStringStack() noexcept
{
    DeleteStack(*this);
}

CStringStack::CStringStack(const CStringStack& other)
{
    if (!other.m_top)
    {
        return;
    }

    CopyStack(other);
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

    DeleteStack(*this);

    if (!other.m_top)
    {
        return *this;
    }

    CopyStack(other);

    return *this;
}

CStringStack& CStringStack::operator=(CStringStack&& other)noexcept
{
    if (this == &other) return *this;
    std::swap(m_top, other.m_top);
    std::swap(m_size, other.m_size);

    DeleteStack(other);

    return *this;
}

void CStringStack::DeleteStack(CStringStack& other)
{
    if (other.m_top)
    {
        while (other.m_top->next)
        {
            MyItem* tempItem = other.m_top;
            other.m_top = other.m_top->next;
            delete tempItem;
        }
        delete other.m_top;
    }
    other.m_top = nullptr;
    m_size = 0;
}

void CStringStack::CopyStack(const CStringStack& source)
{
    if (!source.m_top)
    {
        m_top = nullptr;
        m_size = 0;
        return;
    }

    CStringStack backupStack;
    backupStack.m_top = m_top;
    backupStack.m_size = m_size;
    try
    {
        MyItem* tempOtherItem = source.m_top;
        m_top = new MyItem(*tempOtherItem);
        MyItem* tempItem = m_top;

        while (tempOtherItem->next)
        {
            tempOtherItem = tempOtherItem->next;
            tempItem->next = new MyItem(*tempOtherItem);
            tempItem = tempItem->next;
            ++m_size;
        }
    }
    catch (const std::bad_alloc&)
    {
        DeleteStack(*this);
        m_top = backupStack.m_top;
        m_size = backupStack.m_size;
        throw;
    }
}
