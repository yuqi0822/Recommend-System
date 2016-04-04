#ifndef TIME_H_INCLUDED
#define TIME_H_INCLUDED

#include <iostream>
#include <unordered_map>
#include <vector>
class Time {
public:
    Time();
    Time(std::string cid, std::string pid, std::string amount);
    std::vector<std::string> split(const std::string& s, char delim);
    void setTime(std::string, std::string, std::string);
    void insertToCMap(std::string);
    void insertToPMap(std::string);
    float getCMap(std::string s) { return c_map[s]; }
    float getPMap(std::string s) { return p_map[s]; }
    std::unordered_map<std::string, float> getCMap(){return c_map;}
    std::unordered_map<std::string, float> getPMap(){return p_map;}

    void cal_probability();  // normalize the count to probability
private:
    std::unordered_map<std::string, float> c_map;
    std::unordered_map<std::string, float> p_map;
    int c_count;
    int p_count;
};

#endif // TIME_H_INCLUDED
