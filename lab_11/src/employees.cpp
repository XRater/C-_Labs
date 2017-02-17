#include <employees.h>
#include <iostream>
#include <fstream>
#include <cstdio>

char* read_string(char*& dest) {
    int length = 2;
    dest = new char[length];
    int ptr = 0;
    char symbol = ' ';
    while (symbol == ' ' or symbol == '\n')
        symbol = getchar();
    while (symbol != ' ' and symbol != '\n' and symbol != '\0') {        
        dest[ptr++] = symbol;
        
        if (ptr == length - 1) {
            char* tmp = new char[length * 2];
            for (int i = 0; i < length - 1; i++)
                tmp[i] = dest[i];
            delete [] dest;
            dest = tmp;   
            length *= 2; 
        }
        symbol = getchar();
    }
    dest[ptr++] = '\0';
    return dest;
}

void print_string(const char* source, std::ofstream& os){    
    char symbol = *source;
    while (symbol != '\0') {
        os.write(&symbol, sizeof(char));
        symbol = *(++source);    
    }        
    os.write(&symbol, sizeof(char));
}

char* get_string(char*& dest, std::ifstream& is){    
    int length = 2;
    int ptr = 0;
    dest = new char[length];
    char symbol;
    is.read(&symbol, sizeof(char));
    //std::cout << symbol;
    while (symbol != '\0') {
        dest[ptr++] = symbol;
        
        if (ptr == length - 1) {
            char* tmp = new char[length * 2];
            for (int i = 0; i < length - 1; i++)
                tmp[i] = dest[i];
            delete [] dest;
            dest = tmp;   
            length *= 2; 
        }
        is.read(&symbol, sizeof(char));
      //  std::cout << symbol;
    }        
    dest[ptr++] = symbol;
    //std::cout << dest;
    return dest;
}

std::ostream& operator<<(std::ostream& os, const Employee& emp) {
    emp.print(os);   
    return os;
}

std::istream& operator>>(std::istream& is, Employee& emp) {
    emp.read(is);   
    return is;
}

std::ofstream& operator<<(std::ofstream& os, const Employee& emp) {
    //std::cout << "Hello";
    emp.save(os);   
    return os;
}

std::ifstream& operator>>(std::ifstream& is, Employee& emp) {
    emp.load(is);   
    return is;
}

std::ostream& operator<<(std::ostream& os, const EmployeesArray& arr) {
    for (int i = 0; i < arr._size; i++)
        os << i + 1 << ". " << *arr._employees[i];
    os << "== Total salary: " << arr.total_salary() << "\n\n";
    return os;
}

std::ofstream& operator<<(std::ofstream& os, const EmployeesArray& arr) {
    os.write((char*)&arr._size, sizeof(int));
    for (int i = 0; i < arr._size; i++) {
        os << *arr._employees[i];            
    }
    return os;
}

std::ifstream& operator>>(std::ifstream& is, EmployeesArray& arr) {
    int size;
    is.read((char*)&size, sizeof(int));
    for (int i = 0; i < size; i++) {
        int type;
        is.read((char*)&type, sizeof(int));
        Employee* emp = NULL;
        if (type == 1)
            emp = new Developer;
        if (type == 2)      
            emp = new SalesManager;
        emp->load(is);
        arr.add(emp);
    }
    return is;
}

void Developer::print(std::ostream& os) const {
    os << "Developer\nName: " << _name << "\nBase Salary: " << _base_salary << "\nHas bonus:";
    if (_has_bonus)
        os << " +\n";
    else
        os << " -\n"; 
}

void Developer::read(std::istream& is) {
    read_string(_name);
    is >> _base_salary >> _has_bonus;     
}

void Developer::save(std::ofstream& os) const{
    int type = 1;
    os.write((char*)&type, sizeof(int));
    print_string(_name, os);
    os.write((char*)&_base_salary, sizeof(int));
    os.write((char*)&_has_bonus, sizeof(bool));
}

void Developer::load(std::ifstream& is) {
    get_string(_name, is);
    is.read((char*) &_base_salary, sizeof(int));
    is.read((char*) &_has_bonus, sizeof(bool));
}

void SalesManager::print(std::ostream& os) const {
    os << "Sales Manager\nName: " << _name << "\nBase Salary: " << _base_salary;
    os << "\nSold items: " << _sold_nm << "\nItem price:" << _price << '\n'; 
}

void SalesManager::read(std::istream& is) {
    read_string(_name);
    is >> _base_salary >> _sold_nm >> _price;
}

void SalesManager::save(std::ofstream& os) const{
    int type = 2;
    os.write((char*)&type, sizeof(int));
    print_string(_name, os);
    os.write((char*)&_base_salary, sizeof(int));
    os.write((char*)&_sold_nm, sizeof(int));
    os.write((char*)&_price, sizeof(int));
}

void SalesManager::load(std::ifstream& is) {
    get_string(_name, is);
    is.read((char*) &_base_salary, sizeof(int));
    is.read((char*) &_sold_nm, sizeof(int));
    is.read((char*) &_price, sizeof(int));
}

EmployeesArray::EmployeesArray() {
    _capacity = 1;
    _size = 0;
    _employees = new const Employee*[_capacity];    
}

EmployeesArray::~EmployeesArray() {
    for (int i = 0; i < _size; i++) 
        delete _employees[i];
    std::cout << "Delete Array";
    delete [] _employees;
}

void EmployeesArray::add(const Employee* emp) {
    _employees[_size++] = emp;
    if (_size == _capacity) {
        const Employee** tmp = new const Employee*[_capacity * 2];
        for (int i = 0; i < _capacity; i++)
            tmp[i] = _employees[i];            
        delete [] _employees;
        _employees = tmp;
        _capacity *= 2;
    }     
}

int EmployeesArray::total_salary() const{
    int result = 0;
    for (int i = 0; i < _size; i++)
        result += _employees[i]->salary();
    return result;       
}

void EmployeesArray::save(const char* filename) const{

}
