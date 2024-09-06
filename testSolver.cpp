#include "testSolver.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cassert>
#include <cstring>
#include "findRoots.h"
#include "colors.h"

const float ACCURACY = 0.0001f;

//{---------------------------------------------------------------------------------------------
//! Compare two numbers with less precision
//!
//! @param a  First number
//! @param b second pnumber
//! @return result of comparation
//}---------------------------------------------------------------------------------------------

static int compareTest(float a, float b)
{
    if(isnan(a) && isnan(b)){
        return EQUVAL;
    }
    if(fabs(a - b) < ACCURACY){
        return EQUVAL;
    }
    else if(a - b > ACCURACY){
        return FIRST;
    }
    return SECOND;
}

//{---------------------------------------------------------------------------------------------
//! Structure for data to referense test
//}--------------------------------------------------------------------------------------------

struct testData
{
    coef coefs;
    roots refRoots;
};

//{---------------------------------------------------------------------------------------------
//! Make the structure roots using parameters
//! @return myData data for test in structure
//}---------------------------------------------------------------------------------------------
static testData makeTest(float a, float b, float c, int num, float x1, float x2, float imgn)
{
    testData myData{};
    myData.coefs = makeCoef(a,b,c);
    myData.refRoots = makeRoots(num, x1, x2, imgn);
    return myData;
}

//{---------------------------------------------------------------------------------------------
//! Compare results of the referense test and function
//!
//! @param myTest data for testing
//! @param testOutput where to write results
//!
//! @note Can whire results of test in console or in file
//!
//! @see findRoots(),
//}---------------------------------------------------------------------------------------------
static bool oneTest(testData myTest, FILE * testOutput, int numOfTest)
{
    HANDLE console_color;
    console_color = GetStdHandle(STD_OUTPUT_HANDLE);

    assert(testOutput != NULL);

    roots myRoots{};
    myRoots = findRoots(myTest.coefs);
    int numMistakes = 0;

    if(myRoots.num != myTest.refRoots.num){
        SetConsoleTextAttribute(console_color, Magenta | Black);
        fprintf(testOutput, "[%i]: Test failed \n ", numOfTest);
        SetConsoleTextAttribute(console_color, White | Black);
        fprintf(testOutput,"Number of roots are different: num = %i, numRef = %i. \n",
                myRoots.num, myTest.refRoots.num);
        numMistakes++;
    }

    if((compareTest(myRoots.x1, myTest.refRoots.x1) || compareTest(myRoots.x2, myTest.refRoots.x2)) &&
            (compareTest(myRoots.x1, myTest.refRoots.x2) || compareTest(myRoots.x1, myTest.refRoots.x2))) {
        SetConsoleTextAttribute(console_color, Magenta | Black);
        fprintf(testOutput, "[%i]: Test failed \n ", numOfTest);
        SetConsoleTextAttribute(console_color, White | Black);
        fprintf(testOutput," \t Natash, my vse uronili! \n \t Roots are different: x1 = %f, x1Ref = %f , x2 = %f, x2Ref = %f\n",
                myRoots.x1, myTest.refRoots.x1, myRoots.x2, myTest.refRoots.x2);
        numMistakes++;
    }

    if (compareTest(myRoots.comp, myTest.refRoots.comp)){
        SetConsoleTextAttribute(console_color, Magenta | Black);
        fprintf(testOutput, "[%i]: Test failed \n ", numOfTest);
        SetConsoleTextAttribute(console_color, White | Black);
        fprintf(testOutput, "\t Natash, my vse uronili! Coplex parts are different: comp = %f, compRef = %f \n",
                myRoots.comp, myTest.refRoots.comp);
        numMistakes++;
    }

    if (numMistakes == 0){
        SetConsoleTextAttribute(console_color, LightGreen | Black);
        fprintf( testOutput, "[%i]: Test success \n", numOfTest);
        SetConsoleTextAttribute(console_color, White | Black);
        return false;
    }
    else {
        SetConsoleTextAttribute(console_color, Blue | Black);
        fprintf(testOutput, "\t Lomaets'a na: ");
        SetConsoleTextAttribute(console_color, White | Black);
        fprintf(testOutput, "a = %f, b = %f, c = %f \n"
               "\t Answer: x1 = %f, x2 = %f, comp = %f \n"
               "\t Refer : x1 = %f, x2 = %f, comp = %f \n \n",
               myTest.coefs.a, myTest.coefs.b, myTest.coefs.c,
               myRoots.x1, myRoots.x2, myRoots.comp, myTest.refRoots.x1, myTest.refRoots.x2, myTest.refRoots.comp);
        return true;
    }
}

//{---------------------------------------------------------------------------------------------
//! Read the test from console and write result
//!
//! @param nameOfTest nummer of test? which should be run
//! @param testOutput where to write results
//!
//! @note Can write results in different colors
//!
//! @see oneTest(),
//}---------------------------------------------------------------------------------------------
static void testConsole( int nameOfTest)
{
    HANDLE console_color;
    console_color = GetStdHandle(STD_OUTPUT_HANDLE);

    int numOKTests = 0;
    testData myTest[NUMTESTS] = {
        {0, 0, 0, 0, 1}, // [0]
        {0, 0, 0, 0, 1}, // [1]
        {0, 0, 0, 0, 1}, // [2]
        {0, 0, 0, 0, 1}, // [3]
    };
    myTest[0] = makeTest(0,  0, 0, INFIN_ROOTS, DEFOLT,    DEFOLT,    DEFOLT);
    myTest[1] = makeTest(1,- 2, 1, ONE_ROOT,    2,         1000,      DEFOLT);
    myTest[2] = makeTest(1, -3, 2, TWO_ROOTS,   1,         2,         DEFOLT);
    myTest[3] = makeTest(1,  2, 2, TWO_ROOTS,  -1,        -1,         1     );
    myTest[4] = makeTest(1,  5, 2, TWO_ROOTS,  -4.56155f, -0.438447f, 0     );

    if(nameOfTest == ALL){
        for(int i = 0; i < NUMTESTS; i++){
            numOKTests += oneTest(myTest[i], stdout, i + 1);
        }
        if(numOKTests == 0){
            SetConsoleTextAttribute(console_color, Cyan | Black);
            printf(" \n All tests success! \n"
                   "  /\\_/\\  (\n"
                   " ( ^.^ ) _)\n"
                   "   \\\"/  (\n"
                   " ( | | )\n"
                   "(__d b__) \n");
            SetConsoleTextAttribute(console_color, White | Black);
        }
        else{
            SetConsoleTextAttribute(console_color, Yellow | Black);
            printf("%i of %i test failed \n", numOKTests, NUMTESTS);
            SetConsoleTextAttribute(console_color, White | Black);
        }
    }
    else if (nameOfTest > 0 && nameOfTest <= NUMTESTS){
        oneTest(myTest[nameOfTest - 1], stdout, nameOfTest);
    }
    else {
        SetConsoleTextAttribute(console_color, Red | Black);
        printf("Invalid number of test");
        SetConsoleTextAttribute(console_color, White | Black);
    }
}

//{---------------------------------------------------------------------------------------------
//! Read the test from input file and write result in the output file
//!
//! @param fp file where tests should be get from
//! @param testOutput where to write results
//!
//! @note Can write results in different colors
//!
//! @see oneTest(),
//}---------------------------------------------------------------------------------------------
static void testFile(FILE * fp, FILE * testOutput)
{
    HANDLE console_color;
    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    int numTests = 0, numRoot = 0, numOkTests = 0;
    testData myTest{};
    float a = 0, b = 0, c = 0, x1 = 0, x2 = 0, comp = 0;

    if( fscanf(fp, "%i",&numTests ) == 1){

        while (getc(fp) != '\n')
            ;
        int i = 0;
        for (; i < numTests && !feof(fp); i++) {
            if(fscanf(fp, "%f %f %f %i %f %f %f", &a, &b, &c, &numRoot, &x1, &x2, &comp) == 7){
                myTest = makeTest(a, b, c, numRoot, x1, x2, comp);
                numOkTests += oneTest(myTest, testOutput, i + 1);
            }
        }

        if (numOkTests == 0){
            SetConsoleTextAttribute(console_color, LightGreen | Black);
            printf("All tests success \n");
            SetConsoleTextAttribute(console_color, White | Black);
        }
        else{
            SetConsoleTextAttribute(console_color, Yellow | Black);
            printf("%i of %i test failed \n", numOkTests, i);
            SetConsoleTextAttribute(console_color, White | Black);
        }
    }
}

//{---------------------------------------------------------------------------------------------
//! write help to flags
//}---------------------------------------------------------------------------------------------
static void helpToTest(){
    printf("\t --test  -  to run tests from programm, ALL for all test or yuo can put the number of test which should be run \n"
           "\t --test_file  -  to run tests from file. First argument should be a path to input file, second argument - to output file \n");

}

//{---------------------------------------------------------------------------------------------
//! Calls the desired function to run the tests
//! @see testConsole(), testFile()
//! @note get the command line arguments
//}---------------------------------------------------------------------------------------------
void runAllTests (int argc, char *argv[])
{
    HANDLE console_color;
    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    char strTest[] = "--test";
    char strTestFile[] = "--test_file";
    char helpTest[] = "--help";

    if (argc == 3 && strcmp(strTest, argv[1]) == 0 ){
            int nameOfTest = atoi(argv[2]);
            if (strcmp("ALL", argv[2]) == 0){
                testConsole(ALL);
            }
            else if (nameOfTest != 0 && nameOfTest <= NUMTESTS){
                testConsole(nameOfTest);
            }
            else {
                SetConsoleTextAttribute(console_color, Red | Black);
                printf("No such test \n");
                SetConsoleTextAttribute(console_color, White | Black);
            }
    }
    else if (argc == 4 && strcmp(strTestFile, argv[1]) == 0 ){
        FILE *testInput, *testOutput;

        if (fopen(argv[2], "r") != NULL && fopen(argv[3], "w") != NULL){

            testInput = fopen(argv[2], "r");
            testOutput = fopen(argv[3], "w");
            testFile(testInput, testOutput);
            fclose(testOutput);
            fclose(testInput);

        }
        else{

            SetConsoleTextAttribute(console_color, Red | Black);
            printf("Invalid name of file \n");
            SetConsoleTextAttribute(console_color, White | Black);
        }
    }
    else if(argc == 2 && strcmp(helpTest, argv[1]) == 0){
        helpToTest();
    }
    else{
        SetConsoleTextAttribute(console_color, Red | Black);
        printf("Invalid arguments");
        SetConsoleTextAttribute(console_color, White | Black);
    }

}
