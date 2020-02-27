/////////////////////
// Pathway AI v0.3 //
/////////////////////
//0.3 changes
//better log file, operation algorithms, change comments on line 130 and DISP_DELAY to increase running speed significantly
//
const double VERSION = 0.3;



#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <ctime>
#include <windows.h>

using namespace std;

void disp(int atr, int seed, int aiIter);
string logInit(int seed, int aiIter);
void reasDir(int i, int j, int iChg, int jChg);
void manpBoard();

const int DISP_DELAY = 1e8;//1e8 medium speed

const int ATR_CONT = 0;
const int ATR_CLSS = 1;
const int ATR_FNCT = 2;
const int ATR_CONF = 3;
const int ATR_MANP = 4;
const int ATR_OPST = 5;

const int EDG_CLS_1 = 875; //DIR, OP

const int EDG_DIR_1 = 200; //L
const int EDG_DIR_2 = 250; //LD
const int EDG_DIR_3 = 450; //D
const int EDG_DIR_4 = 500; //DR
const int EDG_DIR_5 = 700; //R
const int EDG_DIR_6 = 750; //RU
const int EDG_DIR_7 = 950; //U, UL=1000

const int EDG_DIR_L  = 200 - 1; //L
const int EDG_DIR_LD = 250 - 1; //LD
const int EDG_DIR_DL = 250 - 1; //LD
const int EDG_DIR_D  = 450 - 1; //D
const int EDG_DIR_DR = 500 - 1; //DR
const int EDG_DIR_RD = 500 - 1; //DR
const int EDG_DIR_R  = 700 - 1; //R
const int EDG_DIR_RU = 750 - 1; //RU
const int EDG_DIR_UR = 750 - 1; //RU
const int EDG_DIR_U  = 950 - 1; //U
const int EDG_DIR_UL = 1000 - 1; //UL
const int EDG_DIR_LU = 1000 - 1; //UL

const int EDG_OPR_1 = 333; //+
const int EDG_OPR_2 = 666; //-, gen


int board[6][8][20]; //col size, row size, [contents, class, function, confidence]
		//
		//0 - contents, 0-9
		//1 - class, 0-1000, 0-875 direction, 876-1000 operation
		//2 - function 0-1000
		//		direction:	L		L+D			D		D+R		R		R+U		U		U+L
		//					0-200	201-250		251-450	451-500	501-700	701-750	751-950	951-1000
		//		operation:	+		-			generate
		//					0-333	334-666		667-1000
		//3 - confidence 0-1000
		//4 - manipulated? bool
		//5 - operation storage


int main()
{
	//////////
	// init //
	//////////
	int loopCnt = 0;
	int aiIter = 0;
	bool resAch = 0;
	int seed = time(NULL);
	srand(seed);
	for (int i(0); i < 6; i++) for (int j(0); j < 8; j++) board[i][j][ATR_CONT] = 0; //init board contents
	board[5][2][ATR_CONT] = 2; board[5][4][ATR_CONT] = 3;
	for (int i(0); i < 6; i++) for (int j(0); j < 8; j++) board[i][j][ATR_CLSS] = rand() % 1000;
	//board[2][2][ATR_CLSS] = 999;
	/*int directions[6][8] = {	{EDG_DIR_L, EDG_DIR_L, EDG_DIR_U, EDG_DIR_L, EDG_DIR_L, EDG_DIR_L, EDG_DIR_L, EDG_DIR_L},
								{EDG_DIR_L, EDG_DIR_L, EDG_DIR_U, EDG_DIR_RD, EDG_DIR_R, EDG_DIR_R, EDG_DIR_R, EDG_DIR_R},
								{EDG_DIR_L, EDG_DIR_L, EDG_DIR_U, EDG_DIR_D, EDG_DIR_L, EDG_DIR_L, EDG_DIR_L, EDG_DIR_L},
								{EDG_DIR_L, EDG_DIR_L, EDG_DIR_U, EDG_DIR_L, EDG_DIR_L, EDG_DIR_L, EDG_DIR_L, EDG_DIR_L},
								{EDG_DIR_L, EDG_DIR_L, EDG_DIR_U, EDG_DIR_D, EDG_DIR_L, EDG_DIR_L, EDG_DIR_L, EDG_DIR_L},
								{EDG_DIR_L, EDG_DIR_L, EDG_DIR_U, EDG_DIR_L, EDG_DIR_L, EDG_DIR_D, EDG_DIR_L, EDG_DIR_L} }; */
	//gets 11
	//initial board glyph :
	//	+ v + <^ > ^ + < v
	//	> > < +	 ^ v ^ <
	//	^ <	> ^ +<	+v
	//	^	>v + ^ <v	< ^ ^<
	//	>	>	+> < ^ < ^ < <
	//	^ <	>^ <	>^ <	>^
	for (int i(0); i < 6; i++) for (int j(0); j < 8; j++) board[i][j][ATR_FNCT] = rand() % 1000; //directions[i][j];
	for (int i(0); i < 6; i++) for (int j(0); j < 8; j++) board[i][j][ATR_CONF] = 0;
	for (int i(0); i < 6; i++) for (int j(0); j < 8; j++) board[i][j][ATR_MANP] = 0;
	for (int i(0); i < 6; i++) for (int j(0); j < 8; j++) board[i][j][ATR_OPST] = 0;

	//turn off cursor
		HANDLE hOut;
		CONSOLE_CURSOR_INFO ConCurInf;

		hOut = GetStdHandle(STD_OUTPUT_HANDLE);

		ConCurInf.dwSize = 10;
		ConCurInf.bVisible = FALSE;

		SetConsoleCursorInfo(hOut, &ConCurInf);

	//log file
		ofstream file("debug log v" + to_string(VERSION) + ".txt");
		file << "Debug log for Pathway AI v" + to_string(VERSION) + "\n"; file.flush();
		file << logInit(seed, aiIter); file.flush();


	///////////////
	// main loop //
	///////////////
	while (1)
	{
		//display fast
		//if (loopCnt % 10 == 0)
		//{
		//	disp(ATR_CONT, seed, aiIter);
		//}
		//display slow
		disp(ATR_CONT, seed, aiIter);
		
		

		//manipulate board
		manpBoard();
		

		//validate behavoir and add some 2's again
		if (board[0][2][ATR_CONT] > 0 || loopCnt >= 30) //spot has a number or 30 loops have passed
		{
			if (board[0][2][ATR_CONT] == 11) //correct answer
			{
				//log results		
				if (!resAch)
				{
					file << logInit(seed, aiIter); file.flush();
				}
				resAch = 1;
				//0 content, operation storage
				for (int i(0); i < 6; i++) for (int j(0); j < 8; j++) board[i][j][ATR_CONT] = 0;
				for (int i(0); i < 6; i++) for (int j(0); j < 8; j++) board[i][j][ATR_OPST] = 0;
				//reset board
				board[5][2][ATR_CONT] = 2; board[5][4][ATR_CONT] = 3;
				loopCnt = 0;
			}
			else //incorrect ans
			{
				//0 content, operation storage
				for (int i(0); i < 6; i++) for (int j(0); j < 8; j++) board[i][j][ATR_CONT] = 0;
				for (int i(0); i < 6; i++) for (int j(0); j < 8; j++) board[i][j][ATR_OPST] = 0;
				//reassign class/function
				for (int i(0); i < 6; i++) for (int j(0); j < 8; j++) board[i][j][ATR_CLSS] = rand() % 1000;
				for (int i(0); i < 6; i++) for (int j(0); j < 8; j++) board[i][j][ATR_FNCT] = rand() % 1000;
				//reset board
				board[5][2][ATR_CONT] = 2; board[5][4][ATR_CONT] = 3;
				aiIter += 1;
				loopCnt = 0;
			}
		}

		//change eventually:
		//change board behavior accounting for validation/confidence


		loopCnt += 1;
	} 

	////exit
	//cout << "\n\n\n\n\n\n\n\n\n\n\n\nPress enter to exit...";
	//std::cin.ignore();
}

void disp(int atr, int seed, int aiIter)
{
	system("CLS");
	cout << "Seed: " << seed << "  Iteration: " << aiIter;
	cout << "\n\n\n    |--------------------------|\n";
	for (int i(0); i < 6; i++)
	{
		cout << "    |  ";
		for (int j(0); j < 8; j++)
		{
			if (board[i][j][atr] == 0)
				cout << "." << "  ";
			else
				cout << board[i][j][atr] << "  ";
			//for (int k(0); k <= 1e7; k++);
		}
		cout << "|\n    |                          |\n";
	}
	cout << "    |--------------------------|\n";


	////disp MANP
	//for (int i(0); i < 6; i++)
	//{
	//	cout << "    |  ";
	//	for (int j(0); j < 8; j++)
	//	{
	//		if (board[i][j][ATR_MANP] == 0)
	//			cout << "." << "  ";
	//		else
	//			cout << board[i][j][ATR_MANP] << "  ";
	//		//for (int k(0); k <= 1e7; k++);
	//	}
	//	cout << "|\n    |                          |\n";
	//}
	//cout << "    |--------------------------|\n";


	for (int k(0); k <= DISP_DELAY; k++);
}

string logInit(int seed, int aiIter)
{
	string logstr;
	logstr = "seed: " + to_string(seed) + "\t\tIteration: " + to_string(aiIter) + "\n\n";

	logstr = logstr + "initial contents: \n"; //[contents, class, function, confidence]
		for (int i(0); i < 6; i++)
		{
			for (int j(0); j < 8; j++)
			{
				logstr = logstr + to_string(board[i][j][ATR_CONT]) + "\t";
			}
			logstr = logstr + "\n";
		}
		logstr = logstr + "\n\n";


	logstr = logstr + "initial board glyph: \n";
		for (int i(0); i < 6; i++)
		{
			for (int j(0); j < 8; j++)
			{
				//class code:
				if (board[i][j][ATR_CLSS] < EDG_CLS_1)
				{
					//direction code:
					if (board[i][j][ATR_FNCT] < EDG_DIR_1)
						logstr = logstr + "<" + "\t"; //L		
					else if (board[i][j][ATR_FNCT] < EDG_DIR_2)
					{
						logstr = logstr + "<v" + "\t"; //LD
					}
					else if (board[i][j][ATR_FNCT] < EDG_DIR_3)
						logstr = logstr + "v" + "\t"; //D
					else if (board[i][j][ATR_FNCT] < EDG_DIR_4)
					{
						logstr = logstr + ">v" + "\t"; //DR
					}
					else if (board[i][j][ATR_FNCT] < EDG_DIR_5)
						logstr = logstr + ">" + "\t"; //R
					else if (board[i][j][ATR_FNCT] < EDG_DIR_6)
					{
						logstr = logstr + ">^" + "\t"; //RU
					}
					else if (board[i][j][ATR_FNCT] < EDG_DIR_7)
						logstr = logstr + "^" + "\t"; //U
					else
					{
						logstr = logstr + "<^" + "\t"; //UL
					}
				}
				else
				{
					//operation code:
					logstr = logstr + "+" + "\t";
				}
			}
			logstr = logstr + "\n";
		}
		logstr = logstr + "\n\n";




	logstr = logstr + "initial class: \n";
		for (int i(0); i < 6; i++)
		{
			for (int j(0); j < 8; j++)
			{
				logstr = logstr + to_string(board[i][j][ATR_CLSS]) + "\t";
			}
			logstr = logstr + "\n";
		}
		logstr = logstr + "\n\n";
	logstr = logstr + "initial function: \n";
		for (int i(0); i < 6; i++)
		{
			for (int j(0); j < 8; j++)
			{
				logstr = logstr + to_string(board[i][j][ATR_FNCT]) + "\t";
			}
			logstr = logstr + "\n";
		}
		logstr = logstr + "\n\n";
	logstr = logstr + "initial confidence: \n";
		for (int i(0); i < 6; i++)
		{
			for (int j(0); j < 8; j++)
			{
				logstr = logstr + to_string(board[i][j][ATR_CONF]) + "\t";
			}
			logstr = logstr + "\n";
		}
		logstr = logstr + "\n\n";
	logstr = logstr + "initial manipulated?: \n";
		for (int i(0); i < 6; i++)
		{
			for (int j(0); j < 8; j++)
			{
				logstr = logstr + to_string(board[i][j][ATR_MANP]) + "\t";
			}
			logstr = logstr + "\n";
		}
		logstr = logstr + "\n\n";


	return logstr;
}

void reasDir(int i, int j, int iChg, int jChg) //reassign direction, changes position of a board element, or duplicates (won't move diagonally)
{
	if (board[i][j][ATR_CONT] > 0) //nonzero contents
	{
		//single direction
		if (!iChg != !jChg) 
		{
			if ((i + iChg >= 0 && i + iChg < 6) && (j + jChg >= 0 && j + jChg < 8)) //movement is within bounds
			{
				if (board[i][j][ATR_MANP] == 0 && board[i + iChg][j + jChg][ATR_MANP] == 0) //wasn't previously manipulated and where it's going wasnt
				{
					//move element
					board[i + iChg][j + jChg][ATR_CONT] = board[i][j][ATR_CONT];
					board[i][j][ATR_CONT] = 0;
					board[i][j][ATR_MANP] = 1;
					board[i + iChg][j + jChg][ATR_MANP] = 1;
				}
			}
			else //movement is out of bounds
			{
				if (board[i][j][ATR_MANP] == 0) //wasn't previously manipulated
				{
					//just delete element
					board[i][j][ATR_CONT] = 0;
					board[i][j][ATR_MANP] = 1;
				}
			}
		}


		//mult directions
		else if (iChg && jChg) 
		{
			//both are within bounds
			if ((i + iChg >= 0 && i + iChg < 6) && (j + jChg >= 0 && j + jChg < 8))
			{
				if (board[i][j][ATR_MANP] == 0) //wasn't previously manipulated
				{
					//move element
					//and where it's going wasnt prev manp
					if (board[i + iChg][j][ATR_MANP] == 0) //i wasnt
					{
						board[i + iChg][j][ATR_CONT] = board[i][j][ATR_CONT];
						board[i + iChg][j][ATR_MANP] = 1;
					}
					if (board[i][j + jChg][ATR_MANP] == 0) //j wasnt
					{
						board[i][j + jChg][ATR_CONT] = board[i][j][ATR_CONT];
						board[i][j + jChg][ATR_MANP] = 1;
					}
					board[i][j][ATR_CONT] = 0;
					board[i][j][ATR_MANP] = 1;
				}
			}
			//i is within bounds
			else if (i + iChg >= 0 && i + iChg < 6)
			{
				if (board[i][j][ATR_MANP] == 0) //wasn't previously manipulated
				{
					//move element
					//and where it's going wasnt prev manp
					if (board[i + iChg][j][ATR_MANP] == 0) //i wasnt
					{
						board[i + iChg][j][ATR_CONT] = board[i][j][ATR_CONT];
						board[i + iChg][j][ATR_MANP] = 1;
					}
					board[i][j][ATR_CONT] = 0;
					board[i][j][ATR_MANP] = 1;
				}
			}
			//j is within bounds
			else if (j + jChg >= 0 && j + jChg < 8)
			{
				if (board[i][j][ATR_MANP] == 0) //wasn't previously manipulated
				{
					//move element
					//and where it's going wasnt prev manp
					if (board[i][j + jChg][ATR_MANP] == 0) //j wasnt
					{
						board[i][j + jChg][ATR_CONT] = board[i][j][ATR_CONT];
						board[i][j + jChg][ATR_MANP] = 1;
					}
					board[i][j][ATR_CONT] = 0;
					board[i][j][ATR_MANP] = 1;
				}
			}
			//none are in bounds
			else
			{
				if (board[i][j][ATR_MANP] == 0) //wasn't previously manipulated
				{
					//just delete element
					board[i][j][ATR_CONT] = 0;
					board[i][j][ATR_MANP] = 1;
				}
			}
		}
	}
}

void manpBoard()
{
	//change: make this follow the rules of class/function, if output or so many turns, move on to validation
		//
		//function 0-1000
		//		direction:	L		L+D			D		D+R		R		R+U		U		U+L
		//					0-200	201-250		251-450	451-500	501-700	701-750	751-950	951-1000
		//		operation:	+		-			generate
		//					0-333	334-666		667-1000
	for (int i(0); i < 6; i++)
	{
		for (int j(0); j < 8; j++)
		{
			//class code:
			if (board[i][j][ATR_CLSS] < EDG_CLS_1)
			{
				//direction code:
				if (board[i][j][ATR_FNCT] < EDG_DIR_1)
					reasDir(i, j, 0, -1); //L		
				else if (board[i][j][ATR_FNCT] < EDG_DIR_2)
				{
					reasDir(i, j, 1, -1); //LD
				}
				else if (board[i][j][ATR_FNCT] < EDG_DIR_3)
					reasDir(i, j, 1, 0); //D
				else if (board[i][j][ATR_FNCT] < EDG_DIR_4)
				{
					reasDir(i, j, 1, 1); //DR
				}
				else if (board[i][j][ATR_FNCT] < EDG_DIR_5)
					reasDir(i, j, 0, 1); //R
				else if (board[i][j][ATR_FNCT] < EDG_DIR_6)
				{
					reasDir(i, j, -1, 1); //RU
				}
				else if (board[i][j][ATR_FNCT] < EDG_DIR_7)
					reasDir(i, j, -1, 0); //U
				else
				{
					reasDir(i, j, -1, -1); //UL
				}
			}
			else
			{
				//operation code:
				if (board[i][j][ATR_CONT] > 0) //nonzero contents
				{
					if (board[i][j][ATR_OPST] == 0) //nothing in storage
					{
						//store
						board[i][j][ATR_OPST] = board[i][j][ATR_CONT];
						board[i][j][ATR_CONT] = 0;
					}
					else
					{
						if (i - 1 >= 0) //if not at top
						{
							//add and move up
							board[i - 1][j][ATR_CONT] = board[i][j][ATR_CONT] + board[i][j][ATR_OPST];
							board[i][j][ATR_CONT] = 0;
						}
					}
				}

			}
		}
	}
	//done manipulating
	for (int i(0); i < 6; i++) for (int j(0); j < 8; j++) board[i][j][ATR_MANP] = 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors

