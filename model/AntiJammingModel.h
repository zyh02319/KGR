 #pragma once
#include <string>
#include "ModelBase.h"
class AntiJammingModel : public ModelBase {
public:
    AntiJammingModel();
    ~AntiJammingModel();
    // 抗干扰参数
    std::string name;
    double effect;
    // 其他参数
    // ...
};
