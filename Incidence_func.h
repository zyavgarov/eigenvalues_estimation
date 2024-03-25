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
        /* Under this class we have two cells connected if they have points on the distance R
         * The distance is computed using metric function
         */
        static long double l_infty(pair<long double, long double>, pair<long double, long double>);

        static long double l(pair<long double, long double>, pair<long double, long double>);

        static long double r_6(pair<long double, long double>, pair<long double, long double>);

        static long double metric_param;
    public:
        static long double (*metric)(pair<long double, long double>, pair<long double, long double>);

        explicit Metric(const string &p);

        ~Metric() = default;

        static bool are_connected(const Cell &I, const Cell &J);
    };

    struct Discrete {
        /* Under this class we have two Cells connected if their centers satisfy round(distance(center1,center2))=R
         * The distance is computed according to metric function
         */
        explicit Discrete(const string &p);

        ~Discrete() = default;

        static bool are_connected(const Cell &I, const Cell &J);

        static long double (*metric)(pair<long double, long double>, pair<long double, long double>);
    };

    static int radius;

    static bool (*are_connected)(const Cell &, const Cell &);

    Incidence_func(const string &type, const string &p, double denominator);;

    static void get_incidences(int i, vector<bool> &incidences);

    static vector<bool> c_incidences;
};

#endif //ESTIMATIONBRUTEFORCE_INCIDENCE_FUNC_H
