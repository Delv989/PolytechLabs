#include <iostream>

bool get_coef(double* a, double* b, double* c) {

    try {
        std::cin >> *a >> *b >> *c;
    }
    catch (const std::istream::failure& ex) {
        std::cerr << "Failed to read coef: " << ex.what() << "\n";
    }
    if (*a == 0)
        return false;
    return true;

}

bool solve_problem(const double a, const double b, const double c, std::pair<double, double>** roots) {
    double discriminant = b * b - 4 * a * c;

    if (discriminant >= 0) {
        std::pair<double, double> new_roots(-b + sqrt(discriminant) / (2 * a), -b - sqrt(discriminant) / (2 * a));

        *roots = &new_roots;
        return true;
    }
    return false;
}

void print_roots(const std::pair<double, double>* roots, const bool has_root) {
    if (has_root && roots->first == roots->second) {
        std::cout << roots->first << "\n";
    }
    else if (has_root) {
        std::cout << roots->first << " " << roots->second << "\n";
    }
    else {
        std::cout << "No real roots\n";
    }

}



int main()
{
    double a, b, c;
    if (get_coef(&a, &b, &c)) {
        std::pair<double, double>* roots;
        bool has_root = solve_problem(a, b, c, &roots);
        print_roots(roots, has_root);
    }
}

