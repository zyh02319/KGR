#pragma once
#include <mysql/mysql.h>
#include <string>
class DataManager {
public:
    DataManager();
    ~DataManager();
    bool connect(const std::string& host, const std::string& user, const std::string& pwd, const std::string& db, unsigned int port=3306);
    void disconnect();
    // 增删改查接口
    // ...
private:
    MYSQL *conn;
};
