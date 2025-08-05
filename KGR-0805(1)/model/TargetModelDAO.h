//目标机模型
#pragma once
#include "DataManager.h"
#include <vector>
#include <string>
#include <utility>

struct TargetModel {
    int id;
    std::string name;
    std::string target_type;
    double longitude;
    double latitude;
    double altitude;
};

class TargetModelDAO {
public:
    static bool insert(const TargetModel& model);
    static std::vector<std::pair<int, std::string>> getAllTargetNamesAndIds();
    static std::vector<TargetModel> findByName(const std::string& name);
    static TargetModel findById(int id);
    static bool deleteById(int id);
    static bool update(const TargetModel& model);
};