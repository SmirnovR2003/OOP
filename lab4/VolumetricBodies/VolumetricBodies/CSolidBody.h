#pragma once
#include "CBody.h"
class CSolidBody :
    public CBody
{
public:

    CSolidBody(const std::string& type, double density);

    double GetDensity() const override;

private:
    double m_density = 0.0;
};

