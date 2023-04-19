#pragma once
#include "CSolidBody.h"
class CCylinder :
    public CSolidBody
{
public:

    CCylinder(double baseRadius, double height, double density);

    double GetBaseRadius() const;

    double GetHeight() const;

    double GetVolume() const override;

private:

    void AppendProperties(std::ostream& strm, int recursionDepth) const override;

    double m_baseRadius = 0.0;

    double m_height = 0.0;
};

