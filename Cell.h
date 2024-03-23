#ifndef ESTIMATIONBRUTEFORCE_CELL_H
#define ESTIMATIONBRUTEFORCE_CELL_H

#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <numeric>
#include <algorithm>
#include <fstream>

using namespace std;

struct Cell {
public:
    int num;
    static int N;

    explicit Cell(int num) {
        this->num = num;
    };

    explicit Cell() {
        this->num = -1;
    };

    Cell(const Cell &old) {
        this->num = old.num;
    };

    ~Cell() = default;

    [[nodiscard]] int line() const;

    [[nodiscard]] int column() const;

    [[nodiscard]] pair<long double, long double> ld() const;

    [[nodiscard]] pair<long double, long double> lu() const;

    [[nodiscard]] pair<long double, long double> ru() const;

    [[nodiscard]] pair<long double, long double> rd() const;

};


#endif //ESTIMATIONBRUTEFORCE_CELL_H
