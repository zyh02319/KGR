//雷达探测模型
#pragma once
#include "DataManager.h"
#include <vector>
#include <string>
#include <utility>

struct RadarModel {
    int id;
    std::string name;
    double wavelength;
    double power;
    double bandwidth;
    double gain;
    double loss_factor;
    double longitude;
    double latitude;
    double altitude;
};

class RadarModelDAO {
public:
    static bool insert(const RadarModel& model);
    static std::vector<std::pair<int, std::string>> getAllRadarNamesAndIds();
    static std::vector<RadarModel> findByName(const std::string& name);
    static RadarModel findById(int id);
    static bool deleteById(int id);
    static bool update(const RadarModel& model);
};