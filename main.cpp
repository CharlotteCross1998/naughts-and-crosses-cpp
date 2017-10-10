/*

	Designed for 3x3 in mind, however the game has been made as scalable as possible.
	Source code by Brad Cross http://www.github.com/bradcross1998 distributed for free.
*/
#include <iostream>
#include <limits> //for clearing cin

using namespace std;

const int GRID_SIZE_Y = 3;
const int GRID_SIZE_X = 3;

int winner = 0;
bool DEBUG = false;

class CNaughts
{
	private:
		int state = 0;
		int grid[GRID_SIZE_X][GRID_SIZE_Y];
	public:
		void Initialise();
		void SetValue(int x, int y, int player);
		void Display();
		void InputCoordinates(int player, CNaughts* &cnaughts);
		int CheckState();
		void ChangeState(int _state);
		void CheckGame();
};

void CNaughts::Initialise()
{
	for (int x = 0; x < GRID_SIZE_X; x++) //initialise all values to 0
	{
		for (int y = 0; y < GRID_SIZE_Y; y++)
		{
			grid[x][y] = 0;
		}
	}
}

void CNaughts::SetValue(int x, int y, int player)
{
	if(DEBUG) cout << "DEBUG: x=" << x <<" || y=" << y << " || player=" << player <<"\n";
	grid[x][y] = player;
}

void CNaughts::Display() //display the board
{
	/*optional - Show grid numbers IE
	
		0 1 2
	0	x y x
	1   y x y
	2   x y x
	*/
	for (int x = 0; x < GRID_SIZE_X; x++)
	{
		for (int y = 0; y < GRID_SIZE_Y; y++)
		{
			cout << grid[x][y];
		}
		cout << "\n";
	}
}

int CNaughts::CheckState()
{
	if(DEBUG) cout << "DEBUG: Current state: " << state <<"\n";
	return state;
}

/*
	States:
		-1 - Error
		0 - Normal running
		1 - Game running
		2 - Winner found
		3 - Game finished - No winner
*/

void CNaughts::ChangeState(int _state)
{
	state = _state;
}

void CNaughts::CheckGame()
{
	//Check for winner
	for (int x = 0; x < GRID_SIZE_X; x++)
	{
		if(grid[x][0] != 0) //if there's a player
			if(grid[x][0] == grid[x][1] && grid[x][1] == grid[x][2])
			{ 
				state = 2;
				if(grid[x][0] == 1) winner = 1;
				else winner = 2;			
			}	
	}
	for (int y = 0; y < GRID_SIZE_Y; ++y)
	{
		if(grid[0][y] != 0)
			if(grid[0][y] == grid[1][y] && grid[1][y] == grid[2][y]) 
			{
				state = 2;
				if(grid[y][0] == 1) winner = 1;
				else winner = 2;
			}
	}
	//diagonal winners
	if (grid[1][1] != 0) //if the middle doesn't = 0
	{
		if(grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2])
		{
			state = 2;
			winner = grid[1][1];
		}		
		if(grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0])
		{
			state = 2;
			winner = grid[1][1];
		}
	}
	//End check for winner
	//Check for no moves left
	bool hasFinished = true;
	for (int x = 0; x < GRID_SIZE_X; x++)
	{
		for (int y = 0; y < GRID_SIZE_Y; ++y)
		{
			if(grid[x][y] == 0) hasFinished = false;
		}
	}
	if(hasFinished) state = 3;
	//End check for no moves left
	if(DEBUG) cout << "DEBUG: Checked game state.\n";
}

void CNaughts::InputCoordinates(int player, CNaughts* &cnaughts) //pass reference since we need to edit it directly
{
	bool isValid = false;
	int xCoordinate, yCoordinate;
	do //while the input isn't valid
	{
		cout << "Enter X coordinate for player " << player << ": ";
		cin >> xCoordinate;
		if (cin.fail() || xCoordinate < -1 || xCoordinate >= GRID_SIZE_X) //if input isn't an int or it is but it's out of bounds
		{		
			cout << "Coordinate not valid!\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clear and reset
		}
		else
		{
			cout << "Enter Y coordinate for player " << player << ": ";
			cin >> yCoordinate;
			if (cin.fail() || yCoordinate < -1 || yCoordinate >= GRID_SIZE_Y)
			{		
				cout << "Coordinate not valid!\n";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			else
			{
				if(grid[xCoordinate][yCoordinate] == 0) isValid = true; //and it's not alraedy been used by another player
				else cout << "Coordinate already in use!\n";
			}
		}
		//optional -> are you sure? y/n
	} while (!isValid);
	if (player == 1) cnaughts->SetValue(xCoordinate, yCoordinate, 1); //place the value into the array
	else cnaughts->SetValue(xCoordinate, yCoordinate, 2);
}

int main()
{
	CNaughts* cnaughts = new CNaughts;
	cnaughts->Initialise(); //initialise the board
	cnaughts->ChangeState(1); //change to game running state
	bool playerOne = true;
	while(cnaughts->CheckState() == 1) //whilst in the game state
	{
		if (playerOne)  //to swap between the players
		{
			cnaughts->InputCoordinates(1, cnaughts); 
			playerOne = false;
		}
		else 
		{
			cnaughts->InputCoordinates(2, cnaughts); 
			playerOne = true;
		}
		cnaughts->Display(); //display the board
		//check for winner or no more moves left
		cnaughts->CheckGame();
	}
	if(cnaughts->CheckState() == 2) cout << "We have a winner: Player " << winner << "!\n";
	else if(cnaughts->CheckState() == 3) cout << "No winner!\n";
	else
	{
		cout << "Something went wrong... \n";
		return -1;
	}
	cout << "Press enter to quit... ";
	cin.get();
	return 0;
}
