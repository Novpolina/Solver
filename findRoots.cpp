//==============================================================================================
//! @file findRoots.cpp
//!
//! Quadratic equvals Solver
//!

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <cassert>
#include <cmath>
#include "findRoots.h"

//{---------------------------------------------------------------------------------------------
//! Make the structure coef using parameters
//!
//! @param num  Number of roots
//! @param x1   first root
//! @param x2   second root
//! @param comp the complex part of the roots
//! @return quatr coefficients in structure
//}---------------------------------------------------------------------------------------------



coef makeCoef (float a, float b, float c){
    coef quatr{};
    quatr.a = a;
    quatr.b = b;
    quatr.c = c;
    return quatr;
}
//{---------------------------------------------------------------------------------------------
//! Make the structure roots using parameters
//!
//! @param a  First parameter
//! @param b second parameter
//! @param c third parameter
//! @return quatr roots in structure
//}---------------------------------------------------------------------------------------------

roots makeRoots (int num, float x1, float x2, float comp){
    roots myRoots{};
    myRoots.num = num;
    myRoots.x1 = x1;
    myRoots.x2 = x2;
    myRoots.comp = comp;
    return myRoots;
}

//{---------------------------------------------------------------------------------------------
//! Compare two numbers
//!
//! @param a  First number
//! @param b second pnumber
//! @return result of comparation
//}---------------------------------------------------------------------------------------------

int compare (float a, float b) {
    if( fabs(a -b) < EPSILON){
        return EQUVAL;
    }
    else if(a - b > EPSILON){
        return FIRST;
    }
    return SECOND;
}

//{---------------------------------------------------------------------------------------------
//! Arranges the roots in ascending order
//!
//! @param myRoots
//}---------------------------------------------------------------------------------------------

void rootsOrder (roots* myRoots){
    assert(myRoots != NULL);

    if(compare(myRoots->x1, myRoots->x2) == FIRST){
        float a = myRoots->x2;
        myRoots->x2 = myRoots->x1;
        myRoots->x1 = a;

    }
}

//{---------------------------------------------------------------------------------------------
//! Solve linear equation
//! @return myRoots   roots of the equation
//}---------------------------------------------------------------------------------------------

roots findLinear(coef quatr){
    roots myRoots{NO_ROOTS, DEFOLT, DEFOLT, DEFOLT};

    if(compare(quatr.b, 0) != 0){
        myRoots.x1 = -quatr.c/quatr.b;
        myRoots.comp = 0;
        myRoots.num = ONE_ROOT;
    }
    else if(compare(quatr.c, 0) == 0){
        myRoots.comp = 0;
        myRoots.num = INFIN_ROOTS;
    }
    else{
        myRoots.comp = 0;
        myRoots.num = NO_ROOTS;

    }
    return myRoots;

}

//{---------------------------------------------------------------------------------------------
//! Solve quadratic equation
//! @return myRoots   roots of the equation
//}---------------------------------------------------------------------------------------------

roots solveQuadratic( coef quatr ){

    roots myRoot{NO_ROOTS, DEFOLT, DEFOLT, DEFOLT};
    int d = quatr.b * quatr.b - 4 * quatr.a * quatr.c;
    float sqrt_val = sqrt(fabs(d));

    if (compare(d, 0) == 1) {
        myRoot.x1 = (-quatr.b + sqrt_val) / (2 * quatr.a); //ошибка quatr.b
        myRoot.x2 = (-quatr.b - sqrt_val) / (2 * quatr.a);
        myRoot.comp = 0;
        myRoot.num = TWO_ROOTS;
    }
    else if (compare(d, 0) == 0) {
        myRoot.x1 =  -quatr.b / (2 * quatr.a);
        myRoot.x2 = myRoot.x1;
        myRoot.comp = 0;
        myRoot.num = ONE_ROOT;
    }
    else
    {
        myRoot.x1 = -quatr.b / (4 * quatr.a); //ошибка 2 а не 4
        myRoot.x2 = myRoot.x1;
        myRoot.comp = sqrt_val / (2 * quatr.a);
        myRoot.num = TWO_ROOTS;
    }
    return myRoot;
}

//{---------------------------------------------------------------------------------------------
//! Calls the desired function to solve the equation
//! @see findLinear(), solveQuadratic(), rootsOrder()
//! @return myRoots   roots of the equation
//}---------------------------------------------------------------------------------------------

roots findRoots(struct coef quatr) {
    roots myRoots{NO_ROOTS, DEFOLT, DEFOLT, DEFOLT};

    assert (&myRoots.x1 != NULL && "X1 un correct");
    assert (&myRoots.x2 != NULL);

    if (compare(quatr.a, 0) == 0) {
        myRoots = findLinear(quatr);
    }
    else if (compare(quatr.c, 0) == 0){
        myRoots.x1 = 0;
        myRoots.x2 = -quatr.b/quatr.c;
        myRoots.comp = 0;
        myRoots.num = ONE_ROOT;
    }
    else {
        myRoots = solveQuadratic(quatr);
    }
    rootsOrder(&myRoots);


    return myRoots;
}
