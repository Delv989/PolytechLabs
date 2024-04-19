#include <iostream>
#include <vector>
#include <limits>
#include <fstream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <queue>





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
    void operator=(const Equation& equation) {
        this->a = equation.a;
        this->b = equation.b;
        this->c = equation.c;
    }
};

class Answer {
public:
    Equation* equation;
    std::vector<double>* roots;
    std::string name_student;
    Answer(Equation eq, std::vector<double>* in_roots, std::string name) {
        equation = new Equation(eq.a, eq.b, eq.c);
        roots = in_roots;
        name_student = name;
    }
};




class Student {
public:
	std::string name;
    virtual void solve_equation(Equation equation, std::vector<double>* roots) {}
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
    void solve_equation(Equation equation, std::vector<double>* roots) {
        equation.find_roots(roots);
        return;
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
    bool check_answer(Equation* equation, std::vector<double>* roots) {
        std::vector<double> right_roots;
        equation->find_roots(&right_roots);
        if (right_roots.size() != roots->size())
            return false;
        for (int i = 0; i < roots->size(); i++) {
            if (abs(( * roots)[i] - right_roots[i]) > std::numeric_limits<double>::epsilon())
                return false;
        }
        return true;
    }
    void check_test(std::queue<Answer*>* answers_student) {
        while (!answers_student->empty()) {
            Answer* ans = answers_student->front();
            answers_student->pop();
            if (progress_table.find(ans->name_student) == progress_table.end()) {
                progress_table[ans->name_student] = 0;
            }
            if (check_answer(ans->equation, ans->roots)) {
                progress_table[ans->name_student]++;
            }
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


void solve_test(Student* student, std::ifstream& in, std::queue<Answer*>* out) {
    in.clear();
    in.seekg(0, std::ios::beg);
    if (in.is_open()) {
        double a, b, c;
        while (in >> a >> b >> c) {
            Equation* equation = new Equation(a, b, c);
            std::vector<double>* roots = new std::vector<double>;
            student->solve_equation(*equation, roots);
            out->push(new Answer(*equation, roots, student->name));
        }
    }
}

int main() {
    srand(time(0));
    std::vector<Student*> group = {new AverageStudent("average"), new GoodStudent("good"), new BadStudent("bad")};
    std::ifstream in("input_students.txt");
    std::queue<Answer*> all_answers;
    for (Student* student : group) {
        solve_test(student, in, &all_answers);
    }
    in.close();

    Teacher* t = new Teacher("teacher");
    std::ofstream out("output_teacher.txt");
    t->check_test(&all_answers);
    t->print_progress_table(out);

    out.close();
}
