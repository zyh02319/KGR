 #pragma once
#include <string>
#include "ModelBase.h"
class TargetModel : public ModelBase {
public:
    TargetModel();
    ~TargetModel();
    // 目标参数
    std::string name;
    double rcs[360];
    // 其他参数
    // ...
};
