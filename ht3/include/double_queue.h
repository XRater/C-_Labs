#pragma once
#include <queue>

template <class T>
class double_queue {
public:
    double_queue() {};
    double_queue(std::queue <T> q) : init_queue(q) {};        
        
    bool empty() {return (init_queue.empty() && second_queue.empty());}
    
    void push(T elem) {second_queue.push(elem);}
    void init_push(T elem) {init_queue.push(elem);}
    
    T pop() {
        if (empty())
            throw;
        
        if (second_queue.empty()) {    
            T tmp = init_queue.front();
            init_queue.pop(); 
            return tmp;
        }
        if (init_queue.empty()) {    
            T tmp = second_queue.front();
            second_queue.pop(); 
            return tmp;
        }
        
        if (init_queue.front() <= second_queue.front()) {
            T tmp = init_queue.front();
            init_queue.pop(); 
            return tmp;
        }
        T tmp = second_queue.front();
        second_queue.pop(); 
        return tmp;
    }
        
private:
    std::queue <T> init_queue;     
    std::queue <T> second_queue;     
};

