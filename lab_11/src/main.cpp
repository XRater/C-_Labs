
#include <cstdio>
#include <cstring>
#include <iostream>
#include <fstream>
#include <employees.h>


int main() {
    char* cmd = new char[10];
    int err = 1;
    EmployeesArray array;
    while (err != 0) {
        err = scanf("%s", cmd);            
        if (strcmp(cmd, "exit") == 0) {
            err = 0;
        }    

        else if (strcmp(cmd, "list") == 0)
            std::cout << array;

        else if (strcmp(cmd, "add") == 0) {
            int type;
            std::cin >> type;
            Employee* emp = NULL;
            if (type == 1)
                emp = new Developer;
            if (type == 2)
                emp = new SalesManager;
            std::cin >> *emp;
            array.add(emp);
        }

        else if (strcmp(cmd, "save") == 0) {
            char* filename;
            read_string(filename);
            std::ofstream fout;
            fout.open(filename, std::ofstream::binary);
            fout << array;
            delete [] filename;
            fout.close();
        }  
   
        else if (strcmp(cmd, "load") == 0) {
            char* filename;
            read_string(filename);
            std::ifstream fin;
            fin.open(filename, std::ifstream::binary);
            fin >> array;
            delete [] filename;
            fin.close();
        }        
        else
            printf("Unknown command\n");
    }
    delete [] cmd;
    return 0;
}
