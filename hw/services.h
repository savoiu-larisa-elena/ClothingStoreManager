#pragma once

#include "action.h"
#include "repository.h"
#include "domain.h"
#include <cstring>
#include <vector>

class Services {
private:
    Repository *repository;
    std::vector<Coat> *shopping_basket;
    float total_price_of_shopping_basket;

    //stacks for undo and redo
    std::vector<Action*> undo_stack;
    std::vector<Action*> redo_stack;
public:
    //the constructor
    Services(Repository *repository, std::vector<Coat> *shopping_basket);

    //function that adds a product to the repository
    //returns true if the product was added, false otherwise
    bool add_product(std::string size, std::string colour, int quantity, float price, std::string photograph);

    //function that reads the products from a file and adds them to the repository
    void read_from_file(std::string file_name);

    //function that writes the products from the repository to a file
    void write_to_file(std::string file_name);

    //function that writes the shopping basket to a file
    void write_to_file_shopping_basket(std::string file_name);

    //function that deletes a product from the repository
    //returns true if the product was deleted, false otherwise
    bool delete_product(std::string size, std::string colour, float price, std::string photograph);

    //function that updates a product from the repository
    //returns true if the product was updated, false otherwise
    bool update_product(Coat coat, Coat new_coat);

    //function that returns the size of the shopping basket
    int get_size();

    //function that returns the shopping basket
    std::vector<Coat> *get_shopping_basket();

    //function that allows the user to add a product to the shopping basket
    //returns true if the product was added, false otherwise
    bool add_to_shopping_basket(Coat coat);

    //function that gets the total price of the shopping basket
    float get_total_price();

    //function that returns all the coats from the repository
    std::vector<Coat> *get_all_products();

    //function that returns the products of a given size and if the size is empty all trench coats will be considered
    std::vector<Coat> *get_products_of_size(std::string size);

    //gets a coat from the repository
    Coat get_coat(int index);

    //sets the type of the file
    void set_type(std::string type);

    //stores in CSV
    void store_CSV();

    //stores in HTML
    void store_HTML();

    void adminUndo();
    void adminRedo();

    //gets the type
    std::string get_type();

    //the destructor
    ~Services();
};