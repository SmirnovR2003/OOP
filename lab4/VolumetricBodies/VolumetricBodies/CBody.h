#pragma once
#include <string>
#include <iostream>
#include <vector>
class CBody
{
public:

	CBody(const std::string& type);

	virtual double GetDensity() const = 0;

	virtual double GetVolume() const = 0;

	virtual double GetMass() const;

	std::string ToString(int recursionDepth = 0) const;

	std::string GetType();

protected:


private:

	virtual void AppendProperties(std::ostream& strm, int recursionDepth) const = 0;

	std::string m_type;
};

