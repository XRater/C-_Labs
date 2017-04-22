#include "initializer.h"
#include "huffman.h"

Initializer::Initializer(int argc, char** const argv) : mode_(-1), input_(""), output_("") {
    if (argc != 6)
        throw HuffmanException("Wrong arguments number\n"); 
    
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-c"))
            if (mode_ == -1)
                mode_ = 0;
            else 
                throw HuffmanException("Incorrect mode format\n");
            
        else if (!strcmp(argv[i], "-u"))
            if (mode_ == -1)
                mode_ = 1;
            else
                throw HuffmanException("Incorrect mode format\n");
        
        else if (!strcmp(argv[i], "-f") || !strcmp(argv[i], "-file"))
            if (i < argc - 1 && input_ == "")
                input_ = argv[++i];
            else 
                throw HuffmanException("Incorrect input file\n");

        else if (!strcmp(argv[i], "-o"))               
            if (i < argc - 1 && output_ == "")
                output_ = argv[++i];
            else
                throw HuffmanException("Incorrect output file\n");
            
        else
            throw HuffmanException("Unknown argument\n");
    }
} 


void Initializer::run() const {
    std::ifstream in;
    in.open(input_.c_str());
    if (!in)
        throw HuffmanException("No such file\n");
    std::ofstream out;
    out.open(output_.c_str());
    
    HuffmanArchiver Arc(&in, &out);
    mode_ == 0 ? Arc.encode() : Arc.decode();

    in.close();
    out.close();
}

