#ifndef NAIVEBAYESIAN_H_INCLUDED
#define NAIVEBAYESIAN_H_INCLUDED
#include <iostream>
#include <vector>

class NaiveBayesian {
public:
    NaiveBayesian(double tsd, const std::string in, const std::string out);
    virtual ~NaiveBayesian();
    void setThreshold(double tsd);
    double getThreshold() const;
    bool isSimilarity(std::vector<double> vec1, std::vector<double> vec2);
    double calCosine(std::vector<double> vec1, std::vector<double> vec2);
private:
    double threshold;
    std::string inputFile;
    std::string outputFile;
};



#endif // NAIVEBAYESIAN_H_INCLUDED
