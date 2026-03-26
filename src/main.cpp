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
void GetChar()
{
    cin.get(look);
}

// Report an Error

void error(string s)
{
    cout << "Error" << s << "\n";
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
   if (look == x) getchar();
   else expected(std::to_string(x));
}

// get an identifier
char GetName()
{
    char name;
    if (!std::isalpha(look)) expected("Name");
    name = toupper(look);
    getchar();
    return name;
}


// Get a Number
char GetNum()
{
    char num;
   if (std::isdigit(look)) expected("Integer");
   num = look;
   getchar();
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
    getchar();
}

// Main Program
int main()
{
    init();
    return 0;
}
