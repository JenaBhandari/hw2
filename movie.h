#ifndef MOVIE_H
#define MOVIE_H
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include "util.h"
#include "product.h"

class Movie : public Product{

public:
	Movie(const std::string name, double price, int qty, const std::string genre, const std::string rating);
	virtual ~Movie();

	//Returns the appropriate keywords that this product should be associated with
  virtual std::set<std::string> keywords() const;

  //Returns a string to display the product info for hits of the search
  virtual std::string displayString() const;

  //Outputs the product info in the database format
  virtual void dump(std::ostream& os) const;

	
private:
	std::string genre_;
	std::string rating_;


};

#endif