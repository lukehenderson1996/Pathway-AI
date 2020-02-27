/*
This code is a template
2/13
Luke Henderson
*/

#include <iostream>
#include <string>
#include <cmath>
#include <ctime>
#include <cassert>
#include <algorithm>
#include <fstream> //update on tester

	using namespace std;
	int main()
	{


		return 0;
	}


#include <iostream>
#include <string>
#include <cmath>
using namespace std;
/////////////
//chapter 1//
/////////////
int main()
{



	//one line comment

	/*multiple
	line
	comment*/



	cout << "Hello, world!\n";
	cout << "sum= " << 2 + 3 << endl;

	int x1;
	int _x1;
	double totalSum = 3;
	int varA, varB, varC, varD;
	int x, y(3), z(4);
	char oneLetter = 'a';
	bool booleanIdentifier;
	string someText = "Hello, World!";

	//characters are in single quotes, strings are
	//in double quotes	

	//declare constants outside of main(), to be global
	const double gravitationalConstant = 6.67384e-11;


	//dont start an identifier with a special character or a
	//number 
	//and remember c++ is case sensitive



	x = (2 * y - 3 * x) / (x + 4);
	//you can't use the ^ for exponents, use the power function

	cin >> varA;


	//shorthand notations (these are equivalent)
	varA = varA + 1;
	varA += 1;

	varA = varA - 1;
	varA -= 1;

	//can be done with * / and % 

	varA++;
	varA--;
	//this executes the line and then adds/subtracts 1
	++varA;
	--varB;
	//this adds/subs 1 and then executes the line


	//remember difference between 2 and 2.0

	/* special characters

	\n newline
	\t horizontal tab
	\v vertical tab
	\b backspace

	*/

	double scTest;
	scTest = static_cast<double>(varA);

	//formatting numbers:
	cout.setf(ios::fixed);  //displays [precision] number of decimals
	cout.setf(ios::scientific); //always sci notation
	cout.unsetf(ios_base::floatfield); //set back to regular
	cout.setf(ios::showpoint);
	cout.precision(2);

	//just use the precision statement for sig figs (not trailing zeros)
	//changes cout for the rest of the program

	return 0;
}

#include <iostream>
#include <string>
#include <cmath>
using namespace std;
/////////////
//chapter 2//
/////////////
int main()
{
	/*logic
	AND &&
	OR ||
	NOT !
	==
	!=
	<
	>
	<=
	>=
	*/



	if (3 > 2)
		double varA = 3;
	else
		double varB = 2;

	if (1)
	{
		//statement1
		//statement2
		//statement3
	}
	else
	{
		//do this
		//do this
	}

	if (1)
		double varA = 3;


	double items(3);

	if (items > 1000)
		cout << "Use box : XL";
	else if ((items <= 1000) && (items > 500))
		cout << "Use box : L";
	else if ((items <= 500) && (items > 100))
		cout << "Use box : M";
	else if ((items <= 100) && (items > 10))
		cout << "Use box : S";
	else
		cout << "Individual Package";

	//switch statement is on page 34

	//conditional operator ?
	//boolean expression ? exp1:exp2;
	int a(6), b(7);
	double absDifference = (a > b) ? a - b : b - a;


	enum Roman { I = 1, V = 5 };
	//seems completely useless...just use int

	//for loop		natural counting
	//while			most control
	//do-while		always executes at least once



	for (int i(1); i <= 100; i++)
	{
		a += i;
	}
	//a == 5050

	for (int i(1); i <= 1000000; i++);
	//the semicolon at the end creates essentially a
	//program delay

	//break;		exits loop
	//continue;		skips rest of loop body



	//break and contunue statements
	int num = 3;
	for (int k = 7; k < 15; k++)
	{
		if (0 == k%num)
			continue;
			cout << k << " ";
	}
	//the break would disp 7 8 and then be done
	// output is 7 8 10 11 13 14


	// while(boolean expression)

	//do-while loop


	int a, b;

	do
	{
		a += a;
		a = 3;
	} while (a == b);

	// while checks before: do-while checks after

	return 0;
}

#include <iostream>
#include <string>
#include <cmath>
#include <ctime>
using namespace std;
/////////////
//chapter 3//
/////////////
int main()

{
	//()functions return a value
	//void functions just execute and dont return a value

	//<cmath>
	pow(2,3); //8
	sqrt(4); //2
	ceil(6.1); // 7.0
	ceil(-6.1); //-6.0
	abs(-4);
	floor(6.9999); //6.0
	round(7.4);
	log(2.0); //natural log
	exp(2.0);  //e^2
	sin(3.14); //0

	// to get pi, do
	double const PI = 4 * atan(1.0);
	
	//<cstdlib>
	abs(-4); //4 integers only
	rand(); //random integer
	exit(1); // void

	rand(); //returns the same pseudorandom number every time
	rand()%6; //squeezes it to be 0 1 2 3 4 or 5
	srand(11); 
	rand(); //different seed, but same every time
	
	(RAND_MAX - (double)rand()) / RAND_MAX; //0-1 fraction

	//psuedorandom numbers with a unique seed every time
	//uses lib <ctime>
	time(NULL); //seconds since 1970
	srand(time(NULL));

	//random averager averager
	int iterMax(500000000), runCount(0);
	double runSum(0);
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(20);
	cout << "\t";
	while (1)
	{
		double sum = 0, average;
		for (int i = 1; i <= 10; i++)
		{
			for (int k = 1; k <= 50000000; k++)
			{
				sum += (RAND_MAX - (double)rand()) / (RAND_MAX);
			}
			cout << i << "0% ";
		}
		average = sum / iterMax;
		runSum += average;
		runCount++;
		cout << endl << average << "     " << runSum / runCount << "\n\t";
	}


	//how to structure functions
		
		//libraries and namespace

		//declaration (can also use double or whatever)
		int fnName(int arg1,int arg2,int arg3);

		//int main() {..function call..}

			//definition (no semicolon, you can have mult returns)
		//	int fnName(int arg1,int arg2,int arg3)
		//	{
		//		
		//		return arg1+arg2+arg3;
		//	}

	//void functions are a statement
	void fnName(double arg1, double arg2);

	//you can use braces {} to make blocks, but what ever
	//happens in vegas stays in vegas

	return 0;
}

#include <iostream>
#include <string>
#include <cmath>
#include <cassert>
using namespace std;
/////////////
//chapter 4//
/////////////
int main()
{
	//advanced function tips
	//you can call functions inside of functions


	//& means call by reference (changes value) used like this
	int fnName(int& arg1, int arg2, int& arg3);
	//in the function declaration/definition place & after datatype

	//dont use ask carlos more logic gates
	bool a = 1, b = 0;
	a | b;
	//a !| b;
	a & b;
	//a !& b;
	a ^ b; //XOR
	// !^ XNOR
	!a; // NOT

	//overloading
	//you can define a different function given certain amounts of parameters
	// fnc(n1,2)	or fnc(1,2,3) both can be defined
	//also f(int, double) and F(double, int) are two different fncs
	//if you make (in the declaration only) some parameters (has to be the last ones) already 
	//assigned to something, for example
	void vol(int l, int w = 1, int h = 1);
	//then this
	vol(2);
	//equals 2*1*1
	//but you can't assign default values to variables by ref.
	//ask carlos why

	//assertions
	//use #include <cassert>
	bool programIsWorking = 1;
	assert(programIsWorking);
	//if true, program continues as normal
	//if false, error message is displayed with the line# and condition
	//
	//to turn all assertions off use this before the cassert lib
	//#define NDEBUG
	



	return 0;
}


#include <iostream>
#include <string>
#include <cmath>
using namespace std;
/////////////
//chapter 5//
/////////////
int main()
{
	//
	//vector call starts AT 0
	//initi
	int vector[5]; //5 elements
	int num = 4; // fifth element
	//int vector2[num]; //this is illegal
	vector[num]; //legal
	int grades[3] = { 95, 99, 105 };
	bool table[2][3] = { {1,0,1},{0,1,0} };
	//array[rows][cols]
	
	//whole array as arg in a function
	//
	//dec/def
	//void funct(int array[ ], int size);
	//void funct(int arrat[][100],int size); //second dim size req.
	//
	//call
	//funct(array,size);
	//
	//but is always passed by ref.

	return 0;
}

#include <iostream>
#include <string>
#include <cmath>
#include <cstring>
using namespace std;
/////////////
//chapter 9//
/////////////
int main()
{
	//strings

	//C-strings are an array of characters ended with \0
	//requires library <cstring>
	char s[14]="Hello, world!"; //14th char is \0 and if there's any leftover space it's memory junk
	char string1[] = "abc"; //c determines size for you
	char individual[] = { 'a', 'b', 'c', '\0' }; //this is the only one you have to add the \0
	//some library functions
	strcpy(individual, "Hi!"); //how to add something else in there later
	strcmp(s, string1); //returns a table of cases by comparing the element's ascii number. the first non-match determines the output
		//negative means str1 is less than str2
		//0 means theyre the same
		//positive means str1 is more than str2
		//think of it like str1-str2
	//two string copies
		//strncpy can specify max number of characters (remember to have a space for the null character)
		//strcpy just copies the whole thing
		char string1[11];
		strncpy(string1, "1234567890", 10);
	//string length
	strlen("123"); //returns 3
	//concatination
	strcat(string1, "987654321"); //will do 12345567890987654321
	strncat(string1, "987654321", 3); //only adds 3 chars
	//to get a string from the user'
	char a[81];
	cin.getline(a, 80); //gets 80 characters max and adds a null character


	//real strings (string class)
	//needs <string> library
	string s1 = "Hello";
	string s2 = ", world!";
	string s3;
	s3 = s2; //works, unlike c-strings
	s1 + s2; //is Hello, world!
	s1 == s2; //returns 0
	s1 == s1; //returns 1
	//getline gets string until \n is detected
	getline(cin, s1); //if the input is "hello my name is" and then the user presses enter this will get the whole thing
	//cin by itself will skip when a space is detected
	getline(cin, s1, '*'); //stops when it finds a star
	//member functions
	//get gets one char (will read spaces, newlines, all characters)
	char symbol;
	cin.get(symbol); //dont even bother using this see page 47 on chapter 9
	//these are member functions
	string stringVar = "Hello, world!";
	stringVar.length(); //returns amount of characters
	stringVar.size();	//returns bytes but only one byte is used per char anyway
	stringVar.compare("Hi, world");	//can compare cstrings versus regular ones
		//returns 0 is they are the same
	stringVar.compare(7, 5, "world"); //position 7 and length 5
	stringVar.compare(6, 5,"hi", 4, 5); //6 for stringVar pos and 4 for "hi" position //used wrong numbers
	cin.ignore(1000, '/n'); //waits 1000 char inputs until user presses return (press enter to continue)
	//stringVar.substr(position,length)
	stringVar.substr(2, 4); // returns llo,
	stringVar.empty(); //returns true "iff" the variable is empty
	stringVar.insert(3, "lo"); //inserts lo at position 3
	stringVar.find("world", 1); //returns 7, first occurence of world in the variable
		//returns -1 if it's not found
		//starts at position 1
	//these need library <cctype>
		toupper('j'); //returns J
		tolower('K'); //returs k
		//to find many versatile character analysis functions
			//look at chapter 9 pg 62-63
	//string conversion to numbers pg 65
	//cstring to string conversion and vise versa pg 67



	return 0;
}

#include <iostream>
#include <string>
#include <cmath>
using namespace std;
/////////////
//chapter 6// finish later
/////////////
struct examScores
{
	double exam1;
	double exam2;
	string name;
	char letterGrade;
};
int main()
{
	//structures
	//defined between namespace and int main
	/*
	struct examScores
	{
		double exam1;
		double exam2;
		string name;
		char letterGrade;
	};
	*/

	//declaration
	examScores student1 = {90.6,105.12,"Luigi",'A'};
	student1.name; //returns the name
	examScores student2;
	student2 = student1;
	//you can make a function of type examScores 
	//structures can be a member of another structure, if previously defined



	//classes
	//these are objects, (can contain functions?)

	//public vs. private

	/*
	class DayOfYear
	{
	public:
		void output(); //member function
		int month;
		int day;
	};
	*/
	//DayOfYear today, birthday;
	//today.day;
	//today.output();

	//member function   (goes after or before main)
	/*
	void DayOfYear::output( ) //thats the scope resolution operator
	{
		1+2;
		2+2;
	}
	*/

	//continue on page 40

	//private can't be accessed from the main, only from member functions

	//pg 58 example

	


	return 0;
}

#include <iostream>
#include <string>
#include <cmath>
using namespace std;
//////////////
//chapter 10//
//////////////
int main()
{
	//pointers
		//grow/shrink arrays
		//are stored in a special variable type
		double *p; //dereferencing op. says it's a pointer var. type
		//this "double" means it can only point to doubles
		double var(3.14);
		p = &var; //saves address of var to p
		cout << p; //returns address of var in memory
		cout << *p; //returns 3.14
		//re read page 16 to end if you get lost
		
	//new op
		//nameless variable of type int is dynamic
		int *pointer;
		pointer = new int ;
		*pointer = 42;
		//#recycle for earth #safety
		delete pointer; 
		pointer = NULL; 

	//type definitions goes after namespace
		typedef int* intPointer;
		typedef double* dPointer;
		intPointer p;

	//how to arrays
		//ordinary arrays
			int array[10];
			pointer = array;
		//dynamic arrays
			int size = 10;
			dPointer ptr = new double[size];
			ptr[2]; //returns the third value 
			delete[] ptr;
			ptr = NULL;
				//to return an array from a function
				//declaration is
				//double* funct(int num);
			//size of pg 49
			//pointer arithmetic pg 50
		//dynamic 2d array
			//set up
			dPointer *dim2 = new dPointer[size];
			for (int i=0; i<size; i++)
				dim2[i] = new double[size];
			//use
			dim2[3][4];
			//delete
			for (int i = 0; i<size; i++) 
				delete[] dim2[i];
			delete[] dim2;
			dim2 = NULL;


	return 0;
}

#include <iostream>
#include <string>
#include <cmath>
using namespace std;
/////////////
//chapter //
/////////////
int main()
{


	return 0;
}