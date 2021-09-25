#include "statistics.hpp"

double statis::average(std::vector<double> values) {
    int size = (int) values.size();

    double sum = statis::sum(values);

    return sum / size;
}

