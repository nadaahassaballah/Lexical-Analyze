#include <iostream>
#include <cctype>
#include <string>
using namespace std;

// Character classes
#define LETTER 1
#define DIGIT 10
#define UNKNOWN 77

// Token codes
#define INT_LIT 1
#define IDENT 11
#define ASSIGN_OP 2
#define ADD_OP 22
#define SUB_OP 3
#define MULT_OP 33
#define DIV_OP 4
#define LEFT_PAREN 44
#define RIGHT_PAREN 5


#define EOF -1

// Global variables
int charClass;
string lexeme;
char nextChar;
int nextToken;
string input = "index = 2 * count + 17 ;";
int inputIndex = 0;

// Function prototypes
void addChar();
void getChar();
void getNonBlank();
int lex();
int lookup(char ch);

int main() {
    getChar();
    do {
        lex();
    } while (nextToken != EOF);
    return 0;
}

int lookup(char ch) {
    switch (ch) {
        case '(':
            addChar();
            nextToken = LEFT_PAREN;
            break;
        case ')':
            addChar();
            nextToken = RIGHT_PAREN;
            break;
        case '+':
            addChar();
            nextToken = ADD_OP;
            break;
        case '-':
            addChar();
            nextToken = SUB_OP;
            break;
        case '*':
            addChar();
            nextToken = MULT_OP;
            break;
        case '/':
            addChar();
            nextToken = DIV_OP;
            break;
        case '=':
            addChar();
            nextToken = ASSIGN_OP;
            break;
        case '{':
        case '}':
        case ';':
            addChar();
            nextToken = UNKNOWN;  // Treat these as unknown for now
            break;
        default:
            addChar();
            nextToken = EOF;
            break;
    }
    return nextToken;
}

void addChar() {
    lexeme += nextChar;
}

void getChar() {
    if (inputIndex < input.length()) {
        nextChar = input[inputIndex++];
        if (isalpha(nextChar))
            charClass = LETTER;
        else if (isdigit(nextChar))
            charClass = DIGIT;
        else
            charClass = UNKNOWN;
    } else {
        charClass = EOF;
    }
}

void getNonBlank() {
    while (isspace(nextChar))
        getChar();
}

int lex() {
    lexeme = "";
    getNonBlank();

    switch (charClass) {
        case LETTER:
            addChar();
            getChar();
            while (charClass == LETTER || charClass == DIGIT) {
                addChar();
                getChar();
            }
            // Check for keywords
            if (lexeme == "int" || lexeme == "float" || lexeme == "return") {
                nextToken = INT_LIT;  // Using INT_LIT for keywords in this simplified version
            } else {
                nextToken = IDENT;
            }
            break;

        case DIGIT:
            addChar();
            getChar();
            while (charClass == DIGIT || nextChar == '.') {
                if (nextChar == '.') {
                    addChar();
                    getChar();
                    while (charClass == DIGIT) {
                        addChar();
                        getChar();
                    }
                    break;
                }
                addChar();
                getChar();
            }
            nextToken = INT_LIT;
            break;

        case UNKNOWN:
            lookup(nextChar);
            getChar();
            break;

        case EOF:
            nextToken = EOF;
            lexeme = "EOF";
            break;
    }

    cout << "Next token is: " << nextToken << ", Next lexeme is " << lexeme << endl;
    return nextToken;
}