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

int Cell::N;
