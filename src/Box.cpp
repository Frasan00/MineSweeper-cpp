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
            this->flagged = false;
            this->value = value;
        }

        bool getFlag(){ return this->flagged; }

        bool getStatus(){ return this->clicked; };
        void setValue(int value){ this->value = value; }

        void unFlag(){ this->flagged = false; }
        void flag(){ this->flagged = true; }

        int getValue(){ return this->value; }
        int click(){ 
            this->clicked = true; 
            return this->value;
        }
    
    private:
        bool clicked;
        bool flagged;
        int value; // 9 = bomb, 0 = null, { 1, 2, 3,..., 8 } near bombs

};

#endif