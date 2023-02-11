#include "mydatastore.h"
#include "product.h"
#include "book.h"
#include "clothing.h"
#include "movie.h"
#include <sstream>
#include <iomanip>
#include "util.h"
#include <string>
#include <map>

using namespace std;

//Constructor
MyDataStore::MyDataStore() : DataStore()
{
	std::map< User*, std::vector<Product*> > carts;

	std::set< Product* > products;

	std::map < std::string, std::vector<Product*> > keywordMap;
}

//Destructor
MyDataStore::~MyDataStore()
{

	for (Product* pr : products)
    delete pr;

	products.clear();


	//delete user  pointers in carts map
	std::map< User*, std::vector<Product*> >::iterator it; 

	for (it = carts.begin(); it != carts.end(); ++it)
	{
		User* curUser =  it->first;

		delete curUser;
	}

	carts.clear();
/*

	for (Product* pr : products)
    delete pr;
	products.clear();
*/
	keywordMap.clear();


}

//---------------------------------------------------------------------------------------------------------
//turn string to all uppercase
std::string MyDataStore::toUpper(std::string word)
{
	std::string upper = "";
	for (char c: word)
	{
		if (c >= 'a' &&  c <= 'z')
		{
			c += 'A'-'a';
		}

		upper += c;
	}

	return upper;
}

//---------------------------------------------------------------------------------------------------------
//Adds a product to the data store and the associated keywords to the set keywordMap
void MyDataStore::addProduct(Product* p)
{
	products.insert(p);

	std::set<std::string> words = p->keywords();
	//std::set<std::string>::iterator wit;
	//cout << "in addProduct, retrieving product's keywords" << endl;
    //for (wit = words.begin(); wit != words.end(); ++wit) {
        //std::cout << *wit << std::endl;
    //}

	std::set<std::string>::iterator it;


	for(it = words.begin(); it != words.end(); ++it)
	{
		//if keyword is not in map, then add a new keyword to product vector pair
		std::vector<Product*> theProduct;
		theProduct.push_back(p);

		//cout << "in addP for loop for word: " << *it << endl;
		
		std::string theWord = toUpper(*it);



		if ( keywordMap.find(theWord) == keywordMap.end())
		{
			//cout << "in addP if statement for word: " << theWord << endl;
			keywordMap.insert(std::pair<std::string, std::vector<Product*>>(theWord, theProduct));
		}
		else
		{
			//cout << "in addP else statement for word: " << theWord << endl;
			keywordMap[theWord].push_back(p);
		}

		std::vector<Product*> newProductList = keywordMap[theWord];

		std::vector<Product*>::iterator pit;
		//cout << "in addP after if statement for word: " << theWord << endl;
		//for (pit = newProductList.begin(); pit != newProductList.end(); ++pit) {
        //std::cout << *pit << std::endl;
    //}

	}
}

//---------------------------------------------------------------------------------------------------------
//Adds a user to the data store
void MyDataStore::addUser(User* u)
{
	if (carts.find(u) == carts.end())
	{
		std::vector<Product*> theCart;
		carts.insert(std::pair< User*, std::vector<Product*> >(u, theCart));
	}
}


//---------------------------------------------------------------------------------------------------------
// Function to convert Vector to Set
std::set<Product*> MyDataStore::toSet(std::vector<Product*> v)
{
    std::set<Product*> s;
 
    for (Product* x : v) {
        s.insert(x);
    }
    return s;
}


//---------------------------------------------------------------------------------------------------------
//Performs a search of products whose keywords match the given "terms"
//type 0 = AND search (intersection of results for each term) while
//type 1 = OR search (union of results for each term)
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
	//cout << "in search" <<endl;
	std::set<Product*> setOfProducts;

	//iterate through terms. find 
	std::vector<std::string>::iterator it;
	for(it = terms.begin(); it != terms.end(); ++it)
	{

		std::string theTerm = toUpper(*it);
		//cout <<" in for loop 1 keyTerm: " << theTerm << endl;
		//if keyword is in the keyword map, find the vector of products and add it to the set
		if (keywordMap.find(theTerm) != keywordMap.end())
		{
			//cout << "in if statement" << endl;
			std::vector<Product*> list = keywordMap[theTerm];
			std::set<Product*> newSet = toSet(list);

			//if its the first keyword, add all of them to the set
			if (setOfProducts.empty())
			{
				//setOfProducts = toSet(keywordMap[*it]);
				setOfProducts = setUnion(setOfProducts, newSet);
			}

			//if its a next keyword, then either OR or AND them to the set
			else
			{
				if (type == 1)
				{
					setOfProducts = setUnion(setOfProducts, newSet);
				}
				else if (type == 0)
				{
					setOfProducts = setIntersection(setOfProducts, newSet);
				}
			}
		}
	}

	std::vector<Product*> theProducts;


	//turn set of products into a vector to return
	std::set<Product*>::iterator next;
	for (next = setOfProducts.begin(); next != setOfProducts.end(); ++next) 
	{
    theProducts.push_back(*next);
  }

	return theProducts;
}

//---------------------------------------------------------------------------------------------------------
//user exists? return user if so, otherwise rtn nullptr
User* MyDataStore::userExists(std::string username)
{
	std::string upperUsername = "";
	for (char c: username)
	{
		if (c >= 'a' &&  c <= 'z')
		{
			c += 'A'-'a';
		}

		upperUsername += c;
	}

	std::map< User*, std::vector<Product*> >::iterator it; 

	for (it = carts.begin(); it != carts.end(); ++it)
	{
		User* curUser =  it->first;
		std::string curUsername = curUser->getName();
		std::string upperCurUsername = "";

		for (char c: curUsername)
		{
			if (c >= 'a' &&  c <= 'z')
			{
				c += 'A'-'a';
			}

			upperCurUsername += c;
		}

		if (upperUsername == upperCurUsername)
		{
			return curUser;
		}

	}

	return nullptr;
}

//---------------------------------------------------------------------------------------------------------
//adds product to user's cart
void MyDataStore::addToCart(std::string username, Product* newProduct)
{
	//is there a user with that name alr in it?
	//if so, add product to that user
	//if not, then add a new user, and then add product to that user

	User* curUser = userExists(username);
	if (curUser == nullptr)
	{
		cout << "Invalid request" << endl;
	}
	else
	{
		std::map<User*, std::vector<Product*> >::iterator it = carts.find(curUser); 
		if (it != carts.end())
		{
			
    	it->second.push_back(newProduct);
		}
	}
}

//---------------------------------------------------------------------------------------------------------
//iterates through users cart and buys in order whatever they can afford or what is in stock
void MyDataStore::buyCart(std::string username)
{
	User* curUser = userExists(username);

	std::vector< Product* > toKeep;

	if (curUser != nullptr)
	{
		std::map<User*, std::vector<Product*> >::iterator it = carts.find(curUser); 
		if (it != carts.end())
		{
    	std::vector< Product* > theCart = it->second;


			std::vector<Product*>::iterator next;
			for(next = theCart.begin(); next != theCart.end(); ++next)
			{
				Product *curProduct = *next;
				if ( (curProduct->getQty() > 0) && (curUser->getBalance() >= curProduct->getPrice()) )
				{
					curProduct->subtractQty(1);
					curUser->deductAmount(curProduct->getPrice());
					
					cout << "deduct balance" << endl;
				}
				else
				{
					toKeep.push_back(*next);
					cout << "can't buy" << endl;
				}
			}

			it->second = toKeep;


		}
	}
	else
	{
		cout << "Invalid username" << endl;
	}
}

//---------------------------------------------------------------------------------------------------------
//iterates through the users carts and prints each item
void MyDataStore::viewCart(std::string username)
{
	User* curUser = userExists(username);
	if (curUser != nullptr)
	{
		std::map<User*, std::vector<Product*> >::iterator it = carts.find(curUser); 
		if (it != carts.end())
		{
    	std::vector< Product* > theCart = it->second;

			std::vector<Product*>::iterator next;
			int count = 1;
			for(next = theCart.begin(); next != theCart.end(); ++next)
			{
				Product *curProduct = *next;
				cout <<"Item " << count << endl;
				cout << curProduct->displayString();
				count++;
			}
		}
	}
	else
	{
		cout << "Invalid Username" << endl;
	}

}
//---------------------------------------------------------------------------------------------------------
//Reproduce the database file from the current Products and User values
void MyDataStore::dump(std::ostream& ofile)
{
	ofile << "<products>" << endl;

	std::set<Product*>::iterator it;

	for (it = products.begin(); it != products.end(); ++it)
	{
		Product* curProduct = *it;
		curProduct->dump(ofile);
	}

	ofile << "</products>" << "\n" << "<users>" << endl;

	std::map< User*, std::vector<Product*> >::iterator next; 

	for (next = carts.begin(); next != carts.end(); ++next)
	{
		User *curUser = next->first;
		curUser->dump(ofile);
	}

	ofile << "</users>" << endl;

}
