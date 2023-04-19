#pragma once
#include "CSolidBody.h"
class CCone :
    public CSolidBody
{
public:

    CCone(double baseRadius, double height, double density);

    double GetBaseRadius() const;

    double GetHeight() const;

    double GetVolume() const override;

private:

    void AppendProperties(std::ostream& strm, int recursionDepth) const override;

    double m_baseRadius = 0.0;

    double m_height = 0.0;
};

