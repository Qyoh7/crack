#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::string;

const char TAB = '\t';

// Variable Declarations

char look;

// Read New Character From Input Stream
void getChar()
{
   cin.get(look);
}

// Report an Error
void error(string s)
{
   cout << "Error " << s << "\n";
}

// Report Error and Halt
void abort(string s)
{
   error(s);
   exit(EXIT_FAILURE);
}

// Report What Was Expected
void expected(string s)
{
   abort(s + " Expected");
}

// Match a Specific Input Character
void match(char x)
{
   if (look == x)
      getChar();
   else
      expected(std::to_string(x));
}

// get an identifier
char GetName()
{
   char name;
   if (!std::isalpha(look))
      expected("Name");
   name = toupper(look);
   getChar();
   return name;
}

// Get a Number
char GetNum()
{
   char num = look;
   if (!std::isdigit(look))
      expected("Integer");
   getChar();
   return num;
}

// Output a String with Tab
void Emit(string s)
{
   cout << TAB << s;
}

// Initialize
void init()
{
   getChar();
}

void parseTerm()
{
   cout << "MOVE #" << GetNum() << ",D0\n";
}

void add()
{
   match('+');
   parseTerm();
   cout << "ADD D1, D0\n";
}

void subtract()
{
   match('-');
   parseTerm();
   cout << "SUB D1,D0\n";
}

void parseExpr()
{
   parseTerm();
   switch (look)
   {
      case '+':
         add();
      case '-':
         subtract();
      default:
         expected("Addop");
   }
}

// Main Program
int main()
{
   init();
   parseExpr();
   return 0;
}
