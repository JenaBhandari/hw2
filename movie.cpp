#include <sstream>
#include <iomanip>
#include "product.h"
#include "movie.h"
#include "util.h"
#include <string>


using namespace std;

//Constructor
Movie::Movie(const std::string name, double price, int qty, const std::string genre, const std::string rating) : Product("movie", name, price, qty), genre_(genre), rating_(rating)
{

}

//Destructor
Movie::~Movie() 
{

}

//---------------------------------------------------------------------------------------------------------
//Returns the appropriate keywords that this product should be associated with
std::set<std::string> Movie::keywords() const
{
	std::set<std::string> words;

	std::string info = getName() + " " + genre_ + " " + rating_ + " movie";

	words = parseStringToWords(info);

	return words;
	
}

//---------------------------------------------------------------------------------------------------------
//Returns a string to display the product info for hits of the search
std::string Movie::displayString() const
{
	std::string info;

	std::stringstream stream;
	stream << std::fixed << std::setprecision(0) << getQty();

	std::string sQty = stream.str();

	std::stringstream stream2;

	stream2 << std::fixed << std::setprecision(2) << getPrice();

	std::string sPrice = stream2.str();

	
	info = getName() + "\n" + "Genre: " + genre_ + " Rating: " + rating_ + "\n" + sPrice + " " + sQty + " left\n";

	return info;
}

//---------------------------------------------------------------------------------------------------------
//Outputs the product info in the database format
void Movie::dump(std::ostream& os) const
{
	Product::dump(os);
	os << genre_ << "\n" << rating_ << endl;
	//os << "movie" << "\n" << getName() << "\n" << getPrice() << "\n" << getQty() << "\n" << genre_ << "\n" << rating_ << "\n" << endl;
}
