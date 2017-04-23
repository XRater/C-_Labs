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
    std::fill(freq_, freq_ + SYMB_NUMB, 0); 
       
    char buffer[BUFF_SIZE];
    while (true) {
        input_->read(buffer, sizeof(buffer));
        for (int i = 0; i < input_->gcount(); i++) {
            symbol_freq[static_cast<unsigned char> (buffer[i])]++;
            freq_[static_cast<unsigned char> (buffer[i])]++;
        }
        if (input_->gcount() == 0)
            break;    
    }
}

void HuffmanArchiver::set_codes_(const HuffmanTree* tree) { //OK
    for (size_t i = 0; i < tree->leafes.size(); i++)
        codes_[tree->leafes[i]->get_name()] = set_code_(tree->leafes[i]);
}


std::string HuffmanArchiver::set_code_(const HuffmanNode* node) const {  //OK
    std::string code = "";

    if (node->get_parent() == NULL)
        return "0";    
    
    while (node->get_parent() != NULL) {
        code = node->get_path() + code;
        node = node->get_parent();
    }
    
    return code;
}


size_t HuffmanArchiver::print_tech_info_() const { //NO TESTS
    size_t printed_bits = 0;
    std::vector <unsigned char> notNull;

    for (size_t i = 0; i < SYMB_NUMB; i++)
        if (freq_[i] != 0)
            notNull.push_back(i);

    for (size_t i = 0; i < SYMB_NUMB; i++)
        printed_bits += freq_[i] * codes_[i].length(); 

    
    size_t size = notNull.size();
    output_->write((char*) &size, sizeof(size_t));
    for (size_t i = 0; i < notNull.size(); i++) {
        output_->write((char*) &notNull[i], sizeof(char));
        output_->write((char*) &freq_[notNull[i]], sizeof(size_t));                    
    }            

    output_->write((char*) &printed_bits, sizeof(size_t));
    return size * (sizeof(size_t) + sizeof(char)) + sizeof(size_t);
}


//--------------------------------------------------------------------------------------------
//Decoder

void HuffmanArchiver::decode() const { //NO TESTS
    size_t symbol_freq[SYMB_NUMB];
    read_symbols_freq_(symbol_freq);
        
    HuffmanTree* tree = new HuffmanTree(symbol_freq);    

    decode_text_(tree);
}


void HuffmanArchiver::read_symbols_freq_(size_t* symbols_freq) const { //NO TESTS
    std::fill(symbols_freq, symbols_freq + SYMB_NUMB, 0);
   
    size_t notNull = 0;
    input_->read((char*) &notNull, sizeof(size_t));
    
    unsigned char symbol;
    size_t symb_freq;
    for (size_t i = 0; i < notNull; i++) {
        input_->read((char*) &symbol, sizeof(char));
        input_->read((char*) &symb_freq, sizeof(size_t));
        symbols_freq[symbol] = symb_freq;
    }
}


void HuffmanArchiver::decode_text_(const HuffmanTree* tree) const { //NO TESTS
    size_t bit_num;
    input_->read((char*) &bit_num, sizeof(size_t));
  
    BinaryReader reader(input_);
    
    for (size_t i = 0; i < bit_num;) {
        HuffmanNode* node = tree->root;
        for (; node->not_leafe(); node = node->move_down(reader.readBit()), i++)
            if (node == NULL)
                throw HuffmanException("ERROR: Not possible to decode");
        char name = node->get_name(); 
        output_->write((char*) &name, sizeof(char));            
    }
    
}

