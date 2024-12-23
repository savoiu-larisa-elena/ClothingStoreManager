#include "services.h"

Services::Services(Repository* repository, std::vector<Coat>* shopping_basket) {
    this->repository = repository;
    this->shopping_basket = shopping_basket;
    this->total_price_of_shopping_basket = 0;
}

bool Services::add_product(std::string size, std::string colour, int quantity, float price, std::string photograph) {
    Coat coat = Coat(size, colour, quantity, price, photograph);
    if (this->repository->add_coat(coat)) {
		undo_stack.push_back(new AddAction(coat, this->repository));
		while (!redo_stack.empty()) {
			redo_stack.pop_back();
		}
		return true;
	}
	return false;
}

void Services::read_from_file(std::string file_name) {
    this->repository->read_from_file(file_name);
}

void Services::write_to_file_shopping_basket(std::string file_name) {
    std::ofstream file(file_name);
    for (auto& coat : *this->shopping_basket) {
        file << coat.get_size() << "|" << coat.get_colour() << "|" << coat.get_quantity() << "|" << coat.get_price() << "|" << coat.get_photograph() << "\n";
    }
    file.close();
}

void Services::write_to_file(std::string file_name) {
    this->repository->write_to_file(file_name);
}

bool Services::delete_product(std::string size, std::string colour, float price, std::string photograph) {
    Coat coat = Coat(size, colour, 0, price, photograph);
    if (this->repository->delete_coat(coat)) {
        undo_stack.push_back(new DeleteAction(coat, this->repository));
        while (!redo_stack.empty()) {
			redo_stack.pop_back();
		}
        return true;
    }
    return false;
}

bool Services::update_product(Coat coat, Coat new_coat) {
    if (this->repository->update_coat(coat, new_coat)) {
        undo_stack.push_back(new UpdateAction(coat, new_coat, this->repository));
        while (!redo_stack.empty()) {
			redo_stack.pop_back();
		}
        return true;
    }
    return false;
}

int Services::get_size() {
    return int(this->repository->get_size());
}

std::vector<Coat>* Services::get_shopping_basket() {
    return this->shopping_basket;
}

bool Services::add_to_shopping_basket(Coat coat) {
    this->shopping_basket->push_back(coat);
    this->total_price_of_shopping_basket += coat.get_price();
    return true;
}

float Services::get_total_price() {
    return this->total_price_of_shopping_basket;
}

std::vector<Coat>* Services::get_all_products() {
    return this->repository->get_coats_vector();
}

std::vector<Coat>* Services::get_products_of_size(std::string size) {
    std::vector<Coat>* coats = new std::vector<Coat>;
    for (auto& coat : *this->repository->get_coats_vector()) {
        if (coat.get_size() == size) {
            coats->push_back(coat);
        }
    }
    if (size == " ")
        return this->repository->get_coats_vector();
    return coats;
}

Coat Services::get_coat(int index) {
    return this->repository->get_coat(index);
}

void Services::set_type(std::string type) {
    if (type == "csv")
        this->repository->set_type("csv");
    else
        this->repository->set_type("html");
}

void Services::store_HTML() {
    this->repository->store_HTML(get_shopping_basket());
}

void Services::store_CSV() {
    this->repository->store_CSV(get_shopping_basket());
}

std::string Services::get_type() {
    return this->repository->get_type();
}

void Services::adminUndo() {
    if (undo_stack.empty()) {
		throw std::exception("No more undos!");
	}
	Action* action = undo_stack.back();
	action->execute_undo();
	redo_stack.push_back(action);
	undo_stack.pop_back();
}

void Services::adminRedo() {
    if (redo_stack.empty()) {
        throw std::exception("No more redos!");
    }
    Action* action = redo_stack.back();
    action->execute_redo();
    undo_stack.push_back(action);
    redo_stack.pop_back();
}

Services::~Services() {
    delete this->repository;
    delete this->shopping_basket;
}
