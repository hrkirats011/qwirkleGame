
#define MAX_BOARD_SIZE  26

#include "Board.h"


// Default constructor
Board::Board(){
    board = {};
    for (int i = 0; i < MAX_BOARD_SIZE; i++){
        vector<string> v = {};
        for(int j = 0; j < MAX_BOARD_SIZE; j++){
            v.push_back("  ");
        } board.push_back(v);
    }
}

Board::~Board(){

}

std::string Board::getTile(int i, int j){
    return board[i][j];
}

bool Board::isEmpty(int r, int c){
    
    bool return_val = false;
    if(board[r][c]== "  "){
        return_val = true;
    }
    return return_val;
}

bool Board::isEmpty(){
    bool return_val = true;
    for (unsigned int i = 0; i<board.size(); i++){
        for(unsigned int j = 0; j<board.size(); j++){
            if (board[i][j] != "  "){
                return_val = false;
            }
        }
    } return return_val;
}

void Board::placeTile(std::shared_ptr<Tile> t, int r, int c){
    
    std::string tile_string = t->toString();
    board[r][c] = tile_string;
}


std::string Board::toString(){
    
    std::string return_val = "";
    for(unsigned int i = 0; i < board.size(); i++){
        char row = intToChar(i);
        
        for(unsigned int j = 0; j < board.size(); j++){
            if(board[i][j] != "  "){
                return_val += board[i][j] + "@";
                return_val += row + std::to_string(j) + ",";
                
            }
        }
    } return return_val;


}

char Board::intToChar(int i){
    return i + 65;
}
// print red shape function
void Board::printRedShape(int shape){
    if (shape == 1)
        cout << u8"\U0001F534"; // print red circle
    else if (shape == 2)
        cout << "\033[1;31m"<< "X " <<"\033[0m";    // print red 4-star
    else if (shape == 3)
        cout << "\033[1;31m"<< u8"\U00002666" << " " <<"\033[0m";   // print red diamond
    else if (shape == 4)
        cout << u8"\U0001F7E5"; // print red square 
    else if (shape == 5)
        cout << "\033[1;31m"<< "* " <<"\033[0m";    // print red 6-star
    else if (shape == 6)
        cout << "\033[1;31m"<< "@ " <<"\033[0m";    // print red clover  
            
}
// print orange shape function
void Board::printOrangeShape(int shape){
    if (shape == 1)
        cout << u8"\U0001F7E0"; // print orange circle
    else if (shape == 2)
        cout << "\033[1;35m"<< "X " <<"\033[0m";    // print orange 4-star
    else if (shape == 3)
        cout << "\033[1;35m"<< u8"\U00002666" << " "  <<"\033[0m";   // print orange diamond
    else if (shape == 4)
        cout << u8"\U0001F7E7"; // print orange square 
    else if (shape == 5)
        cout << "\033[1;35m"<< "* " <<"\033[0m";    // print orange 6-star
    else if (shape == 6)
        cout << "\033[1;33m"<< "@ " <<"\033[0m";    // print orange clover        
    
}
// print yellow shape function
void Board::printYellowShape(int shape){
    if (shape == 1)
        cout << u8"\U0001F7E1"; // print yellow circle
    else if (shape == 2)
        cout << "\033[1;33m"<< "X " <<"\033[0m";    // print yellow 4-star
    else if (shape == 3)
        cout << "\033[1;33m"<< u8"\U00002666" << " "  <<"\033[0m";  // print yellow diamond
    else if (shape == 4)
        cout << u8"\U0001F7E8"; // print yellow square  
    else if (shape == 5)
        cout << "\033[1;33m"<< "* " <<"\033[0m";    // print yellow 6-star
    else if (shape == 6)
        cout << "\033[1;33m"<< "@ " <<"\033[0m";    // print yellow clover
}
// print green shape function
void Board::printGreenShape(int shape){
    if (shape == 1)
        cout << u8"\U0001F7E2"; // print green circle
    else if (shape == 2)
        cout << "\033[1;32m"<< "X " <<"\033[0m";    // print green 4-star
    else if (shape == 3)
        cout << "\033[1;32m"<< u8"\U00002666" << " "  <<"\033[0m";  // print green diamond
    else if (shape == 4)
        cout << u8"\U0001F7E6";     // print green square        
    else if (shape == 5)
        cout << "\033[1;32m"<< "* " <<"\033[0m";    // print green 6-star
    else if (shape == 6)
        cout << "\033[1;32m"<< "@ " <<"\033[0m";    // print green clover
}
// print blue shape function
void Board::printBlueShape(int shape){
    if (shape == 1)
        cout << u8"\U0001F535"; // print blue circle
    else if (shape == 2)
        cout << "\033[1;34m"<< "X " <<"\033[0m";    // print blue 4-star
    else if (shape == 3)
        cout << "\033[1;34m"<< u8"\U00002666" << " "  <<"\033[0m";  // print blue diamond
    else if (shape == 4)
        cout << u8"\U0001F7E6";     // print blue square
    else if (shape == 5)
        cout << "\033[1;34m"<< "* " <<"\033[0m";    // print blue 6-star
    else if (shape == 6)
        cout << "\033[1;34m"<< "@ " <<"\033[0m";    // print blue clover
}
// print purple shape function
void Board::printPurpleShape(int shape){
    if (shape == 1)
        cout << u8"\U0001F7E3";         // print purple circle
    else if (shape == 2)
        cout << "\033[1;36m"<< "X " <<"\033[0m";    // print purple 4-star
    else if (shape == 3)
        cout << "\033[1;36m"<< u8"\U00002666" << " "  <<"\033[0m";  // print purple diamond
    else if (shape == 4)
        cout << u8"\U0001F7EA";         // print purple square
    else if (shape == 5)
        cout << "\033[1;36m"<< "* " <<"\033[0m";    // print purple 6-star
    else if (shape == 6)
        cout << "\033[1;36m"<< "@ " <<"\033[0m";    // print purple clover
}
void Board::printElement(string str){
    // if tiles is empty, print space
    if (str.compare("  ") == 0){
        cout << "  ";
        return;
    }        
    char color = str[0];        // get color of tile
    int shape = atoi(&str[1]);  // get shape of tile
    if (color == 'R')
        printRedShape(shape);   // print red shape
    else if (color == 'O')
        printOrangeShape(shape);    // print orange shape
    else if (color == 'Y')
        printYellowShape(shape);    // print yellow shape
    else if (color == 'G')
        printGreenShape(shape);     // print green shape
    else if (color == 'B')
        printBlueShape(shape);      // print blue shape
    else if (color == 'P')
        printPurpleShape(shape);    // print purple shape
}
void Board::printBoard(){

    cout << " ";
    for (int i = 0; i < 10; i++){
        cout << "  " << i;
    }
    
    cout << " ";
    for (int i = 10; i < MAX_BOARD_SIZE; i++){
        cout << " " << i;
    } cout << endl;  
    

    for (int i = 0; i<=MAX_BOARD_SIZE; i++){
        cout << "---";
    } cout << endl;
    

    char row_label = 'A';
    for(int i = 0; i < MAX_BOARD_SIZE; i++){
        cout << row_label << " ";        
        for(int j = 0; j < MAX_BOARD_SIZE; j++){
            cout << "|";            
            // print tiles        
            printElement(board[i][j]);
        } 
        cout << "|" << endl;
        row_label++;
    }
}







