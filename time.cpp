#include "time.h"

Time::Time(): c_map(), p_map(), c_count(0), p_count(0) {

}

void Time::insertToCMap(std::string s) {
    ++c_map[s];
    ++c_count;
}

void Time::insertToPMap(std::string s) {
    ++p_map[s];
    ++p_count;
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
