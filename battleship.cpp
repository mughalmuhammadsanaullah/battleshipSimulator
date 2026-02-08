#include <iostream>
#include <string>
#include <windows.h>
#include <ctime>
#include <conio.h>

using namespace std;

//Global constants
//const int SIZE=10;
//Global variables and arrays
bool playerTurnCheck=false;
bool isHit=false;
int playerTurns=6;
int computerTurns=6;
int COLOR;
string name;
int rowIdxPlayer[5]={-1};
int colIdxPlayer[5]={-1};
int rowIdxComputer[5]={-1};
int colIdxComputer[5]={-1};
bool playerVerticalShip[5]={false};
bool computerVerticalShip[5]={false};


//Group functions
void printBoard(char board[10][10],bool hideShips);
void clearScreen();
void showLeaderboard(const string playerNames[],const int scores[],int totalPlayers);
void showGameMenu();
void instructions();

//Student1 functions
void vsComputer(char playerBoard[10][10],char computerBoard[10][10]);
void setRandomShips(char board[10][10]);
void computerAttack(char playerBoard[10][10], int &computerscore);
void clearBoard(char board[10][10]);
void updateScore(int &score);
void initializeBoard(char board[10][10]);

//Helper functions
void setColor(int textColor,int bgColor);
void placeVertical(char board[10][10],int shipSize,int row,int col,bool &placeExist,int i=-1);
void playerAttack(char computerBoard[10][10],int &playerScore);
void startNewGame();

int main()
{
    showGameMenu();
    return 0;
}

//  Game menu
void showGameMenu()
{
	clearScreen();
	
	int n;
	cout<<"  ==================================================="<<endl;
	cout<<"            WELCOME TO THE BATTLESHIP GAME"<<endl<<endl<<endl;
	cout<<"  ==================================================="<<endl<<endl;
	cout<<"                     MAIN MENU"<<endl;
	cout<<"  ---------------------------------------------------"<<endl;
	cout<<"  1. Start New Game"<<endl;
	cout<<"  2. Instructions"<<endl;
	cout<<"  3. View Leadership board"<<endl;
	cout<<"  4. Exit"<<endl;
	cout<<"  ---------------------------------------------------"<<endl;
	cout<<"  Enter your choice (1-4): ";
	cin>>n;
	
	while(n<1 || n>4)
	{
		cout<<"You entered invalid choice!"<<endl;
		cout<<"Enter your choice again: ";
		cin>>n;
	}
	
	switch(n)
	{
		case 1:
			startNewGame();
			break;
		case 2:	
			instructions();
			break;
		case 3:
			//showLeaderboard();
			break;
		case 4:
		    return;
			break;		
	}
}


void startNewGame()
{       
	int mode,choice;
	char playerBoard[10][10],computerBoard[10][10];
	static int i=1;
	
	if(i==1)
	{
		initializeBoard(computerBoard);
		initializeBoard(playerBoard);
	}
	else //Resetting values to default
	{
		clearBoard(computerBoard);
		clearBoard(playerBoard);
	}
	
	i++;	
	
	for(int i=0;i<5;i++)
	{	
		playerVerticalShip[i]=false;
		computerVerticalShip[i]=false; 
	}
	
	for(int i=0 ; i<5 ; i++)
	{
		rowIdxPlayer[i]=-1;
		colIdxPlayer[i]=-1;
		rowIdxComputer[i]=-1;
		colIdxComputer[i]=-1;
	}
	
	
	cout<<endl<<"-------------------------------------"<<endl<<endl;
    cout<<"          START NEW GAME     "<<endl;
    cout<<endl<<"-------------------------------------"<<endl<<endl;
    
    cout<<endl<<"Choose mode(1-2): \n1. Player Vs Computer \n2. Player Vs Player"<<endl;
    cin>>mode;
    cin.ignore();
    
    while(mode<1 || mode>2)
	{
		cout<<endl<<"Invalid Choice,Enter Again: ";
		cin>>mode;
	}
	
	if(mode==2)
	{
		cout<<"Player vs Player is not implemented yet. Please wait for the next version."<<endl;
//		cout<<"Press any key to return to main menu.";
//		getch();
//		showGameMenu;
//		getch();
		return;
	}
  
    cout<<"Enter Player name: ";
    getline(cin,name);
    
    clearScreen();	
	vsComputer(playerBoard,computerBoard);
}


//Instructions
void instructions()
{
	cout<<"----------------------------------------------------"<<endl;
	cout<<"                  INSTRUCIONS                       "<<endl;
	cout<<"----------------------------------------------------"<<endl<<endl;
	cout<<"1. Place your ships on the board."<<endl;
	cout<<"2. You and Computer take turns firing shots.  "<<endl;
	cout<<"3. \"X\" means hit and \"O\" means miss "<<endl;
	cout<<"4. Sink All enemy boats to win.  "<<endl;
	cout<<"5. Your score is based on Accuracy and speed.  "<<endl;
	cout<<"----------------------------------------------------"<<endl;
	cout<<"(Press any key to return to main menu)";
	getch();
	showGameMenu();
}


//Helper functions definition
void clearScreen() 
{
	system("CLS"); 
}


void clearBoard(char board[10][10])
{
	for(int i=0;i<10;i++)
	{
		for(int j=0;j<10;j++)
		{
			board[i][j]='~';
		}
	}
}


void initializeBoard(char board[10][10])
{
	for(int i=0;i<10;i++)
	{
		for(int j=0;j<10;j++)
		{
			board[i][j]='~';
		}
	}
}


void updateScore(int &score)
{
	if(isHit) 
	   score+=10;
	else
	   score-=1;
}


void setColor(int textColor,int bgColor)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), bgColor * 16 + textColor);
}


void playerAttack(char computerBoard[10][10], int &playerScore) //Player Attack function
{
	int row,col;	
	
	for(int i=0;i<playerTurns;i++)
	{
		cout<<endl<<"Enter row to hit: ";
	    cin>>row;
	    
	    while(row<0 || row>9)
	    {
	    	cout<<"Invalid input for row! Enter Again: ";
	    	cin>>row;
		}
		
		cout<<"Enter Column to hit: ";
		cin>>col;
		
		while(col<0 || col>9)
	    {
	    	cout<<"Invalid input for column! Enter Again:";
	    	cin>>col;
		}
		
		while(computerBoard[row][col]=='X' || computerBoard[row][col]=='O')
		{
			cout<<endl<<"Already attacked in this cell! Attack another cell.";
			cout<<endl<<"Enter row to hit: ";
	        cin>>row;
	        
	        while(row<0 || row>9)
	    	{
	  	 	 	cout<<endl<<"Invalid input for row! Enter Again:";
	    		cin>>row;
			}
			
			cout<<endl<<"Enter Column to hit: ";
			cin>>col;
		
			while(col<0 || col>9)
	   		{
	    		cout<<endl<<"Invalid input for columns! Enter Again:";
	    		cin>>col;
			}			
		}
		
		if(computerBoard[row][col]=='S')
		{
			isHit=true;
			computerBoard[row][col]='X';
			//computerboard[rowp][colp]='X';
			updateScore(playerScore);
		}
		
		else if(computerBoard[row][col]=='~')
		{
			isHit=false;
			computerBoard[row][col]='O';
			//computerboard[rowp][colp]='o';
			updateScore(playerScore);
		}		
	}
}


void computerAttack(char playerBoard[10][10], int &computerScore) //computer Attack function
{	
	srand(time(0));
	int row,col;
	
	for(int i=0;i<computerTurns;i++)
	{
		row=rand()%10;
		col=rand()%10;
	
		if(playerBoard[row][col]=='X' || playerBoard[row][col]=='O')
		{	
			i--;
			continue;
		}
		
		if(playerBoard[row][col]=='S')
		{	
			isHit=true;
			playerBoard[row][col]='X';
		//	playerboard[rowc][colc] = 'X';
			updateScore(computerScore);
		}
		
		else if(playerBoard[row][col]=='~')
		{	
			isHit=false;
			playerBoard[row][col] = 'O';
		//	playerboard[rowc][colc] = 'o';
			updateScore(computerScore);
		}
	}	
}


void placeVertical(char board[10][10],int shipSize,int row,int col,bool &placeExist,int i) //For vertical ship placement
{
	if(shipSize>10-row)
	{
		placeExist=false;
	}
	
	int endIdx=row+shipSize;
	for(int j=row;j<endIdx;j++)
	{
		if(board[j][col]=='S')
		{
			placeExist=false;
		}
	}
	
	if(placeExist)
	{
		rowIdxPlayer[i]=row;
		colIdxPlayer[i]=col;
		for(int j=row;j<endIdx;j++)
		{
			board[j][col]='S';
		}
		playerVerticalShip[i]=true;
	}
	else
	{
		placeExist=false;
	}
}


void printBoard(char board[10][10],bool hideships)
{
	
	if(hideships)
	{
	    // Print column headers (hardcoded)
    	cout << "       0     1     2     3     4     5     6     7     8     9  " << endl;

	    // Top border
	    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
	
	    // Row 0
	    cout << "  0 �"; 
	    for (int i = 0; i < 10; i++)
	    {
	        char cell = board[0][i];
	        setColor(7, 1); cout << "  ~  "; setColor(7,0); cout << "�";
	    }
	    cout << endl;
	    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----�" << endl;
	
	    // Row 1
	    cout << "  1 �"; 
	    for (int i = 0; i < 10; i++)
	    {
	        char cell = board[1][i];
	        if (cell == 'X') { setColor(15, 12); cout << "  X  "; setColor(7,0); }
	        else if (cell == 'O') { setColor(0, 8); cout << "  O  "; setColor(7,0); }
	        else { setColor(7, 1); cout << "  ~  "; setColor(7,0); } cout << "�";
	    }
	    cout << endl;
	    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----�" << endl;
	
	    // Row 2
	    cout << "  2 �"; 
	    for (int i = 0; i < 10; i++)
	    {
	        char cell = board[2][i];
	        if (cell == 'X') { setColor(15, 12); cout << "  X  "; setColor(7,0); }
	        else if (cell == 'O') { setColor(0, 8); cout << "  O  "; setColor(7,0); }
	        else { setColor(7, 1); cout << "  ~  "; setColor(7,0); }
			cout << "�";
	    }
	    cout << endl;
	    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----�" << endl;
	
	    // Row 3
	    cout << "  3 �"; 
	    for (int i = 0; i < 10; i++)
	    {
	        char cell = board[3][i];
	        if (cell == 'X') { setColor(15, 12); cout << "  X  "; setColor(7,0); }
	        else if (cell == 'O') { setColor(0, 8); cout << "  O  "; setColor(7,0); }
	        else { setColor(7, 1); cout << "  ~  "; setColor(7,0); } cout << "�";
	    }
	    cout << endl;
	    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----�" << endl;
	
	    // Row 4
	    cout << "  4 �"; 
	    for (int i = 0; i < 10; i++)
	    {
	        char cell = board[4][i];
	        if (cell == 'X') { setColor(15, 12); cout << "  X  "; setColor(7,0); }
	        else if (cell == 'O') { setColor(0, 8); cout << "  O  "; setColor(7,0); }
	        else { setColor(7, 1); cout << "  ~  "; setColor(7,0); } cout << "�";
	    }
	    cout << endl;
	    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----�" << endl;
	
	    // Row 5
	    cout << "  5 �"; 
	    for (int i = 0; i < 10; i++)
	    {
	        char cell = board[5][i];
	        if (cell == 'X') { setColor(15, 12); cout << "  X  "; setColor(7,0); }
	        else if (cell == 'O') { setColor(0, 8); cout << "  O  "; setColor(7,0); }
	        else { setColor(7, 1); cout << "  ~  "; setColor(7,0); } cout << "�";
	    }
	    cout << endl;
	    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----�" << endl;
	
	    // Row 6
	    cout << "  6 �"; 
	    for (int i = 0; i < 10; i++)
	    {
	        char cell = board[6][i];
	        if (cell == 'X') { setColor(15, 12); cout << "  X  "; setColor(7,0); }
	        else if (cell == 'O') { setColor(0, 8); cout << "  O  "; setColor(7,0); }
	        else { setColor(7, 1); cout << "  ~  "; setColor(7,0); } cout << "�";
	    }
	    cout << endl;
	    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----�" << endl;
	
	    // Row 7
	    cout << "  7 �"; 
	    for (int i = 0; i < 10; i++)
	    {
	        char cell = board[7][i];
	        if (cell == 'X') { setColor(15, 12); cout << "  X  "; setColor(7,0); }
	        else if (cell == 'O') { setColor(0, 8); cout << "  O  "; setColor(7,0); }
	        else { setColor(7, 1); cout << "  ~  "; setColor(7,0); }
	        cout << "�";
	    }
	    cout << endl;
	    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----�" << endl;
	
	    // Row 8
	    cout << "  8 �"; 
	    for (int i = 0; i < 10; i++)
	    {
	        char cell = board[8][i];
	        if (cell == 'X') { setColor(15, 12); cout << "  X  "; setColor(7,0); }
	        else if (cell == 'O') { setColor(0, 8); cout << "  O  "; setColor(7,0); }
	        else { setColor(7, 1); cout << "  ~  "; setColor(7,0); } cout << "�";
	    }
	    cout << endl;
	    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----�" << endl;
	
	    // Row 9
	    cout << "  9 �"; 
	    for (int i = 0; i < 10; i++)
	    {
	        char cell = board[9][i];
	        if (cell == 'X') { setColor(15, 12); cout << "  X  "; setColor(7,0); }
	        else if (cell == 'O') { setColor(0, 8); cout << "  O  "; setColor(7,0); }
	        else { setColor(7, 1); cout << "  ~  "; setColor(7,0); } cout << "�";
	    }
	    cout << endl;
	
	    // Bottom border
	    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
	    
	}
	
    else
    {
		// Print column headers (hardcoded)
	    cout << "       0     1     2     3     4     5     6     7     8     9  " << endl;
	
	    // Top border
	    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
	
	    // Row 0
	    cout << "  0 �"; 
	    for (int i = 0; i < 10; i++)
	    {
	        char cell = board[0][i];
			if (cell == 'S') { setColor(15, COLOR); cout << "  S  "; setColor(7,0); }
	        else { setColor(7, 1); cout << "  ~  "; setColor(7,0); }
	        cout << "�";    }
	    cout << endl;
	    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----�" << endl;
	
	    // Row 1
	    cout << "  1 �"; 
	    for (int i = 0; i < 10; i++)
	    {
	        char cell = board[1][i];
	        if (cell == 'S') { setColor(15, COLOR); cout << "  S  "; setColor(7,0); }
	        else { setColor(7, 1); cout << "  ~  "; setColor(7,0); }
	        cout << "�";
	    }
	    cout << endl;
	    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----�" << endl;
	
	    // Row 2
	    cout << "  2 �"; 
	    for (int i = 0; i < 10; i++)
	    {
	        char cell = board[2][i];
	        if (cell == 'S') { setColor(15, COLOR); cout << "  S  "; setColor(7,0); }
	        else { setColor(7, 1); cout << "  ~  "; setColor(7,0); }
	        cout << "�";
	    }
	    cout << endl;
	    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----�" << endl;
	
	    // Row 3
	    cout << "  3 �"; 
	    for (int i = 0; i < 10; i++)
	    {
	        char cell = board[3][i];
	        if (cell == 'S') { setColor(15, COLOR); cout << "  S  "; setColor(7,0); }
	        else { setColor(7, 1); cout << "  ~  "; setColor(7,0); }
	        cout << "�";
	    }
	    cout << endl;
	    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----�" << endl;
	
	    // Row 4
	    cout << "  4 �"; 
	    for (int i = 0; i < 10; i++)
	    {
	        char cell = board[4][i];
			if (cell == 'S') { setColor(15, COLOR); cout << "  S  "; setColor(7,0); }
	        else { setColor(7, 1); cout << "  ~  "; setColor(7,0); }
	        cout << "�";    }
	    cout << endl;
	    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----�" << endl;
	
	    // Row 5
	    cout << "  5 �"; 
	    for (int i = 0; i < 10; i++)
	    {
	        char cell = board[5][i];
			if (cell == 'S') { setColor(15, COLOR); cout << "  S  "; setColor(7,0); }
	        else { setColor(7, 1); cout << "  ~  "; setColor(7,0); }
	        cout << "�";    }
	    cout << endl;
	    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----�" << endl;
	
	    // Row 6
	    cout << "  6 �"; 
	    for (int i = 0; i < 10; i++)
	    {
	        char cell = board[6][i];
			if (cell == 'S') { setColor(15, COLOR); cout << "  S  "; setColor(7,0); }
	        else { setColor(7, 1); cout << "  ~  "; setColor(7,0); }
	        cout << "�";    }
	    cout << endl;
	    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----�" << endl;
	
	    // Row 7
	    cout << "  7 �"; 
	    for (int i = 0; i < 10; i++)
	    {
	        char cell = board[7][i];
	        if (cell == 'S') { setColor(15, COLOR); cout << "  S  "; setColor(7,0); }
	        else { setColor(7, 1); cout << "  ~  "; setColor(7,0); }
	        cout << "�";
	    }
	    cout << endl;
	    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----�" << endl;
	
	    // Row 8
	    cout << "  8 �"; 
	    for (int i = 0; i < 10; i++)
	    {
	        char cell = board[8][i];
			if (cell == 'S') { setColor(15, COLOR); cout << "  S  "; setColor(7,0); }
	        else { setColor(7, 1); cout << "  ~  "; setColor(7,0); }
	        cout << "�";    }
	    cout << endl;
	    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----�" << endl;
	
	    // Row 9
	    cout << "  9 �"; 
	    for (int i = 0; i < 10; i++)
	    {
	        char cell = board[9][i];
			if (cell == 'S') { setColor(15, COLOR); cout << "  S  "; setColor(7,0); }
	        else { setColor(7, 1); cout << "  ~  "; setColor(7,0); }
	        cout << "�";
			    }
	    cout << endl;
	
	    // Bottom border
	    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
	    
			
	}

}


void setRandomShips(char board[10][10])
{
	srand(time(0));
	int shipSize[5]={5,4,3,3,2},row,col,size,endIdx;
	bool placeHorizontally,placeExist=true;
	
	for(int i=0;i<5;i++)
	{
		size=shipSize[i]; //Current ship size
		bool flag=true;
		while(flag)
		{
			placeExist=true;
			row=rand()%10;
			col=rand()%10;
			placeHorizontally=rand()%2;
			
			if(placeHorizontally)   //horizontal ship placement
			{
				if(size>10-col)
				{
					continue;
				}
				else
				{   
					endIdx=col+size;
					for(int j=col;j<endIdx;j++)
			    	{			
						if(board[row][j]=='S')
						{
	                      placeExist=false;
	                      break;
						}
		        	}
		        	
		        	if(placeExist)
		        	{
		        		if(playerTurnCheck) //Check if it is for player or computer random ship placement
		        		{
		        			rowIdxPlayer[i]=row;
		        			colIdxPlayer[i]=col;
						}
						else
						{
							rowIdxComputer[i]=row;
		        			colIdxComputer[i]=col;	
						}
		        
		        		for(int j=col;j<endIdx;j++)
			    		{			
							board[row][j]='S';
		        		}
					}
					else
					{
						continue;
					}
				}						
			}
			
			else //Vertical ship placement
			{
				endIdx=row+size;
				if(size>10-row)     //Boundry validation
				{
					continue;
				}
				
				else
				{  
					for(int j=row;j<endIdx;j++)
			    	{			
						if(board[j][col]=='S')    
						{
	                      placeExist=false;
	                      break;
						}
		        	}
		        	
		        	if(placeExist)
		        	{
		        		if(playerTurnCheck) //Check if it is for player or computer random ship placement
		        		{
		        			rowIdxPlayer[i]=row;
		        			colIdxPlayer[i]=col;
		        			playerVerticalShip[i]=true;
						}
						else
						{
							rowIdxComputer[i]=row;
		        			colIdxComputer[i]=col;	
		        			computerVerticalShip[i]=true;
						}
		        		
		        		for(int j=row;j<endIdx;j++)
			    		{			
							board[j][col]='S';
		        		}
					}
					
					else
					{
						continue;
					}
		 			
				}
							
			}
			
			flag=false;
		}
				
	}
			
}



//Core vsComputer function definition
void vsComputer(char playerBoard[10][10],char computerBoard[10][10])
{
	srand(time(0));
	int shipSize,row,col,endIdx,ch;
	bool chooseColor=true,vertical,placeExist=true,flag=true;
	char choice,randomChoice;
	
	initializeBoard(playerBoard);
	initializeBoard(computerBoard);
	
	if(chooseColor)  
	{
	    cout<<endl<<"Choose your battleships color(0-8): "<<endl;
   	    
   	    cout<<"0. Black"<<endl;
   	    setColor(1,0);
   	    cout<<"1. Blue"<<endl;
   	    setColor(2,0);
   	    cout<<"2. Green"<<endl;
   	    setColor(3,0);
   	    cout<<"3. Cyan"<<endl;
   	    setColor(4,0);
   	    cout<<"4. Red"<<endl;
   	    setColor(5,0);
   	    cout<<"5. Magenta"<<endl;
   	    setColor(6,0);
   	    cout<<"6. Yellow"<<endl;
   	    setColor(7,0);
   	    cout<<"7. White"<<endl;
   	    setColor(8,0);
   	    cout<<"8. Grey"<<endl;
   	    setColor(7,0);
   	    
   	    cin>>COLOR;      
   	    
   	    while(COLOR<1 || COLOR>8)
   		{
  		 	cout<<endl<<"Invalid choice of colors!"<<endl<<"Enter your choice again: ";
   			cin>>COLOR;
   	    }
   		clearScreen();
	   // shipColor(choice); 
		chooseColor=false;    
	}
	
	printBoard(playerBoard,false);
	
	for(int i=0;i<5;i++)
	{
		vertical=true;
		if(i==0)
		{
			cout<<"Do you want to place all of your ships RANDOMLY (Y/N) ? ";
			cin>>randomChoice;
			
			while(randomChoice!='N' && randomChoice!='n' && randomChoice!='Y' && randomChoice!='y')
			{
				cout<<endl<<"Invalid choice! Enter again(Y/N): ";
				cin>>randomChoice;
				clearScreen();
			}
			
			if(randomChoice=='Y' || randomChoice=='y')
			{
				clearScreen();
				playerTurnCheck=true;
				setRandomShips(playerBoard);
				printBoard(playerBoard,false);
				playerTurnCheck=false;
				break;
			}
		}
		
		switch(i)
		{
		    case 0:
		        cout<<"You have an Aircraft Carrier of size 5 and you have to place it."<<endl;
		        shipSize=5;
		        break;
		
		    case 1:
		        cout<<endl<<"You have a Battleship of size 4 and you have to place it."<<endl;
		        shipSize=4;
		        break;
		
		    case 2:
		        cout<<endl<<"You have a Destroyer of size 3 and you have to place it."<<endl;
		        shipSize=3;
		        break;
		
		    case 3:
		        cout<<endl<<"You have a Submarine of size 3 and you have to place it."<<endl;
		        shipSize=3;
		        break;
		
		    case 4:
		        cout<<endl<<"You have a Patrol Boat of size 2 and you have to place it."<<endl;
		        shipSize=2;
		        break;
		
		    default:
		        cout<<"Invalid ship index."<<endl;
		        break;
		}
	
		
		cout<<"Choose Placement Option: "<<endl; 
		cout<<"1. Manual "<<endl;
		cout<<"2. Random "<<endl;
		cin>>ch;
		
		while(ch<1 || ch>2)
		{
			cout<<endl<<"Invalid Choice! Enter again: ";
			cin>>ch;
		}
		cout<<endl;
		
		if(ch==1)
		{
			cout<<endl<<"Enter row number (0-9): ";
			cin>>row;
			rowIdxPlayer[i]=row;
			
			while(row<0 || row>9)
		    {
				cout<<"Enter Valid row (0-9): ";
				cin>>row;
				rowIdxPlayer[i]=row;
		 		clearScreen();
	    	}
			
			cout<<"Enter Column Number (0-9): ";
			cin>>col;
			colIdxPlayer[i]=col;
			
			while(col<0 || col>9)
			{
				cout<<"Enter Valid Column (0-9): ";
				cin>>col;
				colIdxPlayer[i]=col;
				clearScreen();
			}
			
			while(shipSize>10-col)
			{
				cout<<"Ship can not be placed here because it is going out of the boundary."<<endl;
				cout<<"Enter column again: ";
				cin>>col;
				colIdxPlayer[i]=col;
				while(col<0 || col>9)
				{
					cout<<"Enter Valid Column: ";
					cin>>col;
					colIdxPlayer[i]=col;
					clearScreen();
				}
			}
			
			endIdx=col+shipSize;
			for(int j=col;j<endIdx;j++)
			{
				if(playerBoard[row][j]=='S')
				{
					placeExist=false;
				}
			}
			
			while(!placeExist)
			{
				cout<<"Your ship is overlapping. There are alredy ships placed here"<<endl;
				cout<<"Enter row again: ";
				cin>>row;
				rowIdxPlayer[i]=row;
				
				while(row<0 || row>9)
		    	{
					cout<<"Enter Valid row (0-9): ";
					cin>>row;
					rowIdxPlayer[i]=row;
			 		clearScreen();
	    		}
	    		
	    		cout<<"Enter column again: ";
				cin>>col;
				colIdxPlayer[i]=col;
				
				while(col<0 || col>9)
				{
					cout<<"Invalid input for column! Enter column again: ";
					cin>>col;
					colIdxPlayer[i]=col;
				}
				
				while(shipSize>10-col)
				{
					cout<<"Ship can not be placed here because it is going out of the boundary."<<endl;
					cout<<"Enter column again: ";
					cin>>col;
					colIdxPlayer[i]=col;
					while(col<0 || col>9)
					{
						cout<<"Enter Valid Column: ";
						cin>>col;
						colIdxPlayer[i]=col;
						clearScreen();
					}
				}
				
				placeExist=true;
				endIdx=col+shipSize;
				
				for(int j=col;j<endIdx;j++)
			    {
					if(playerBoard[row][j]=='S')
					{
						placeExist=false;
					}
			    }
			    
			    if(placeExist)
			    {
			    	for(int j=col;j<endIdx;j++)
			    	{
			    		playerBoard[row][j]='S';
					}
				}
			}
			for(int j=col;j<endIdx;j++)
    		{
       			playerBoard[row][j]='S';
   			}
   			
   			printBoard(playerBoard,false);
	   		cout<<endl<<"Do you want to place it vertically (Y/N): "; //Asking for vertical placement
			cin>>choice;
			
			while(choice!='N' && choice!='n' && choice!='Y' && choice!='y')
			{
				cout<<endl<<"Invalid choice! Enter again(Y/N): ";
				cin>>choice;
				clearScreen();
			}
			
			if(choice=='Y' || choice=='y')
			{
				
				if(shipSize>10-row)
				{
					cout<<endl<<"Ship Can't be Placed vertically because it is going out of the boundary."<<endl;
					vertical=false;
					continue;
				}
				
				endIdx=row+shipSize;
				for(int j=row;j<endIdx;j++)
				{ 
				    if(j==row)				//It is So that it does not check smae box for 'S' therefore continue it
					{
						continue;
					}
					
					if(playerBoard[j][col]=='S')
					{
						vertical=false ;
						break;
					}
				}
				
				if(!vertical)
				{
					cout<<endl<<"Ship can not be placed vertically because it is overlapping."<<endl;
				}
				
				if(vertical)
				{
			    	rowIdxPlayer[i]=row;
    	        	colIdxPlayer[i]=col;
		        	playerVerticalShip[i]=true; //tracks player ships vertically
		        	
					for(int j=0;j<shipSize;j++)    	
					{				
						playerBoard[row][col+j]='~';
					}
					
					for(int j=0;j<shipSize;j++)    	
					{				
						playerBoard[row+j][col]='S';
					}	
				}		
		    }
	    }
	    
		else if(ch==2) //Random placement if(ch==2)
		{
			flag=true;
			while(flag)
			{
				placeExist=true;
				row=rand()%10;
				col=rand()%10;
				bool placeHorizontally=rand()%2;
				
				if(shipSize>10-col)
				{
					continue;
				}
				
				if(placeHorizontally) //For horizontal random ship placement
				{
					endIdx=col+shipSize;
					for(int j=col;j<endIdx;j++)
					{
						if(playerBoard[row][j]=='S')
						{
							placeExist=false;
						}
					}
				
					if(placeExist)
					{
						rowIdxPlayer[i]=row;
						colIdxPlayer[i]=col;
						
						for(int j=col;j<endIdx;j++)
						{
							playerBoard[row][j]='S';
						}
					}
					else
					{
						continue;
					}
				}
				else //For vertical random ship placement
				{
					placeVertical(playerBoard,shipSize,row,col,placeExist,i);
					if(!placeExist) continue;
				}
				
				flag=false; //If all validation conditions are satisfied
			}
		}
		
		clearScreen();
	    printBoard(playerBoard,false);	
	}
	cout<<endl<<"Your ships have been placed!"<<endl;
	cout<<endl<<"Now, computer is placing its ships..."<<endl;
	setRandomShips(computerBoard);
	cout<<endl<<"Computer has placed its ships. Press any key to continue."<<endl;
	getch();
	
	//-------------------------------------
	//Attacking starst from here
	//-------------------------------------
	
	int computerScore=0,playerScore=0;
	
	bool cShipDestroyed[5]={false};
	bool pShipDestroyed[5]={false};
	bool reduceComputerTurns[5]={false};
	bool reducePlayerTurns[5]={false};
	
	for(int turn=1;turn<=50;turn++)
	{
		clearScreen();
		
		if(turn==1)
		{
			cout<<"			  ====================================================================="<<endl;
			cout<<"				          Player vs Computer. Let's Start            "<<endl;
			cout<<"			  ====================================================================="<<endl<<endl;
		}
		
	    if(turn%2==1) //player's turn
		{
			cout<<endl<<name<<"'s Turn..."<<endl;
		
			cout<<endl<<"     COMPUTER'S BOARD                                      OPPONENT                                       "<<name<<"'s BOARD"<<endl;	
		    cout<<endl<<"     COMPUTER'S SCORE:"<<computerScore<<"                                                                 		  "<<name<<"'s SCORE:"<<playerScore<<endl;
			cout << "   		   	          0     1     2     3     4     5     6     7     8     9  " << endl;
			cout<<"  0 1 2 3 4 5 6 7 8 9	       +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+	       0 1 2 3 4 5 6 7 8 9"<<endl;	
			
			for(int i=0;i<10;i++) //loop to traverse through total rows (complete board)
			{
				cout<<i<<" ";
				for(int j=0;j<10;j++) //loop for traversal of left small board (COMPUTER BOARD)
				{
	    			if(computerBoard[i][j]=='S' || computerBoard[i][j]=='~')
	    				cout<<". ";
	    			else
	    				cout<<computerBoard[i][j]<<" ";
				}
				
				cout<<"      "<<i<<" � ";
				
		    	for(int j=0 ; j<10 ; j++) //loop for traversal of main board
		    	{	
		    		if(computerBoard[i][j]=='X')
		    		{
		    			setColor(15,12);
		    			cout<<"  "<<computerBoard[i][j]<<"  ";
		    			setColor(7,0); cout << "�";
					}
					
					else if(computerBoard[i][j]=='O')
					{
		    			setColor(0, 8);
		    			cout<<"  "<<computerBoard[i][j]<<"  ";
		    			setColor(7,0); cout << "�";
					}
					
					else
					{
						setColor(7,1);
						cout<< "  ~  ";
		    			setColor(7,0);
						cout << "�";
					}	
				}
				
				cout<<"         "<<i<<" ";
				
    			for(int j=0;j<10;j++) //loop for traversal of right small board (PLAYER BOARD)
    			{
    				if(playerBoard[i][j]=='S' || playerBoard[i][j]=='~')
	    				cout<<". ";
	    			else
	    				cout<<playerBoard[i][j]<<" ";
				}
    			cout<<endl;	
				
				cout<<"   			       +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+"<<endl;		
			}
			
			playerAttack(computerBoard,playerScore); //Calling playerAttack function
			
			// Check if computer ships are destroyed (after player attacks)
			// Ship 0:Aircraft Carrier (size 5)
			if(computerVerticalShip[0])  //for vertical orientation
			{
			    if((computerBoard[rowIdxComputer[0]][colIdxComputer[0]]=='X') && 
			       (computerBoard[rowIdxComputer[0]+1][colIdxComputer[0]]=='X') &&
			       (computerBoard[rowIdxComputer[0]+2][colIdxComputer[0]]=='X') && 
			       (computerBoard[rowIdxComputer[0]+3][colIdxComputer[0]]=='X') &&
			       (computerBoard[rowIdxComputer[0]+4][colIdxComputer[0]]=='X'))
			    {			
			        if(!cShipDestroyed[0])
			        {
			            computerTurns--;
			            cShipDestroyed[0]=true;
			            setColor(7, 2);
			            cout<<endl<<"Computer's Aircraft Carrier DESTROYED! Computer loses 1 turn!"<<endl;
			            getch();
			            setColor(7, 0);
			        }
			    }
			}
			else  // for horizontal orientation
			{
			    if((computerBoard[rowIdxComputer[0]][colIdxComputer[0]]=='X') && 
			       (computerBoard[rowIdxComputer[0]][colIdxComputer[0]+1]=='X') &&
			       (computerBoard[rowIdxComputer[0]][colIdxComputer[0]+2]=='X') && 
			       (computerBoard[rowIdxComputer[0]][colIdxComputer[0]+3]=='X') &&
			       (computerBoard[rowIdxComputer[0]][colIdxComputer[0]+4]=='X'))
			    {     		
			        if(!cShipDestroyed[0])
			        {
			            computerTurns--;
			            cShipDestroyed[0]=true;
			            setColor(7, 2);
			            cout<<endl<<"Computer's Aircraft Carrier DESTROYED! Computer loses 1 turn!"<<endl;
			            getch();
			            setColor(7, 0);
			        }
			    }
			}
			
			// Ship 1:Battleship (size 4)
			if(computerVerticalShip[1])
			{
			    if((computerBoard[rowIdxComputer[1]][colIdxComputer[1]]=='X') && 
			       (computerBoard[rowIdxComputer[1]+1][colIdxComputer[1]]=='X') &&
			       (computerBoard[rowIdxComputer[1]+2][colIdxComputer[1]]=='X') && 
			       (computerBoard[rowIdxComputer[1]+3][colIdxComputer[1]]=='X'))
			    {
			        if(!cShipDestroyed[1])
			        {
			            computerTurns--;
			            cShipDestroyed[1]=true;
			            setColor(7, 2);
			            cout<<endl<<"Computer's Battleship DESTROYED! Computer loses 1 turn!"<<endl;
			            getch();
			            setColor(7, 0);
			        }
			    }
			}
			else
			{
			    if((computerBoard[rowIdxComputer[1]][colIdxComputer[1]]=='X') && 
			       (computerBoard[rowIdxComputer[1]][colIdxComputer[1]+1]=='X') &&
			       (computerBoard[rowIdxComputer[1]][colIdxComputer[1]+2]=='X') && 
			       (computerBoard[rowIdxComputer[1]][colIdxComputer[1]+3]=='X'))
			    {
			        if(!cShipDestroyed[1])
			        {
			            computerTurns--;
			            cShipDestroyed[1]=true;
			            setColor(7, 2);
			            cout<<endl<<"Computer's Battleship DESTROYED! Computer loses 1 turn!"<<endl;
			            getch();
			            setColor(7, 0);
			        }
			    }
			}
			
			// Ship 2:Destroyer (size 3)
			if(computerVerticalShip[2])
			{
			    if((computerBoard[rowIdxComputer[2]][colIdxComputer[2]]=='X') && 
			       (computerBoard[rowIdxComputer[2]+1][colIdxComputer[2]]=='X') &&
			       (computerBoard[rowIdxComputer[2]+2][colIdxComputer[2]]=='X'))
			    {
			        if(!cShipDestroyed[2])
			        {
			            computerTurns--;
			            cShipDestroyed[2]=true;
			            setColor(7, 2);
			            cout<<endl<<"Computer's Destroyer DESTROYED! Computer loses 1 turn!"<<endl;
			            getch();
			            setColor(7, 0);
			        }
			    }
			}
			else
			{
			    if((computerBoard[rowIdxComputer[2]][colIdxComputer[2]]=='X') && 
			       (computerBoard[rowIdxComputer[2]][colIdxComputer[2]+1]=='X') &&
			       (computerBoard[rowIdxComputer[2]][colIdxComputer[2]+2]=='X'))
			    {
			        if(!cShipDestroyed[2])
			        {
			            computerTurns--;
			            cShipDestroyed[2]=true;
			            setColor(7, 2);
			            cout<<endl<<"Computer's Destroyer DESTROYED! Computer loses 1 turn!"<<endl;
			            getch();
			            setColor(7, 0);
			        }
			    }
			}
			
			// Ship 3:Submarine (size 3)
			if(computerVerticalShip[3])
			{
			    if((computerBoard[rowIdxComputer[3]][colIdxComputer[3]]=='X') && 
			       (computerBoard[rowIdxComputer[3]+1][colIdxComputer[3]]=='X') &&
			       (computerBoard[rowIdxComputer[3]+2][colIdxComputer[3]]=='X'))
			    {
			        if(!cShipDestroyed[3])
			        {
			            computerTurns--;
			            cShipDestroyed[3]=true;
			            setColor(7, 2);
			            cout<<endl<<"Computer's Submarine DESTROYED! Computer loses 1 turn!"<<endl;
			            getch();
			            setColor(7,0);
			        }
			    }
			}
			else
			{
			    if((computerBoard[rowIdxComputer[3]][colIdxComputer[3]]=='X') && 
			       (computerBoard[rowIdxComputer[3]][colIdxComputer[3]+1]=='X') &&
			       (computerBoard[rowIdxComputer[3]][colIdxComputer[3]+2]=='X'))
			    {
			        if(!cShipDestroyed[3])
			        {
			            computerTurns--;
			            cShipDestroyed[3] = true;
			            setColor(7, 2);
			            cout<<endl<<"Computer's Submarine DESTROYED! Computer loses 1 turn!"<<endl;
			            getch();
			            setColor(7, 0);
			        }
			    }
			}
			
			// Ship 4:Patrol Boat (size 2)
			if(computerVerticalShip[4])
			{
			    if((computerBoard[rowIdxComputer[4]][colIdxComputer[4]]=='X') && 
			       (computerBoard[rowIdxComputer[4]+1][colIdxComputer[4]]=='X'))
			    {
			        if(!cShipDestroyed[4])
			        {
			            computerTurns--;
			            cShipDestroyed[4] = true;
			            setColor(7, 2);
			            cout<<endl<<"Computer's Patrol Boat DESTROYED! Computer loses 1 turn!"<<endl;
			            getch();
			            setColor(7, 0);
			        }
			    }
			}
			else
			{
			    if((computerBoard[rowIdxComputer[4]][colIdxComputer[4]]=='X') && 
			       (computerBoard[rowIdxComputer[4]][colIdxComputer[4]+1]=='X'))
			    {
			        if(!cShipDestroyed[4])
			        {
			            computerTurns--;
			            cShipDestroyed[4]=true;
			            setColor(7, 2);
			            cout<<endl<<"Computer's Patrol Boat DESTROYED! Computer loses 1 turn!"<<endl;
			            getch();
			            setColor(7, 0);
			        }
			    }
			}
			
			clearScreen();
			cout<<endl<<name<<"'s Attack Successful..."<<endl;
		
			cout<<endl<<"     COMPUTER'S BOARD                                      OPPONENT                                       "<<name<<"'s BOARD"<<endl;	
		    cout<<endl<<"     COMPUTER'S SCORE:"<<computerScore<<"                                                                 		  "<<name<<"'s SCORE:"<<playerScore<<endl;
			cout << "   		   	          0     1     2     3     4     5     6     7     8     9  " << endl;
			cout<<"  0 1 2 3 4 5 6 7 8 9	       +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+	       0 1 2 3 4 5 6 7 8 9"<<endl;	
			
			for(int i=0;i<10;i++) //loop to traverse through total rows (complete board)
			{
				cout<<i<<" ";
				for(int j=0;j<10;j++) //loop for traversal of left small board (COMPUTER BOARD)
				{
	    			if(computerBoard[i][j]=='S' || computerBoard[i][j]=='~')
	    				cout<<". ";
	    			else
	    				cout<<computerBoard[i][j]<<" ";
				}
				
				cout<<"      "<<i<<" � ";
				
		    	for(int j=0 ; j<10 ; j++) //loop for traversal of main board
		    	{	
		    		if(computerBoard[i][j]=='X')
		    		{
		    			setColor(15,12);
		    			cout<<"  "<<computerBoard[i][j]<<"  ";
		    			setColor(7,0); cout << "�";
					}
					
					else if(computerBoard[i][j]=='O')
					{
		    			setColor(0, 8);
		    			cout<<"  "<<computerBoard[i][j]<<"  ";
		    			setColor(7,0); cout << "�";
					}
					
					else
					{
						setColor(7,1);
						cout<< "  ~  ";
		    			setColor(7,0);
						cout << "�";
					}	
				}
				
				cout<<"         "<<i<<" ";
				
    			for(int j=0;j<10;j++) //loop for traversal of right small board (PLAYER BOARD)
    			{
    				if(playerBoard[i][j]=='S' || playerBoard[i][j]=='~')
	    				cout<<". ";
	    			else
	    				cout<<playerBoard[i][j]<<" ";
				}
    			cout<<endl;	
				
				cout<<"   			       +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+"<<endl;		
			}
			cout<<endl<<name<<"'s Attack was Successful!"<<endl;
			cout<<"Press any key to continue.";
			getch();
			
			//Checking winning condition for player
			if(cShipDestroyed[0] && cShipDestroyed[1] && cShipDestroyed[2] && cShipDestroyed[3] && cShipDestroyed[4])
			{
				setColor(7, 2);
				cout<<"CONGRATULATIONS! YOU won the match."<<endl;
				setColor(7, 0);
				cout<<"Press any key to return to main menu.";
				getch();
				showGameMenu();
			}
			
		}
	
        else //turn%2==0 means COMPUTER'S Turn
		{	
			cout<<endl<<"COMPUTER'S Turn..."<<endl;
		
			cout<<endl<<"     COMPUTER'S BOARD                                      OPPONENT                                       "<<name<<"'s BOARD"<<endl;	
		    cout<<endl<<"     COMPUTER'S SCORE:"<<computerScore<<"                                                                 		  "<<name<<"'s SCORE:"<<playerScore<<endl;
			cout << "   		   	          0     1     2     3     4     5     6     7     8     9  " << endl;
			cout<<"  0 1 2 3 4 5 6 7 8 9	       +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+	       0 1 2 3 4 5 6 7 8 9"<<endl;	
			
			for(int i=0;i<10;i++) //loop to traverse through total rows (complete board)
			{
				cout<<i<<" ";
				for(int j=0;j<10;j++) //loop for traversal of left small board (COMPUTER BOARD)
				{
	    			if(computerBoard[i][j]=='S' || computerBoard[i][j]=='~')
	    				cout<<". ";
	    			else
	    				cout<<computerBoard[i][j]<<" ";
				}
				
				cout<<"      "<<i<<" � ";
				
		    	for(int j=0;j<10;j++) //loop for traversal of main board
		    	{	
		    		if(playerBoard[i][j]=='X')
		    		{
		    			setColor(15,12);
		    			cout<<"  "<<playerBoard[i][j]<<"  ";
		    			setColor(7,0); cout << "�";
					}
					
					else if(playerBoard[i][j]=='O')
					{
		    			setColor(0, 8);
		    			cout<<"  "<<computerBoard[i][j]<<"  ";
		    			setColor(7,0); cout << "�";
					}
					
					else
					{
						setColor(7,1);
						cout<< "  ~  ";
		    			setColor(7,0);
						cout << "�";
					}	
				}
				
				cout<<"         "<<i<<" ";
				
    			for(int j=0;j<10;j++) //loop for traversal of right small board (PLAYER BOARD)
    			{
    				if(playerBoard[i][j]=='S' || playerBoard[i][j]=='~')
	    				cout<<". ";
	    			else
	    				cout<<playerBoard[i][j]<<" ";
				}
    			cout<<endl;	
				
				cout<<"   			       +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+"<<endl;		
			}
			
			computerAttack(playerBoard,computerScore); //Calling playerAttack function
			clearScreen();
			cout<<endl<<"COMPUTER'S Turn..."<<endl;
		
			cout<<endl<<"     COMPUTER'S BOARD                                      OPPONENT                                       "<<name<<"'s BOARD"<<endl;	
		    cout<<endl<<"     COMPUTER'S SCORE:"<<computerScore<<"                                                                 		  "<<name<<"'s SCORE:"<<playerScore<<endl;
			cout << "   		   	          0     1     2     3     4     5     6     7     8     9  " << endl;
			cout<<"  0 1 2 3 4 5 6 7 8 9	       +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+	       0 1 2 3 4 5 6 7 8 9"<<endl;	
			
			for(int i=0;i<10;i++) //loop to traverse through total rows (complete board)
			{
				cout<<i<<" ";
				for(int j=0;j<10;j++) //loop for traversal of left small board (COMPUTER BOARD)
				{
	    			if(computerBoard[i][j]=='S' || computerBoard[i][j]=='~')
	    				cout<<". ";
	    			else
	    				cout<<computerBoard[i][j]<<" ";
				}
				
				cout<<"      "<<i<<" � ";
				
		    	for(int j=0;j<10;j++) //loop for traversal of main board
		    	{	
		    		if(playerBoard[i][j]=='X')
		    		{
		    			setColor(15,12);
		    			cout<<"  "<<playerBoard[i][j]<<"  ";
		    			setColor(7,0); cout << "�";
					}
					
					else if(playerBoard[i][j]=='O')
					{
		    			setColor(0, 8);
		    			cout<<"  "<<playerBoard[i][j]<<"  ";
		    			setColor(7,0); cout << "�";
					}
					
					else
					{
						setColor(7,1);
						cout<< "  ~  ";
		    			setColor(7,0);
						cout << "�";
					}	
				}
				
				cout<<"         "<<i<<" ";
				
    			for(int j=0;j<10;j++) //loop for traversal of right small board (PLAYER BOARD)
    			{
    				if(playerBoard[i][j]=='S' || playerBoard[i][j]=='~')
	    				cout<<". ";
	    			else
	    				cout<<playerBoard[i][j]<<" ";
				}
    			cout<<endl;	
				
				cout<<"   			       +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+"<<endl;		
			}	
			
			cout<<endl<<"COMPUTER'S Attack was successful! Press any key to continue.";
			getch();
			
			// Check if player ships are destroyed (after computer attacks)
			// Ship 0:Aircraft Carrier (size 5)
			if(playerVerticalShip[0])  //for vertical orientation
			{
			    if((playerBoard[rowIdxPlayer[0]][colIdxPlayer[0]]=='X') && 
			       (playerBoard[rowIdxPlayer[0]+1][colIdxPlayer[0]]=='X') &&
			       (playerBoard[rowIdxPlayer[0]+2][colIdxPlayer[0]]=='X') && 
			       (playerBoard[rowIdxPlayer[0]+3][colIdxPlayer[0]]=='X') &&
			       (playerBoard[rowIdxPlayer[0]+4][colIdxPlayer[0]]=='X'))
			    {			
			        if(!pShipDestroyed[0])
			        {
			            playerTurns--;
			            pShipDestroyed[0]=true;
			            setColor(15,12);
			            cout<<endl<<"Your Aircraft Carrier DESTROYED! You lose 1 turn!"<<endl;
			            getch();
			            setColor(7,0);
			        }
			    }
			}
			else  //for horizontal orientation
			{
			    if((playerBoard[rowIdxPlayer[0]][colIdxPlayer[0]]=='X') && 
			       (playerBoard[rowIdxPlayer[0]][colIdxPlayer[0]+1]=='X') &&
			       (playerBoard[rowIdxPlayer[0]][colIdxPlayer[0]+2]=='X') && 
			       (playerBoard[rowIdxPlayer[0]][colIdxPlayer[0]+3]=='X') &&
			       (playerBoard[rowIdxPlayer[0]][colIdxPlayer[0]+4]=='X'))
			    {     		
			        if(!pShipDestroyed[0])
			        {
			            playerTurns--;
			            pShipDestroyed[0]=true;
			            setColor(15,12);
			            cout<<endl<<"Your Aircraft Carrier DESTROYED! You lose 1 turn!"<<endl;
			            getch();
			            setColor(7,0);
			        }
			    }
			}
			
			// Ship 1:Battleship (size 4)
			if(playerVerticalShip[1])
			{
			    if((playerBoard[rowIdxPlayer[1]][colIdxPlayer[1]]=='X') && 
			       (playerBoard[rowIdxPlayer[1]+1][colIdxPlayer[1]]=='X') &&
			       (playerBoard[rowIdxPlayer[1]+2][colIdxPlayer[1]]=='X') && 
			       (playerBoard[rowIdxPlayer[1]+3][colIdxPlayer[1]]=='X'))
			    {
			        if(!pShipDestroyed[1])
			        {
			            playerTurns--;
			            pShipDestroyed[1]=true;
			            setColor(15, 12);
			            cout<<endl<<"Your Battleship DESTROYED! You lose 1 turn!"<<endl;
			            getch();
			            setColor(7,0);
			        }
			    }
			}
			else
			{
			    if((playerBoard[rowIdxPlayer[1]][colIdxPlayer[1]]=='X') && 
			       (playerBoard[rowIdxPlayer[1]][colIdxPlayer[1]+1]=='X') &&
			       (playerBoard[rowIdxPlayer[1]][colIdxPlayer[1]+2]=='X') && 
			       (playerBoard[rowIdxPlayer[1]][colIdxPlayer[1]+3]=='X'))
			    {
			        if(!pShipDestroyed[1])
			        {
			            playerTurns--;
			            pShipDestroyed[1]=true;
			            setColor(15, 12);
			            cout<<endl<<"Your Battleship DESTROYED! You lose 1 turn!"<<endl;
			            getch();
			            setColor(7, 0);
			        }
			    }
			}
			
			// Ship 2:Destroyer (size 3)
			if(playerVerticalShip[2])
			{
			    if((playerBoard[rowIdxPlayer[2]][colIdxPlayer[2]]=='X') && 
			       (playerBoard[rowIdxPlayer[2]+1][colIdxPlayer[2]]=='X') &&
			       (playerBoard[rowIdxPlayer[2]+2][colIdxPlayer[2]]=='X'))
			    {
			        if(!pShipDestroyed[2])
			        {
			            playerTurns--;
			            pShipDestroyed[2]=true;
			            setColor(15, 12);
			            cout<<endl<<"Your Destroyer DESTROYED! You lose 1 turn!"<<endl;
			            getch();
			            setColor(7, 0);
			        }
			    }
			}
			else
			{
			    if((playerBoard[rowIdxPlayer[2]][colIdxPlayer[2]]=='X') && 
			       (playerBoard[rowIdxPlayer[2]][colIdxPlayer[2]+1]=='X') &&
			       (playerBoard[rowIdxPlayer[2]][colIdxPlayer[2]+2]=='X'))
			    {
			        if(!pShipDestroyed[2])
			        {
			            playerTurns--;
			            pShipDestroyed[2]=true;
			            setColor(15, 12);
			            cout<<endl<<"Your Destroyer DESTROYED! You lose 1 turn!"<<endl;
			            getch();
			            setColor(7, 0);
			        }
			    }
			}
			
			// Ship 3:Submarine (size 3)
			if(playerVerticalShip[3])
			{
			    if((playerBoard[rowIdxPlayer[3]][colIdxPlayer[3]]=='X') && 
			       (playerBoard[rowIdxPlayer[3]+1][colIdxPlayer[3]]=='X') &&
			       (playerBoard[rowIdxPlayer[3]+2][colIdxPlayer[3]]=='X'))
			    {
			        if(!pShipDestroyed[3])
			        {
			            playerTurns--;
			            pShipDestroyed[3]=true;
			            setColor(15, 12);
			            cout<<endl<<"Your Submarine DESTROYED! You lose 1 turn!"<<endl;
			            getch();
			            setColor(7, 0);
			        }
			    }
			}
			else
			{
			    if((playerBoard[rowIdxPlayer[3]][colIdxPlayer[3]]=='X') && 
			       (playerBoard[rowIdxPlayer[3]][colIdxPlayer[3]+1]=='X') &&
			       (playerBoard[rowIdxPlayer[3]][colIdxPlayer[3]+2]=='X'))
			    {
			        if(!pShipDestroyed[3])
			        {
			            playerTurns--;
			            pShipDestroyed[3]=true;
			            setColor(15, 12);
			            cout<<endl<<"Your Submarine DESTROYED! You lose 1 turn!"<<endl;
			            getch();
			            setColor(7, 0);
			        }
			    }
			}
			
			// Ship 4:Patrol Boat (size 2)
			if(playerVerticalShip[4])
			{
			    if((playerBoard[rowIdxPlayer[4]][colIdxPlayer[4]]=='X') && 
			       (playerBoard[rowIdxPlayer[4]+1][colIdxPlayer[4]]=='X'))
			    {
			        if(!pShipDestroyed[4])
			        {
			            playerTurns--;
			            pShipDestroyed[4]=true;
			            setColor(15, 12);
			            cout<<endl<<"Your Patrol Boat DESTROYED! You lose 1 turn!"<<endl;
			            getch();
			            setColor(7, 0);
			        }
			    }
			}
			else
			{
			    if((playerBoard[rowIdxPlayer[4]][colIdxPlayer[4]]=='X') && 
			       (playerBoard[rowIdxPlayer[4]][colIdxPlayer[4]+1]=='X'))
			    {
			        if(!pShipDestroyed[4])
			        {
			            playerTurns--;
			            pShipDestroyed[4]=true;
			            setColor(15, 12);
			            cout<<endl<<"Your Patrol Boat DESTROYED! You lose 1 turn!"<<endl;
			            getch();
			            setColor(7, 0);
			        }
			    }
		    }
			
			//Checking winning condition for computer
			if(pShipDestroyed[0] && pShipDestroyed[1] && pShipDestroyed [2] && pShipDestroyed[3] && pShipDestroyed[4])
			{
				setColor(15, 12);
				cout<<"OOPS! COMPUTER won the match."<<endl;
				setColor(7, 0);
				cout<<"Press any key to return to main menu.";
				getch();
				showGameMenu();
			}
	    }
	}
}
