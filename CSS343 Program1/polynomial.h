#ifndef POLYNOMIAL_H                                   
#define POLYNOMIAL_H
#include <iostream>
#include <string>
using namespace std;
// --------------------------------polynomial.h--------------------------------
// Sean-Luc Ghim CSS343D
// Created 1/09/23
// Date of Last Modification: 1/14/23
// ----------------------------------------------------------------------------
/* Purpose - Header file to create polynomials. Terms will be stored in a 
   doubly linked circular list that utilizes a dummy header. Leading term will
   be head->next whereas the last term will be head->prev. User may add as 
   many terms into their polynomial as they please.
*/
class Polynomial {
  // Overloaded <<: prints Cn * x^n + Cn-1 * X^n-1 + ... C1 * X + C0
  friend ostream& operator<<(ostream &output, const Polynomial& rhs);
  // Constructor: the default is a 0-degree polynomial with 0.0 coefficient
 public:
  // Member functions
  Polynomial();
  Polynomial(const Polynomial& rhs);
  ~Polynomial();
  int degree() const; // returns the degree of a polynomial
  double coefficient(const int power) const; 
                 // returns the coefficient of the x^power term.
  bool changeCoefficient(const double newCoefficient, const int power);
                 // replaces the coefficient of the x^power term
  // Arithmetic operators
  Polynomial operator+(const Polynomial& rhs) const;
  Polynomial operator-(const Polynomial& rhs) const;
  // Boolean comparison operators
  bool operator==(const Polynomial& rhs) const;
  bool operator!=(const Polynomial& rhs) const;
  // Assignment operators
  Polynomial& operator=(const Polynomial& rhs);
  Polynomial& operator+=(const Polynomial& rhs);
  Polynomial& operator-=(const Polynomial& rhs);
 private:
  struct Term {     // a term on the sparce polynomial
    double coeff;   // the coefficient of each term
    int power;      // the degree of each term
    Term *prev;     // a pointer to the previous higher term
    Term *next;     // a pointer to the next lower term
  };
  int size;         // # terms in the sparce polynomial
  Term *head;       // a pointer to the doubly-linked circular list of
                    // sparce polynomial
  bool insert(Term* pos, const double newCoeff, const int power);
  bool remove(Term* pos);
};
#endif
