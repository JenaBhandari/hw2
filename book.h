#ifndef BOOK_H
#define BOOK_H
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include "product.h"

class Book : public Product{

public:
	Book(const std::string name, double price, int qty, const std::string author, const std::string isbn);
	virtual ~Book();

	//Returns the appropriate keywords that this product should be associated with
  virtual std::set<std::string> keywords() const;

  //Returns a string to display the product info for hits of the search
  virtual std::string displayString() const;

  //Outputs the product info in the database format
  virtual void dump(std::ostream& os) const;

	
private:
	std::string author_;
	std::string isbn_;


};

#endif