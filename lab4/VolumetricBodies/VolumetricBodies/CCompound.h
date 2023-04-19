#pragma once
#include "CBody.h"
#include <vector>
#include <memory>

class CCompound :
    public CBody
{
public:
    //CBody->CSolidBody->SimleBody
    CCompound();

    ~CCompound();


    bool AddChildBody(const std::shared_ptr<CBody>& child) ;
     
    double GetVolume() const override;

    double GetDensity() const override;

    double GetMass() const override;

private:

    bool FindFather(const std::shared_ptr<CBody>& father);

    void AppendProperties(std::ostream& strm, int recursionDepth) const override;

    std::vector<std::shared_ptr<CBody>> m_childs;

    std::shared_ptr<CBody> m_father;
};

