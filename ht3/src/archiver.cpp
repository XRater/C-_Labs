#include "archiver.h"

#include <fstream>
#include <iostream>

#include <cstring>
#include <vector>
#include <queue>

#include <algorithm>


void Archiver::encode() {  //No need in tests
    get_encode_table_();
    
    std::pair<size_t, size_t> inf;
    inf = encode_text_();    
    
    size_t added_inf;
    added_inf = print_tech_info_();
    
    print_stat_(inf.first, inf.second, added_inf);
}


void Archiver::decode() {
//    get_codes_();
}


std::pair<size_t, size_t> Archiver::encode_text_() const{ //OK
    input_->clear();
    input_->seekg(0);
    
    size_t baits_read = 0, baits_printed = 0;
    
    BinaryPrinter printer(output_);    
    char buffer[1000];
    while (true) {
        input_->read(buffer, sizeof(buffer));
        for (int i = 0; i < input_->gcount(); i++)
            printer.accum(codes_[(unsigned char) buffer[i]]), baits_read++; 
        if (input_->gcount() == 0)
            break;    
    }

    printer.flush();
    baits_printed = printer.get_printed_chars();   
    
    return std::make_pair(baits_read, baits_printed);
}


void Archiver::print_stat_(size_t file_size, size_t encoded_size, size_t added_size) const { //No need in tests
    std::cout << file_size << '\n' << encoded_size << '\n' << added_size;
}


//--------------------------------------------------------------------------------------------------------
//BinaryPrinter

void BinaryPrinter::accum(const std::string& s) { //OK
    for (size_t i = 0; i < s.length(); i++)
        buff_.push_back(s[i]);
    
    if (buff_.size() > BUFF_SIZE)
        flush();
}


void BinaryPrinter::flush() { //OK
    while (buff_.size() % CBITS != 0)
        buff_.push_back('0');
        
    for (size_t i = 0; i < buff_.size(); i += CBITS)
        print_char_(i);       

    buff_.clear();
}


void BinaryPrinter::print_char_(size_t index) { //OK
    unsigned char c = 0;
    for (size_t i = index; i < index + CBITS; i++)
        c = c * 2 + (buff_[i] - '0');
    *out << c;        
    printed_chars_++;
}


