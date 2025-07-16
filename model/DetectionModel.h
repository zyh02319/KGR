 #pragma once
#include <string>
#include "ModelBase.h"
class DetectionModel : public ModelBase {
public:
    DetectionModel();
    ~DetectionModel();
    // 探测模型参数
    std::string name;
    double radar_range;
    double antenna_gain;
    double clutter;
    double rcs[360];
    // 其他参数
    // ...
};
