#include "launcher.h"

using namespace std;


int main() {

    /* Brief description of launch_destination arguments:
     * launch_estimation(10, 15, 5, l_1, "eigenvalues.txt", true);
     * means that there will be checked eigenvalues for N = 10, 11, 12, 13, 14 with R = N/5
     * with metrics set up by function l_1
     * result will be saved to file "eigenvalues.txt" ('true' is responsible for that)
     * the progress of program will be shown in console
     *
     * if filename is "" then nothing is written to file
     * if the last parameter is false then nothing is written to console
     */

    launch_estimation(10, 100, 10, "metric", "1", "eigenvalues_m_1.txt", true);
    launch_estimation(10, 100, 2, "metric", "2", "eigenvalues_m_2_2.txt", true);
    launch_estimation(10, 100, 10, "metric", "2", "eigenvalues_m_2.txt", true);
    launch_estimation(10, 100, 10, "metric", "infinity", "eigenvalues_m_infinity.txt", true);
    launch_estimation(10, 100, 10, "metric", "r_6", "eigenvalues_m_r.txt", true);
    launch_estimation(10, 100, 10, "discrete", "1", "eigenvalues_d_1.txt", true);
    launch_estimation(10, 100, 2, "discrete", "2", "eigenvalues_d_2_2.txt", true);
    launch_estimation(10, 100, 10, "discrete", "2", "eigenvalues_d_2.txt", true);
    launch_estimation(10, 100, 10, "discrete", "infinity", "eigenvalues_d_infinity.txt", true);
    launch_estimation(10, 100, 10, "discrete", "r_6", "eigenvalues_d_r.txt", true);
    return 0;
}