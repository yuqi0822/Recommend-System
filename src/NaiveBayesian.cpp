#include "NaiveBayesian.h"
#include <cmath>

NaiveBayesian::NaiveBayesian(double tsd, const std::string in, const std::string out)
    : threshold(tsd), inputFile(in), outputFile(out) {
}

NaiveBayesian::~NaiveBayesian() {

}
void NaiveBayesian::setThreshold(double tsd) {
    threshold = tsd;
}

double NaiveBayesian::getThreshold() const {
    return threshold;
}

bool NaiveBayesian::isSimilarity(std::vector<double> vec1, std::vector<double> vec2) {
    if( calCosine(vec1, vec2) >= threshold )
        return true;
    else
        return false;
}

double NaiveBayesian::calCosine(std::vector<double> vec1, std::vector<double> vec2) {
    if(vec1.size() > vec2.size()) {
        vec2.resize(vec1.size());
    } else if(vec1.size() < vec2.size()) {
        vec1.resize(vec2.size());
    } else ;


    double result, dotProduct = 0, vecMode1 = 0, vecMode2 = 0;
    unsigned int i;
    for(i = 0; i < vec1.size(); i++) {
        dotProduct += vec1[i]*vec2[i];
        vecMode1 += vec1[i]*vec1[i];
        vecMode2 += vec2[i]*vec2[i];
        //std::cout << "vec1:" <<  vec1[i] << "vec2:" << vec2[i] << std::endl;
    }
    result = dotProduct/(sqrt(vecMode1)*sqrt(vecMode2));

    return result;
}
