#include "puzzleobject.h"

//***ignore this part******//
int stoi(const string& str) {
    stringstream ss(str);
    int result;
    ss >> result;
    return result;
}

//*************************//


void PuzzleObject::set_num(string num){
    if((num.size()!=6)){
        cout<<"Enter 6 digit number\n";
    }else{
        stored_num = num;
    }

}

void FinalPuzzle::set_final_puzzle(string num){
        stored_num = num;
}


int PuzzleObject::get_first_part(){
    if((!stored_num.empty()) && (is_valid_number())){
        return stoi(stored_num.substr(0,2));
    }
    return -1;
}

string PuzzleObject::get_central_part(){
    if((!stored_num.empty()) && (is_valid_number())){
        return stored_num.substr(2,(stored_num.length()-4));
    }
    return "Getting_central_part_error";
}

int PuzzleObject::get_last_part(){
    if((!stored_num.empty()) && (is_valid_number())){
        return stoi(stored_num.substr(stored_num.length()-2,2));
    }
    return -1;
}

bool PuzzleObject::is_number_setted(){
    if((!stored_num.empty()) && (is_valid_number())){
        return 1;
    } else {
        return 0;
    }
}

bool PuzzleObject::is_valid_number() {
    if (stored_num.size() != stored_num.length()) return false;
    for (int i = 0; i < stored_num.length(); i++) {
        if (!isdigit(stored_num[i])) return false;
    }
    return true;
}
