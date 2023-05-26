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

class Cell {
public:
    int num;
    static int N;
    static double R;
    static vector<bool> c_incidences;

    static long double (*metrics)(pair<long double, long double>, pair<long double, long double>);

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

    static void get_incidences(int i, vector<bool> &incidences);

private:
    [[nodiscard]] pair<long double, long double> lu() const;

    [[nodiscard]] pair<long double, long double> ru() const;

    [[nodiscard]] pair<long double, long double> ld() const;

    [[nodiscard]] pair<long double, long double> rd() const;

    static bool are_connected(const Cell &I, const Cell &J,
                              long double (*metric)(pair<long double, long double>,
                                                        pair<long double, long double>));
};


#endif //ESTIMATIONBRUTEFORCE_CELL_H
