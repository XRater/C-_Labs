#pragma once

#include <fstream>
#include <iostream>

#include <cstring>
#include <vector>
#include <queue>

const size_t SYMB_NUMB = 256;
const size_t CBITS = 8;


class Archiver {
    
    friend class HuffmanTest;

public:
    Archiver(std::istream* in = &std::cin, std::ostream* out = &std::cout) : input_(in), output_(out)
         {std::fill(codes_, codes_ + SYMB_NUMB, "");}
    
    void encode();
    void decode(); 

protected:
    
    void virtual get_encode_table_() = 0;         
    size_t virtual print_tech_info_() const = 0;   //returns number of printed baits
    
    std::pair<size_t, size_t> encode_text_() const; //returns number of read baits and number of printed baits
    void print_stat_(size_t read_size, size_t encoded_size, size_t added_size) const;    
    
    std::istream* input_;
    std::ostream* output_;
    
    std::string codes_[SYMB_NUMB];
};


class BinaryPrinter {

    friend class ReadPrintTest;    
    
public:
    BinaryPrinter(std::ostream* out = &std::cout) : printed_chars_(0), out(out) {};
    
    void accum(const std::string& s);
    void accum(const char c) {std::string s = ""; s += c; accum(s);} //not used
    void flush();
    
    size_t get_printed_chars() {return printed_chars_;}
private:
    const static size_t BUFF_SIZE = CBITS * 1e7;

    void print_char_(size_t index);

    size_t printed_chars_;

    std::string buff_;
    std::ostream* out;
};


