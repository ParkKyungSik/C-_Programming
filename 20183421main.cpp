#include <iostream>

using namespace std;

class Player
{
private:
	int score;
	int findedCards[8];
 
public:
	Player()
	{
		score = 0;
		for (int i = 0; i < 8; i++)
			findedCards[i] = 0;
	}
	int getfindedCards(int i) { return findedCards[i]; }
	int setScore()
	{
		int cnt = 0;
		for (int i = 0; i < 8; i++)
		{
			if (findedCards[i] != 0)
				cnt++;	
		}
		if (findedCards[6] == 1) 
			cnt++;
		return cnt;
	}
	void setfindedCards(int i, int n) { findedCards[i] = n; };
};

class Gameboard
{
private:
	int board[4][4];
	int numDatabase[8];
	void resetBasicBoard()
	{
		int n = 1;
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				board[i][j] = n;
				board[3 - i][3 - j] = n;
				n++;
			}
		}
	}
	void resetBoard()
	{
		int n;
		for (int i = 0; i < 8; i++)
			numDatabase[i] = 2;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				while (true)
				{
					n = rand() % 8 + 1;
					if (numDatabase[n - 1] != 0)
					{
						board[i][j] = n;
						numDatabase[n - 1] -= 1;
						break;
					}
				}
			}
		}
	}

public:
	Gameboard(int mode)
	{
		switch (mode)
		{
			case 1:
				resetBasicBoard();
				break;
			case 2:
				resetBoard();
				break;
			default:
				break;
		}
	}
	int getPosBoard(int x, int y) { return board[x][y]; }
};

int main()
{
	int mode, rawdata1, rawdata2;
	int posX1, posY1, posX2, posY2;
	int cnt = 0;
	int endTrigger = 0;
	int gamedata[8];
	for (int i = 0; i < 8; i++)
		gamedata[i] = 0;
	Player p1, p2;
	cout << "choose game mode" << endl;
	cout << "1. basic" << endl;
	cout << "2. random" << endl;
	cin >> mode;
	Gameboard game(mode);
	while (endTrigger != 8)
	{
		cout << endl;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (gamedata[game.getPosBoard(i, j) - 1] == 0) cout << 'x'; 
				else cout << game.getPosBoard(i, j);
			}
			cout << endl;
		}
		switch (cnt % 2)
		{
			case 0:
				cout << "P1's turn, choose two cards: ";
				cin >> rawdata1 >> rawdata2;
				while (rawdata1 == rawdata2)
				{
					cout << "you pick the same position!" << endl;
					cin >> rawdata1 >> rawdata2;
				}
				posX1 = rawdata1 / 10 - 1;
				posY1 = rawdata1 % 10 - 1;
				posX2 = rawdata2 / 10 - 1;
				posY2 = rawdata2 % 10 - 1;
				if (game.getPosBoard(posX1, posY1) == game.getPosBoard(posX2, posY2) && gamedata[game.getPosBoard(posX1, posY1) - 1] == 0)
				{
					gamedata[game.getPosBoard(posX1, posY1) - 1] = 1;
					p1.setfindedCards(game.getPosBoard(posX1, posY1) - 1, 1);
					endTrigger++;
					for (int i = 0; i < 4; i++)
					{
						for (int j = 0; j < 4; j++)
						{
							if (gamedata[game.getPosBoard(i, j) - 1] == 0) cout << 'x'; 
							else cout << game.getPosBoard(i, j);
						}
						cout << endl;
					}
					cout << "P1 found a matching pair! P1's score: " << p1.setScore() << ", P2's score: " << p2.setScore() << endl;
				}
				else if (game.getPosBoard(posX1, posY1) == game.getPosBoard(posX2, posY2)) cout << endl << "you cheater!" << endl;
				else
				{
					for (int i = 0; i < 4; i++)
					{
						for (int j = 0; j < 4; j++)
						{
							if (gamedata[game.getPosBoard(i, j) - 1] == 0) cout << 'x'; 
							else cout << game.getPosBoard(i, j);
						}
						cout << endl;
					}
					cout << "P1 failed to find a matching pair" << endl;
				}
				break;
			case 1:
				cout << "P2's turn, choose two cards: ";
				cin >> rawdata1 >> rawdata2;
				while (rawdata1 == rawdata2)
				{
					cout << "you pick the same position!" << endl;
					cin >> rawdata1 >> rawdata2;
				}
				posX1 = rawdata1 / 10 - 1;
				posY1 = rawdata1 % 10 - 1;
				posX2 = rawdata2 / 10 - 1;
				posY2 = rawdata2 % 10 - 1;
				if (game.getPosBoard(posX1, posY1) == game.getPosBoard(posX2, posY2) && gamedata[game.getPosBoard(posX1, posY1) - 1] == 0)
				{
					gamedata[game.getPosBoard(posX1, posY1) - 1] = 1;
					p2.setfindedCards(game.getPosBoard(posX1, posY1) - 1, 1);
					endTrigger++;
					for (int i = 0; i < 4; i++)
					{
						for (int j = 0; j < 4; j++)
						{
							if (gamedata[game.getPosBoard(i, j) - 1] == 0) cout << 'x'; 
							else cout << game.getPosBoard(i, j);
						}
						cout << endl;
					}
					cout << "P2 found a matching pair! P1's score: " << p1.setScore() << ", P2's score: " << p2.setScore() << endl;
				}
				else if (game.getPosBoard(posX1, posY1) == game.getPosBoard(posX2, posY2)) cout << endl << "you cheater!" << endl;
				else 
				{
					for (int i = 0; i < 4; i++)
					{
						for (int j = 0; j < 4; j++)
						{
							if (gamedata[game.getPosBoard(i, j) - 1] == 0) cout << 'x'; 
							else cout << game.getPosBoard(i, j);
						}
						cout << endl;
					}
					cout << "P2 failed to find a matching pair" << endl;
				}
				break;
			default:
				break;
		}
		cnt++;
	}
	cout << "Game finished. Final scores are P1: " << p1.setScore() << ", and P2's score: " << p2.setScore() << endl;
	p1.setScore();
	p2.setScore();
	if (p1.setScore() > p2.setScore()) cout << "Player 1 WIN!" << endl;
	else if (p1.setScore() < p2.setScore()) cout << "Player 2 WIN!" << endl;
	else cout << "DRAW!" << endl;
}