#ifndef FINDROOTS_H_INCLUDED
#define FINDROOTS_H_INCLUDED


const float EPSILON = 0.000001;
const float DEFOLT = 0;

//! @class Enum for corparation
enum comparation{
    EQUVAL, ///< numbers are equval
    FIRST,  ///< the first number is greater than the second
    SECOND ///< the second number is greater than the first
};

//! To store the number of roots of the equation
enum numberOfRoots{
    NO_ROOTS, ONE_ROOT, TWO_ROOTS,
    INFIN_ROOTS ///< shows that equation has an infinite number of roots
};

//{---------------------------------------------------------------------------------------------
//! Structure for coefficients of the quadratic equation
//}--------------------------------------------------------------------------------------------
struct coef{
    float a;
    float b;
    float c;
};

//{---------------------------------------------------------------------------------------------
//! @class Structur for roots of the quadratic equation
//! @param num  Number of roots
//! @param x1   first root
//! @param x2   second root
//! @param comp the complex part of the roots
//}--------------------------------------------------------------------------------------------
struct roots{
    int num;
    float x1;
    float x2;
    float comp;
};

roots makeRoots(int, float, float, float);

coef makeCoef(float, float, float);

roots findRoots(struct coef);

int compare(float, float);

roots findRoots(coef);

#endif // FINDROOTS_H_INCLUDED
