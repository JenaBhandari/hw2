#ifndef MYDATASTORE_H
#define MYDATASTORE_H
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
#include "datastore.h"
#include "user.h"
#include <map>

class MyDataStore : public DataStore {

	public:
		MyDataStore();

    virtual ~MyDataStore();

    //Adds a product to the data store
    virtual void addProduct(Product* p);

    //Adds a user to the data store
    virtual void addUser(User* u);

  //Performs a search of products whose keywords match the given "terms"
	//type 0 = AND search (intersection of results for each term) while
	//type 1 = OR search (union of results for each term)
    virtual std::vector<Product*> search(std::vector<std::string>& terms, int type);

    //Reproduce the database file from the current Products and User values
    virtual void dump(std::ostream& ofile);

		//adds product to user's cart
		void addToCart(std::string username, Product* newProduct);

		//user exists? return user if so, otherwise rtn nullptr
		User* userExists(std::string username);

		//iterates through users cart and buys in order whatever they can afford or what is in stock
		void buyCart(std::string username);

		//iterates through the users carts and prints each item
		void viewCart(std::string username);

		//turn string to all uppercase
		std::string toUpper(std::string word);

	private:

	std::map< User*, std::vector<Product*> > carts;

	std::set< Product* > products;

	std::map < std::string, std::vector<Product*> > keywordMap;
	
	std::set<Product*> toSet(std::vector<Product*> v);
};

#endif