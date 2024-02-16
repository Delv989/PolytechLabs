#include <iostream>

bool get_coef(double* a, double* b, double* c) {

    try {
        std::cin >> *a;
        if (*a == 0) {
            std::cout << "Incorrect coef a";
            return false;
        }
        std::cin >> *b;
        std::cin >> *c;
    }
    catch (const std::istream::failure& ex) {
        std::cerr << "Failed to read coef: " << ex.what() << "\n";
    }

    return true;

}

void print_roots(const double root1, const double root2, const bool has_root) {
    if (has_root && root1 == root2) {
        std::cout << root2 << "\n";
    }
    else if (has_root) {
        std::cout << root1 << " " << root2 << "\n";
    }
    else {
        std::cout << "No real roots\n";
    }

}

bool solve_problem(const double a, const double b, const double c, double* root1, double* root2) {
    double discriminant = b * b - 4 * a * c;

    if (discriminant >= 0) {
        *root1 = (-b + sqrt(discriminant)) / (2 * a);
        *root2 = (-b - sqrt(discriminant)) / (2 * a);
        return true;
    }
    return false;
}





int main()
{
    double a, b, c;
    if (get_coef(&a, &b, &c)) {
        double root1, root2;
        bool has_root = solve_problem(a, b, c, &root1, &root2);
        print_roots(root1, root2, has_root);
    }
}
