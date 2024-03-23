//
// Created by tcatacatcat on 08.03.24.
//

#ifndef ESTIMATIONBRUTEFORCE_INCIDENCE_FUNC_H
#define ESTIMATIONBRUTEFORCE_INCIDENCE_FUNC_H

#include <string>
#include "Cell.h"

using namespace std;

/* we want smth like that:
 * Incidence_func F = Incidence_func("metric", "infinity", denominator);
 * -----------------------------------
 * //in launch:
 * are_connected(Cell I, Cell J) // or smth like that
 */

struct Incidence_func {
public:
    struct Metric {
        static long double l_infty(pair<long double, long double>, pair<long double, long double>);

        static long double l_2(pair<long double, long double>, pair<long double, long double>);

        static long double l_1(pair<long double, long double>, pair<long double, long double>);

    public:
        static long double (*metric)(pair<long double, long double>, pair<long double, long double>);

        Metric(const string &p);
        ~Metric() = default;
        static bool are_connected(const Cell &I, const Cell &J);
    };

    struct Discrete {

    };

    static int radius;

    static bool (*are_connected)(const Cell &, const Cell &);

    Incidence_func(const string &type, const string &p, double denominator);;

    static void get_incidences(int i, vector<bool> &incidences);

    static vector<bool> c_incidences;
};

#endif //ESTIMATIONBRUTEFORCE_INCIDENCE_FUNC_H
