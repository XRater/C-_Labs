#include <cstring>
#include <iostream>
#include "huffman.h"
#include "double_queue.h" // FIX MAKEFILE

class Initializer {
public:
    Initializer(int argc, char** const argv);

    void run() {
        //Archiver A();
        //HuffmanArchiver A1();
        HuffmanArchiver Arc(input, output);
        mode == 0 ? Arc.encode() : Arc.decode();
    }
    
private:    
    int mode;
    std::string input;
    std::string output;
    
    Initializer(const Initializer& other);
    Initializer& operator=(const Initializer);
};

Initializer::Initializer(int argc, char** const argv) : mode(-1), input(""), output("") {
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-c"))
            if (mode == -1)
                mode = 0;
            else {
                std::cout << "Incorrect mode format\n";
                return;
            }
            
        else if (!strcmp(argv[i], "-u"))
            if (mode == -1)
                mode = 1;
            else {
                std::cout << "Incorrect mode format\n";
                return;
            }
        
        else if (!strcmp(argv[i], "-f") || !strcmp(argv[i], "-file"))
            if (i < argc - 1 && input == "")
                input = argv[++i];
            else {
                std::cout << "Incorrect input file\n";
                return;
            }

        else if (!strcmp(argv[i], "-o"))               
            if (i < argc - 1 && output == "")
                output = argv[++i];
            else {
                std::cout << "Incorrect output file\n";
                return;
            }
            
        else {
            std::cout << "Unknown argument\n";
            return;
        }
    }
    
    if (mode == -1) {
        std::cout << "No mode found\n";
        return;
    }
    if (input == "") {
        std::cout << "No input file found\n";
        return;
    }
    if (output == "") {
        std::cout << "No output file found\n";
        return;
    }
} 

int main(int argc, char** argv) {    
    Initializer init(argc, argv);        
    init.run();
    /*std::queue <int> q;
    int a;
    q.push(4);
    q.push(6);
    double_queue <int> dq(q); 
    dq.push(5);
    dq.push(3);
    while (!dq.empty()) {
        a = dq.pop();
        std::cout << a;
    }*/
    return 0;
}
