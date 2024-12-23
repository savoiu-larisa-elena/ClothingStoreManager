#include "validator.h"
#include <cctype>
#include <cstring>

bool Validator::validate_size(std::string size)
{
	if (size.size() == 0)
        throw ValidationError("Size cannot be empty!");
	if (size[0] != 'S' && size[0] != 'M' && size[0] != 'L' && size[0] != 'X')
        throw ValidationError("Size must be XXS, XS, S, M, L, XL or XXL!");
	return true;
}

bool Validator::validate_colour(std::string colour)
{
	if (colour.size() == 0)
        throw ValidationError("Colour cannot be empty!");
	auto it = colour.begin();
    while (it != colour.end())
    {
        if (!isalpha(*it) && *it != '_')
			throw ValidationError("Colour can only contain letters and underscores!");
        it++;
    }
	return true;
}

bool Validator::validate_price(float price)
{
	if (price <= 0)
        throw ValidationError("Price must be a positive number!");
	return true;
}

bool Validator::validate_quantity(int quantity)
{
	if (quantity < 0)
		throw ValidationError("Quantity must be a positive number!");
	return true;
}

bool Validator::validate_photograph(std::string photograph)
{
	if (photograph.size() == 0)
		throw ValidationError("Photograph cannot be empty!");
    if(photograph[0] != 'h' && photograph[1] != 't' && photograph[2] != 't' && photograph[3] != 'p')
		throw ValidationError("Photograph must start with http!");
	return true;
}

bool Validator::validate_coat(Coat coat)
{
	return validate_size(coat.get_size()) && validate_colour(coat.get_colour()) && validate_price(coat.get_price()) && validate_quantity(coat.get_quantity()) && validate_photograph(coat.get_photograph());
}