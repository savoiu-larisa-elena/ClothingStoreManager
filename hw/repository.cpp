    #include "repository.h"

    Repository::Repository(std::vector<Coat> *coats_vector, Validator validator) {
        this->coats_vector = coats_vector;
        this->validator = validator;
    }

    void Repository::read_from_file(std::string file_name) {
        std::ifstream file(file_name);
        if (!file.is_open()) {
            throw RepositoryError("The file could not be opened!");
        }
        Coat coat;
        std::string line;
        while (std::getline(file, line)) {
            std::vector<std::string> tokens;
            std::stringstream stream(line);
            std::string token;
            while (std::getline(stream, token, '|')) {
                tokens.push_back(token);
                if(tokens.size() < 5){
                    continue;
                }
                break;
            }
            coat.set_size(tokens[0]);
            coat.set_colour(tokens[1]);
            coat.set_quantity(std::stoi(tokens[2])); // std::stoi converts a string to an integer
            coat.set_price(std::stof(tokens[3])); // std::stof converts a string to a float
            coat.set_photograph(tokens[4]);
            this->add_coat(coat);
        }
        file.close();
    }

    bool Repository::add_coat(Coat coat) {
        if (this->validator.validate_coat(coat) && this->search_coat(coat) == -1) {
            this->coats_vector->push_back(coat);
            return true;
        }
        return false;
    }

    bool Repository::delete_coat(Coat coat) {
        if (!validator.validate_coat(coat)) {
            return false;
        }
        int to_delete = this->search_coat(coat);
        if (to_delete == -1) {
            return false;
        } else if (coat.get_quantity() == 0) {
            this->coats_vector->erase(this->coats_vector->begin() + to_delete);
            return true;
        }
        return false;

    }

    bool Repository::update_coat(Coat coat, Coat new_coat) {
        if(!validator.validate_coat(coat) || !validator.validate_coat(new_coat)){
            return false;
        }
        int index = this->search_coat(coat);
        if(index == -1){
            return false;
        }
        this->coats_vector->at(index) = new_coat;
        return true;
    }

    unsigned long long Repository::get_size() {
        return this->coats_vector->size();
    }

    std::vector<Coat> *Repository::get_coats_vector() {
        return this->coats_vector;
    }

    int Repository::search_coat(Coat coat) {
        for (unsigned long long index = 0; index < this->coats_vector->size(); index++) {
            if (this->coats_vector->at(index).get_size() == coat.get_size() &&
                this->coats_vector->at(index).get_colour() == coat.get_colour() &&
                this->coats_vector->at(index).get_price() == coat.get_price() &&
                this->coats_vector->at(index).get_photograph() == coat.get_photograph() &&
                this->coats_vector->at(index).get_quantity() == coat.get_quantity()){
                return index;
            }
        }
        return -1;
    }

    Coat Repository::get_coat(int index) {
        return this->coats_vector->at(index);
    }

    void Repository::write_to_file(std::string file_name) {
        std::ofstream file(file_name);
        if (!file.is_open()) {
            throw RepositoryError("The file could not be opened!");
        }
        for (auto &coat: *this->coats_vector) {
            file << coat.get_size() << "|" << coat.get_colour() << "|" << coat.get_quantity() << "|" << coat.get_price()
                 << "|" << coat.get_photograph() << "\n";
        }
        file.close();
    }

    void Repository::set_type(std::string type) {
        this->type = type;
    }

    void Repository::store_HTML(std::vector<Coat> *sb) {
        std::ofstream file("sb.html");
        if (!file.is_open()) {
            throw RepositoryError("The file could not be opened!");
        }
        file << "<!DOCTYPE html>\n";
        file << "<html>\n";
        file << "<head>\n";
        file << "<title>Shopping Basket</title>\n";
        file << "</head>\n";
        file << "<body>\n";
        file << "<table border=\"1\">\n";
        file << "<tr>\n";
        file << "<td>Size</td>\n";
        file << "<td>Colour</td>\n";
        file << "<td>Quantity</td>\n";
        file << "<td>Price</td>\n";
        file << "<td>Photograph</td>\n";
        file << "</tr>\n";
        for (auto &coat: *sb) {
            file << "<tr>\n";
            file << "<td>" << coat.get_size() << "</td>\n";
            file << "<td>" << coat.get_colour() << "</td>\n";
            file << "<td>" << coat.get_quantity() << "</td>\n";
            file << "<td>" << coat.get_price() << "</td>\n";
            file << "<td><a href=\"" << coat.get_photograph() << "\">Link</a></td>\n";
            file << "</tr>\n";
        }
        file << "</table>\n";
        file << "</body>\n";
        file << "</html>\n";
        file.close();
    }

    void Repository::store_CSV(std::vector<Coat> *sb) {
        std::ofstream file("sb.csv");
        if (!file.is_open()) {
            throw RepositoryError("The file could not be opened!");
        }
        else
        {
            for (auto &coat: *sb) {
                file << coat.get_size() << "," << coat.get_colour() << "," << coat.get_quantity() << "," << coat.get_price()
                     << "," << coat.get_photograph() << "\n";
            }
            file.close();
        }
    }


    Repository::~Repository() = default;