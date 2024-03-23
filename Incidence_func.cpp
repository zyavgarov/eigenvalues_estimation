//
// Created by tcatacatcat on 08.03.24.
//

#include "Incidence_func.h"

bool (*Incidence_func::are_connected)(const Cell &, const Cell &);

long double (*Incidence_func::Metric::metric)(pair<long double, long double>, pair<long double, long double>);

int Incidence_func::radius;
vector<bool> Incidence_func::c_incidences;

Incidence_func::Metric::Metric(const string &p) {
    if (p == "infinity") {
        //Incidence_func::are_connected = &Metric::are_connected;
        metric = &Metric::l_infty;
    } else if (stoi(p) == 2) {
        metric = &Metric::l_2;
    } else if (stoi(p) == 1) {
        metric = &Metric::l_1;
    }
}

bool Incidence_func::Metric::are_connected(const Cell &I, const Cell &J) {
    if (I.num == J.num) return true;
    vector<long double> distances(16);

    distances[0] = (*metric)(I.ld(), J.rd());
    distances[1] = (*metric)(I.ld(), J.lu());
    distances[2] = (*metric)(I.ld(), J.ru());
    distances[3] = (*metric)(I.ld(), J.ld());
    distances[4] = (*metric)(I.ru(), J.ld());
    distances[5] = (*metric)(I.ru(), J.rd());
    distances[6] = (*metric)(I.ru(), J.lu());
    distances[7] = (*metric)(I.ru(), J.ru());
    distances[8] = (*metric)(I.rd(), J.lu());
    distances[9] = (*metric)(I.rd(), J.ru());
    distances[10] = (*metric)(I.rd(), J.ld());
    distances[11] = (*metric)(I.rd(), J.rd());
    distances[12] = (*metric)(I.lu(), J.rd());
    distances[13] = (*metric)(I.lu(), J.ru());
    distances[14] = (*metric)(I.lu(), J.ld());
    distances[15] = (*metric)(I.lu(), J.lu());

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
    if (max >= radius && min <= radius) {
        return true;
    } else {
        return false;
    }
}

long double Incidence_func::Metric::l_infty(pair<long double, long double> a, pair<long double, long double> b) {
    return max(abs(a.first - b.first), abs(a.second - b.second));
}

long double Incidence_func::Metric::l_2(pair<long double, long double> a, pair<long double, long double> b) {
    return sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}

long double Incidence_func::Metric::l_1(pair<long double, long double> a, pair<long double, long double> b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

Incidence_func::Incidence_func(const string &type, const string &p, double R_denominator) {
    c_incidences = vector<bool>(Cell::N * Cell::N, false);
    radius = (double) (Cell::N) / R_denominator;
    if (type == "metric") {
        if (p == "infinity") {
            auto l_infty = Metric(p);
            are_connected = Incidence_func::Metric::are_connected;
        } else if (stoi(p) == 2) {
            auto l_2 = Metric(p);
            are_connected = Incidence_func::Metric::are_connected;
        } else if (stoi(p) == 1) {
            auto l_1 = Metric(p);
            are_connected = Incidence_func::Metric::are_connected;
        } else {
            cout << "Incorrect p" << endl;
        }
    } else if (type == "discrete") {
        //tbd
    } else {
        cout << "Incorrect type" << endl;
    }
}

void Incidence_func::get_incidences(int i, vector<bool> &incidences) {
    // we solve incidence for one central cell, after just move it for others
    Cell central;
    if (Cell::N % 2 == 0) {
        central = Cell(Cell::N * Cell::N / 2 - Cell::N / 2);
    } else {
        central = Cell(Cell::N * Cell::N / 2);
    }
    if (i == 0) {
        for (int k = 0; k < c_incidences.size(); ++k) {
            c_incidences[k] = are_connected(central, Cell(k));
        }
    }
    int shift = i - central.num;
    for (int j = 0; j < incidences.size(); ++j) {
        incidences[(j + shift + Cell::N * Cell::N) % (Cell::N * Cell::N)] = c_incidences[j];
    }
}