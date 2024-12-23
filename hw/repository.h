#pragma once
#include "domain.h"
#include "validator.h"
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "exceptions.h"

class Repository {
private:
	std::vector <Coat>* coats_vector;
	Validator validator;
    std::string type;
public:
	//the constructor
	Repository(std::vector <Coat>* coats_vector, Validator validator);

	//the function that adds a coat to the repository
	//returns true if the coat was added, false otherwise
	bool add_coat(Coat coat);

	//the function that deletes a coat from the repository
	//returns true if the coat was deleted, false otherwise
	bool delete_coat(Coat coat);

	//the function that updates a coat from the repository
	//returns true if the coat was updated, false otherwise
	bool update_coat(Coat coat, Coat new_coat);

	//the function that returns the size of the repository
    unsigned long long get_size();

	//the function that gets all the coats from the repository
	std::vector <Coat>* get_coats_vector();

	//the function that searches for a coat in the repository
	int search_coat(Coat coat);

	//the function that returns the coat from the repository
	Coat get_coat(int index);

    //read from file
    void read_from_file(std::string file_name);

    //write to file
    void write_to_file(std::string file_name);

    //set the type of the file
    void set_type(std::string type);

    //gets the type
    std::string get_type() {return this->type;};

    //stores html
    void store_HTML(std::vector<Coat> *coats_vector);

    //stores csv
    void store_CSV(std::vector<Coat> *coats_vector);

	//the destructor
	~Repository();
};