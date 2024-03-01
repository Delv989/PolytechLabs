#include <iostream>
#include <vector>
#include <limits>

bool is_equal_zero(double a) {
    return abs(a) < std::numeric_limits<double>::epsilon();
}

bool get_coef(double* a, double* b, double* c) {
    if (!(std::cin >> *a >> *b >> *c)) {
        std::cout << "Wrong input";
        return false;
    }
    if (is_equal_zero(*a) && is_equal_zero(*b)) {
        std::cout << "Incorrect coef\n";
        return false;
    }
    return true;
}

void print_roots(std::vector<double>* const roots) {
    if ((*roots).size() == 0) {
        std::cout << "No real roots\n";
    }
    else {
        for (double root : *roots) {
            std::cout << root << " ";
        }
        std::cout << "\n";
    }

}

void find_roots(const double a, const double b, const double c, std::vector<double>* roots) {
    double discriminant = b * b - 4.0 * a * c;
    if  (is_equal_zero(a)) {
        (*roots).push_back(-c / b);
        return;
    }
    else if (is_equal_zero(discriminant)) {
        (*roots).push_back(-b / (2.0 * a));
        return;
    }
    else if (discriminant > 0) {
        (*roots).push_back((-b + sqrt(discriminant)) / (2.0 * a));
        (*roots).push_back((-b - sqrt(discriminant)) / (2.0 * a));
        return;
    }
}


int main()
{
    double a, b, c;
    if (get_coef(&a, &b, &c)) {
        std::vector<double> roots;
        find_roots(a, b, c, &roots);
        print_roots(&roots);
    }
}
