#include "CCylinder.h"

const double PI = 3.14;

CCylinder::CCylinder(double baseRadius, double height, double density)
: CSolidBody::CSolidBody("Cylinder", density)
, m_height((height >= 0.0) ? height : 0.0)
, m_baseRadius((baseRadius >= 0.0) ? baseRadius : 0.0)
{
}

double CCylinder::GetBaseRadius() const
{
    return m_baseRadius;
}

double CCylinder::GetHeight() const
{
    return m_height;
}

double CCylinder::GetVolume() const
{
    return PI * m_baseRadius * m_baseRadius * m_height;
}

void CCylinder::AppendProperties(std::ostream& strm, int recursionDepth) const
{
    for (int i = 0; i < recursionDepth-1; i++)
    {
        strm << "\t";
    }
    strm << "\tbase radius = " << GetBaseRadius() << std::endl;
    for (int i = 0; i < recursionDepth-1; i++)
    {
        strm << "\t";
    }
    strm << "\theight = " << GetHeight() << std::endl;
}