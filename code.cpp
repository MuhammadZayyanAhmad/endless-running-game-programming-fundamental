#include <iostream>
#include <conio.h>
#include <windows.h> 
#include <time.h>
#include <stdlib.h>
#include <fstream>
using namespace std;

const int row = 27;
const int col = 19;
const char player = 'X';
char board[row][col];
int playerRow, playerCol;
const char obstacleSymbol = '#';
const char coinSymbol = 'O';
int health = 3;
int score = 0;
float second = 0;
time_t start = time(NULL);

void Board() {                                      //Initialization of board
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            if (i == 0 || i == row - 1) {
                board[i][j] = '.';
            } else if (j == 0 || j == col - 1) {
                board[i][j] = '.';
            } else {
                board[i][j] = ' ';
            }
        }
    }
}

void Player(){                                      //Initialize the player position on the start of game
    playerRow = 22;
    playerCol = 7;
    board[playerRow][playerCol] = player;        
}

void displayBoard(){                                //Display board
    system ("cls");                                 //Used for refresh the screen
    for (int i = 0 ; i < row; i++){
        for (int j = 0; j < col; j++) {
            cout << board[i][j];
        }
        cout << endl;
    }
}
	

void playerPosition() {							//Player movements 											
						
		if (kbhit()){
		char direction = getch();				//getch() is used as a input of character
        switch (direction){							
			case ' ':									
			{
    		
    			board[playerRow][playerCol] = ' '; 
    			playerRow--; 
    			if (playerRow < 0) {
        			playerRow = 0; 
    			}
    			board[playerRow][playerCol] = player; 
    			break;			
            } 
                	
            case 'w':
        		if (playerRow > 1){							//Border checking
        			board[playerRow][playerCol] = ' ';
                    playerRow = playerRow - 2;
                    board[playerRow][playerCol] = player;
				}
			break;
				
			case 's':
				if (playerRow < row -2){					//Border checking
					board[playerRow][playerCol] = ' ';
                    playerRow++;
                    board[playerRow][playerCol] = player;
				}
			break;
					
            case 'a':
                if(playerCol >  1) {							//Border checking
                    board[playerRow][playerCol] = ' ';
                    playerCol = playerCol - 2;
                    board[playerRow][playerCol] = player;
                }
            break;
                	
            case 'd':
                if(playerCol < col - 2 ) {						//Border checking
                    board[playerRow][playerCol] = ' ';
                    playerCol++;
                    board[playerRow][playerCol] = player;
                }
            break;	
			}
		}
	}


void obstacle() {
    srand(time(NULL)); 							
    int obstacle = 0; 								
    while (obstacle < 3) { 						// generate up to 3 obstacle
        int i = rand() % (row - 1) + 1; 		
        int j = rand() % (col - 2) + 1; 		
        if (board[i][j] == ' ') { 				
            board[i][j] = obstacleSymbol; 		
            obstacle++; 						
        }
    }
}

void moveObstacle() {
    int obstacleMove = 0; 
    for(int i = row - 2; i > 0; i--) { 
        for(int j = 1; j < col - 2; j++) { 
            if(obstacleMove >= 3) { 
                return;
            }
            if(board[i][j] == obstacleSymbol) { 
                board[i][j] = ' '; 								
                if (board[i+1][j] != obstacleSymbol && i+1 != row - 1) { 
                    board[i+1][j] = obstacleSymbol; 
                    obstacleMove++; 
                } else if (i+1 == row - 1) { 
                    board[i][j] = ' '; 
                    obstacleMove--; 
                }
            }
        }
    }

    while (obstacleMove < 3) {
        int j = rand() % (col - 2) + 1; 
        if (board[1][j] == ' ') { 
            board[1][j] = obstacleSymbol; 
            obstacleMove++; 
        }
        if (obstacleMove == 3) { 
            break;
        }
    }
}

void heavyObstacle() {
    srand(time(NULL)); 							
    int obstacle = 0; 								
    while (obstacle < 6) { 						// generate up to 6 obstacle
        int i = rand() % (row - 1) + 1; 		
        int j = rand() % (col - 2) + 1; 		
        if (board[i][j] == ' ') { 				
            board[i][j] = obstacleSymbol; 		
            obstacle++; 						
        }
    }
}

void moveHeavyObstacle() {
    int obstacleMove = 0; 
    for(int i = row - 2; i > 0; i--) { 
        for(int j = 1; j < col - 2; j++) { 
            if(obstacleMove >= 6) { 
                return;
            }
            if(board[i][j] == obstacleSymbol) { 
                board[i][j] = ' '; 								
                if (board[i+1][j] != obstacleSymbol && i+1 != row - 1) { 
                    board[i+1][j] = obstacleSymbol; 
                    obstacleMove++; 
                } else if (i+1 == row - 1) { 
                    board[i][j] = ' '; 
                    obstacleMove--; 
                }
            }
        }
    }

    while (obstacleMove < 6) {
        int j = rand() % (col - 2) + 1; 
        if (board[1][j] == ' ') { 
            board[1][j] = obstacleSymbol; 
            obstacleMove++; 
        }
        if (obstacleMove == 6) { 
            break;
        }
    }
}


void coins() {
    srand(time(NULL)); 							
    int coins = 0; 								
    while (coins < 5) { 						// generate up to 5 coins
        int i = rand() % (row - 1) + 1; 		
        int j = rand() % (col - 2) + 1; 		
        if (board[i][j] == ' ') { 				
            board[i][j] = coinSymbol; 		
            coins++; 						
        }
    }
}

void moveCoins() {
    int coinsMoved = 0; 
    for(int i = row - 2; i > 0; i--) { 
        for(int j = 1; j < col - 2; j++) { 
            if(coinsMoved >= 5) { 
                return;
            }
            if(board[i][j] == coinSymbol) { 
                board[i][j] = ' '; 								
                if (board[i+1][j] != coinSymbol && i+1 != row - 1) { 
                    board[i+1][j] = coinSymbol; 
                    coinsMoved++; 
                } else if (i+1 == row - 1) { 
                    board[i][j] = ' '; 
                    coinsMoved--; 
                }
            }
        }
    }

    while (coinsMoved < 5) {
        int j = rand() % (col - 2) + 1; 
        if (board[1][j] == ' ') { 
            board[1][j] = coinSymbol; 
            coinsMoved++; 
        }
        if (coinsMoved == 5) { 
            break;
        }
    }
}

void update(int& health, int& score) {
    if (board[playerRow][playerCol] == obstacleSymbol) {
    	Beep(2000, 400);		//for sound
        health--;
    }
    if (board[playerRow][playerCol] == coinSymbol) {
    	Beep(1500, 100);
        score++;
    }
}

void updateInfo(int& distance, time_t start){
		cout<<"HEALTH = " << health<<endl;
		cout<<"SCORE = " << score << endl;
		
		time_t current = time(NULL);
    	double second = difftime(current, start); // add data type to second variable
    	cout << "DISTANCE = " << second * 8.1 << " METERS"; // multiply with 8.1 to get distance
    	distance = second * 8.1;
}
	
void saveHighScore(int score) {
    int highScore = 0;
    ifstream file("HighScore.txt");
    if (file >> highScore) {
        if (score > highScore) {
            ofstream outFile("HighScore.txt");
            outFile << score << endl;
            outFile.close();
        }
    } else {
        // File doesn't exist or is empty
        ofstream outFile("HighScore.txt");
        outFile << score << endl;
        outFile.close();
    }
}

void showHighScore() {
    int highScore = 0;
    ifstream file("HighScore.txt");
    if (file >> highScore) {
        cout << highScore << endl;
    }
    file.close();
}

void gameOver(int distance) {
	if (health <= 0){
		system("cls");
    	cout << "\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tGAME OVER\n\n";
    	cout << "\n\t\t\t\t\t\tHIGH SCORE = ";
    	showHighScore();
    	cout << endl;
    	cout << "\n\t\t\t\t\t\tYOUR SCORE = " << score << endl;
    	cout << "\n\t\t\t\t\t\tTOTAL DISTANCE COVER = " << distance << endl;
    	cout << endl << endl;
    	saveHighScore(score);
    	system("pause");
	}
}

int main (){
    Board();
    Player();
    obstacle();
    heavyObstacle();
    coins();
    time_t start = time(NULL);
    int distance = 0;
    while (true) {
    	if (distance < 2000){
    		moveObstacle();
		} 
		else {
			moveHeavyObstacle();
		}
        moveCoins();
        displayBoard();
        playerPosition();
        update(health, score);
        updateInfo(distance, start);
        saveHighScore(score);
        gameOver(distance);
	}
    return 0;
}
