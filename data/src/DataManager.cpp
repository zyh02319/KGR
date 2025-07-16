#include "DataManager.h"
DataManager::DataManager() : conn(nullptr) {}
DataManager::~DataManager() { disconnect(); }
bool DataManager::connect(const std::string& host, const std::string& user, const std::string& pwd, const std::string& db, unsigned int port) {
    conn = mysql_init(nullptr);
    if (!conn) return false;
    if (!mysql_real_connect(conn, host.c_str(), user.c_str(), pwd.c_str(), db.c_str(), port, nullptr, 0)) {
        conn = nullptr;
        return false;
    }
    return true;
}
void DataManager::disconnect() {
    if (conn) {
        mysql_close(conn);
        conn = nullptr;
    }
}
