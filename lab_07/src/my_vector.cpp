#include "../include/my_vector.h"
#include <cstdio>

MyVector :: MyVector(){
    capacity_v = 2;
    array = new int[capacity_v];
    size_v = 0;
}

MyVector :: MyVector(std::size_t init_capacity){
    capacity_v = init_capacity;
    array = new int[capacity_v];
    size_v = 0;
}

MyVector :: ~MyVector(){
    delete []array;
}

void MyVector :: resize(std::size_t new_size){    
    if (new_size < capacity_v)    
        for (int i = size_v; i < new_size; i++)
            array[i] = 0;
    else{
        capacity_v = new_size*2;
        int* new_array = new int[capacity_v];
        for (int i = 0; i <= new_size; i++){
            if (size_v > i)
                new_array[i] = array[i];
            else
                new_array[i] = 0;
        }       
        delete []array;
        array = new_array; 
    }   
    size_v = new_size;
}

void MyVector :: print(){
    for (int i = 0; i < size_v; i++)
        printf("%d ", array[i]);
    printf("\n");
}

void MyVector :: push_back(int value){
    if (size_v == capacity_v)
        reserve(2*capacity_v);
    array[size_v++] = value;    
}

void MyVector :: set(size_t i, int value){
    if (size_v > i)
        array[i] = value;      
}

std::size_t MyVector :: size(){
    return size_v;
}

std::size_t MyVector :: capacity(){
    return capacity_v;
}


void MyVector :: reserve(std::size_t new_capacity){
    capacity_v = new_capacity;
    int* new_array = new int[capacity_v];
    for (int i = 0; i < size_v; i++)
        if (size_v > i)
            new_array[i] = array[i];
    delete []array;
    array = new_array;
}

int MyVector :: get(std::size_t i){
    return array[i];
}

void MyVector :: erase(std::size_t ind){
    size_v--;
    for (int i = ind; i < size_v; i++)
        array[i] = array[i + 1];
}

void MyVector :: insert(std::size_t ind, int value){
    resize(size_v + 1);
    for (int i = size_v - 1; i > ind; i--)
        array[i] = array[i - 1];
    array[ind] = value;
}
