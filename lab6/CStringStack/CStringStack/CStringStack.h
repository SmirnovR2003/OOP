#pragma once

#include <string>

struct MyItem
{
	std::string value;
	MyItem* next;
};

class CStringStack
{
public:
	CStringStack();

	~CStringStack()noexcept;

	CStringStack(const CStringStack& other);

	CStringStack(CStringStack&& other)noexcept;

	void Push(const std::string& str);

	std::string Top()const;

	void Pop();

	size_t Size()const;

	CStringStack& operator=(const CStringStack& other);

	CStringStack& operator=(CStringStack&& other)noexcept;

private:

	MyItem* m_top = nullptr;

	size_t m_size = 0;

	void DeleteStack(CStringStack& other);

	void CopyStack(const CStringStack& source);
};

