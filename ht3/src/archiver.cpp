#include "archiver.h"

#include <fstream>
#include <iostream>

#include <cstring>
#include <vector>
#include <queue>

#include <algorithm>


void Archiver::encode() {  //No need in tests
    get_encode_table_();
    
    size_t added_inf;
    added_inf = print_tech_info_() + sizeof(size_t); // size_t for number of written bits

    std::pair<size_t, size_t> inf;
    inf = encode_text_();    
    print_stat_(inf.first, inf.second, added_inf);
}


std::pair<size_t, size_t> Archiver::encode_text_() const{ //OK
    input_->clear();
    input_->seekg(0);    
    
    int32_t bytes_read = 0, bytes_printed = 0;
        
    BinaryPrinter printer(output_);    
    char buffer[BUFF_SIZE];
    while (true) {
        input_->read(buffer, sizeof(buffer));
        for (int i = 0; i < input_->gcount(); i++)
            printer.accum(codes_[(unsigned char) buffer[i]]), bytes_read++;
        if (input_->gcount() == 0)
            break;    
    }

    printer.flush();
    bytes_printed = printer.get_printed_chars();   
        
    return std::make_pair(bytes_read, bytes_printed);
}


void Archiver::print_stat_(size_t file_size, size_t encoded_size, size_t added_size) const { //No need in tests
    std::cout << file_size << '\n' << encoded_size << '\n' << added_size;
}


//--------------------------------------------------------------------------------------------------------
//BinaryPrinterReader

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
    *out_ << c;        
    printed_chars_++;
}

char BinaryReader::readBit() {
    if (buff_.size() == 0)
        read_buff_();
            
    if (buff_.size() == 0)
        throw(HuffmanException("Not possible to decode"));            

    char bit = buff_.front();
    buff_.pop();
    return bit;
}

void BinaryReader::read_buff_() {
    char buffer[BUFF_SIZE];
    in_->read(buffer, sizeof(buffer));    
    
    for (int i = 0; i < in_->gcount(); i++)
        bit_split_(buffer[i]);
}


void BinaryReader::bit_split_(char byte) {
    char bits[CBITS];
    
    for (size_t i = 0; i < CBITS; i++) {
        bits[i] = (byte & 1) + '0'; 
        byte = byte >> 1;        
    }
    
    for (int i = CBITS - 1; i >= 0; i--)
        buff_.push(bits[i]);
}
