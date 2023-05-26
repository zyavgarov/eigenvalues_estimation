#include "Cell.h"

int Cell::line() const {
    return num / N;
}

int Cell::column() const {
    return num % N;
}

pair<long double, long double> Cell::lu() const {
    return {this->column(), this->line() + 1};
}

pair<long double, long double> Cell::ru() const {
    return {this->column() + 1, this->line() + 1};
}

pair<long double, long double> Cell::ld() const {
    return {this->column(), this->line()};
}

pair<long double, long double> Cell::rd() const {
    return {this->column() + 1, this->line()};
}

bool Cell::are_connected(const Cell &I, const Cell &J,
                         long double (*metric)(pair<long double, long double>,
                                                   pair<long double, long double>)) {
    if (I.num == J.num) return true;
    vector<long double> distances(16);

    distances[0] = metric(I.ld(), J.rd());
    distances[1] = metric(I.ld(), J.lu());
    distances[2] = metric(I.ld(), J.ru());
    distances[3] = metric(I.ld(), J.ld());
    distances[4] = metric(I.ru(), J.ld());
    distances[5] = metric(I.ru(), J.rd());
    distances[6] = metric(I.ru(), J.lu());
    distances[7] = metric(I.ru(), J.ru());
    distances[8] = metric(I.rd(), J.lu());
    distances[9] = metric(I.rd(), J.ru());
    distances[10] = metric(I.rd(), J.ld());
    distances[11] = metric(I.rd(), J.rd());
    distances[12] = metric(I.lu(), J.rd());
    distances[13] = metric(I.lu(), J.ru());
    distances[14] = metric(I.lu(), J.ld());
    distances[15] = metric(I.lu(), J.lu());

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

void Cell::get_incidences(int i, vector<bool> &incidences) {
    // we solve incidence for one central cell, after just move it for others
    Cell central;
    if (N % 2 == 0) {
        central = Cell(N * N / 2 - N / 2);
    } else {
        central = Cell(N * N / 2);
    }
    Cell I(i);
    if (i == 0) {
        for (int k = 0; k < c_incidences.size(); ++k) {
            c_incidences[k] = are_connected(central, Cell(k), metrics);
        }
    }
    int shift = i - central.num;
    for (int j = 0; j < incidences.size(); ++j) {
        incidences[(j + shift + N * N) % (N * N)] = c_incidences[j];
    }
}

long double (*Cell::metrics)(pair<long double, long double>, pair<long double, long double>);

int Cell::N;
double Cell::R;
vector<bool> Cell::c_incidences;