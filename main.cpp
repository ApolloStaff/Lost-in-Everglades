#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function prototypes
void rulesofGame();
void boardInitialiser(char[][5], char[][5]);
void moveRanger(char [][5], char [][5], int&, int&, int&);
void printBoard(char [][5]);
void handleDanger(char [][5], char [][5], int&, int& , int&, int, int);
int mapToRange(char);
bool istheGameOver(char [][5]);

int main()
{
    // Variables (1)
    int rangerRow = 0, rangerCol = 0;
    int gongs=12;
    char displayBoard[5][5]; // Display Board is the board which will be shown to the player. Its like a frontend.
    char shadowBoard[5][5];  // Shaow Board is the board which will take care of all the updation of the monster and stuff.
    displayBoard[0][0]='R';
    // The ranger starts at (0, 0).
    displayBoard[4][4]='T';
    // The tourists are at (4, 4).
    boardInitialiser(displayBoard, shadowBoard);
    while (gongs>0) 
    {
        // gongs hit zero, the game will end.
        cout << endl << "Choose one of the following options:" << endl << endl;
        cout << "\t1. See Rules" << endl;
        cout << "\t2. Play" << endl;
        cout << "\t3. Quit" << endl << endl;
        cout << "Option: ";
        bool temp=true;
        // temp is a bool that is initially true but turns to false whenever the ranger reaches the tourists.
        string input;
        cin >> input;

        if (input == "1") 
        {
            rulesofGame();
        } 
        else if (input == "2") 
        {
            cout << "Lost in the Everglades..." << endl<<endl;
            // Prompt user for ranger movement
            while (temp)
            {
                printBoard(displayBoard);
                cout<<endl<<"Gongs Left: "<<gongs<< endl;
                moveRanger(displayBoard, shadowBoard, rangerRow, rangerCol, gongs);
                temp=istheGameOver(displayBoard);
            }
        } 
        else if (input == "3") 
        {
            cout << "Good Bye..." << endl;
            return 0;
        } 
        else 
        {
            cout << "Invalid choice. Please try again." << endl << endl;
        }
    }
    
    cout<<"The end";
    return 0;
}

// The rules of games are displayed using this function 
void rulesofGame() 
{
    cout << "Lost in the Everglades in an RPG (Role-Playing-Game) between a player and the computer."
    << "\n\nA group of tourists has been lost in the Everglades and a ranger must rescue them before time runs"
    << "\nout."
    << "\n\nThe Everglades are represented by a 5x5 matrix.The ranger (R) starts the rescue at the upperleft"
    << "\ncorner of the park, the group of tourists (T) are lost at the lower-right corner. The ranger has 12"
    << "\ngongs of time to find and rescue the tourists before they perish."
    << "\n\nDuring the journey, the ranger might find dangers (hungry alligator, swarm of giant mosquitoes,"
    << "\nvenomous spider or Python)."
    << "\n\nWhen the ranger finds a danger, they can choose to fight them or hide and wait for them to leave"
    << "\n\n\t* If the Ranger hides& waits"
    << "\n\t\t* Moves to the desired cell"
    << "\n\t\t* Loses 5 gongs of time"
    << "\n\t• If the Ranger fights & wins"
    << "\n\t\t* Moves to the desired cell"
    << "\n\t\t* Loses 2 gongs of time"
    << "\n\t• If the Ranger fights & loses"
    << "\n\t\t* Goes back to the initial cell"
    << "\n\t\t* Loses 3 gongs of time"
    << "\n\t\t* The Danger remains in the cell"<< endl;
}

// Places asterisks and danger in the board
void boardInitialiser(char displayBoard[][5], char shadowBoard[][5]) 
{
    // The array conatins all the dangers available to us.
    char dangerFill[] = { 'A', 'M', 'S', 'P' };
    for (int i = 0; i < 5; i++) 
    {
        for (int j = 0; j < 5; j++) 
        {
            displayBoard[i][j] = '*';
            shadowBoard[i][j] = '*';
        }
    }
    displayBoard[0][0] = 'R'; // Place the ranger at (0, 0)
    displayBoard[4][4] = 'T'; // Place tourists at (4, 4)
    srand(time(NULL));
    for (int i = 0; i < 10; i++) 
    {
        int row = rand() % 5; // Randomly places the danger on the shadowBoard.
        int col = rand() % 5; // Randomly places the danger on the shadowBoard.
        shadowBoard[row][col] = dangerFill[i % 4]; // Ensure dangerFill indices stay within range
    }
    shadowBoard[0][0] = 'R'; // Place the ranger at (0, 0)
    shadowBoard[4][4] = 'T'; // Place tourists at (4, 4)
}

// Function that handles user input, validate the move, and update the ranger's position on the display board.
void moveRanger(char displayBoard[][5], char shadowBoard[][5], int& rangerRow, int& rangerCol, int& gongs)
{
    while (gongs >= 0) 
    {
        cout << endl << "Enter next cell (row & col): ";
        int newRow, newCol;
        // stores the coordinates of the move.
        cin >> newRow >> newCol;
        if (shadowBoard[newRow][newCol] == ' ' || (newRow == rangerRow && newCol == rangerCol))
        {
            // Player can't move to empty space and his current position.
            cout << "Invalid move. You cannot move there." << endl;
        }
        else if (shadowBoard[newRow][newCol] != '*' && shadowBoard[newRow][newCol] != ' ')
        {
            // If the player moves to a tile which is neither a 
            handleDanger(displayBoard, shadowBoard, gongs, rangerRow, rangerCol, newRow, newCol); // Handle the danger
            shadowBoard[newRow][newCol] = ' '; // Remove the danger from shadow
            if (gongs > 0) // If gongs are still available
            {
                // Move the ranger after handling danger
                displayBoard[rangerRow][rangerCol] = ' ';
                rangerRow = newRow;
                rangerCol = newCol;
                displayBoard[rangerRow][rangerCol] = 'R';
            }
        }
        else if (shadowBoard[newRow][newCol] == 'T')
        {
        // Handle tourists
            gongs--;
            cout << "Congratulations! You rescued the tourists and won the game!" << endl;
            displayBoard[newRow][newCol] = 'R'; // Update displayBoard after rescue
            shadowBoard[newRow][newCol] = 'R'; // Update shadowBoard after rescue
            displayBoard[rangerRow][rangerCol] = ' '; 
            shadowBoard[rangerRow][rangerCol] = ' ';
            printBoard(displayBoard);
            gongs = -1; // Set gongs to a negative value to exit the game loop
            return; // Exit the function
        }
        else
        {
            if (newRow < 0 || newRow >= 5 || newCol < 0 || newCol >= 5) 
            {
                cout << "Invalid row or column. Please enter values between 0 and 4." << endl;
            } 
            else if ((abs(newRow - rangerRow) == 1 && abs(newCol - rangerCol) == 0) ||
                    (abs(newRow - rangerRow) == 0 && abs(newCol - rangerCol) == 1) ||
                    (abs(newRow - rangerRow) == 1 && abs(newCol - rangerCol) == 1)) 
            {
                // Move the ranger
                displayBoard[rangerRow][rangerCol] = ' ';
                rangerRow = newRow;
                rangerCol = newCol;
                displayBoard[rangerRow][rangerCol] = 'R';
                gongs--;
                cout << "---> Cell (" << rangerRow << ", " << rangerCol << ") is free ... You Advance!" << endl<<endl;

                if (rangerCol == 4 && rangerRow == 4) // Check if ranger reached tourists
                {
                    cout << "Congratulations! You rescued the tourists and won the game!" << endl;
                    gongs = -1; // Set gongs to a negative value to exit the game loop
                    return; // Exit the function
                }
                else if (gongs <= 0) // Check if gongs ran out
                {
                    cout << "Game over! The ranger's gongs have run out. You lost." << endl;
                    return; // Exit the function
                }
                break; // Exit the loop
            } 
            else 
            {
                cout << "Invalid move. The ranger can only move one tile in any direction." << endl;
            }
        }
    }
}

// Prints the display board
void printBoard(char displayBoard[][5])
{
    cout << "    0   1   2   3   4  " << endl;
    for (int i = 0; i < 5; i++) 
    {
        cout << i << " | ";
        for (int j = 0; j < 5; j++) 
        {
            cout << displayBoard[i][j] << " | ";
        }
        cout << endl;
    }
}

// Function kicks in when the ranger moves to a tile where danger lingers.
void handleDanger(char displayBoard[][5], char shadowBoard[][5], int& gongs, int& rangerRow, int& rangerCol, int newRow, int newCol)
{
    int temp=mapToRange(shadowBoard[newRow][newCol]);
    string dangerNames[] = { "Hungry Alligator", "Swarm of Giant Mosquitos", "Venomous Spider", "Python" };
    cout << "---> Watch out! There is a "<< dangerNames[temp] <<"ahead"<<endl<<endl;
    cout << "Choose your next move:" << endl;
    cout << "\t1. Wait until it leaves." << endl;
    cout << "\t2. Fight it." << endl;
    cout << "Move (1-2): ";
    int choice;
    cin >> choice;
    cout<<endl;
    int outcome = rand() % 2;
    switch (choice) 
    {
        case 1: 
            // Hide and wait
            gongs -= 5;
            cout << "---> "<<dangerNames[temp] <<" is gone... You Advance"<<endl<<endl;
            displayBoard[newRow][newCol] = 'R'; // Update displayBoard after handling danger
            shadowBoard[newRow][newCol] = 'R'; // Update shadowBoard after handling danger
            displayBoard[rangerRow][rangerCol] = ' '; 
            shadowBoard[rangerRow][rangerCol] = ' ';
            printBoard(displayBoard);
            break;
        case 2: 
            // Fighting part
            // generate outcome (win or lose)
            if (outcome == 0)
            {
                // the part where the ranger wins
                gongs -= 2;
                cout << "---> You fight the "<<dangerNames[temp] <<" and win ... You Advance!"<<endl<<endl;
                displayBoard[newRow][newCol] = 'R'; // Update displayBoard after handling danger
                shadowBoard[newRow][newCol] = 'R'; // Update shadowBoard after handling danger
                displayBoard[rangerRow][rangerCol] = ' '; 
                shadowBoard[rangerRow][rangerCol] = ' ';
                printBoard(displayBoard);
            }
            else
            {
                // the part where the ranger loses
                gongs -= 3;
                cout << "---> You fight the "<<dangerNames[temp] <<" and lose ... retreat"<<endl<<endl;
                displayBoard[newRow][newCol] = shadowBoard[newRow][newCol]; // Update displayBoard after handling danger
                printBoard(displayBoard);
                
            }
            break;
            default:
                cout << "Invalid choice." << endl;
                break;
    }
}

int mapToRange(char value) 
{
    // a small program for the index of the dangerNames array.
    if (value == 'A') return 0;
    if (value == 'M') return 1;
    if (value == 'S') return 2;
    if (value == 'P') return 3;
    return -1; 
}

bool istheGameOver(char displayBoard[][5]) 
{
    // gives false when the ranger reaches tourists.
    return displayBoard[4][4] != 'R';
}
