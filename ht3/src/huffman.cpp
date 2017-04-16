#include "huffman.h"
#include "double_queue.h"

#include <fstream>
#include <iostream>

#include <cstring>
#include <vector>
#include <queue>

#include <algorithm>


Archiver::Archiver(std::string in, std::string out) : in_(in), out_(out) {
    input_.open(in.c_str());
    if (!input_)
        std::cout << "No such file\n";

    output_.open(out.c_str());
}


Archiver::~Archiver() {
    input_.close();
    output_.close();
}


void Archiver::encode() {
    get_encode_table_();
    encode_text_();    
}


void Archiver::decode() {
//    get_codes_();
}


void Archiver::encode_text_() {
    input_.close();
    input_.open(in_.c_str());
    
    BinaryPrinter printer(&output_);    
    char c;
    while ((c = input_.get()) != EOF) {
        printer.print(codes_[(unsigned char)c]); 
        printer.print(" ");
    }           
}


HuffmanArchiver::~HuffmanArchiver() {
    delete tree_;
}


void HuffmanArchiver::get_encode_table_() {
    get_symbols_freq_();
    build_tree_();

    for (size_t i = 0; i < leafes.size(); i++)
        get_code_(leafes[i]);
}


void HuffmanArchiver::get_symbols_freq_() {
    char c;
    std::fill(symbol_freq_, symbol_freq_ + CSIZE, 0);
    while ((c = input_.get()) != EOF)
        symbol_freq_[(unsigned char)c]++;
}


void HuffmanArchiver::build_tree_() {
    for (size_t i = 0; i < CSIZE; i++)    
        if (symbol_freq_[i] > 0)
            leafes.push_back(new HuffmanNode(i, symbol_freq_[i]));
  
    double_queue<HuffmanNode*> dq;
    sort(leafes.begin(), leafes.end());
    for (size_t i = 0; i < leafes.size(); i++)
        dq.init_push(leafes[i]);

    tree_ = new HuffmanTree(dq);
}


void HuffmanArchiver::get_code_(HuffmanNode* node) {
    unsigned char name = node->get_name();
    codes_[name] = "";
    while (node->get_parent() != NULL) {
        codes_[name] += node->get_path();
        node = node->get_parent();
    }
};


HuffmanTree::HuffmanTree(double_queue <HuffmanNode*> dq) {
    while (!dq.empty()) {    
        HuffmanNode* left;                                   
        left = dq.pop();
        if (dq.empty()) {
            root = left;
            return;
        }

        HuffmanNode* right;
        right = dq.pop();
    
        HuffmanNode* node = new HuffmanNode(left, right);
        left->set_parent(node, '0');
        right->set_parent(node, '1');
        dq.push(node);
    }
}


HuffmanNode::~HuffmanNode() {
    delete left_;
    delete right_;
}

