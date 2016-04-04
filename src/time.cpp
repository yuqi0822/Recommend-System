#include "time.h"
#include <cstdlib>
#include <sstream>
Time::Time():
    c_map(), p_map(), c_count(0), p_count(0){
}

Time::Time(std::string cid, std::string pid, std::string amount):
    c_map(), p_map(), c_count(0), p_count(0){
    std::vector<std::string> temp = split(pid, ';');
    for(int j = 0; j < atoi(amount.c_str()); j++) {
        for(unsigned int i = 0; i < temp.size(); i++) {
            insertToPMap(temp[i]);
        }
        insertToCMap(cid);
    }
}

void Time::setTime(std::string cid, std::string pid, std::string amount) {

    std::vector<std::string> temp = split(pid, ';');
    for(int j = 0; j < atoi(amount.c_str()); j++) {
        for(unsigned short i = 0; i < temp.size(); i++) {
            insertToPMap(temp[i]);
        }
        insertToCMap(cid);
    }
}

void Time::insertToCMap(std::string s) {
    ++c_map[s];
    ++c_count;
}

void Time::insertToPMap(std::string s) {
    ++p_map[s];
    ++p_count;
}

std::vector<std::string> Time::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

void Time::cal_probability() {
    std::unordered_map<std::string, float>::iterator it_c = c_map.begin();
    while(it_c != c_map.end()) {
        it_c->second /= c_count;
        ++it_c;
    }
    std::unordered_map<std::string, float>::iterator it_p = p_map.begin();
    while(it_p != p_map.end()) {
        it_p->second /= p_count;
        ++it_p;
    }
}
