#ifndef TIME_H_INCLUDED
#define TIME_H_INCLUDED
#include <iostream>
#include <unordered_map>
class Time {
public:
    Time();
    void insertToCMap(std::string);
    void insertToPMap(std::string);
    float getCMap(std::string s) { return c_map[s]; }
    float getPMap(std::string s) { return p_map[s]; }

    void cal_probability();  // normalize the count to probability
private:
    std::unordered_map<std::string, float> c_map;
    std::unordered_map<std::string, float> p_map;
    int c_count;
    int p_count;
};


#endif // TIME_H_INCLUDED
