// 干扰机模型的增删改查
#pragma once
#include "DataManager.h"
#include <vector>
#include <string>
#include <utility>

struct JammerModel {
    int id;
    std::string name;
    std::string jamming_type;
    double power;
    double bandwidth;
    double gain;
    double longitude;
    double latitude;
    double altitude;
};

class JammerModelDAO {
public:
    static bool insert(const JammerModel& model);
    static std::vector<std::pair<int, std::string>> getAllJammerNamesAndIds();
    static std::vector<JammerModel> findByName(const std::string& name);
    static JammerModel findById(int id);
    static bool deleteById(int id);
    static bool update(const JammerModel& model);
    // 添加新方法：按名称搜索，只返回名称和ID
    static std::vector<std::pair<int, std::string>> searchJammerNamesAndIdsByName(const std::string& name);
};