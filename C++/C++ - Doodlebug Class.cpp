#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <string>
using namespace std;

const int SIZE_OF_GRID = 20;
const int INITIAL_DDBUG = 5;
const int INITIAL_ANTS = 100;
const int ANT_BREED_TIME = 3;
const int DDBUG_BREED_TIME = 8;
const int DDBUG_STARVE_TIME = 3;
const char ANT_CHAR = 'o';
const char DDBUG_CHAR = 'X';
const char EMPTY_CHAR = '-';

class Grid;
class Organism;
class Ant;
class Doodlebug;

//*****************************************
// set the organism class
class Organism {
public:
    int row, col;
    Organism();
    ~Organism();
    Organism(const int& newRow, int& newCol){row = newRow, col = newCol;}
    virtual void Move(Grid& grid) = 0;
    virtual void Breed(Grid& grid) = 0;
    virtual void Starve(Grid& grid) = 0;
    virtual void Print(ostream& outs) const = 0;
    virtual char getType() const = 0;
    void setPosition(int newRow, int newCol){row = newRow; col = newCol;};
    void Die(Grid& grid) const;
    int getRow() const;
    int getCol() const;
    friend ostream& operator <<(ostream& outs, const Organism& organism);
};

//*****************************************
// set the ant class
class Ant :public Organism {
    int breedTime;
public:
    Ant() : breedTime(0){}
    ~Ant();
    Ant(const int& newRow, int& newCol) : breedTime(0) {row = newRow; col = newCol;}
    virtual void Move(Grid& grid);
    virtual void Breed(Grid& grid);
    virtual void Starve(Grid& grid);
    virtual void Print(ostream& outs) const;
    bool isAdjEmpty(int direction);
    virtual char getType() const;

};

//*****************************************
// set the doodlebug class
class Doodlebug :public Organism {
    int breedTime;
    int starveTime;
    vector<int> adjAnts(Grid& grid);
public:
    Doodlebug() : breedTime(0), starveTime(0){}
    ~Doodlebug();
    Doodlebug(const int& newRow, int& newCol) : breedTime(0), starveTime(0) {row = newRow; col = newCol;}
    virtual void Move(Grid& grid);
    virtual void Breed(Grid& grid);
    virtual void Starve(Grid& grid);
    virtual void Print(ostream& outs) const;
    virtual char getType() const;
};

//*****************************************
// set the grid class
class Grid {
public:
    Grid();
    ~Grid();
    void print() const;
    void nextStep();
    bool isAdjEmpty(int row, int col) const;
    vector <int> getEmptyAdj(int row, int col) const;
    Organism* getOrganism(int row, int col) const;
    void setOrganism(int row, int col, Organism* organismPtr);
    void moveOrganism(int row, int col, int newRow, int newCol);
    void removeOrganism(const Organism* organismPtr);

private:
    Organism* array[SIZE_OF_GRID][SIZE_OF_GRID];
};

//*****************************************
// MAIN FUNCTION
int main(){
    srand(time(0));
    Grid grid;
    int timeStep = 0;
    bool stop = false;
    char input;
    
    while (!stop){
        cout << "World at time " << timeStep << ":" << endl;
        grid.print();
        cout << "Press ENTER to continue" << endl;   
        cin.get(input);
        if (input == '!'){
            break;
        } else {
            grid.nextStep();
        }
        timeStep += 1;
    } 
    
}

// *******************
// Organsim functions
Organism::Organism(){}
Organism::~Organism(){}
void Organism::Print(ostream& outs) const{};

int Organism::getRow() const{
    return row;
}
int Organism::getCol() const{
    return col;
}

void Organism::Die(Grid& grid) const{grid.removeOrganism(this);}

ostream& operator <<(ostream& outs, const Organism& organism){
    organism.Print(outs);
    return outs;
}

// *******************
// Ant functions

Ant::~Ant(){}
char Ant::getType() const {return ANT_CHAR;}

void Ant::Starve(Grid& grid){};

void Ant::Move(Grid& grid){
    
    int direction = rand() % 4;
    int tempRow = row;
    int tempCol = col;
    
    // 0 is up, 1 is down, 2 is left, 3 is right
    if (direction == 0){
            tempRow -= 1; 
        } else if (direction == 1){
            tempRow += 1;
        } else if (direction == 2){
            tempCol -= 1;
        } else if (direction == 3){
            tempCol += 1;
    }

    if (grid.isAdjEmpty(tempRow, tempCol)){
        grid.moveOrganism(row, col, tempRow, tempCol);
    } 

    breedTime++;
}

void Ant::Breed(Grid& grid){
    if (breedTime < ANT_BREED_TIME){
        return;
    }
    vector<int> emptyAdj = grid.getEmptyAdj(row, col);
    if (emptyAdj.size() != 0){
        int dir = rand() % emptyAdj.size();
        int tempRow = getRow();
        int tempCol = getCol();
    
            // 0 is up, 1 is down, 2 is left, 3 is right
        if (emptyAdj[dir] == 0){
            tempRow -= 1; 
        } else if (emptyAdj[dir] == 1){
            tempRow += 1;
        } else if (emptyAdj[dir] == 2){
            tempCol -= 1;
        } else if (emptyAdj[dir] == 3){
            tempCol += 1;
        }
        grid.setOrganism(tempRow, tempCol, new Ant);
    }
    breedTime = 0;
    emptyAdj.clear();
    
}

void Ant::Print(ostream& outs) const{
    outs << ANT_CHAR;
}


// *******************
// Doodlebug functions
Doodlebug::~Doodlebug(){}

char Doodlebug::getType() const {return DDBUG_CHAR;}
void Doodlebug::Move(Grid& grid){
    vector<int> emptyAdj = grid.getEmptyAdj(row, col);
    vector<int> antsAdj = adjAnts(grid);

    if (antsAdj.size() != 0) {
        int randNum = rand() % antsAdj.size();
        int eatDir = antsAdj[randNum];
        int newRow = getRow();
        int newCol = getCol();

        if (eatDir == 0) {
            newRow -= 1;
        } else if (eatDir == 1) {
            newRow += 1;
        } else if (eatDir == 2) {
            newCol -= 1;
        } else if (eatDir == 3) {
            newCol += 1;
        }

        grid.getOrganism(newRow, newCol)->Die(grid);
        grid.moveOrganism(row, col, newRow, newCol);

        breedTime++;
        starveTime = 0;
    } else if (emptyAdj.size() != 0) {
        int direction = rand() % emptyAdj.size();
        int newRow = getRow();
        int newCol = getCol();

        if (emptyAdj[direction] == 0) {
            newRow -= 1;
        } else if (emptyAdj[direction] == 1) {
            newRow += 1;
        } else if (emptyAdj[direction] == 2) {
            newCol -= 1;
        } else if (emptyAdj[direction] == 3) {
            newCol += 1;
        }

        grid.moveOrganism(row, col, newRow, newCol);

        breedTime++;
        starveTime++;
        
    } else {
        breedTime++;
        starveTime++;
    }

    emptyAdj.clear();
    antsAdj.clear();
    
}
void Doodlebug::Breed(Grid& grid){
    if (breedTime < DDBUG_BREED_TIME){
        return;
    }
        vector<int> emptyAdj = grid.getEmptyAdj(row, col);
        if (emptyAdj.size() != 0){
            int breedDir = rand() % emptyAdj.size();
            int tempRow = getRow();
            int tempCol = getCol();

            // 0 is up, 1 is down, 2 is left, 3 is right
            if (emptyAdj[breedDir] == 0){
                    tempRow -= 1; 
                } else if (emptyAdj[breedDir] == 1){
                    tempRow += 1;
                } else if (emptyAdj[breedDir] == 2){
                    tempCol -= 1;
                } else if (emptyAdj[breedDir] == 3){
                    tempCol += 1;
            }
            grid.setOrganism(tempRow, tempCol, new Doodlebug);
        }
        breedTime = 0;
        emptyAdj.clear();
}


void Doodlebug::Starve(Grid& grid){
    if (starveTime < DDBUG_STARVE_TIME){
        return;
    }
    Die(grid);
}

vector<int> Doodlebug::adjAnts(Grid& grid){
    vector <int> findAdjAnts;
    
    int tempRow = getRow();
    int tempCol = getCol();

    vector <int> allAdjRow = {tempRow-1, tempRow+1, tempRow, tempRow};
    vector <int> allAdjCol = {tempCol, tempCol, tempCol-1, tempCol+1};

    // There are four directions: 0 is up, 1 is down, 2 is left, 3 is right
    for (int i = 0; i < 4; i++) {
        Organism* organismPtr = grid.getOrganism(allAdjRow[i], allAdjCol[i]);
        if ((organismPtr != NULL) && (organismPtr->getType() == ANT_CHAR)){
            findAdjAnts.push_back(i);
        }
    }
    allAdjRow.clear();
    allAdjCol.clear();
    return findAdjAnts;
}

void Doodlebug::Print(ostream& outs) const {
    outs << DDBUG_CHAR;
}

//***************
// Grid functions
// initialize the grid with 5 doodlebugs and 100 ants
Grid::Grid(){
    for (int i = 0; i < SIZE_OF_GRID; i++){
        for (int j = 0; j < SIZE_OF_GRID; j++){
            array[i][j] = NULL;
        }
    }
    
    for (int i = 0; i < INITIAL_DDBUG; i++){
        int row = rand() % SIZE_OF_GRID;
        int column = rand() % SIZE_OF_GRID;
        while (array[row][column] != NULL){
            row = rand() % SIZE_OF_GRID;
            column = rand() % SIZE_OF_GRID;
        }
        array[row][column] = new Doodlebug(row, column);
    }    

    for (int i = 0; i < INITIAL_ANTS; i++){
        int rowAnt = rand() % SIZE_OF_GRID;
        int colAnt = rand() % SIZE_OF_GRID;
        while (array[rowAnt][colAnt] != NULL){
            rowAnt = rand() % SIZE_OF_GRID;
            colAnt = rand() % SIZE_OF_GRID;
        }
        array[rowAnt][colAnt] = new Ant(rowAnt, colAnt);
    }    
}

Grid::~Grid(){
    for (int i = 0; i < SIZE_OF_GRID; i++){
        for (int j = 0; j < SIZE_OF_GRID; j++){
            if (array[i][j] != NULL){
                delete array[i][j];
            }
        }
    }
}

void Grid::print() const {
    for (int i = 0; i < SIZE_OF_GRID; i++){
        for (int j = 0; j < SIZE_OF_GRID; j++){
            if (array[i][j] == NULL){
                cout << EMPTY_CHAR << " ";
            } else {
                cout << (*array[i][j]) << " ";
            }
        }
        cout << endl;
    }
}

void Grid::nextStep(){
    vector<Organism*> ants;
    vector<Organism*> ddbugs;

    for (int i = 0; i < SIZE_OF_GRID; i++){
        for (int j = 0; j < SIZE_OF_GRID; j++){
            if ((array[i][j] != NULL) && (array[i][j] -> getType() == DDBUG_CHAR)){
                ddbugs.push_back(array[i][j]);
            }
        }
    }

    for (int i = 0; i < ddbugs.size(); i++){
        ddbugs[i]->Move(*this);
    }

    for (int i = 0; i < ddbugs.size(); i++){
        ddbugs[i]->Breed(*this);
    }

    for (int i = 0; i < ddbugs.size(); i++){
        ddbugs[i]->Starve(*this);
    }

    for (int i = 0; i < SIZE_OF_GRID; i++){
        for (int j = 0; j < SIZE_OF_GRID; j++){
            if ((array[i][j] != NULL) && (array[i][j] -> getType() == ANT_CHAR)){
                ants.push_back(array[i][j]);
            }
        }
    }

    for (int i = 0; i < ants.size(); i++){
        ants[i]->Move(*this);
    }
    

    for (int i = 0; i < ants.size(); i++){
        ants[i]->Breed(*this);
    }
    ants.clear();
    ddbugs.clear();
}

bool Grid::isAdjEmpty(int row, int col) const {
    return (row >= 0) && (row < SIZE_OF_GRID) && (col >= 0) && (col < SIZE_OF_GRID) && (array[row][col] == NULL);
}

vector<int> Grid::getEmptyAdj(int row, int col) const {
    vector<int> emptyAdj;
    
    // 0 is up, 1 is down, 2 is left, 3 is right
    if (isAdjEmpty(row-1, col)){
        emptyAdj.push_back(0);
    }
    if (isAdjEmpty(row+1, col)){
        emptyAdj.push_back(1);
    }
    if (isAdjEmpty(row, col-1)){
        emptyAdj.push_back(2);
    }
    if (isAdjEmpty(row, col+1)){
        emptyAdj.push_back(3);
    }    
    return emptyAdj;
}


Organism* Grid::getOrganism(int row, int col) const{
    if ((row >= 0) && (row < SIZE_OF_GRID) && (col >= 0) && (col < SIZE_OF_GRID)){
        return array[row][col];
    } else {
        return NULL;
    }
}

void Grid::setOrganism(int row, int col, Organism* organismPtr){
    array[row][col] = organismPtr;
    organismPtr->setPosition(row, col);
}

void Grid::moveOrganism(int row, int col, int newRow, int newCol){
    array[newRow][newCol] = array[row][col];
    array[newRow][newCol]->setPosition(newRow, newCol);
    array[row][col] = NULL;
}

void Grid::removeOrganism(const Organism *organismPtr){
    array[organismPtr->getRow()][organismPtr->getCol()] = NULL;
    delete organismPtr;
}

