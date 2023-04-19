#pragma once
#include "CSolidBody.h"
class CParallelepiped :
    public CSolidBody
{
public:

    CParallelepiped(double height, double width, double depth, double density);

    double GetHeight() const;

    double GetWidth() const;

    double GetDepth() const;

    double GetVolume() const override;

private:

    void AppendProperties(std::ostream& strm, int recursionDepth) const override;

    double m_height = 0.0;

    double m_width = 0.0;

    double m_depth = 0.0;
};

