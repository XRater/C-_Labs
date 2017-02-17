#ifndef __LAB11_EMPLOYEES_H_INCLUDED
#define __LAB11_EMPLOYEES_H_INCLUDED

#include <stdint.h>
#include <iostream>
#include <fstream>

char* read_string(char*& dest);

class Employee {
public:
    virtual ~Employee() {
        std::cout << "Deleted\n";
        delete [] _name;    
    }
    virtual int salary() const = 0;
    virtual void read(std::istream& is) = 0;
    virtual void print(std::ostream& os) const = 0;
    
    virtual void save(std::ofstream& os) const = 0;
    virtual void load(std::ifstream& is) = 0;
    
    friend std::ostream& operator<<(std::ostream& os, const Employee& emp);
    friend std::istream& operator>>(std::istream& is, Employee& emp);
    friend std::ofstream& operator<<(std::ofstream& os, const Employee& emp);
    friend std::ifstream& operator>>(std::ifstream& is, Employee& emp);
protected:
    char* _name;
    int _name_length;
    int32_t _base_salary;
};


class Developer : public Employee {
public:
    int salary() const {
        int salary = _base_salary;
        if (_has_bonus) { salary += 1000; }
            return salary;
    }
    void read(std::istream& is);
    void print(std::ostream& os) const;    
    void load(std::ifstream& is);
    void save(std::ofstream& os) const;    
private:
    bool _has_bonus;
};


class SalesManager : public Employee {
public:
    int salary() const {
        return _base_salary + _sold_nm * _price * 0.01;
    }
    void read(std::istream& is);
    void print(std::ostream& os) const;    
    void load(std::ifstream& is);
    void save(std::ofstream& os) const;    
private:
    int32_t _sold_nm, _price;
};


class EmployeesArray {
public:
    EmployeesArray();
    ~EmployeesArray();
    void add(const Employee *e);
    int total_salary() const;
    
    void save(const char* filename) const;
    
    friend std::ostream& operator<<(std::ostream& os, const EmployeesArray& emp);
    friend std::ofstream& operator<<(std::ofstream& os, const EmployeesArray& emp);
    friend std::ifstream& operator>>(std::ifstream& is, EmployeesArray& emp);
private:
    int _capacity;  
    int _size;
    const Employee** _employees;
};

#endif
