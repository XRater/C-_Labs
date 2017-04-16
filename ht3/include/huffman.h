#pragma once
#include "double_queue.h"

#include <fstream>
#include <iostream>

#include <cstring>
#include <vector>
#include <queue>

const int CSIZE = 256;

class Archiver {
public:
    Archiver(std::string in, std::string out);
    ~Archiver();

    
    void encode();
    void decode();    

protected:
    
    void virtual get_encode_table_() = 0;
    
    void encode_text_();

    std::string in_, out_;
    std::ifstream input_;
    std::ofstream output_;                
    
    std::string codes_[CSIZE];
};


class HuffmanNode {
public:
    HuffmanNode(char name = 0, int freq = 0) : name_(name), freq_(freq) {};
    HuffmanNode(HuffmanNode* left, HuffmanNode* right) : left_(left), right_(right) {};
    ~HuffmanNode();

    bool operator <(const HuffmanNode& other) {return freq_ < other.freq_;}

    void set_parent(HuffmanNode* p, char path) {parent_ = p; path_ = path;}

    int get_name() {return name_;}
    int get_path() {return path_;}
    
    HuffmanNode* get_parent() {return parent_;}    
private:    
    HuffmanNode(const HuffmanNode& other);
    HuffmanNode& operator=(const HuffmanNode);

    HuffmanNode *left_ = NULL, *right_ = NULL;
    HuffmanNode *parent_ = NULL;    

    char path_;
    char name_;
    int freq_;
};


class HuffmanTree {
public:
    HuffmanTree() {};
    HuffmanTree(double_queue <HuffmanNode*> dq);

    ~HuffmanTree() {delete root;}
private:
    HuffmanTree(const HuffmanTree& other);
    HuffmanTree& operator=(const HuffmanTree);

    HuffmanNode* root = NULL;
};


class HuffmanArchiver : public Archiver {
public:
    HuffmanArchiver(std::string in, std::string out) : Archiver(in, out) {};
    ~HuffmanArchiver();
    
    void get_encode_table_();
    
private:
    HuffmanArchiver(const HuffmanArchiver& other);
    HuffmanArchiver& operator=(const HuffmanArchiver);
    
    void build_tree_();

    void get_symbols_freq_();
    void get_code_(HuffmanNode* node);    
        
    int symbol_freq_[CSIZE];
    
    std::vector <HuffmanNode*> leafes;
    HuffmanTree* tree_ = NULL; 
};


class BinaryPrinter {
public:
    BinaryPrinter(std::ofstream* out) : out(out) {};
    
    void print(std::string s) {*out << s; std::cout << s;}
private:
    std::ofstream* out;
};


