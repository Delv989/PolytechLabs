#include <iostream>
#include <vector>
#include <limits>

bool get_coef(double* a, double* b, double* c) {
    std::cin >> *a;
    std::cin >> *b;
    std::cin >> *c;
    if (a == NULL || b == NULL || c == NULL)
        return false;

    if (*a < std::numeric_limits<double>::epsilon() && *b < std::numeric_limits<double>::epsilon()) 
        return false;
    
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
    double discriminant = b * b - 4 * a * c;
    if  (a < std::numeric_limits<double>::epsilon()) {
        (*roots).push_back(-c / b);
        return;
    }
    else if (discriminant < std::numeric_limits<double>::epsilon()) {
        (*roots).push_back(-b / (2 * a));
        return;
    }
    else if (discriminant > 0) {
        (*roots).push_back((-b + sqrt(discriminant)) / (2 * a));
        (*roots).push_back((-b - sqrt(discriminant)) / (2 * a));
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
    else {
        std::cout << "Incorrect coef\n";
    }
}
