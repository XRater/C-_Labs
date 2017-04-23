#pragma once
#include "archiver.h"

#include <iostream>
#include <queue>
#include <cstdlib>

template <class T>
class Comp_ptr {
public:
    bool operator()(T first, T second) {return *first > *second;}
};


class HuffmanNode {
    
    friend class HuffmanTest;

public:
    HuffmanNode(unsigned char name = 0, size_t freq = 0) : name_(name), freq_(freq) {};
    HuffmanNode(HuffmanNode* left, HuffmanNode* right) : 
                    left_(left), right_(right), freq_(left->freq_ + right->freq_) {};
    
    ~HuffmanNode() {delete left_; delete right_;};

    bool operator >(const HuffmanNode& other) const {return freq_ > other.freq_;}

    void set_parent(HuffmanNode* p, char path) {parent_ = p; path_ = path;}

    unsigned char get_name() const {return name_;}
    char get_path() const {return path_;}    
    HuffmanNode* get_parent() const {return parent_;}    

    bool not_leafe() {return (left_ != NULL || right_ != NULL);}
    HuffmanNode* move_down(char path) {return (path == '0' ? left_ : right_);}

private:   
    HuffmanNode(const HuffmanNode& other);
    HuffmanNode& operator=(const HuffmanNode);

    HuffmanNode *left_ = NULL, *right_ = NULL;
    HuffmanNode *parent_ = NULL;    

    char path_;
    unsigned char name_;
    size_t freq_;
};


class HuffmanTree {
    
    friend class HuffmanTest;

public:
    HuffmanTree() {}
    HuffmanTree(size_t* symbol_freq);    
    
    ~HuffmanTree() {delete root;}

    HuffmanNode* root = NULL;

    std::vector <HuffmanNode*> leafes;
private:
    HuffmanTree(const HuffmanTree& other);
    HuffmanTree& operator=(const HuffmanTree);

    void get_leafes_(size_t* symbol_freq);
};


class HuffmanArchiver : public Archiver {
    
    friend class HuffmanTest;

public:
    HuffmanArchiver(std::istream* in = &std::cin, std::ostream* out = &std::cout) : Archiver(in, out)
        {std::fill(freq_, freq_ + SYMB_NUMB, 0);}
    
    void decode() const;
    
private:
    const static size_t BUFF_SIZE = 1e3;

    HuffmanArchiver(const HuffmanArchiver& other);
    HuffmanArchiver& operator=(const HuffmanArchiver);
    
    void get_encode_table_();
    
    size_t print_tech_info_() const;    
    void decode_text_(const HuffmanTree* tree) const;

    void get_symbols_freq_(size_t* symbol_freq);
    void read_symbols_freq_(size_t* symbol_freq) const;

    void set_codes_(const HuffmanTree* tree);
    std::string set_code_(const HuffmanNode* node) const;        

    size_t freq_[SYMB_NUMB];
};


