#include "CSPhere.h"

using namespace std;

const double M_PI = 3.14;

CSphere::CSphere(double radius, double density)
	: CSolidBody::CSolidBody("Sphere", density)
	, m_radius((radius >= 0.0) ? radius : 0.0)
{
}

double CSphere::GetRadius()const
{
	return m_radius;
}

double CSphere::GetVolume()const
{
	return (pow(m_radius, 3) * M_PI) * 4 / 3;
}

void CSphere::AppendProperties(ostream& strm, int recursionDepth) const
{
	for (int i = 0; i < recursionDepth-1; i++)
	{
		strm << "\t";
	}
	strm << "\tradius = " << GetRadius() << endl;
}
