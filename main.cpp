//==============================================================================================
//! @file main.cpp
//!
//! Quadratic equvals Solver and tests
//!
//! @author Novikova Polina
//!
//! @mainpage The program solves quadratic equations in real and complex numbers. It is possible to test from the console or from a file
//!
//! @mainpage It is possible to test from the console or from a file




#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <cassert>
#include <cmath>
#include <cstring>
#include "testSolver.h"
#include "findRoots.h"
const int IND = 3;
//{---------------------------------------------------------------------------------------------
//! Reads one coefficient from the console
//!
//! @param No parameters
//!
//! @note If the entered value is not a number, it displays a message about it and asks you to enter the correct number
//!
//}--------------------------------------------------------------------------------------------

float getOneCof() {
    float a = 0;

    printf ("Enter next value\n");

    while (scanf ("%f", &a)  != 1 || (getchar() != '\n' && getchar() != ' ')) {

        printf ("It's not a number\n");
        printf ("Enter correct value\n");

        while(getchar() != '\n')
            ;
    }
    return a;
}

//{---------------------------------------------------------------------------------------------
//! Reads coefficients from the console
//!
//! @param quatr  The structure in which the entered coefficients are recorded
//!
//}--------------------------------------------------------------------------------------------

void getCof (coef* quatr){

    assert(quatr != NULL);
    quatr->a = getOneCof();
    quatr->b = getOneCof();
    quatr->c = getOneCof();

    //{---------------------------------------------------------------------------------------------
//! Prints the found roots of the quadratic equation
//!
//! @param myRoots Roots, which should be print
//!
//! The function can output real and complex roots or a message that there are no roots
//! The function displays messages in different colors"
//! @see class roots
//}---------------------------------------------------------------------------------------------

}

void printRoots (roots myRoots){
    HANDLE console_color;
    console_color = GetStdHandle(
            STD_OUTPUT_HANDLE);

    switch (myRoots.num) {
        case NO_ROOTS:
            printf("Korney net, no est' kotik \n");
            printf(" ,_     _\n"
                   " |\\\\_,-~/\n"
                   " / _  _ |    ,--.\n"
                   "(  @  @ )   / ,-'\n"
                   " \\  _T_/-._( (\n"
                   " /         `. \\\n"
                   "|         _  \\ |\n"
                   " \\ \\ ,  /      |\n"
                   "  || |-_\\__   /\n"
                   " ((_/`(____,-'");
            break;

        case ONE_ROOT:
            printf("Roots are real and same\n");
            printf("%f", myRoots.x1);
            break;

        case TWO_ROOTS:
            if(myRoots.comp == 0){
                printf("Roots are real and different\n");
                printf("%f\n%f", myRoots.x1, myRoots.x2);
                printf("");
            }
            else{
                printf("Roots are complex\n");
                printf("%f - i%f\n%f + i%f", myRoots.x1, myRoots.comp, myRoots.x1, myRoots.comp);
            }
            break;

        case INFIN_ROOTS:
            printf("Any number");
            break;

        default:
            SetConsoleTextAttribute(console_color, PINK);
            printf("Error: roots = %d\n", myRoots.num);
            SetConsoleTextAttribute(console_color, WHITE);
    }
}

//{---------------------------------------------------------------------------------------------
//! Reads coefficients from the command line using the "--coefs" flag
//!
//! @param argc   Command line argument, shows the number of parameters
//! @param argv   Array of pointers to command line parameters
//! @param quatr  The structure in which the entered coefficients are recorded
//!
//! @return bool  Was the reading successful
//}---------------------------------------------------------------------------------------------


bool commandCoefs(int argc, char *argv[], coef* quatr){
    char coefComp[] = "--coefs";
    for(int i = 1; i < argc; i++){
            if(strcmp(coefComp, argv[i]) == 0){
            int is_coef = 0;
            is_coef += sscanf(argv[i+1], "%f", &(*quatr).a);
            is_coef += sscanf(argv[i+2], "%f", &(*quatr).b);
            is_coef += sscanf(argv[i+3], "%f", &(*quatr).c);
            if(is_coef == 3){
                return true;
            }
        }
    }
    return false;
}


//{---------------------------------------------------------------------------------------------
//! The main function
//!
//! @param argc   Command line argument, shows the number of parameters
//! @param argv   Array of pointers to command line parameters
//!
//! @see run_allTests(), commandCoefs(), getCof(), findRoots(), printRoots()
//}---------------------------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    roots myRoots{};
    coef quatr{};
#define DEBUG
#ifdef  DEBUG
    run_allTests(argc, argv);
#endif
    if(!(commandCoefs(argc, argv, &quatr))){
        getCof(&quatr);
    }
    myRoots = findRoots(quatr);
    printRoots(myRoots);

    return 0;
}
