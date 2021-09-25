#include "statistics.hpp"

double statis::sum(std::vector<double> values) {
    double accum = 0;

    for (std::vector<double>::iterator it = values.begin(); it != values.end(); ++it) {
        double value = *it;

        accum = accum + value; // accum += value; accum += *it;
    }

    return accum;
}

