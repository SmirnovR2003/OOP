#include "CBody.h"
#include <sstream>
#include <iomanip>
using namespace std;

CBody::CBody(const string& type)
	: m_type(type)
{
}

string CBody::GetType()
{
	return m_type;
}

double CBody::GetMass()const
{
	return GetVolume() * GetDensity();
}

std::string CBody::ToString(int recursionDepth)const
{
	ostringstream strm{};
	for (int i = 0; i < recursionDepth; i++)
	{
		strm << "\t";
	}
	strm << m_type << ":" << endl << setprecision(10);

	for (int i = 0; i < recursionDepth; i++)
	{
		strm << "\t";
	}
	strm << "\tdensity = " << GetDensity() << endl;

	for (int i = 0; i < recursionDepth; i++)
	{
		strm << "\t";
	}
	strm << "\tvolume = " << GetVolume() << endl;

	for (int i = 0; i < recursionDepth; i++)
	{
		strm << "\t";
	}
	strm << "\tmass = " << GetMass() << endl;

	AppendProperties(strm, recursionDepth + 1);
	return strm.str();
}
