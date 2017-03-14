#include <matrix.h>
#include <fstream>
#include <iostream>

int get_reg(std::string s) {
    return (s[1] - '0');
}

class Interpretator {
public:
    Interpretator() {;}
    int get_cmd();
private:
    Interpretator(const Interpretator& other);
    Interpretator& operator=(const Interpretator);

    Matrix vars_[10];
};


int Interpretator::get_cmd() {
    std::string cmd;
    std::cin >> cmd;
    try {
        if (cmd == "load") {
            std::string reg;
            std::string filename;           
            std::ifstream fin;
            std::cin >> reg >> filename;
            fin.open(filename.c_str());
            fin >> vars_[get_reg(reg)];
         }
        else if (cmd == "print") {
            std::string reg;
            std::cin >> reg;
            std::cout << vars_[get_reg(reg)];
        }
        else if(cmd == "add") {
            std::string reg1, reg2;
            std::cin >> reg1 >> reg2;
            vars_[get_reg(reg1)] += vars_[get_reg(reg2)];
        }
        else if(cmd == "mul") {
            std::string reg1, reg2;
            std::cin >> reg1 >> reg2;
            vars_[get_reg(reg1)] *= vars_[get_reg(reg2)];
        }
        else if (cmd == "elem") {
            std::string reg;
            int i, j;
            std::cin >> reg >> i >> j;
            std::cout << vars_[get_reg(reg)].get(i, j);
        }        
        else if (cmd == "exit")
            return 1;
        else 
            std::cout << "Wrong command\n";
    }      
    catch(MatrixExeption& e) {
        e.inform();
    }
    return 0;
}


int main() {
    Interpretator I;
    while(true) {
        if (I.get_cmd() != 0)
            break;
    }
/*
    std::ifstream fin;
    fin.open("in.txt", std::ifstream::binary);
    Matrix a(2, 3);
    Matrix b(3, 4);
    fin >> a;
    
    std::ifstream fin1;
    fin1.open("in1.txt", std::ifstream::binary);
    fin1 >> b;
    
    a *= b;
    std::cout << a;*/
}
