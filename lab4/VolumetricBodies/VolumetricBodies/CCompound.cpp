#include "CCompound.h"
CCompound::CCompound()
    : CBody::CBody("Compound")
    , m_childs{}
    //утечка памяти
    //хранить отцов
    , m_father()
{
}
//посчтитать количество деструкторов
CCompound::~CCompound()
{
}

bool CCompound::AddChildBody(const std::shared_ptr<CBody>& child)
{
    if (child.get()->GetType() == "Compound")
    {
        if (FindFather(child))
        {
            return false;
        }
        else
        {
            m_childs.push_back(child);
            m_father = child;
        }
    }
    else
    {
        m_childs.push_back(child);
    }
    return true;
}

double CCompound::GetVolume() const
{
    double volume = 0.0;

    for (auto& child : m_childs)
    {
        volume += child.get()->GetVolume();
    }
    return volume;
}

double CCompound::GetDensity() const
{
    return GetMass() / GetVolume();
}

double CCompound::GetMass() const
{
    double mass = 0.0;

    for (auto& child : m_childs)
    {
        mass += child.get()->GetMass();
    }
    return mass;

}

bool CCompound::FindFather(const std::shared_ptr<CBody>& father)
{
    if (father.get() == this)
    {
        return true;
    }
    else
    {
        if ((bool)m_father)
        {
            return dynamic_cast<CCompound*>(m_father.get())->FindFather(father);
        }
        else
        {
            return false;
        }
    }
}

void CCompound::AppendProperties(std::ostream& strm, int recursionDepth) const
{
    for (auto& child : m_childs)
    {
        strm << child.get()->ToString(recursionDepth);
    }
}

