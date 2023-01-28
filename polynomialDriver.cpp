#include "polynomial.h"
// ----------------------------polynomialDriver.cpp----------------------------
// Sean-Luc Ghim CSS343D
// Created 1/09/23
// Date of Last Modification: 1/14/23
// ----------------------------------------------------------------------------
/* Purpose - Run tests for every method/function in polynomial.cpp. 
*/
int main() {
    // Leading term with a negative power.
    Polynomial p1;
    p1.changeCoefficient(1, -1);
    cout << "Negative power test: p1 = " << p1 << endl;

    // Insertion with random coefficients and powers in random order.
    p1.changeCoefficient(5.3, 3);
    p1.changeCoefficient(3, 2);
    p1.changeCoefficient(1, 1);
    p1.changeCoefficient(6, 0);
    p1.changeCoefficient(-2.1, 5);
    p1.changeCoefficient(1.2, 7);
    cout << "\nMultiple insertion test: p1 = " << p1 << endl;

    // Inserting a new coefficient, but with a pre-existing power.
    p1.changeCoefficient(2.3,3);
    cout << "\nPre-existing power test: p1 = " << p1 << endl;

    // Inserting term with a negative power into pre-existing polynomial.
    p1.changeCoefficient(5, -5);
    cout << "\nNegative power test: p1 = " << p1 << endl;

    // Copy constructor test.
    Polynomial p2(p1);
    cout << "\nCopy constructor test: p2 = " << p2 << endl;

    // Overloaded polynomial assignment operator test.
    Polynomial p3 = p2;
    cout << "\nAssignment operator test: p3 = " << p3 << endl;

    // Creating a new polynomial, for further testing.
    Polynomial p4;
    p4.changeCoefficient(3.1, 2);
    p4.changeCoefficient(2, 1);
    p4.changeCoefficient(9, 0);
    cout << "\n p4 = " << p4 << endl;

    // Overloaded boolean operator== test.
    if (p3 == p2) {
        cout << "\nOperator== test: p3 == p2: " << 
        "Polynomials are equivalent." << endl;
    } 
    else {
        cout << "\nOperator== test: p3 == p2: " << 
        "Polynomials are not equivalent." << endl;
    }

    if (p3 == p4) {
        cout << "\nOperator== test: p3 == p4: " << 
        "Polynomials are equivalent." << endl;
    } 
    else {
        cout << "\nOperator== test: p3 == p4: " << 
        "Polynomials are not equivalent." << endl;
    }
    // Overloaded boolean operator!= test.
    if (p1 != p2) {
        cout << "\nOperator!= test: p1 != p2: " << 
        "Polynomials are not equivalent." << endl;
    }
    else {
        cout << "\nOperator!= test: p1 != p2: " << 
        "Polynomials are equivalent." << endl;
    }

    if (p1 != p4) {
        cout << "\nOperator!= test: p1 != p4: " << 
        "Polynomials are not equivalent." << endl;
    }
    else {
        cout << "\nOperator!= test: p1 != p4: " << 
        "Polynomials are equivalent." << endl;
    }

    // Testing operator+
    Polynomial p5;
    p5 = p4 + p1;
    cout << "\nPolynomial operator+ test: p5 = " << p5 << endl;
    

    // Testing operator-
    Polynomial p6 = p4 - p1;
    cout << "\nPolynomial operator- test: p6 = " << p6 << endl;
    
    // Testing operator+=
    Polynomial p7;
    p7 += p4;
    cout << "\nPolynomial operator+= test: (p7 += p4) = " << p7 << endl;
    
    //Testing operator-=
    Polynomial p8;
    p8 -= p1;
    cout << "\nPolynomial operator-= test: (p8 -= p1) = " << p8 << endl;
}

