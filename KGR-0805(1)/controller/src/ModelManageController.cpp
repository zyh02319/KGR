//用于增删改查model的控制器
#include "ModelManageController.h"
#include <iostream>

// bool ModelManageController::createJammerModel(const JammerModel& model) {
//     std::cout << "[ModelManageController] createJammerModel called for: " << model.name << std::endl;
//     return JammerModelDAO::insert(model);
// }

bool ModelManageController::createJammerModel(const JammerModel& model) {
    std::cout << "[ModelManageController] createJammerModel called for: " << model.name << std::endl;
    bool result = JammerModelDAO::insert(model);
    if (!result) {
        std::cerr << "CreateJammerModel failed for: " << model.name << std::endl;
    }
    return result;
}

// bool ModelManageController::updateJammerModel(const JammerModel& model) {
//     std::cout << "[ModelManageController] updateJammerModel called for ID: " << model.id << std::endl;
//     return JammerModelDAO::update(model);
// }

bool ModelManageController::updateJammerModel(const JammerModel& model) {
    std::cout << "[ModelManageController] updateJammerModel called for ID: " << model.id << std::endl;
    bool result = JammerModelDAO::update(model);
    if (!result) {
        std::cerr << "UpdateJammerModel failed for ID: " << model.id << std::endl;
    }
    return result;
}


bool ModelManageController::deleteJammerModel(int id) {
    std::cout << "[ModelManageController] deleteJammerModel called for ID: " << id << std::endl;
    return JammerModelDAO::deleteById(id);
}

// JammerModel ModelManageController::getJammerModelById(int id) {
//     std::cout << "[ModelManageController] getJammerModelById called for ID: " << id << std::endl;
//     return JammerModelDAO::findById(id);
// }
// 按ID获取完整模型
JammerModel ModelManageController::getJammerModelById(int id) {
    std::cout << "[ModelManageController] getJammerModelById called for ID: " << id << std::endl;
    return JammerModelDAO::findById(id);
}
//待改进，获取全部的名字和ID就可以了，不用挨个查一遍
// std::vector<JammerModel> ModelManageController::getAllJammerModels() {
//     std::cout << "[ModelManageController] getAllJammerModels called." << std::endl;
//     std::vector<JammerModel> models;
//     auto namesAndIds = JammerModelDAO::getAllJammerNamesAndIds();
//     for (const auto& pair : namesAndIds) {
//         std::cout << "[ModelManageController] getJammerModelById called for ID: " << pair.first << std::endl;
//         models.push_back(JammerModelDAO::findById(pair.first));
//     }
//     return models;
// }
//改进后，获取全部的名字和ID
std::vector<std::pair<int, std::string>> ModelManageController::getAllJammerNamesAndIds() {
    std::cout << "[ModelManageController] getAllJammerNamesAndIds called." << std::endl;
    return JammerModelDAO::getAllJammerNamesAndIds();
}


// std::vector<JammerModel> ModelManageController::searchJammerModelsByName(const std::string& name) {
//     std::cout << "[ModelManageController] searchJammerModelsByName called for name: " << name << std::endl;
//     return JammerModelDAO::findByName(name);
// }
// 按名称搜索干扰机模型，只返回名称和ID
std::vector<std::pair<int, std::string>> ModelManageController::searchJammerModelsByName(const std::string& name) {
    std::cout << "[ModelManageController] searchJammerModelsByName called for name: " << name << std::endl;
    return JammerModelDAO::searchJammerNamesAndIdsByName(name);
}