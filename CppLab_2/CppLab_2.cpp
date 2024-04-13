#include <iostream>
#include <vector>
#include <limits>
#include <fstream>

/*
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
};
*/

class Equation {
public:
    double a, b, c;

    bool is_equal_zero(double a) {
        return abs(a) < std::numeric_limits<double>::epsilon();
    }

    void find_roots(std::vector<double>* roots) {
        
        double discriminant = b * b - 4.0 * a * c;
        if (is_equal_zero(a)) {
            (* roots).push_back(-c / b);
            return;
        }
        else if (is_equal_zero(discriminant)) {
            (* roots).push_back(-b / (2.0 * a));
            return;
        }
        else if (discriminant > 0) {
            (*roots).push_back((-b + sqrt(discriminant)) / (2.0 * a));
            (*roots).push_back((-b - sqrt(discriminant)) / (2.0 * a));
            return;
        }
    }
    Equation(double in_a, double in_b, double in_c) {
        a = in_a;
        b = in_b;
        c = in_c;
    }
};



class Student {
public:
	std::string name;
};
class BadStudent : public Student {
public:
   void solve_equation(Equation equation, std::vector<double>* roots) {
        roots->push_back(0);
        return;
    }
    void solve_test(std::ifstream& in, std::ofstream& out) {
        if (in.is_open()) {
            double a, b, c;
            while (in >> a >> b >> c) {
                Equation* equation = new Equation(a, b, c);
                std::vector<double> roots;
                solve_equation(*equation, &roots);
                if (out.is_open()) {
                    for (double root : roots) {
                        out << root << " ";
                    }
                    out << "\n";
                }
            }
        }
    }
    BadStudent(std::string s) {
        name = s;
    }

};
class GoodStudent : public Student {
public:
    void solve_equation(Equation equation, std::vector<double>* roots) {
        equation.find_roots(roots);
        return;
    }
    void solve_test(std::ifstream& in, std::ofstream& out) {
        if (in.is_open()) {
            double a, b, c;
            while (in >> a >> b >> c) {
                Equation* equation = new Equation(a, b, c);
                std::vector<double> roots;
                solve_equation(*equation, &roots);
                if (out.is_open()) {
                    for (double root : roots) {
                        out << root << " ";
                    }
                    out << "\n";
                }
            }
        }
    }
    GoodStudent(std::string s) {
        name = s;
    }
};

class AverageStudent : public Student {
public:
    void solve_equation(Equation equation, std::vector<double>* roots) {
        double probability = 0.55;
        
        if ((double)rand() / (double)RAND_MAX < probability) {
            equation.find_roots(roots);
            return;
        }
        else {
            equation.find_roots(roots);
            roots->push_back(0);
            return;
        }
    }
    void solve_test(std::ifstream& in, std::ofstream& out) {
        if (in.is_open()) {
            double a, b, c;
            while (in >> a >> b >> c) {
                Equation* equation = new Equation(a, b, c);
                std::vector<double> roots;
                solve_equation(*equation, &roots);
                if (out.is_open()) {
                    for (double root : roots) {
                        out << root << " ";
                    }
                    out << "\n";
                }
            }
        }
    }
    AverageStudent(std::string s) {
        name = s;
    }
};

int main() {
    srand(time(0));
    AverageStudent* me = new AverageStudent("123");
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    me->solve_test(in, out);
}
