#ifndef HEADER1_H_INCLUDED
#define HEADER1_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

const int GREEN = 10;
const int RED = 13;
const int WHITE = 15;
const int PINK = 12;
const int CAT = 23;
const int ALL = 50;

const int NUMTESTS = 5;
void testSquare(int);
void testFile(FILE *);
void run_allTests(int, char*[]);

#endif // HEADER1_H_INCLUDED
