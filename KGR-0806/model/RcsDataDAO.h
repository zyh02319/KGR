//目标机RCS
#pragma once
#include "DataManager.h"
#include <vector>
#include <string>
#include <utility>

struct RcsData {
    int target_model_id;
    double azimuth;
    double elevation;
    double rcs_value;
};

class RcsDataDAO {
public:
    static bool insert(const RcsData& data);
    static std::vector<std::pair<int, std::string>> getAllTargetRcsNamesAndIds();
    static std::vector<RcsData> findByTargetId(int targetId);
    static RcsData findByTargetIdAndAngles(int targetId, double azimuth, double elevation);
    static bool deleteByTargetIdAndAngles(int targetId, double azimuth, double elevation);
    static bool update(const RcsData& data);
    // 添加批量删除方法
    static bool deleteByTargetId(int targetId);
};