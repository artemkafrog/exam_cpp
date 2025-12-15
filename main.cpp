#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <windows.h>
using namespace std;

class Employee 
{
private:
    string name;
    int id;
    double salary;

public:
    Employee(string name_in, int id_in, double salary_in) : name(name_in), id(id_in), salary(salary_in) {}
    string getName() const { return name; }
    int getId() const { return id; }
    virtual double getSalary() const { return salary; }
    void setSalary(double newSalary) { salary = newSalary; }
};

bool isValidEmployeeData(const string& name, int id, double salary) 
{
    if (name.empty()) 
    {
        cout << "Имя пустое" << endl;
        return false;
    }
    if (id <= 0) 
    {
        cout << "Айди неположительное" << endl;
        return false;
    }
    if (salary < 0) 
    {
        cout << "Отрицательная зарплата" << endl;
        return false;
    }
    return true;
}

void saveToFile(const Employee employees[], int size, const string& filename) 
{
    ofstream file(filename);
    for (int i = 0; i < size; i++) 
    {
        file << employees[i].getId() << " "
            << employees[i].getName() << " "
            << employees[i].getSalary() << endl;
    }
    file.close();
}

class Manager : public Employee 
{
private:
    string department;

public:
    Manager(string n, int i, double s, string d) : Employee(n, i, s), department(d) {}

    double getSalary() const override 
    { return Employee::getSalary() * 1.1; }
    string getDepartment() const { return department; }
};

Employee findEmployeeWithHighestSalary(const string& filename) 
{
    ifstream file(filename);
    string line;
    Employee highest_salary("", 0, 0);
    bool first = true;

    while (getline(file, line)) 
    {
        istringstream iss(line);
        int id;
        string name;
        double salary;

        if (iss >> id >> name >> salary) 
        {
            Employee emp(name, id, salary);
            if (first || emp.getSalary() > highest_salary.getSalary()) 
            {
                highest_salary = emp;
                first = false;
            }
        }
    }
    file.close();
    return highest_salary;
}

int main() 
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    vector<Employee> employees;
    const int size = 5;

    for (int i = 0; i < 3; i++) 
    {
        string name;
        int id;
        double salary;

        cout << "Введите имя: ";
        if (i>0) cin.ignore();
        getline(cin, name);
        cout << "Введите ID: ";
        cin >> id;
        cout << "Введите зарплату: ";
        cin >> salary;

        if (isValidEmployeeData(name, id, salary))
        {
            employees.emplace_back(name, id, salary);
        }
        else 
        {
            cout << "Данные неверны\n";
        }
    }

    for (const auto& emp : employees) 
    {
        cout << "ID: " << emp.getId() 
            << ", Name: " << emp.getName()
            << ", Salary: " << emp.getSalary() << endl;
    }

    /*if (!employees.empty()) 
    {
        saveToFile(employees.data(), employees.size(), "employees.txt");
    }*/
    saveToFile(employees.data(), employees.size(), "employees.txt"); 
    // по заданию наверное так, про обработку ниче не сказано
    

    vector<Employee*> ukemp(4);
    ukemp[0] = new Employee("Иван ФФФ", 404, 50000);
    ukemp[1] = new Employee("ИВАН ИИЫ", 505, 55000);
    ukemp[2] = new Manager("ИВА ННН", 812, 700000, "TikTok");
    ukemp[3] = new Manager("ИВ АНННН", 212, 7500, "Like");

    for (size_t i = 0; i < ukemp.size(); i++)
    {
        cout << "Сотрудник " << i + 1 << ", а его зарплата = "
            << ukemp[i]->getSalary() << endl;
    }

    Employee highest = findEmployeeWithHighestSalary("employees.txt");
    if (highest.getId() != 0)
    {
        cout << "Сотрудник с максимальной зарплатой:\n";
        cout << "ID: " << highest.getId()
            << ", Name: " << highest.getName()
            << ", Salary: " << highest.getSalary() << endl;
    }
    else cout << "Нет сотрудников";
    /*cout << "Сотрудник с максимальной зарплатой:\n";
    cout << "ID: " << highestPaid.getId()
        << ", Name: " << highestPaid.getName()
        << ", Salary: " << highestPaid.getSalary() << endl;*/
    // тут тоже хз, в хорошем случае первое надо, но второе, т.к в задании такого нет
    return 0;
}
