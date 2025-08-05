//用于增删改查model的控制器
#pragma once
#include <vector>
#include <string>
#include "JammerModelDAO.h"

class ModelManageController {
public:
    static bool createJammerModel(const JammerModel& model);
    static bool updateJammerModel(const JammerModel& model);
    static bool deleteJammerModel(int id);
    // static JammerModel getJammerModelById(int id);
    // static std::vector<JammerModel> getAllJammerModels();
    // static std::vector<JammerModel> searchJammerModelsByName(const std::string& name);

    // 修改返回类型，只获取名称和ID
    static std::vector<std::pair<int, std::string>> getAllJammerNamesAndIds();
    // 添加新方法，按ID获取完整模型
    static JammerModel getJammerModelById(int id);
    // 修改搜索方法，只返回名称和ID
    static std::vector<std::pair<int, std::string>> searchJammerModelsByName(const std::string& name);
};