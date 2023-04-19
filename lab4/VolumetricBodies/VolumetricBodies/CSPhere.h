#pragma once
#include "CSolidBody.h"

class CSphere final : public CSolidBody
{
public:

	CSphere(double radius, double density);

	double GetRadius() const;

	double GetVolume() const override;

private:

	void AppendProperties(std::ostream& strm, int recursionDepth) const override;

	double m_radius;
};

