#include "launcher.h"

using namespace std;

/* You can use one of metric functions below or write your own
 * Your function must satisfy the following template:
 * long double your_metric(pair<long double, long double> a, pair<long double, long double> b);
 */

long double l_2(pair<long double, long double> a, pair<long double, long double> b) {
    long double d = sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
    return d;
}

long double l_1(pair<long double, long double> a, pair<long double, long double> b) {
    long double d = abs(a.first - b.first) + abs(a.second - b.second);
    return d;
}

long double l_infty(pair<long double, long double> a, pair<long double, long double> b) {
    long double d = max(abs(a.first - b.first), abs(a.second - b.second));
    return d;
}

int main() {

    /* Brief description of launch_destination arguments:
     * launch_estimation(10, 15, 5, l_1, "eigenvalues.txt", true);
     * means that there will be checked eigenvalues for N = 10, 11, 12, 13, 14 with R = N/5
     * with metrics set up by function l_2
     * result will be saved to file "eigenvalues.txt"
     * the progress of program will be shown in console
     *
     * if filename is "" then nothing is written to file
     * if the last parameter is false then nothing is written to console
     */

    launch_estimation(10, 100, 10, l_1, "eigenvalues_1.txt", true);
    launch_estimation(10, 100, 10, l_infty, "eigenvalues_infty.txt", true);
    launch_estimation(10, 100, 2, l_2, "eigenvalues_2_2.txt", true);
    launch_estimation(10, 100, 10, l_2, "eigenvalues_2_10.txt", true);
    return 0;
}