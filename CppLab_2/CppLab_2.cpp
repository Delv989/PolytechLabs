#include <iostream>
#include <vector>
#include <limits>
#include <fstream>
#include <unordered_map>
#include <string>
#include <sstream>


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
    virtual void solve_equation(Equation equation, std::vector<double>* roots) {
        equation.find_roots(roots);
        return;
    }
};


class BadStudent : public Student {
public:
   void solve_equation(Equation equation, std::vector<double>* roots) {
        roots->push_back(0);
        return;
    }
    BadStudent(std::string s) {
        name = s;
    }

};


class GoodStudent : public Student {
public:
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
    AverageStudent(std::string s) {
        name = s;
    }
};


class Teacher {
public:
    std::string name;
    std::unordered_map<std::string, int> progress_table;
    bool check_answer(Equation equation, std::vector<double>* roots) {
        std::vector<double> right_roots;
        equation.find_roots(&right_roots);
        if (right_roots.size() != roots->size())
            return false;
        for (int i = 0; i < roots->size(); i++) {
            if (roots[i] != right_roots)
                return false;
        }
        return true;
    }
    void check_test(std::ifstream& in, std::ofstream& out) {
        std::string row;
        while (std::getline(in, row)) {
            std::stringstream line(row);
            double a, b, c;
            line >> a >> b >> c;
            Equation* equation = new Equation(a, b, c);
            std::string other;
            std::getline(in, other, '(');

            std::string solutions;
            std::getline(in, solutions, ')');
            std::stringstream ss(solutions);
            std::vector<double> roots;
            double root;
            while (ss >> root) {
                roots.push_back(root);
            }

            std::string other1;
            std::getline(in, other1, ' ');

            std::string student;
            std::getline(in, student);

            if (check_answer(*equation, &roots)) {
                if (progress_table.find(student) == progress_table.end()) {
                    progress_table[student] = 1;
                }
                else {
                    progress_table[student]++;
                }
            }
            else if (progress_table.find(student) == progress_table.end())
                progress_table[student] = 0;
        }
    }
    void print_progress_table(std::ofstream& out) {
        for (auto const& row : progress_table) {
            out << row.first << " " << row.second << "\n";
        }
    }
        
    Teacher(std::string s) {
        name = s;
    }
};


void solve_test(Student* student, std::ifstream& in, std::ofstream& out) {
    in.clear();
    in.seekg(0, std::ios::beg);
    if (in.is_open()) {
        double a, b, c;
        while (in >> a >> b >> c) {
            Equation* equation = new Equation(a, b, c);
            std::vector<double> roots;
            student->solve_equation(*equation, &roots);
            if (out.is_open()) {
                out << a << " " << b << " " << c << " ";
                out << "(";
                for (double root : roots) {
                    out << root << " ";
                }
                out << ") ";
                out << student->name;
                out << "\n";
            }
        }
    }
}

int main() {
    srand(time(0));
    Student* me = new AverageStudent("123");
    Student* he = new GoodStudent("456");
    std::ifstream in("input_students.txt");
    std::ofstream out("output_students.txt");
    solve_test(me, in, out);
    solve_test(he, in, out);
    Teacher* t = new Teacher("Veronika");
    in.close();
    out.close();
    std::ifstream in1("output_students.txt");
    std::ofstream out1("output_teacher.txt");
    t->check_test(in1, out1);
    t->print_progress_table(out1);
}
