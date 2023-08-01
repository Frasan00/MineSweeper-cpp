#ifndef BOX_H
#define BOX_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Box {
    public:
        Box(int value = 0){
            this->clicked = false;
            this->value = value;
        }

        bool getStatus(){ return this->clicked; };

        int getValue(){ return this->value; }
        int click(){ 
            this->clicked = true; 
            return this->value;
        }
    
    private:
        bool clicked;
        int value; // -1 = bomb, 0 = null, { 1, 2, 3,..., 8 } near bombs

};

#endif