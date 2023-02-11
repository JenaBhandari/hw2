#ifndef CLOTHING_H
#define CLOTHING_H

#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include "util.h"
#include "product.h"

class Clothing : public Product{

public:
	Clothing(const std::string name, double price, int qty, const std::string size, const std::string brand);
	virtual ~Clothing();

	//Returns the appropriate keywords that this product should be associated with
  virtual std::set<std::string> keywords() const;

  //Returns a string to display the product info for hits of the search
  virtual std::string displayString() const;

  //Outputs the product info in the database format
  virtual void dump(std::ostream& os) const;

	
private:
	std::string size_;
	std::string brand_;


};

#endif