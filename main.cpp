#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <numeric>
#include <algorithm>
#include <fstream>

#define NUMBER_OF_ITERATIONS 120
using namespace std;

class Cell {
public:
    int num{};
    static int N;
    static double R;
    static vector<bool> c_incidences;

    explicit Cell(int num) {
        this->num = num;
    }

    explicit Cell() {
        this->num = -1;
    }

    Cell(const Cell &old) {
        num = old.num;
    }

    ~Cell() = default;

    int line() const {
        return num / N;
    }

    int column() const {
        return num % N;
    }

private:

    pair<long double, long double> lu() const {
        return {this->column(), this->line() + 1};
    }

    pair<long double, long double> ru() const {
        return {this->column() + 1, this->line() + 1};
    }

    pair<long double, long double> ld() const {
        return {this->column(), this->line()};
    }

    pair<long double, long double> rd() const {
        return {this->column() + 1, this->line()};
    }

    static long double dist_2(pair<long double, long double> a, pair<long double, long double> b) {
        long double d = sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
        // cout << "distance: " << d << endl;
        return d;
    }

    static long double dist_1(pair<long double, long double> a, pair<long double, long double> b) {
        long double d = abs(a.first - b.first) + abs(a.second - b.second);
        // cout << "distance: " << d << endl;
        return d;
    }

    static long double dist_infty(pair<long double, long double> a, pair<long double, long double> b) {
        long double d = max(abs(a.first - b.first), abs(a.second - b.second));
        // cout << "distance: " << d << endl;
        return d;
    }

public:
    static bool are_connected_2(const Cell &I, const Cell &J) {

        /* we consider two cells I and J connected if there are two points i in I, j in J and distance(i,j) = R
         * we think of cells to be connected if there are their corners distance between them is less than R and
         * two corners with distance more than R
         */
        if (I.num == J.num) return true;
        vector<long double> distances(16);

        distances[0] = dist_2(I.ld(), J.rd());
        distances[1] = dist_2(I.ld(), J.lu());
        distances[2] = dist_2(I.ld(), J.ru());
        distances[3] = dist_2(I.ld(), J.ld());
        distances[4] = dist_2(I.ru(), J.ld());
        distances[5] = dist_2(I.ru(), J.rd());
        distances[6] = dist_2(I.ru(), J.lu());
        distances[7] = dist_2(I.ru(), J.ru());
        distances[8] = dist_2(I.rd(), J.lu());
        distances[9] = dist_2(I.rd(), J.ru());
        distances[10] = dist_2(I.rd(), J.ld());
        distances[11] = dist_2(I.rd(), J.rd());
        distances[12] = dist_2(I.lu(), J.rd());
        distances[13] = dist_2(I.lu(), J.ru());
        distances[14] = dist_2(I.lu(), J.ld());
        distances[15] = dist_2(I.lu(), J.lu());
        // search min and max in vector
        long double min = distances[0];
        long double max = distances[0];
        for (auto i: distances) {
            if (i < min) {
                min = i;
            } else if (i > max) {
                max = i;
            }
        }
        if (max >= R && min <= R) {
            return true;
        } else {
            return false;
        }
    }

    static bool are_connected_infty(const Cell &I, const Cell &J) {
        if (I.num == J.num) return true;
        vector<long double> distances(16);

        distances[0] = dist_infty(I.ld(), J.rd());
        distances[1] = dist_infty(I.ld(), J.lu());
        distances[2] = dist_infty(I.ld(), J.ru());
        distances[3] = dist_infty(I.ld(), J.ld());
        distances[4] = dist_infty(I.ru(), J.ld());
        distances[5] = dist_infty(I.ru(), J.rd());
        distances[6] = dist_infty(I.ru(), J.lu());
        distances[7] = dist_infty(I.ru(), J.ru());
        distances[8] = dist_infty(I.rd(), J.lu());
        distances[9] = dist_infty(I.rd(), J.ru());
        distances[10] = dist_infty(I.rd(), J.ld());
        distances[11] = dist_infty(I.rd(), J.rd());
        distances[12] = dist_infty(I.lu(), J.rd());
        distances[13] = dist_infty(I.lu(), J.ru());
        distances[14] = dist_infty(I.lu(), J.ld());
        distances[15] = dist_infty(I.lu(), J.lu());
        // search min and max in vector
        long double min = distances[0];
        long double max = distances[0];
        for (auto i: distances) {
            if (i < min) {
                min = i;
            } else if (i > max) {
                max = i;
            }
        }
        if (max >= R && min <= R) {
            return true;
        } else {
            return false;
        }
    }

    static bool are_connected_1(const Cell &I, const Cell &J) {
        if (I.num == J.num) return true;
        vector<long double> distances(16);

        distances[0] = dist_1(I.ld(), J.rd());
        distances[1] = dist_1(I.ld(), J.lu());
        distances[2] = dist_1(I.ld(), J.ru());
        distances[3] = dist_1(I.ld(), J.ld());
        distances[4] = dist_1(I.ru(), J.ld());
        distances[5] = dist_1(I.ru(), J.rd());
        distances[6] = dist_1(I.ru(), J.lu());
        distances[7] = dist_1(I.ru(), J.ru());
        distances[8] = dist_1(I.rd(), J.lu());
        distances[9] = dist_1(I.rd(), J.ru());
        distances[10] = dist_1(I.rd(), J.ld());
        distances[11] = dist_1(I.rd(), J.rd());
        distances[12] = dist_1(I.lu(), J.rd());
        distances[13] = dist_1(I.lu(), J.ru());
        distances[14] = dist_1(I.lu(), J.ld());
        distances[15] = dist_1(I.lu(), J.lu());

        // search min and max in vector
        long double min = distances[0];
        long double max = distances[0];
        for (auto i: distances) {
            if (i < min) {
                min = i;
            } else if (i > max) {
                max = i;
            }
        }
        if (max >= R && min <= R) {
            return true;
        } else {
            return false;
        }
    };

    static bool (*are_connected)(const Cell &, const Cell &);

    static void get_incidences(int i, vector<bool> &incidences) {
        // we solve incidence for on central cell, after just move it for others
        // cout << "getting incidences" << endl;
        Cell central;
        if (N % 2 == 0) { // statement should not be simplified if asked by IDE
            central = Cell(N * N / 2 - N / 2);
        } else {
            central = Cell(N * N / 2);
        }
        Cell I(i);
        if (i == 0) {
            for (int k = 0; k < c_incidences.size(); ++k) {
                c_incidences[k] = are_connected(central, Cell(k));
            }
        }
        //vector<bool> incidences (N * N);
        int shift = i - central.num;
        for (int j = 0; j < incidences.size(); ++j) {
            //cout << (j + shift + N * N) % (N * N) << endl;
            incidences[(j + shift + N * N) % (N * N)] = c_incidences[j];
        }
    }
};

bool (*Cell::are_connected)(const Cell &, const Cell &) = &Cell::are_connected_1;

int Cell::N;
double Cell::R;

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

vector<bool> Cell::c_incidences = vector<bool>(N * N, false);


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

int main() {

    vector<double> eigenvalues(100);

    Cell::are_connected = &Cell::are_connected_1;
    for (int N = 10; N < 100; ++N) {

        // matrix of incidence
        Cell::c_incidences = vector<bool>(N * N, false);
        Cell::N = N;
        Cell::R = N / 10.0;
        vector<vector<long double>> M(N * N, vector<long double>(N * N));
        vector<int> d(N * N, 0);
        const long double EPS = numeric_limits<long double>::epsilon();

        /* Here is how enumeration works:
         * let i - number of cell
         * so i % (N*N) - number of column and
         * i / (N*N) - number of line
         * Cells are numbered from 0 up to N-1
         */
        bool change_N = false;

        for (int i = 0; i < N * N; ++i) {
            vector<bool> s(N * N, false);
            Cell::get_incidences(i, s);
            for (int j = 0; j < N * N; ++j) {
                M[i][j] = (long double) (s[j]);
            }
        }
        for (long double i: M[0]) {
            d[0] += i;
        }
        for (int i = 0; i < N * N; ++i) {
            for (int j = 0; j < N * N; ++j) {
                M[i][j] = M[i][j] / d[0];
            }
        }

        cout << "N = " << N << endl;
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
            //cout << "norm2 = " << norm2 << endl;
            for (int i = 0; i < N * N; ++i) {
                errors3[i] = errors2[i] / norm2;
            }
            vector<long double> mw = Mv(errors3, M, N);
            long double l2 = sqrt(sc(mw, mw));

            if (abs(l2 - l2_prev) < 5E-3) {
                cout << "lambda_2 = " << l2 << endl;
                eigenvalues[N] = l2;
                change_N = true;
            }

            /* In every next iteration norm of errors2 is less than in previous
             * It means that from some moment normalization of errors2 makes miscalculations more probable
             * Usually it makes l2 to be shown as nan or 1. This is senseless
             * In that case we stop */

            if (abs(l2 - 1) < 1e-10 || isnan(l2)) {
                cout << "w'' is too small to continue. You should choose most probable l2 yourself" << endl;
                change_N = true;
            }
            //uncomment line below to search l2 yourself
            //cout << l2 << endl;
            S = MS;
            l2_prev = l2;
        }
        //cout << "Run out of iterations" << endl;
    }

    // writing eigenvalues to file
    ofstream file1("eigenvalues_1.txt");
    for (double eigenvalue: eigenvalues) {
        file1 << eigenvalue << endl;
    }


    Cell::are_connected = &Cell::are_connected_infty;
    for (int N = 90; N < 100; ++N) {

        // matrix of incidence
        Cell::c_incidences = vector<bool>(N * N, false);
        Cell::N = N;
        Cell::R = N / 10.0;
        vector<vector<long double>> M(N * N, vector<long double>(N * N));
        vector<int> d(N * N, 0);
        const long double EPS = numeric_limits<long double>::epsilon();

        /* Here is how enumeration works:
         * let i - number of cell
         * so i % (N*N) - number of column and
         * i / (N*N) - number of line
         * Cells are numbered from 0 up to N-1
         */
        bool change_N = false;

        for (int i = 0; i < N * N; ++i) {
            vector<bool> s(N * N, false);
            Cell::get_incidences(i, s);
            for (int j = 0; j < N * N; ++j) {
                M[i][j] = (long double) (s[j]);
            }
        }
        for (long double i: M[0]) {
            d[0] += i;
        }
        for (int i = 0; i < N * N; ++i) {
            for (int j = 0; j < N * N; ++j) {
                M[i][j] = M[i][j] / d[0];
            }
        }

        cout << "N = " << N << endl;
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
                cout << "lambda_2 = " << l2 << endl;
                eigenvalues[N] = l2;
                change_N = true;
            }

            /* In every next iteration norm of errors2 is less than in previous
             * It means that from some moment normalization of errors2 makes miscalculations more probable
             * Usually it makes l2 to be shown as nan or 1. This is senseless
             * In that case we stop */

            if (abs(l2 - 1) < 1e-10 || isnan(l2)) {
                cout << "w'' is too small to continue. You should choose most probable l2 yourself" << endl;
                change_N = true;
            }
            //uncomment line below to search l2 yourself
            //cout << l2 << endl;
            S = MS;
            l2_prev = l2;
        }
        //cout << "Run out of iterations" << endl;
    }
    // writing eigenvalues to file
    ofstream file_infty("eigenvalues_infty.txt");
    for (double eigenvalue: eigenvalues) {
        file_infty << eigenvalue << endl;
    }



    Cell::are_connected = &Cell::are_connected_2;
    for (int N = 90; N < 100; ++N) {

        // matrix of incidence
        Cell::c_incidences = vector<bool>(N * N, false);
        Cell::N = N;
        Cell::R = N / 10.0;
        vector<vector<long double>> M(N * N, vector<long double>(N * N));
        vector<int> d(N * N, 0);
        const long double EPS = numeric_limits<long double>::epsilon();

        /* Here is how enumeration works:
         * let i - number of cell
         * so i % (N*N) - number of column and
         * i / (N*N) - number of line
         * Cells are numbered from 0 up to N-1
         */
        bool change_N = false;

        for (int i = 0; i < N * N; ++i) {
            vector<bool> s(N * N, false);
            Cell::get_incidences(i, s);
            for (int j = 0; j < N * N; ++j) {
                M[i][j] = (long double) (s[j]);
            }
        }
        for (long double i: M[0]) {
            d[0] += i;
        }
        for (int i = 0; i < N * N; ++i) {
            for (int j = 0; j < N * N; ++j) {
                M[i][j] = M[i][j] / d[0];
            }
        }

        //cout << "Degree of vertex is " << d[0] << endl;
        //cout << "Matrix was created" << endl;
        cout << "N = " << N << endl;
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
                cout << "lambda_2 = " << l2 << endl;
                eigenvalues[N] = l2;
                change_N = true;
            }

            /* In every next iteration norm of errors2 is less than in previous
             * It means that from some moment normalization of errors2 makes miscalculations more probable
             * Usually it makes l2 to be shown as nan or 1. This is senseless
             * In that case we stop */

            if (abs(l2 - 1) < 1e-10 || isnan(l2)) {
                cout << "w'' is too small to continue. You should choose most probable l2 yourself" << endl;
                change_N = true;
            }
            //uncomment line below to search l2 yourself
            //cout << l2 << endl;
            S = MS;
            l2_prev = l2;
        }
        //cout << "Run out of iterations" << endl;
    }
    // writing eigenvalues to file
    ofstream file_2_10("eigenvalues_2_10.txt");
    for (double eigenvalue: eigenvalues) {
        file_2_10 << eigenvalue << endl;
    }


    Cell::are_connected = &Cell::are_connected_2;
    for (int N = 90; N < 100; ++N) {

        // matrix of incidence
        Cell::c_incidences = vector<bool>(N * N, false);
        Cell::N = N;
        Cell::R = N / 2.0;
        vector<vector<long double>> M(N * N, vector<long double>(N * N));
        vector<int> d(N * N, 0);
        const long double EPS = numeric_limits<long double>::epsilon();

        /* Here is how enumeration works:
         * let i - number of cell
         * so i % (N*N) - number of column and
         * i / (N*N) - number of line
         * Cells are numbered from 0 up to N-1
         */
        bool change_N = false;

        for (int i = 0; i < N * N; ++i) {
            vector<bool> s(N * N, false);
            Cell::get_incidences(i, s);
            for (int j = 0; j < N * N; ++j) {
                M[i][j] = (long double) (s[j]);
            }
        }
        for (long double i: M[0]) {
            d[0] += i;
        }
        for (int i = 0; i < N * N; ++i) {
            for (int j = 0; j < N * N; ++j) {
                M[i][j] = M[i][j] / d[0];
            }
        }

        cout << "N = " << N << endl;
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
            //cout << "norm2 = " << norm2 << endl;
            for (int i = 0; i < N * N; ++i) {
                errors3[i] = errors2[i] / norm2;
            }
            vector<long double> mw = Mv(errors3, M, N);
            long double l2 = sqrt(sc(mw, mw));

            if (abs(l2 - l2_prev) < 5E-3) {
                cout << "lambda_2 = " << l2 << endl;
                eigenvalues[N] = l2;
                change_N = true;
            }

            /* In every next iteration norm of errors2 is less than in previous
             * It means that from some moment normalization of errors2 makes miscalculations more probable
             * Usually it makes l2 to be shown as nan or 1. This is senseless
             * In that case we stop */

            if (abs(l2 - 1) < 1e-10 || isnan(l2)) {
                cout << "w'' is too small to continue. You should choose most probable l2 yourself" << endl;
                change_N = true;
            }
            //uncomment line below to search l2 yourself
            //cout << l2 << endl;
            S = MS;
            l2_prev = l2;
        }
        //cout << "Run out of iterations" << endl;
    }
    // writing eigenvalues to file
    ofstream file_2_2("eigenvalues_2_2.txt");
    for (double eigenvalue: eigenvalues) {
        file_2_2 << eigenvalue << endl;
    }
    return 0;
}