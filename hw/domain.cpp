#include "domain.h"

Coat::Coat() = default;

Coat::Coat(std::string& size, std::string& colour, int quantity, float price, std::string& photograph)
{
	this->size = size;
	this->colour = colour;
	this->quantity = quantity;
	this->price = price;
	this->photograph = photograph;
}

std::string Coat::get_size()
{
	return this->size;
}

std::string Coat::get_colour()
{
	return this->colour;
}

int Coat::get_quantity()
{
	return this->quantity;
}

float Coat::get_price()
{
	return this->price;
}

std::string Coat::get_photograph()
{
	return this->photograph;
}

void Coat::set_size(std::string& new_size)
{
	this->size = new_size;
}

void Coat::set_colour(std::string& new_colour)
{
	this->colour = new_colour;
}

void Coat::set_quantity(int new_quantity)
{
	this->quantity = new_quantity;
}

void Coat::set_price(float new_price)
{
	this->price = new_price;
}

void Coat::set_photograph(std::string& new_photograph)
{
	this->photograph = new_photograph;
}

std::string Coat::to_string()
{
	return this->size + " | " + this->colour + " | " + std::to_string(this->quantity) + " | " + std::to_string(this->price);
}

Coat::~Coat() = default;