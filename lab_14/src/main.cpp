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
    catch(MatrixException& e) {
        std::cout << e.what();
    }
    return 0;
}


int main() {
    Interpretator I;
    while(true) {
        if (I.get_cmd() != 0)
            break;
    }
}
