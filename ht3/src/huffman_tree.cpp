#include "huffman_tree.h"
#include "queue"
#include <iostream>

HuffmanTree::HuffmanTree(std::priority_queue <HuffmanNode*, std::vector<HuffmanNode*>, Comp_ptr <HuffmanNode*> > pq) {
    while (!pq.empty()) {    
        
        HuffmanNode* left;                                   
        left = pq.top();
        pq.pop();
        
        if (pq.empty()) {
            root = left;
            return;
        }

        HuffmanNode* right;
        right = pq.top();
        pq.pop();
    
        HuffmanNode* node = new HuffmanNode(left, right);
        left->set_parent(node, '0');
        right->set_parent(node, '1');
        pq.push(node);
    }
}


HuffmanNode::~HuffmanNode() {
    delete left_;
    delete right_;
}

HuffmanArchiver::~HuffmanArchiver() {
    delete tree_;
}


void HuffmanArchiver::get_encode_table_() {
    get_symbols_freq_();
    tree_ = build_tree_();

    for (size_t i = 0; i < leafes.size(); i++)
        get_code_(leafes[i]);
    
}


void HuffmanArchiver::get_symbols_freq_() {
    std::fill(symbol_freq_, symbol_freq_ + CSIZE, 0); 
       
    char buffer[1000];
    while (true) {
        input_.read(buffer, sizeof(buffer));
        for (int i = 0; i < input_.gcount(); i++)
            symbol_freq_[(unsigned char) buffer[i]]++, file_size_++;
        if (input_.gcount() == 0)
            break;    
    }
}


HuffmanTree* HuffmanArchiver::build_tree_() {
    for (size_t i = 0; i < CSIZE; i++)    
        if (symbol_freq_[i] > 0)
            leafes.push_back(new HuffmanNode(i, symbol_freq_[i]));
  
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, Comp_ptr <HuffmanNode*> > pq;
    for (size_t i = 0; i < leafes.size(); i++)
        pq.push(leafes[i]);

    return new HuffmanTree(pq);
}


void HuffmanArchiver::get_code_(HuffmanNode* node) {
    unsigned char name = node->get_name();
    codes_[name] = "";

    if (node->get_parent() == NULL) {
        codes_[name] = "0";
        return;    
    }
    while (node->get_parent() != NULL) {
        codes_[name] += node->get_path();
        node = node->get_parent();
    }
};

