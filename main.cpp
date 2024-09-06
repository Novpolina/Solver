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


#include <cstdio>
#include <cstdlib>
#include <clocale>
#include <cassert>
#include <cmath>
#include <cstring>
#include <ctime>

#include "testSolver.h"
#include "findRoots.h"
#include "colors.h"

const int IND = 3;

//! @class Enum for flags from console
enum flags{
   NOFLAG, COEFS, ERRCOEFS,  HELP, ERROW, MEOW //
};

#ifdef DEBUG
#else
//{---------------------------------------------------------------------------------------------
//! Reads one coefficient from the console
//!
//! @param No parameters
//!
//! @note If the entered value is not a number, it displays a message about it and asks you to enter the correct number
//!
//}--------------------------------------------------------------------------------------------
static float getOneCof()
{
    float a = 0;
    printf ("Enter next value\n");

    while (scanf ("%f", &a)  != 1 || (getchar() != '\n' && getchar() != ' ' && getchar() != EOF)) {

        printf ("It's not a number\n");
        printf ("Enter correct value\n");

        int b = getchar();
        while(b != '\n' && b != EOF){
            b = getchar();
        }

        if(b == EOF){
            exit(1);
        }

    }
    return a;
}

//{---------------------------------------------------------------------------------------------
//! Reads coefficients from the console
//!
//! @param quatr  The structure in which the entered coefficients are recorded
//!
//}--------------------------------------------------------------------------------------------
 static void getCof (coef* quatr)
 {
    assert(quatr != NULL);
    quatr->a = getOneCof();
    quatr->b = getOneCof();
    quatr->c = getOneCof();
 }

//{---------------------------------------------------------------------------------------------
//! Prints the found roots of the quadratic equation
//!
//! @param myRoots Roots, which should be print
//!
//! The function can output real and complex roots or a message that there are no roots
//! The function displays messages in different colors"
//! @see class roots
//}---------------------------------------------------------------------------------------------
static void printRoots (roots myRoots)
{
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
            SetConsoleTextAttribute(console_color, Magenta | Black);
            printf("\t x1 = x2 = ");
            SetConsoleTextAttribute(console_color, White | Black);
            printf("%f", myRoots.x2);
            break;

        case TWO_ROOTS:
            if(compare(myRoots.comp, 0) == EQUVAL){
                printf("Roots are real and different\n");
                SetConsoleTextAttribute(console_color, Magenta | Black);
                printf("\t x1 = ");
                SetConsoleTextAttribute(console_color, White | Black);
                printf("%f \n", myRoots.x1);
                SetConsoleTextAttribute(console_color, Magenta | Black);
                printf("\t x2 = ");
                SetConsoleTextAttribute(console_color, White | Black);
                printf("%f", myRoots.x2);
            }
            else{
                printf("Roots are complex\n");
                SetConsoleTextAttribute(console_color, Magenta | Black);
                printf("\t x1 = ");
                SetConsoleTextAttribute(console_color, White | Black);
                printf("%f - i%f \n ", myRoots.x1, myRoots.comp);
                SetConsoleTextAttribute(console_color, Magenta | Black);
                printf("\t x2 = ");
                SetConsoleTextAttribute(console_color, White | Black);
                printf("%f + i%f", myRoots.x1, myRoots.comp);
            }
            break;

        case INFIN_ROOTS:
            printf("\t Any number");
            break;

        default:
            SetConsoleTextAttribute(console_color, Red | Black);
            printf("Error: roots = %d\n", myRoots.num);
            SetConsoleTextAttribute(console_color, White | Black);
    }
}

//{---------------------------------------------------------------------------------------------
//! function meows;)
//}---------------------------------------------------------------------------------------------
static void meow()
{
    HANDLE console_color;
    console_color = GetStdHandle(
            STD_OUTPUT_HANDLE);

    const int minn = 1, maxx = 14; // const naming // kConstName // CONST_NAME
    srand((int)time(0));
    for(int i =0; i < 500;i++){
          int num = rand()%(maxx-minn+1) + minn;
          SetConsoleTextAttribute(console_color, (short unsigned int)num | Black);
          printf("meow ");
    }
    SetConsoleTextAttribute(console_color, White | Black);
}

//{---------------------------------------------------------------------------------------------
//! write help to flags
//}---------------------------------------------------------------------------------------------
static void help()
{
    printf("\t --coefs   -  get the coefficients from console \n"
           "\t --meow    -  meows;) \n");

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
static int readCommandFlags(int argc, char *argv[], coef* quatr)
{
    char coefComp[] = "--coefs";
    char help[] = "--help";
    char meow[] = "--meow";
    int flag = ERROW;
    if(argc == 1){
        flag = NOFLAG;
    }

    for(int i = 0; i < argc; i++){
        if (strcmp(coefComp, argv[i]) == 0){
            int is_coef = 0;
            is_coef += sscanf(argv[i+1], "%f", &(*quatr).a);//argc
            is_coef += sscanf(argv[i+2], "%f", &(*quatr).b);
            is_coef += sscanf(argv[i+3], "%f", &(*quatr).c);
            if (is_coef == 3){
                flag = COEFS;
                i += 3;
            }
            else{
                flag = ERRCOEFS;
            }
        }
        else if(strcmp(help, argv[i]) == 0){
            flag = HELP;
        }
        else if(strcmp(meow, argv[i]) == 0){
            flag = MEOW;
        }
    }
    return flag;
}
#endif // DEBUG

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
#ifdef DEBUG
    runAllTests(argc, argv);
#else
    roots myRoots = {};
    coef quatr = {};
    HANDLE console_color = GetStdHandle(STD_OUTPUT_HANDLE);

    int flag = readCommandFlags(argc, argv, &quatr);
    switch(flag){
        case COEFS:
            myRoots = findRoots(quatr);
            printRoots(myRoots);
            break;

        case ERRCOEFS:
            SetConsoleTextAttribute(console_color, Red | Black);
            printf("Invalid coefficents");
            SetConsoleTextAttribute(console_color, White | Black);
            break;

        case HELP:
            help();
            break;

        case NOFLAG:
            getCof(&quatr);
            myRoots = findRoots(quatr);
            printRoots(myRoots);
            break;

        case MEOW:
            meow();
            break;

        case ERROW:
            SetConsoleTextAttribute(console_color, Red | Black);
            printf("Invalid argument \n");
            SetConsoleTextAttribute(console_color, White | Black);
            break;

        default:
            assert(0 && "Errow");
    }
#endif

    return 0;
}
