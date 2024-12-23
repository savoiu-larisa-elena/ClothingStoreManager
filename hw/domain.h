#pragma once
#include <iostream>
#include <string>

class Coat {
private:
	std::string size;
	std::string colour;
	int quantity;
	float price;
	std::string photograph;
public:
    //the basic constructor
    Coat();

	//the constructor
	//-> the size of the coat is a string
	//-> the colour of the coat is a string
	//-> the quantity of the coat is an integer
	//-> the price of the coat is a float
	//-> the photograph of the coat is a string
	Coat(std::string& size, std::string& colour, int quantity, float price, std::string& photograph);

	//function that returns the size of the coat
	std::string get_size();

	//function that returns the colour of the coat
	std::string get_colour();

	//function that returns the quantity of the coat
	int get_quantity();

	//function that returns the price of the coat
	float get_price();

	//function that returns the photograph of the coat
	std::string get_photograph();

	//function that sets the size of the coat
	void set_size(std::string& new_size);

	//function that sets the colour of the coat
	void set_colour(std::string& new_colour);

	//function that sets the quantity of the coat
	void set_quantity(int new_quantity);

	//function that sets the price of the coat
	void set_price(float new_price);

	//function that sets the photograph of the coat
	void set_photograph(std::string& new_photograph);
	
	//function that returns the coat as a string
	std::string to_string();

	bool operator==(const Coat& other) const {
		// Define your comparison logic here
		return (this->size == other.size && this->colour == other.colour && this->price == other.price && this->photograph == other.photograph);
	}

	//the destructor
	~Coat();
};
