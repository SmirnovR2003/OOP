#include "CParallelepiped.h"

CParallelepiped::CParallelepiped(double height, double width, double depth, double density)
: CSolidBody::CSolidBody("Parallelepiped", density)
, m_height((height >= 0.0) ? height : 0.0)
, m_width((width >= 0.0) ? width : 0.0)
, m_depth((depth >= 0.0) ? depth : 0.0)
{
}

double CParallelepiped::GetHeight() const
{
    return m_height;
}

double CParallelepiped::GetWidth() const
{
    return m_width;
}

double CParallelepiped::GetDepth() const
{
    return m_depth;
}

double CParallelepiped::GetVolume() const
{
    return m_height * m_width * m_depth;
}

void CParallelepiped::AppendProperties(std::ostream& strm, int recursionDepth) const
{
    for (int i = 0; i < recursionDepth-1; i++)
    {
        strm << "\t";
    }
    strm << "\theight = " << GetHeight() << std::endl;
    for (int i = 0; i < recursionDepth-1; i++)
    {
        strm << "\t";
    }
    strm << "\twidth = " << GetWidth() << std::endl;
    for (int i = 0; i < recursionDepth-1; i++)
    {
        strm << "\t";
    }
    strm << "\tdepth = " << GetDepth() << std::endl;
}