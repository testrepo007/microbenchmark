/* 
 * File:   main.cpp
 * Author: ernestpob
 *
 * Created on November 1, 2017, 2:54 PM
 */

#include <thread>
#include <iostream>
#include <vector>
#include <mutex>
#include <pthread.h>
#include <atomic>
using namespace std;

struct Counter {
    int up=0; int down=50;
    std::mutex mutex;

    void increment(){
        mutex.lock();
        ++up;
        mutex.unlock();
    }
    
    void decrement(){
        if(down == 0){
            throw "Value cannot be less than 0";
        }

        --down;
    }
};


int main(){    
    vector<thread> threads;
    Counter cc;
    for(int i = 0; i < 4; ++i){
        threads.push_back(std::thread([&cc](){ 
                for (int k = 0; k < 10; ++k){
                    cc.increment();
		    cc.decrement();
                }
        }));
    }
    
    for(auto& thread : threads){
        thread.join();    
    }
    
    cout << "up is " << cc.up <<   endl;
    cout << "down is " << cc.down <<   endl;

    return 0;
}
