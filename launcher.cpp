#include "launcher.h"

#define NUMBER_OF_ITERATIONS 120

vector<long double> randomVectorWithSumOne(int size) {
    // Create a random number generator
    // written by chatgpt, I have no idea what's going on there
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<long double> dis(0.0, 1.0);

    // Fill the vector with random numbers
    vector<long double> v(size);
    generate(v.begin(), v.end(), [&]() { return dis(gen); });

    // Normalize the vector to have a sum of 1
    long double sum = accumulate(v.begin(), v.end(), 0.0);
    transform(v.begin(), v.end(), v.begin(), [&](long double x) { return x / sum; });

    // Return the vector
    return v;
}

vector<long double> Mv(vector<long double> v, vector<vector<long double>> M, int N) {
    // multiplying operator M to vector v
    vector<long double> MS(N * N, 0);
    for (int i = 0; i < MS.size(); ++i) {
        for (int j = 0; j < MS.size(); ++j) {
            MS[i] += M[i][j] * v[j];
        }
    }
    return MS;
}

long double sc(const std::vector<long double> &v1, const std::vector<long double> &v2) {
    // scalar product of v1 and v2
    long double result = 0.0;
    for (int i = 0; i < v1.size(); ++i) {
        result += v1[i] * v2[i];
    }
    return result;
}

vector<long double>
launch_estimation(int first_num, int last_num, double R_denominator, const string &type, const string &p,
                  const string &filename, bool print_progress) {

    /* launches estimation of eigenvalues of graph defined in work
     *
     * for N \in [first_num, last_num)
     * for radius N/R_denominator
     * and using metrics from argument
     *
     * The result is written to file with defined filename
     * If the filename is not defined or empty then nothing is written
     * Function returns vector of eigenvalues
     *
     * Note that results are saved and returned in following format:
     * at first there go first_num zeros
     * then goes eigenvalues up to last_num
     * then end.
     * It's made for easy separation of computations between different machines: computation takes a lot of time and a lot of RAM
     */

    vector<long double> eigenvalues(last_num, 0);
    for (int N = first_num; N < last_num; ++N) {

        // matrix of incidence
        Cell::N = N;
        //Cell::metrics = type;
        vector<vector<long double>> M(N * N, vector<long double>(N * N));
        int d = 0; // degree of graph

        /* Here is how enumeration works:
         * let i - number of cell
         * so i % (N*N) - number of column and
         * i / (N*N) - number of line
         * Cells are numbered from 0 up to N-1
         */

        bool change_N = false;

        Incidence_func inc(type, p, R_denominator);
        for (int i = 0; i < N * N; ++i) {
            vector<bool> s(N * N, false);
            Incidence_func::get_incidences(i, s);
            for (int j = 0; j < N * N; ++j) {
                M[i][j] = (long double) (s[j]);
            }
        }

        for (long double i: M[0]) {
            d += (int) i;
        }
        for (int i = 0; i < N * N; ++i) {
            for (int j = 0; j < N * N; ++j) {
                M[i][j] = M[i][j] / d;
            }
        }

        if (print_progress) {
            cout << "N = " << N << endl;
        }
        vector<long double> S = randomVectorWithSumOne(N * N);
        long double l2_prev = -1;
        //multiplications
        for (int m = 0; m < NUMBER_OF_ITERATIONS && !change_N; ++m) {

            vector<long double> MS = Mv(S, M, N);

            // errors, errors1 and errors2 are just w', w'' and w''' where w'=Mw_k
            vector<long double> errors(N * N);
            for (int i = 0; i < N * N; ++i) {
                errors[i] = (S[i] - 1. / (N * N));
            }

            vector<long double> errors1 = Mv(errors, M, N);
            vector<long double> e(N * N, 1);

            // e = (1,1,..,1,1)
            long double c = sc(errors1, e) / sc(e, e);

            vector<long double> errors2(N * N);
            for (int i = 0; i < N * N; ++i) {
                errors2[i] = errors1[i] - c * e[i];
            }

            vector<long double> errors3(N * N);
            long double norm2 = sqrt(sc(errors2, errors2));
            for (int i = 0; i < N * N; ++i) {
                errors3[i] = errors2[i] / norm2;
            }
            vector<long double> mw = Mv(errors3, M, N);
            long double l2 = sqrt(sc(mw, mw));

            if (abs(l2 - l2_prev) < 5E-3) {
                if (print_progress) {
                    cout << "lambda_2 = " << l2 << endl;
                }
                eigenvalues[N] = l2;
                change_N = true;
            }

            /* In every next iteration norm of errors2 is less than in previous
             * It means that from some moment normalization of errors2 makes miscalculations more probable
             * Usually it makes l2 to be shown as nan or 1. This is senseless
             * In that case we stop */

            if (abs(l2 - 1) < 1e-10 || isnan(l2)) {
                if (print_progress) {
                    cout << "w'' is too small to continue. You should choose most probable l2 yourself" << endl;
                }
                change_N = true;
            }
            //uncomment line below to search l2 yourself
            //cout << l2 << endl;
            S = MS;
            l2_prev = l2;
        }
        //cout << "Run out of iterations" << endl;
    }
    if (!filename.empty()) {
        ofstream output(filename);
        for (long double eigenvalue: eigenvalues) {
            output << eigenvalue << endl;
        }
    }
    return eigenvalues;
}
