//  prog5_1024.cpp
//     Text and graphical version of the game 1024, a variant of 2048 available online at:
//        http://gabrielecirulli.github.io/2048/
//     Object of game is to combine number tiles with the same value, accumulating
//     points as the game progresses, to try and create the tile with the value 1024.
//     Each move consists of sliding pieces to the left, up, right or down.
// 
// Instructions:
//    To run this demo, first select the "Build and Run" option at the top of the window. You
//    can ignore the following error messages that will appear:
//         Failed to use the XRandR extension while trying to get the desktop video modes
//         Failed to use the XRandR extension while trying to get the desktop video modes
//         Failed to initialize inotify, joystick connections and disconnections won't be notified
//    To see the graphical output then select the "Viewer" option at the top of the window.
//    
// For more information about SFML graphics, see: https://www.sfml-dev.org/tutorials
// Be sure to close the old window each time you rebuild and rerun, to ensure you
// are seeing the latest output.
//
//
#include <SFML/Graphics.hpp> // Needed to access all the SFML graphics libraries
#include <iostream>          // Since we are using multiple libraries, now use std::
                             // in front of every cin, cout, endl, and string 
#include <cstdio>            // For sprintf, "printing" to a string
#include <cstring>           // For c-string functions such as strlen() 
#include <chrono>            // Used in pausing for some milliseconds using sleep_for(...)
#include <thread>            // Used in pausing for some milliseconds using sleep_for(...)

const int MaxBoardSize = 12;  // Max number of squares per side


//--------------------------------------------------------------------
// Display Instructions
void displayInstructions()
{
    std::cout << "Welcome to 1024. \n"
			  << "  \n"
			  << "For each move enter a direction as a letter key, as follows: \n"
			  << "    W    \n"
			  << "  A S D  \n"
			  << "where A=left,W=up, D=right and S=down. \n"
			  << "  \n"
			  << "After a move, when two identical valued tiles come together they    \n"
			  << "join to become a new single tile with the value of the sum of the   \n"
			  << "two originals. This value gets added to the score.  On each move    \n"
			  << "one new randomly chosen value of 2 or 4 is placed in a random open  \n"
			  << "square.  User input of x exits the game.                            \n"
			  << "  \n";
}//end displayInstructions()


//--------------------------------------------------------------------
// Place a randomly selected 2 or 4 into a random open square on
// the board.
void placeRandomPiece( int board[], int squaresPerSide)
{
    // Randomly choose a piece to be placed (2 or 4)
    int pieceToPlace = 2;
    if( rand()%2 == 1) {
        pieceToPlace = 4;
    }
    
    // Find an unoccupied square that currently has a 0
    int index;
    do {
        index = rand() % (squaresPerSide*squaresPerSide);
    }while( board[ index] != 0);
    
    // board at position index is blank, so place piece there
    board[ index] = pieceToPlace;
}//end placeRandomPiece()

	
//--------------------------------------------------------------------
int main()
{
    int score = 0;
    int boardSize = 4;                               // User will enter this value.  Default to 4
    int board[MaxBoardSize * MaxBoardSize];          // Board of integers, of max possible size
    int previousBoard[MaxBoardSize * MaxBoardSize];  // Copy of board, used to see if 
													 //    a move changed the board.
    
    // Display instructions
    displayInstructions();
    
    // get the board size, create and initialize the board, and set the max tile value
    // ...
    
    // Main loop to display board, prompt for and handle move and check for win

        // Display the board
        // ...
        
        // Copy board.  After attempting a move this is used to verify that the board
        // changed, which allows randomly placing an additional piece on board and
        // updating the move number.
        // ...
        
        // Prompt for and handle user input
        cout << move << ". Your move: ";
        cin >> userInput;
		// ...
        
        // If the move resulted in pieces changing position, then it was a valid move
        // so place a new random piece (2 or 4) in a random open square and update move number.
        // ...
        
    
    cout << "Exiting program...\n\n";
    return 0;
}//end main()