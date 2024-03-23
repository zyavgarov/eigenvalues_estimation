#include "launcher.h"

using namespace std;

long double r_6(pair<long double, long double> a, pair<long double, long double> b) {
    // the metric chooses the shortest way if allowed directions are sides of equal sided triangle
    long double x = b.first - a.first;
    long double y = b.second - a.second;
    // determinantion of the phi of vector
    if (x == 0 && y == 0) {
        return 0;
    }
    long double phi = atan2(y, x);
    if ((phi > -M_PI && phi <= -2 * M_PI / 3) || (phi > 0 && phi <= M_PI / 3)) {
        pair<long double, long double> a_12 = pair<long double, long double>(x - y / sqrtl(3), 2 * y / sqrtl(3));
        return abs(a_12.first) + abs(a_12.second);
    } else if ((phi > -2 * M_PI / 3 && phi <= -M_PI / 3) || (phi >= M_PI / 3 && phi < 2 * M_PI / 3)) {
        pair<long double, long double> a_23 = pair<long double, long double>(x + y / sqrtl(3), y / sqrtl(3) - x);
        return abs(a_23.first) + abs(a_23.second);
    } else if ((phi > -M_PI / 3 && phi <= 0) || (phi > 2 * M_PI / 3 && phi <= M_PI)) {
        pair<long double, long double> a_13 = pair<long double, long double>(x + y / sqrtl(3), 2 * y / sqrtl(3));
        return abs(a_13.first) + abs(a_13.second);
    }
    return -1;
}

int main() {

    /* Brief description of launch_destination arguments:
     * launch_estimation(10, 15, 5, l_1, "eigenvalues.txt", true);
     * means that there will be checked eigenvalues for N = 10, 11, 12, 13, 14 with R = N/5
     * with metrics set up by function l_1
     * result will be saved to file "eigenvalues.txt" ('true' is re         sponsible for that)
     * the progress of program will be shown in console
     *
     * if filename is "" then nothing is written to file
     * if the last parameter is false then nothing is written to console
     */

    /*launch_estimation(10, 100, 10, l_1, "eigenvalues_1.txt", true);
    launch_estimation(10, 100, 10, l_infty, "eigenvalues_infty.txt", true);
    launch_estimation(10, 100, 2, l_2, "eigenvalues_2_2.txt", true);
    launch_estimation(10, 100, 10, l_2, "eigenvalues_2_10.txt", true);
    launch_estimation(10, 60, 10, r_6, "eigenvalues_6_2.txt", true);*/

    launch_estimation(20, 51, 2, "metric", "1", "eigenvalues_1.txt", true);
    /*
     * //this code is smh a proof that usage of thin metrics is legal
    int n = 1000;
    for (int i = 0; i < n; i++) {
        // circle has formula sqrt((n)^2-(x-0.5)^2)+0.5;
        int j = floor(sqrt(pow(n, 2) - pow(i - 0.5, 2)) + 0.5);
        //cout << j << endl;
        // now we look at circle with center (i+0.5, j+0.5) and radius n
        // it's formula: (i+0.5-x)^2+(j+0.5-y)^2=n^2
        // y=-sqrt(n^2-(x-(i+0.5))^2)+(j+0.5)
        int i_ = floor(-sqrt(pow(n, 2) - pow(1 - i - 0.5, 2)) + j + 0.5);
        if (0 != i_) {
            cout << i << " " << i_ << endl;
        }
    }*/
    return 0;
}