#include "polynomial.h"
// -------------------------------polynomial.cpp-------------------------------
// Sean-Luc Ghim CSS343D
// Created 1/09/23
// Date of Last Modification: 1/14/23
// ----------------------------------------------------------------------------
/* Purpose - Implement polynomial.h to allow polynomials to be stored in a 
   doubly linked circular list that utilizes a dummy header. Leading term will
   be head->next whereas the last term will be head->prev. User may add as many
   terms into their polynomial as they please.
*/

// ----------------------------Default Constructor-----------------------------
// Initialize all values as 0 then construct dummy header. Since our polynomial
// is a doubly-linked circular list, set dummy header's prev and next to the 
// header itself.
// Precondition: None.
// Postcondition: Polynomial object with dummy header constructed. 
// ----------------------------------------------------------------------------
Polynomial::Polynomial() {
head = new Term();
this->size = 0;
head->coeff = 0.0;
head->power = 0;
head->prev = head;
head->next = head;
}

// ------------------------------Copy Constructor------------------------------
// Assign all values of an already existing polynomial into a newly constructed
// polynomial.
// Precondition: None.
// Postcondition: Deep copy of a polynomial object is constructed.
// ----------------------------------------------------------------------------
Polynomial::Polynomial(const Polynomial& rhs) {
head = new Term();
this->size = rhs.size;
head->coeff = rhs.head->coeff;
head->power = rhs.head->power;
head->prev = head;
head->next = head;
*this = rhs;
}

// ---------------------------------Destructor---------------------------------
// Delete/deallocate every node via list traversal, deallocate dummy head.
// Precondition: None.
// Postcondition: Delete all nodes including dummy head to deallocate memory.
// ----------------------------------------------------------------------------
Polynomial::~Polynomial() {
  Term* crawler = head->next;
  while (crawler != head) {
    remove(crawler);
    crawler = head->next;
  }
  head->coeff = 0.0;
  head->power = 0;
  head->prev = nullptr;
  head->next = nullptr;
  delete head;
  head = nullptr;
}

// -----------------------------MEMBER FUNCTIONS-------------------------------
// --------------------------------degree--------------------------------------
// Returns the greatest degree of a polynomial.
// Precondition: Be sure list is not empty.
// Postcondition: Return the leading coefficient's power.
// ----------------------------------------------------------------------------
int Polynomial::degree() const {
  // If doubly circular list is empty, return.
  if (size == 0) {
    return 0;
  } else {
    return head->next->power;
  }
}

// -------------------------------coefficient----------------------------------
// Returns the coefficient of the x^power term.
// Precondition: Be sure the list is not empty.
// Postcondition: Return the coefficient that has the target power if it exist.
// ----------------------------------------------------------------------------
double Polynomial::coefficient(const int power) const {
  Term *crawler = head->next;
  // Doubly circular list traversal
  while (crawler != head) {
    if (crawler->power == power) {
      return crawler->coeff;
    }
    else if (power > crawler->power) {
      return 0.0;
    }
    else if (power != crawler->power) {
      crawler = crawler->next;
    }
  }
  // Failed to find coefficient with the x^power term.
  return 0.0;
}

// ----------------------------changeCoefficient-------------------------------
// Replaces the coefficient of the x^power term
// Precondition: Be sure that the power is nonnegative.
// Postcondition: Either changes the coefficient of the term with the target 
// power or inserts a completely new term into the polynomial.
// ----------------------------------------------------------------------------
bool Polynomial::changeCoefficient(const double newCoeff, const int power) {
    // Return if power is < 0. Only use nonnegative powers for this program.
    if (power < 0) {
      cout << "ERROR: (Power != nonnegative); Term deleted." << endl;
      return false;
    }
  // List traversal for special cases.
  Term *crawler = head->next;
  while (crawler != head) {
    // If power is greater than leading term, insert.
    if (power > crawler->power) {
      return insert(crawler, newCoeff, power);
    }
    // If power found:
    else if (power == crawler->power) {
      if (newCoeff == 0.0) {
        return remove(crawler); // Delete, there is no coeff to change if 0. 
      }
      else {
        crawler->coeff = newCoeff; // Successfully changed coeff.
        return true;
      }
    }
    // Iterate until power spotted to change coefficient.
    else if (power < crawler->power) {
      crawler = crawler->next;
    }
  }
  // If all special cases fail, perform normal insertion.
  return insert(crawler, newCoeff, power);
  }
  
// ----------------------------OVERLOADED OPERATOR-----------------------------
// ---------------------------------operator<<---------------------------------
// Overloaded << operator to output Polynomial objects. 
// Precondition: Polynomial object exists to print out.
// Postcondition: Polynomial printed as: CnX^n + Cn-1X^(n-1) + ... + C1X + C0. 
// ----------------------------------------------------------------------------
ostream& operator<<(ostream& output, const Polynomial& rhs) {
// Test degree and coefficient methods.
  Polynomial::Term* crawler = rhs.head->next;
  while (crawler != rhs.head) {
    // Test if coefficient or power are 0.
     if ((crawler->coeff == 0.0) || (crawler->power == 0)) {
      // No value when coeff & power are 0.
      if ((crawler->power == 0) && (crawler->coeff == 0.0)) {
        output << ""; // Print nothing, there's no value in this term.
        return output;
      }
        else if ((crawler->power == 0) && (crawler->coeff != 0.0)) {
          output << crawler->coeff; // Print constant
          return output;
        }
        else if ((crawler->power != 0) && (crawler->coeff == 0.0)) {
          output << "x^" << crawler->power; // Print x^power without constant.
          return output;
        }
      }

    // If all special cases fail, then standard output performed.
    output << crawler->coeff << "x^" << crawler->power;
    // Preparing the next term in polynomial.
    if (crawler->next->coeff > 0.0) {
      output << " + ";
    }
    // Iterate.
    crawler = crawler->next;
  }
  return output;
}

// ----------------------------ARITHMETIC OPERATORS----------------------------
// ---------------------------------operator+----------------------------------
// Merges two polynomials together, adding all like terms if any.
// Precondition: The two polynomials are not empty.
// Postcondition: A new polynomial with the sum of any like terms.
// ----------------------------------------------------------------------------
Polynomial Polynomial::operator+(const Polynomial& rhs) const {
    // Create two polynomial objects. Merge thisPoly with rhsPoly.
    Polynomial thisPoly(*this);
    Polynomial rhsPoly(rhs);
    // Utilize crawlers for both polynomial's term traversal
    Term *thisCrawler;
    Term *rhsCrawler = rhsPoly.head->next;
    while(rhsCrawler != rhsPoly.head){
        thisCrawler = thisPoly.head->next;
        // Traversal for thisPoly.
        while(thisCrawler != thisPoly.head) {  
            // Adding like terms
            if(rhsCrawler->power == thisCrawler->power) {
                thisPoly.changeCoefficient(thisCrawler ->coeff
                 + rhsCrawler->coeff, thisCrawler ->power);             
            }
            // Iterate for thisPoly.
            thisCrawler = thisCrawler ->next;
        }
        // Inserting the rest of the rhs's terms into thisPoly.
        if(rhsCrawler->power != thisCrawler->power) {
            thisPoly.changeCoefficient(rhsCrawler->coeff, rhsCrawler->power);
        }
        rhsCrawler = rhsCrawler ->next;
    }
    return thisPoly;
}

// -------------------------------operator(-)----------------------------------
// Merges two polynomials together, subtracting all like terms if any. 
// Precondition: The two polynomials are not empty.
// Postcondition: A new polynomial with the difference of any like terms.
// ----------------------------------------------------------------------------
Polynomial Polynomial::operator-(const Polynomial& rhs) const {
    // Create two polynomial objects. Merge thisPoly with rhsPoly.
    Polynomial thisPoly(*this);
    Polynomial rhsPoly(rhs);
    // Utilize crawlers for both polynomial's term traversal
    Term *thisCrawler;
    Term *rhsCrawler = rhsPoly.head->next;
    while(rhsCrawler != rhsPoly.head){
        thisCrawler = thisPoly.head->next;
        // Traversal for thisPoly.
        while(thisCrawler != thisPoly.head) {  
            // Subtracting like terms
            if(rhsCrawler->power == thisCrawler->power) {
                thisPoly.changeCoefficient(thisCrawler ->coeff
                 - rhsCrawler->coeff, thisCrawler ->power);             
            }
            // Iterate for thisPoly.
            thisCrawler = thisCrawler ->next;
        }
        // Insert the rest of the rhs's terms into thisPoly.
        if(rhsCrawler->power != thisCrawler->power) {
            thisPoly.changeCoefficient(rhsCrawler->coeff, rhsCrawler->power);
        }
        rhsCrawler = rhsCrawler ->next;
    }
    return thisPoly;
}
  
// -----------------------------BOOLEAN OPERATORS------------------------------
// ---------------------------------operator==---------------------------------
// See if two polynomial objects are equivalent.
// Precondition: The two polynomials are not empty.
// Postcondition: Boolean value if the two polynomials are equivalent or not.
// ----------------------------------------------------------------------------
bool Polynomial::operator==(const Polynomial& rhs) const {
    Term* thisCrawler = head->next;
    Term* rhsCrawler = rhs.head->next;
    while (thisCrawler != head) {
      if ((thisCrawler->power == rhsCrawler->power) && 
      (thisCrawler->coeff == rhsCrawler->coeff)) {
          thisCrawler = thisCrawler->next;
          rhsCrawler = rhsCrawler->next;
      }
      else {
        break;
      }
      return true;
    }
    return false;
}

// ---------------------------------operator!=---------------------------------
// See if two polynomial objects are not equivalent.
// Precondition: The two polynomials are not empty.
// Postcondition: Boolean value if the two polynomials are equivalent or not.
// ----------------------------------------------------------------------------  
bool Polynomial::operator!=(const Polynomial& rhs) const {
  if (*this == rhs) {
    return false;
  }
  else {
    return true;
  }
}
  
// ----------------------------ASSIGNMENT OPERATORS----------------------------
// ----------------------------------operator=---------------------------------
// Creates a copy of an object and assigns to a new polynomial. This polynomial
// is first emptied then copies all of rhs's terms.  
// Precondition: Polynomial object must exist prior to assignment.
// Postcondition: Returns a reference of rhs polynomial.
// ---------------------------------------------------------------------------- 
Polynomial &Polynomial::operator=(const Polynomial& rhs) {
  if (this != &rhs) {
    //Empty this polynomial.
    Term* thisCrawler = head->next;
    while (thisCrawler != head) {
      remove(thisCrawler);
      thisCrawler = thisCrawler->next;
    }
    // Copy rhs polynomial into this polynomial.
    Term* rhsCrawler = rhs.head->next;
    while (rhsCrawler != rhs.head) {
      changeCoefficient(rhsCrawler->coeff, rhsCrawler->power);
      rhsCrawler = rhsCrawler->next;
    }
  }
  return *this;
}

// ---------------------------------operator+=---------------------------------
// Similar to operator+, merges two polynomial objects together and adds up the
// like terms and save the results into this polynomial.
// Precondition: The polynomials are not empty.
// Postcondition: Polynomial object that contains the merged polynomials with
// the sum of any like terms. 
// ----------------------------------------------------------------------------  
Polynomial &Polynomial::operator+=(const Polynomial& rhs) {
  return *this = (*this + rhs);
}
// ---------------------------------operator-=---------------------------------
// Similar to operator+, merges two polynomial objects together and subtracts
// the like terms and save the results into this polynomial.
// Precondition: The polynomials are not empty.
// Postcondition: Polynomial object that contains the merged polynomials with 
// the difference of any like terms.
// ---------------------------------------------------------------------------- 
Polynomial &Polynomial::operator-=(const Polynomial& rhs) {
  return *this = (*this - rhs);
}

// ------------------------------PRIVATE METHODS-------------------------------
// -----------------------------------insert-----------------------------------
// Inserts a new Term node with newCoefficient and power just before the 
// existing Term pointed by the pos pointer. The insert function will be used
// by changeCoefficient to insert new term. Returns false if insertion fails.
// Precondition:
// Postcondition:
// ---------------------------------------------------------------------------- 
bool Polynomial::insert(Term* pos, const double newCoeff, const int power) {
  if (pos != nullptr) {
    Term *ins = new Term;
    size++;
    ins->coeff = newCoeff;
    ins->power = power;
    ins->prev = pos->prev;
    ins->next = pos;
    pos->prev->next = ins;
    pos->prev = ins;
    return true;
  }
  else {
    return false;
  }
}

// -----------------------------------remove-----------------------------------
// Removes an existing Term node pointed by the pos pointer.
// Precondition: The pos pointer exists and the polynomial is not empty.
// Postcondition: Removes the term pointed by the pos pointer.
// ---------------------------------------------------------------------------- 
bool Polynomial::remove(Term* pos) {
  if (pos != nullptr || size > 0) {      
    size--;
    // Link pos->prev's next to pos->next
    pos->prev->next = pos->next;
    // Link pos->next's prev to pos->prev
    pos->next->prev = pos->prev;
    pos->prev = nullptr;
    pos->next = nullptr;
    pos->coeff = 0.0;
    pos->power = 0;
    delete pos;
    return true;
  }
  else {
    return false;
  }
}