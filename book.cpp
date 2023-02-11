#include <sstream>
#include <iomanip>
#include "book.h"
#include "util.h"
#include <string>


using namespace std;

//Constructor
Book::Book(const std::string name, double price, int qty, const std::string author, const std::string isbn) : Product("book", name, price, qty), author_(author), isbn_(isbn) 
{

}

/*
	std::string author_(author);
	std::string isbn_(isbn);

	author_(author), isbn_(isbn)
	*/

//Destructor
Book::~Book()
{

}

//---------------------------------------------------------------------------------------------------------
//Returns the appropriate keywords that this product should be associated with
std::set<std::string> Book::keywords() const
{
	std::set<std::string> words;

	std::string info = getName() + " " + author_ + " " + isbn_ + " book";

	words = parseStringToWords(info);

	return words;
	
}

//---------------------------------------------------------------------------------------------------------
//Returns a string to display the product info for hits of the search
std::string Book::displayString() const
{
	std::string info;

	std::stringstream stream;
	stream << std::fixed << std::setprecision(0) << getQty();

	std::string sQty = stream.str();

	std::stringstream stream2;

	stream2 << std::fixed << std::setprecision(2) << getPrice();

	std::string sPrice = stream2.str();

	info = getName() + "\n" + "Author: " + author_ + " ISBN: " + isbn_ + "\n" + sPrice + " " + sQty + " left\n";

	return info;
}

//---------------------------------------------------------------------------------------------------------
//Outputs the product info in the database format
void Book::dump(std::ostream& os) const
{
	Product::dump(os);
	os << isbn_ << "\n" << author_ << endl;

	os << "book" << "\n" << getName() << "\n" << getPrice() << "\n" << getQty() << "\n" << isbn_ << "\n" << author_ << endl;
}

