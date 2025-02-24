#ifndef PUZZLEOBJECT_H
#define PUZZLEOBJECT_H

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class PuzzleObject{
protected:
    string stored_num;
public:
    void set_num(string num);
    int get_first_part();
    string get_central_part();
    int get_last_part();
    bool is_number_setted();
    bool is_valid_number();
};

class FinalPuzzle: public PuzzleObject{
public:
    void set_final_puzzle(string num);

};

#endif // PUZZLEOBJECT_H
