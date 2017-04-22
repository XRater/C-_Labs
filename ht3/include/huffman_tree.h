#pragma once
#include <iostream>
#include <queue>
#include <cstdlib>

template <class T>
class Comp_ptr {
public:
    bool operator()(T first, T second) {return *first > *second;}
};


class HuffmanNode {
public:
    HuffmanNode(unsigned char name = 0, size_t freq = 0) : name_(name), freq_(freq) {};
    HuffmanNode(HuffmanNode* left, HuffmanNode* right) : 
                    left_(left), right_(right), freq_(left->freq_ + right->freq_) {};
    ~HuffmanNode();

    bool operator >(const HuffmanNode& other) {return freq_ > other.freq_;}

    void set_parent(HuffmanNode* p, char path) {parent_ = p; path_ = path;}

    unsigned char get_name() {return name_;}
    char get_path() {return path_;}
    
    HuffmanNode* get_parent() {return parent_;}    

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
public:
    HuffmanTree() {};
    HuffmanTree(std::priority_queue <HuffmanNode*, std::vector<HuffmanNode*>, Comp_ptr <HuffmanNode*> > pq);

    ~HuffmanTree() {delete root;}

private:
    HuffmanTree(const HuffmanTree& other);
    HuffmanTree& operator=(const HuffmanTree);

    HuffmanNode* root = NULL;
    std::vector <HuffmanNode*> leafes;
};


class HuffmanArchiver : public Archiver {
public:
    HuffmanArchiver(std::string in, std::string out) : Archiver(in, out) {};
    ~HuffmanArchiver();
    
    void get_encode_table_();
    
private:
    HuffmanArchiver(const HuffmanArchiver& other);
    HuffmanArchiver& operator=(const HuffmanArchiver);
    
    HuffmanTree* build_tree_();

    void get_symbols_freq_(); //also counts file_size_
    void get_code_(HuffmanNode* node);    
        
    int symbol_freq_[CSIZE];
    
    std::vector <HuffmanNode*> leafes; //delete this field
    HuffmanTree* tree_ = NULL; 
};

