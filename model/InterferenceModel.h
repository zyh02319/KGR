 #pragma once
#include <string>
#include "ModelBase.h"
class InterferenceModel : public ModelBase {
public:
    InterferenceModel();
    ~InterferenceModel();
    // 干扰机参数
    std::string name;
    double gain;
    double bandwidth;
    double power;
    // RCS参数
    double rcs[360];
    // 其他参数
    // ...
};
