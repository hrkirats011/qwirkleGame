
#include "Game.h"

Game::Game()
{
    board = std::make_shared<Board>();
    tile_bag = std::make_shared<TileBag>();    
    p_turn = std::make_shared<Player>();
}

Game::~Game()
{
}

std::shared_ptr<Board> Game::getBoard()
{
    return board;
}
std::shared_ptr<Player> Game::getPlayer(int i)
{
    return p[i];
}

void Game::startNewGame(int cnt)
{
    count = cnt;
    p = new std::shared_ptr<Player>[count];
    for(int i = 0;i < count;i++)
        p[i] = std::make_shared<Player>();
    p_turn = p[0];    
    // fill bag with tiles
    tile_bag->fillBag();
    // shuffle bag
    tile_bag->shuffle();
    // set up player hands
    for(int i = 0;i < count;i++)
        setUpHand(p[i]);
    
    // get player names
    for(int i = 0;i < count;i++)
        inputPlayerName(p[i], i + 1);
    // start game
    std::cout << "Let's play!" << std::endl;

    playGame();
}

void Game::loadGame(std::string filename)
{

    // attempt to open file
    std::ifstream file;
    file.open(filename);
    // if file opened successfully
    if (file)
    {
        std::string str;
        int lineNum = 1;
        int index = 0;
        file >> count;
        cout << "count " << count << endl;

        p = new std::shared_ptr<Player>[count];
        for(int i = 0;i < count;i++)
            p[i] = std::make_shared<Player>();
        p_turn = p[0];    

        // process file line by line
        while (std::getline(file, str))
        {
            cout << "line-num " << lineNum << endl;
            if (lineNum < 3 * count + 1){
                index = (lineNum - 1)    / 3;
                if (lineNum % 3 == 1)
                {
                    p[index]->setName(str);
                    lineNum++;
                } // p1 score
                else if (lineNum % 3 == 2)
                {
                    p[index]->setScore(stoi(str));
                    lineNum++;
                } // p1 hand
                else if (lineNum % 3 == 0)
                {
                    readTiles(str, p[index]->getHand());
                    lineNum++;
                }
            } // board shape
            else if (lineNum == 3 * count + 1)
            {
                lineNum++;
            } // board state
            else if (lineNum == 3 * count + 2)
            {
                readBoard(str);
                lineNum++;
            } // tile bag contents
            else if (lineNum == 3 * count + 3)
            {
                readTiles(str, tile_bag->getList());
                lineNum++;
            } // current player
            else if (lineNum == 3 * count + 4)
            {
                for(int i = 0;i <count;i++)
                    if (str == p[i]->getName())
                        p_turn = p[i];
                lineNum++;
            }
        }
        playGame();
    }
    else
    {
        cout << "file doesn't exist";
    }
}

void Game::readTiles(std::string str,
                     std::shared_ptr<LinkedList> list)
{
    
    std::string tile = "";
    Colour c;
    Shape s;
    std::shared_ptr<Tile> t;

    // find tile
    for (auto x : str)
    {
        if (x == ',')
        {   // add tile to list
            c = tile[0];
            s = shapeInt(tile[1]);
            t = std::make_shared<Tile>(c, s);
            list->addBack(t);
            tile = "";
        }
        else
        {
            tile = tile + x;
        }
    }
    if (tile != "")
    {   // add last tile to list
        c = tile[0];
        s = shapeInt(tile[1]);
        t = std::make_shared<Tile>(c, s);
        list->addBack(t);
    }
}

void Game::readBoard(std::string str)
{
    std::string word = "";
    Colour c;
    Shape s;
    std::shared_ptr<Tile> t;
    // find tile@pos 
    for (auto x : str)
    {
        if (x == ',')
        {   // add tile to board
            c = word[0];
            s = shapeInt(word[1]);
            t = std::make_shared<Tile>(c, s);
            board->placeTile(t, charToInt(word[3]), shapeInt(word[4]));
            word = "";
        }
        else
        {
            word = word + x;
        }
    }
    if (word != "")
    {   // add last tile to board
        c = word[0];
        s = shapeInt(word[1]);
        t = std::make_shared<Tile>(c, s);
        board->placeTile(t, word[3], word[4]);
    }
}

void Game::inputPlayerName(std::shared_ptr<Player> p, int z)
{

    std::string name = "";
    do
    {   // continue asking user for input until something valid is supplied
        std::cout << std::endl;
        std::cout << "  Enter a name for player " << z << " (uppercase characters only)" << std::endl;
        std::cout << "> ";
        std::cin >> name;

    } while (!validatePlayerName(name));
    p->setName(name);
}

bool Game::validatePlayerName(std::string s)
{

    bool return_val = true;
    char c;

    if (s == "" || std::cin.eof())
    {
        return_val = false;
    }
    else
    {
        for (unsigned int i = 0; i < s.size(); i++)
        {   // check that input is all uppercase alphabetical characters
            c = s[i];
            if (c < 'A' || c > 'Z')
            {
                return_val = false;
            }
        }
    }
    if (return_val == false)
    {   // error message
        std::cout << "  You supplied an invalid name! Please try again." << std::endl;
    }
    return return_val;
}

void Game::setUpHand(std::shared_ptr<Player> p)
{
    // initialise player hand with 6 tiles randomly drawn from the bag
    for (int i = 0; i < MAX_HAND_SIZE; i++)
    {
        std::shared_ptr<Tile> t = tile_bag->removeFront();
        p->getHand()->addBack(t);
    }
}

void Game::drawTile(std::shared_ptr<Player> p)
{   //  remove tile from "front" of bag
    std::shared_ptr<Tile> t = tile_bag->removeFront();
    p->getHand()->addBack(t);
}

void Game::playGame()
{

    std::string command = "";
    bool success = false;

    // while bag not empty, player hands are not empty and
    // user hasnt input ctrl D to quit
    while (command != "quit" && !stopCondition())
    {
        // print current game state 
        printGameInfo(p_turn);

        while (success == false)
        {   // get user command
            command = getCommand();
            // return true if command is legal
            success = processCommand(command, p_turn);
        }
        // reset
        success = false;
        // pick up new tile
        drawTile(p_turn);
        // switch player
        switchPlayer();
    }
    endMessage();
}

bool Game::stopCondition()
{

    bool return_val = false;
    // stopping cond 1: bag is empty
    if (tile_bag->isEmpty())
    {
        return_val = true;
    } // stopping cond 2: one player runs out of tiles
    else 
    {
        for(int i = 0;i < count;i++)
            if (p[i]->getHand()->getSize() == 0)
                return_val = true;            
    }
    return return_val;
}

void Game::printGameInfo(std::shared_ptr<Player> curr)
{

    cout << endl;
    cout << curr->getName() << ", it's your turn" << endl;
    cout << "Score for " << curr->getName() << ": " << curr->getScore() << endl;
    for (int i = 0;i < count;i++)
        if ((curr != p[i]))
            cout << "Score for " << p[i]->getName() << ": " << p[i]->getScore() << endl;
    board->printBoard();

    cout << "Your hand is" << endl;
    curr->getHand()->printTiles();

    cout << endl;
    cout << "> ";
}

vector<string> Game::splitString(string str)
{
    // split user command into a vector of strings
    // where each element represents a sinle word
    vector<string> v = {};
    std::string word = "";

    for (auto x : str)
    {
        if (x == ' ')
        {
            v.push_back(word);
            word = "";
        }
        else
        {
            word = word + x;
        }
    }
    if (word != "")
    {
        v.push_back(word);
    }
    return v;
}

std::string Game::getCommand()
{

    std::string command = "";

    if (!std::getline(std::cin, command))
    {
        command = "quit";
    }
    return command;
}

bool Game::processCommand(std::string command, std::shared_ptr<Player> p)
{

    bool success = false;

    vector<string> v = splitString(command);
    int size = v.size();
    bool flag = false;
    if (size == 1)
    {
        if (v[0] == "quit")
        {
            success = true;
        }
        else if (v[0] == "help"){
            flag = true;
            cout << "- To place titel on board, you should input like this command.\n";
            cout << "  place <tile> at <grid location>\n";
            cout << "  To replace a tile in your bag, you should input like this \n";
            cout << "  replace <tile>\n";
            cout << "- To save the game, please input like this command.\n";
            cout << "  save <filename>\n";
            cout << "- To exit game, please input 'quit'\n";
        }
    }
    else if (size == 2)
    {
        if (v[0] == "replace")
        {   // v[0] = tile to replace
            success = replaceTile(v[1], p);
        }
        else if (v[0] == "save")
        {   // v[1] = name of file to save game to
            success = save(v[1], tile_bag);
        }
    }
    else if (size == 4)
    {   // v[1] = tile label and v[3] = positon on board 
        if (v[0] == "place" && v[2] == "at")
        {
            success = placeTile(v[1], v[3], p);
        }
    }
    if (flag)
        return false;
    if (success == false && command != "")
    {
        std::cout << "Invalid Input, please see the helper.\nIf you need to help, please type help" << std::endl;
        std::cout << "> ";
    }
    return success;
}

void Game::switchPlayer()
{
    for(int i = 0;i < count;i++)
        if (p_turn == p[i]){
            if (i == count - 1)
                p_turn = p[0];
            else    
                p_turn = p[i + 1];    
        }
}

bool Game::validatePosition(std::string s)
{

    bool return_val = false;
    unsigned int min = 2;
    unsigned int max = 3;

    if (s.size() >= min && s.size() <= max)
    {
        int row = charToInt(s[0]);
        std::string substr = s.substr(1, s.size());

        if (isNumeric(substr))
        {
            int col = std::stoi(substr);
            // position in board range
            if (row >= 0 && row < MAX_BOARD_SIZE)
            {
                if (col >= 0 && col < MAX_BOARD_SIZE)
                {
                    return_val = true;
                }
            }
        }
    }
    return return_val;
}

bool Game::isNumeric(std::string s)
{
    bool return_val = true;
    if (s != "")
    {
        for (unsigned int i = 0; i < s.size(); i++)
        {
            char c = s[i];
            if (!std::isdigit(c))
            {
                return_val = false;
            }
        }
    }
    else
    {
        return_val = false;
    }
    return return_val;
}

int Game::charToInt(char c)
{
    return (int)c - 65;
}

bool Game::validateTile(std::string str)
{

    bool return_val = false;
    if (str.size() == 2)
    {
        Colour colour = str[0];
        Shape shape = (int)str[1] - 48;

        if (validColour(colour) && validShape(shape))
        {
            return_val = true;
        }
    }
    return return_val;
}

bool Game::validColour(Colour colour)
{

    char colours[] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
    bool colour_found = false;

    for (Colour c : colours)
    {
        if (c == colour)
        {
            colour_found = true;
        }
    }
    return colour_found;
}

bool Game::validShape(Shape shape)
{

    int shapes[] = {CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER};
    bool shape_found = false;

    for (Shape s : shapes)
    {
        if (s == shape)
        {
            shape_found = true;
        }
    }
    return shape_found;
}

bool Game::placeTile(std::string tile, std::string pos,
                     std::shared_ptr<Player> p)
{

    bool success = false;
    
    if (validatePosition(pos))
    {
        int row = charToInt(pos[0]);
        std::string substr = pos.substr(1, pos.size());
        int col = std::stoi(substr);

        if (board->isEmpty(row, col))
        {

            if (validateTile(tile))
            {
                int i = p->getHand()->getTileIndex(tile);
                if (i != -1)
                {

                    if (validMove(tile, pos))
                    {

                        std::shared_ptr<Tile> t = p->getHand()->remove(i);
                        board->placeTile(t, row, col);
                        updateScore(pos, p);
                        //update score
                        success = true;
                    }
                }
            }
        }
    }
    return success;
}

bool Game::replaceTile(std::string tile, std::shared_ptr<Player> p)
{

    bool success = false;

    if (validateTile(tile))
    {
        int i = p->getHand()->getTileIndex(tile);
        if (i != -1)
        {
            std::shared_ptr<Tile> t = p->getHand()->remove(i);
            std::shared_ptr<Tile> t_new = tile_bag->removeFront();
            tile_bag->addBack(t);
            p->getHand()->addBack(t_new);
            success = true;
        }
    }
    return success;
}

bool Game::validMove(std::string tile, std::string pos)
{

    bool success = false;
    int row = charToInt(pos[0]);
    std::string substr = pos.substr(1, pos.size());
    int col = std::stoi(substr);

    if (board->isEmpty())
    {
        success = true;
    }
    else if (hasNeighbour(row, col))
    {
        if (validateHorizontal(row, col, tile))
        {
            if (validateVertical(row, col, tile))
            {
                success = true;
            }
        }
    }
    return success;
}

bool Game::hasNeighbour(int row, int col)
{

    bool success = false;

    // left
    if (col - 1 >= 0 && !board->isEmpty(row, col - 1))
    {
        success = true;
    } // right
    else if (col + 1 < MAX_BOARD_SIZE && !board->isEmpty(row, col + 1))
    {
        success = true;
    } // up
    else if (row - 1 >= 0 && !board->isEmpty(row - 1, col))
    {
        success = true;
    }
    else if (row + 1 < MAX_BOARD_SIZE && !board->isEmpty(row + 1, col))
    {
        success = true;
    }
    return success;
}

int Game::shapeInt(char c)
{
    return c - 48;
}

bool Game::validateHorizontal(int row, int col, std::string tile)
{

    bool success = false;

    // horizontal check
    vector<char> colours_found = {};
    vector<char> shapes_found = {};

    char c = tile[0];
    char s = tile[1];
    std::string t = "";

    colours_found.push_back(c);
    shapes_found.push_back(s);

    // left
    int i = col - 1;

    while (i >= 0 && !board->isEmpty(row, i))
    {
        t = board->getTile(row, i);
        c = t[0];
        s = t[1];
        colours_found.push_back(c);
        shapes_found.push_back(s);
        i -= 1;
    }

    // right
    i = col + 1;

    while (i < MAX_BOARD_SIZE && board->getTile(row, i) != "  ")
    {
        t = board->getTile(row, i);
        c = t[0];
        s = t[1];
        colours_found.push_back(c);
        shapes_found.push_back(s);
        i += 1;
    }

    if (allSame(colours_found) && allUnique(shapes_found))
    {
        success = true;
    }
    else if (allSame(shapes_found) && allUnique(colours_found))
    {

        success = true;
    }

    return success;
}

bool Game::validateVertical(int row, int col, std::string tile)
{

    bool success = false;

    // vertical check
    vector<char> colours_found = {};
    vector<char> shapes_found = {};

    char c = tile[0];
    char s = tile[1];
    std::string t = "";

    colours_found.push_back(c);
    shapes_found.push_back(s);

    // up
    int i = row - 1;

    while (i >= 0 && board->getTile(i, col) != "  ")
    {
        t = board->getTile(i, col);
        c = t[0];
        s = t[1];
        colours_found.push_back(c);
        shapes_found.push_back(s);
        i -= 1;
    }
    // down
    i = row + 1;

    while (i < MAX_BOARD_SIZE && board->getTile(i, col) != "  ")
    {
        t = board->getTile(i, col);
        c = t[0];
        s = t[1];
        colours_found.push_back(c);
        shapes_found.push_back(s);
        i += 1;
    }

    if (allSame(colours_found) && allUnique(shapes_found))
    {
        success = true;
    }
    else if (allSame(shapes_found) && allUnique(colours_found))
    {
        success = true;
    }

    return success;
}

bool Game::allUnique(vector<char> v)
{

    bool return_val = true;
    char c;

    for (unsigned int i = 0; i < v.size(); i++)
    {
        c = v[i];
        for (unsigned int j = i + 1; j < v.size(); j++)
        {
            if (v[j] == c)
            {
                return_val = false;
            }
        }
    }

    return return_val;
}

bool Game::allSame(vector<char> v)
{

    bool return_val = true;
    char first_elm = v[0];
    for (unsigned int i = 0; i < v.size(); i++)
    {
        if (v[i] != first_elm)
        {
            return_val = false;
        }
    }
    return return_val;
}

int Game::updateScore(std::string pos, std::shared_ptr<Player> p)
{
    int counter = 1;
    int score = 1;
    int row = charToInt(pos[0]);
    std::string substr = pos.substr(1, pos.size());
    int col = std::stoi(substr);

    // left
    int i = col - 1;
    while (i >= 0 && board->getTile(row, i) != "  ")
    {
        counter += 1;
        score += 1;
        i -= 1;
    }

    // right
    i = col + 1;
    while (i < MAX_BOARD_SIZE && board->getTile(row, i) != "  ")
    {
        counter += 1;
        score += 1;
        i += 1;
    }

    if (counter >= 6)
    {
        counter += 6;
        score += 6;
        std::cout << "QWIRKLE!!" << std::endl;
    }

    counter = 1;

    // up
    i = row - 1;
    while (i >= 0 && board->getTile(i, col) != "  ")
    {

        counter += 1;
        score += 1;
        i -= 1;
    }

    // down
    i = row + 1;
    while (i < MAX_BOARD_SIZE && board->getTile(i, col) != "  ")
    {
        counter += 1;
        score += 1;
        i += 1;
    }

    if (counter >= 6)
    {
        counter += 6;
        score += 6;
        std::cout << "QWIRKLE!!" << std::endl;
    }

    counter = 1;
    p->setScore(p->getScore() + score);
    return score;
}

bool Game::save(std::string filename,
                std::shared_ptr<TileBag> tile_bag)
{
    //bool success = false;
    std::ofstream outFile;

    outFile.open(filename);
    outFile << count << " ";
    // player i info
    for(int i = 0;i < count;i++){
        outFile << p[i]->getName() << std::endl;
        outFile << p[i]->getScore() << std::endl;
        outFile << p[i]->getHand()->getAllTiles() << std::endl;
    }    

    // current board shape and board state
    outFile << MAX_BOARD_SIZE << "," << MAX_BOARD_SIZE << std::endl;
    outFile << this->board->toString() << std::endl;

    // tile bag contents
    outFile << tile_bag->getAllTiles() << std::endl;

    // current player name
    outFile << p_turn->getName() << std::endl;

    // close file
    outFile.close();
    return true;
}

void Game::endMessage()
{
    // game over
    std::cout << " Game Over!" << std::endl;

    // Display the scores
    for(int i = 0;i < count;i++)
        std::cout << " Score for " << p[i] << ": " << p[i]->getScore() << std::endl;
    
    int index = 0;
    int score = p[0]->getScore();
    for(int i = 1;i < count;i++)
        if (score < p[i]->getScore()){
            index = i;
            score = p[i]->getScore();
        }

    bool flag = true;
    score = p[0]->getScore();
    for(int i = 1;i < count;i++)
        if (score == p[i]->getScore()){            
            score = p[i]->getScore();
            flag = true;
        }
        else {
            flag = false;
            break;
        }        

    if (!flag)
        std::cout << " Player " << p[index]<< " won!" << std::endl;
    else
        std::cout << " It is a draw! " << p[0]->getScore() << std::endl; 
    // good bye message
    std::cout << " Goodbye!" << std::endl;
}
