#include "huffman.h"

#include <queue>
#include <iostream>


HuffmanTree::HuffmanTree(size_t* symbol_freq) { //NO TESTS
    get_leafes_(symbol_freq);
    
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, Comp_ptr <HuffmanNode*> > pq;
    for (size_t i = 0; i < leafes.size(); i++)
        pq.push(leafes[i]);
    
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


void HuffmanTree::get_leafes_(size_t* symbol_freq) { //OK
    for (size_t i = 0; i < SYMB_NUMB; i++)    
        if (symbol_freq[i] > 0)
            leafes.push_back(new HuffmanNode(i, symbol_freq[i]));
}


//----------------------------------------------------------------------------------------------------------------------------


void HuffmanArchiver::get_encode_table_() { //No need in tests
    size_t symbol_freq[SYMB_NUMB];
        
    get_symbols_freq_(symbol_freq);
    HuffmanTree* tree = new HuffmanTree(symbol_freq);

    set_codes_(tree);    
    
    delete tree;
}


void HuffmanArchiver::get_symbols_freq_(size_t* symbol_freq) { //OK
    std::fill(symbol_freq, symbol_freq + SYMB_NUMB, 0); 
       
    char buffer[BUFF_SIZE];
    while (true) {
        input_->read(buffer, sizeof(buffer));
        for (int i = 0; i < input_->gcount(); i++)
            symbol_freq[static_cast<unsigned char> (buffer[i])]++;
        if (input_->gcount() == 0)
            break;    
    }
}

void HuffmanArchiver::set_codes_(const HuffmanTree* tree) { //OK
    for (size_t i = 0; i < tree->leafes.size(); i++)
        set_code_(tree->leafes[i]);
}


std::string HuffmanArchiver::set_code_(const HuffmanNode* node) {  //OK
    unsigned char name = node->get_name();
    codes_[name] = "";

    if (node->get_parent() == NULL) {
        codes_[name] = "0";
        return "0";    
    }
    
    while (node->get_parent() != NULL) {
        codes_[name] = node->get_path() + codes_[name];
        node = node->get_parent();
    }
    
    return codes_[name];
}


size_t HuffmanArchiver::print_tech_info_() const {
    std::vector <int> notNull;
    for (size_t i = 0; i < SYMB_NUMB; i++)
        if (codes_[i] != "")
            notNull.push_back(i);
    
    
                
    return notNull.size();
}


