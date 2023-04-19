#include "CCone.h"

using namespace std;

const double M_PI = 3.14;

CCone::CCone(double baseRadius, double height, double density)
: CSolidBody::CSolidBody("Cone", density)
, m_height((height >= 0.0) ? height : 0.0)
, m_baseRadius((baseRadius >= 0.0) ? baseRadius : 0.0)
{
}

double CCone::GetBaseRadius() const
{
    return m_baseRadius;
}

double CCone::GetHeight() const
{
    return m_height;
}


double CCone::GetVolume() const
{
    return M_PI * pow(m_baseRadius, 2) * m_height / 3;
}

void CCone::AppendProperties(ostream& strm, int recursionDepth) const
{
    for (int i = 0; i < recursionDepth-1; i++)
    {
        strm << "\t";
    }
    strm << "\tbase radius = " << GetBaseRadius() << endl;
    for (int i = 0; i < recursionDepth-1; i++)
    {
        strm << "\t";
    }
    strm << "\theight = " << GetHeight() << endl;
}
