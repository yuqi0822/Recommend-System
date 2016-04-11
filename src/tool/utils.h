#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include "fileIO.h"
#include <unordered_map>
#include <cstdlib>

class Utils {
public:
    static Utils& getInstance(std::string file);
    vector<std::string> getVector() const;
    unordered_map<std::string, int> getTMap();
    unordered_map<std::string, int> getMapping();
    int getCatNum() const { return cat_num; }
    int getProNum() const { return pro_num; }
    int getTMax() const { return tMax; }
private:
    Utils(std::string file);
    static Utils& instance;
    fileIO& fr;
    std::string fileName;
    int tMax;
    int cat_num;
    int pro_num;
    vector<string> vec;
    unordered_map<std::string, int> mapping;
};

#endif // UTILS_H_INCLUDED
