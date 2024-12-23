#pragma once
#include <string>
#include "domain.h"
#include "exceptions.h"

class Validator {
public:
	//validates the size of the product
	//TRUE if the size is valid
	//FALSE if the size is invalid
	bool validate_size(std::string size);

	//validates the colour of the product
	//TRUE if the colour is valid
	//FALSE if the colour is invalid
	bool validate_colour(std::string colour);

	//validates the price of the product
	//TRUE if the price is valid
	//FALSE if the price is invalid
	bool validate_price(float price);

	//validates the quantity of the product
	//TRUE if the quantity is valid
	//FALSE if the quantity is invalid
	bool validate_quantity(int quantity);

	//validates the photograph of the product
	//TRUE if the photograph is valid
	//FALSE if the photograph is invalid
	bool validate_photograph(std::string photograph);

	//validates if the coat is valid
	//TRUE if the coat is valid
	//FALSE if the coat is invalid
	bool validate_coat(Coat coat);
};