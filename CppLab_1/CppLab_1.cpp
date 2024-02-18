#include <iostream>
#include <vector>

bool get_coef(double* a, double* b, double* c) {
    std::cin >> *a;
    std::cin >> *b;
    if (*a == 0 && *b == 0) {
        std::cout << "Incorrect coefs";
        return false;
    }
    std::cin >> *c;

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
    if  (a == 0) {
        (*roots).push_back(-c / b);
        return;
    }
    else if (discriminant == 0) {
        (*roots).push_back(-b / (2 * a));
        return;
    }
    else if (discriminant > 0) {
        (*roots).push_back((-b + sqrt(discriminant)) / (2 * a));
        (*roots).push_back((-b - sqrt(discriminant)) / (2 * a));
        return;
    }
}


void solution() {
    double a, b, c;
    if (get_coef(&a, &b, &c)) {
        std::vector<double> roots;
        find_roots(a, b, c, &roots);
        print_roots(&roots);
    }
}


int main()
{
    solution();
}
