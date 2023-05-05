#include "CSolidBody.h"

CSolidBody::CSolidBody(const std::string& type, double density)
	:CBody::CBody(type)
	//использовать max
	,m_density((density >= 0.0) ? density : 0.0)
{
}


double CSolidBody::GetDensity() const
{
	return m_density;
}
