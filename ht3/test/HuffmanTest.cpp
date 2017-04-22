#include <sstream>

#include "HuffmanTest.h"

#define DO_CHECK(EXPR) Test::check(EXPR, __FUNCTION__, __FILE__, __LINE__); 


void HuffmanTest::runAllTests() {
    test_get_symbols_freq();        
    test_get_leafes();
    test_set_codes();
    
    test_encode_text();
}


void HuffmanTest::test_get_symbols_freq() {
    bool flag = 0;
    size_t array[SYMB_NUMB];
    size_t ans[SYMB_NUMB];

//JUST SMT    
    std::stringstream in1("aaaaaa");
    HuffmanArchiver arc1(&in1, &std::cout);
    flag = 0;
    arc1.get_symbols_freq_(array);
    std::fill(ans, ans + SYMB_NUMB, 0);
    ans['a'] = 6;
    for (size_t i = 0; i < SYMB_NUMB; i++)
        flag |= array[i] != ans[i];
    DO_CHECK(flag == 0);

//EMTY TEST
    std::stringstream in2("");
    HuffmanArchiver arc2(&in2, &std::cout);
    flag = 0;
    arc2.get_symbols_freq_(array);
    std::fill(ans, ans + SYMB_NUMB, 0);
    for (size_t i = 0; i < SYMB_NUMB; i++)
        flag |= array[i] != ans[i];
    DO_CHECK(flag == 0);

//SIDE SYMBOLS
    std::string s;
    s.resize(3);
    s[0] = 0, s[1] = SYMB_NUMB - 1, s[2] = 0; 
    std::stringstream in3(s);
    HuffmanArchiver arc3(&in3, &std::cout);
    flag = 0;
    arc3.get_symbols_freq_(array);
    std::fill(ans, ans + SYMB_NUMB, 0);
    ans[0] = 2;
    ans[SYMB_NUMB - 1] = 1;
    for (size_t i = 0; i < SYMB_NUMB; i++)
        flag |= array[i] != ans[i];
    DO_CHECK(flag == 0);

}


void HuffmanTest::test_get_leafes() {
    bool flag = 0;
    size_t array[SYMB_NUMB];
    
    std::fill(array, array + SYMB_NUMB, 0);
    HuffmanTree* tree = new HuffmanTree(); 
    tree->get_leafes_(array);
    DO_CHECK(tree->leafes.size() == 0);
    delete tree;


    flag = 0;
    std::fill(array, array + SYMB_NUMB, 1);
    tree = new HuffmanTree(); 
    tree->get_leafes_(array);
    DO_CHECK(tree->leafes.size() == SYMB_NUMB);
    for (size_t i = 0; i < tree->leafes.size(); i++)
        flag |= (tree->leafes[i]->freq_ != 1);
    DO_CHECK(flag == 0);
    
    for (size_t i = 0; i < tree->leafes.size(); i++)
        delete tree->leafes[i];
    delete tree;


    flag = 0;
    std::fill(array, array + SYMB_NUMB, 0);
    array[8] = 67, array[0] = 15;
    tree = new HuffmanTree();
    tree->get_leafes_(array);
    DO_CHECK(tree->leafes.size() == 2);

    for (size_t i = 0; i < tree->leafes.size(); i++)
        delete tree->leafes[i];
    delete tree;
}


void HuffmanTest::test_set_codes() {
    bool flag = 0;
    size_t array[SYMB_NUMB];    
    
    HuffmanArchiver arc1;     
    std::fill(array, array + SYMB_NUMB, 0);
    array[5] = 1;
    HuffmanTree* tree = new HuffmanTree(array);   
    arc1.set_codes_(tree);   
    DO_CHECK(arc1.codes_[5] == "0");
    delete tree;
    
    HuffmanArchiver arc2;     
    std::fill(array, array + SYMB_NUMB, 0);
    array[0] = 1, array[1] = 9;
    tree = new HuffmanTree(array);   
    arc2.set_codes_(tree);   
    DO_CHECK(arc2.codes_[0] == "0");
    DO_CHECK(arc2.codes_[1] == "1");
    delete tree;
    
    HuffmanArchiver arc3;     
    std::fill(array, array + SYMB_NUMB, 0);
    array[1] = 1, array[2] = 9, array[3] = 2, array[4] = 4;
    tree = new HuffmanTree(array);
    arc3.set_codes_(tree);   
    DO_CHECK(arc3.codes_[1] == "000");
    DO_CHECK(arc3.codes_[2] == "1");
    DO_CHECK(arc3.codes_[3] == "001");
    DO_CHECK(arc3.codes_[4] == "01");
    delete tree;
    
    HuffmanArchiver arc4;     
    std::fill(array, array + SYMB_NUMB, 0);
    array[1] = 5, array[2] = 6, array[3] = 7, array[4] = 8;
    tree = new HuffmanTree(array);   
    arc4.set_codes_(tree);   
    DO_CHECK(arc4.codes_[1] == "00");
    DO_CHECK(arc4.codes_[2] == "01");
    DO_CHECK(arc4.codes_[3] == "10");
    DO_CHECK(arc4.codes_[4] == "11");
    delete tree;

    HuffmanArchiver arc5;     
    std::fill(array, array + SYMB_NUMB, 0);
    array[1] = 5, array[2] = 6, array[3] = 7, array[4] = 8, array[5] = 50;
    tree = new HuffmanTree(array);   
    arc5.set_codes_(tree);   
    DO_CHECK(arc5.codes_[1] == "000");
    DO_CHECK(arc5.codes_[2] == "001");
    DO_CHECK(arc5.codes_[3] == "010");
    DO_CHECK(arc5.codes_[4] == "011");
    DO_CHECK(arc5.codes_[5] == "1");
    delete tree;

    HuffmanArchiver arc6;     
    std::fill(array, array + SYMB_NUMB, 0);
    array[1] = 5, array[2] = 6, array[3] = 7, array[4] = 8, array[5] = 20;
    tree = new HuffmanTree(array);   
    arc6.set_codes_(tree);   
    DO_CHECK(arc6.codes_[1] == "100");
    DO_CHECK(arc6.codes_[2] == "101");
    DO_CHECK(arc6.codes_[3] == "110");
    DO_CHECK(arc6.codes_[4] == "111");
    DO_CHECK(arc6.codes_[5] == "0");
    delete tree;
}


void HuffmanTest::test_encode_text() {
    char* s = new char[20];

    std::stringstream in1("a 1ad");    
    std::stringstream out1;        
    HuffmanArchiver arc1(&in1, &out1);
    std::fill(arc1.codes_, arc1.codes_ + SYMB_NUMB, "!");        
    arc1.codes_['a'] = "00";
    arc1.codes_[' '] = "01"; //00011000
    arc1.codes_['1'] = "1";
    arc1.codes_['d'] = "";        
    std::pair<size_t, size_t> res;
    res = arc1.encode_text_();
    out1.read(s, 1);
    DO_CHECK(res.first == 5 && res.second == 1);
    DO_CHECK(s[0] == 24);   
       

    std::stringstream in2("abacaba");    
    std::stringstream out2;        
    HuffmanArchiver arc2(&in2, &out2);
    std::fill(arc2.codes_, arc2.codes_ + SYMB_NUMB, "!");        
    arc2.codes_['a'] = "10";
    arc2.codes_['b'] = "101"; //10101100 11010101 10
    arc2.codes_['c'] = "0110";
    res = arc2.encode_text_();
    out2.read(s, 3);
    DO_CHECK(res.first == 7 && res.second == 3);
    DO_CHECK(s[0] == -84 && s[1] == -43 && s[2] == -128);   

    std::stringstream in3("");    
    std::stringstream out3;        
    HuffmanArchiver arc3(&in3, &out3);
    std::fill(arc3.codes_, arc3.codes_ + SYMB_NUMB, "!");        
    res = arc3.encode_text_();
    DO_CHECK(res.first == 0 && res.second == 0);

    delete [] s;
}


