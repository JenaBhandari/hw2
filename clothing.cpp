#include <sstream>
#include <iomanip>
#include "product.h"
#include "clothing.h"
#include "util.h"
#include <string>

using namespace std;

//Constructor
Clothing::Clothing(const std::string name, double price, int qty, const std::string size, const std::string brand) : Product("clothing", name, price, qty), size_(size), brand_(brand)
{

}

//Destructor
Clothing::~Clothing()
{

}

//---------------------------------------------------------------------------------------------------------
//Returns the appropriate keywords that this product should be associated with
std::set<std::string> Clothing::keywords() const
{
	std::set<std::string> words;

	std::string info = getName() + " " + size_ + " " + brand_ + " clothing";

	words = parseStringToWords(info);

	return words;
	
}

//---------------------------------------------------------------------------------------------------------
//Returns a string to display the product info for hits of the search
std::string Clothing::displayString() const
{
	std::string info;

	std::stringstream stream;
	stream << std::fixed << std::setprecision(0) << getQty();

	std::string sQty = stream.str();

	std::stringstream stream2;

	stream2 << std::fixed << std::setprecision(2) << getPrice();

	std::string sPrice = stream2.str();
	
	info = getName() + "\n" + "Size: " + size_ + " Brand: " + brand_ + "\n" + sPrice + " " + sQty + " left\n";

	return info;
}

//---------------------------------------------------------------------------------------------------------
//Outputs the product info in the database format
void Clothing::dump(std::ostream& os) const
{
	Product::dump(os);
	os << size_ << "\n" << brand_  << endl;
	//os << "clothing" << "\n" << getName() << "\n" << getPrice() << "\n" << getQty() << "\n" << size_ << "\n" << brand_ << "\n" << endl;
}
