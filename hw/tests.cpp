#include "tests.h"

Services* services = new Services(new Repository(new std::vector<Coat>, Validator()), new std::vector<Coat>);

void testAll() {
    test_add_product();
    test_delete_product();
    test_update_product();
    test_get_size();
    test_add_to_shopping_basket();
    test_get_shopping_basket();
    test_get_total_price();
    test_get_products_of_size();
    test_get_products_of_size_empty();
    test_get_coat();
    test_read_from_file();
    test_write_to_file();
}

void test_add_product(){
    //add a product
    std::string size = "M";
    std::string colour = "black";
    int quantity = 10;
    float price = 30;
    std::string photograph = "http::photo1";
    assert(services->add_product(size, colour, quantity, price, photograph) == true);
    //add another product
    std::string size1 = "S";
    std::string colour1 = "red";
    int quantity1 = 5;
    float price1 = 20;
    std::string photograph1 = "http::photo2";
    assert(services->add_product(size1, colour1, quantity1, price1, photograph1) == true);
    //add a product that already exists
    assert(services->add_product(size1, colour1, quantity1, price1, photograph1) == false);
}

void test_delete_product(){
    //delete a product
    Coat coat = services->get_coat(0);
    coat.set_quantity(0);
    services->update_product(services->get_coat(0), coat);
    assert(services->delete_product("M", "black", 30, "http::photo1") == true);
    //delete a product that does not exist
    assert(services->delete_product("M", "black", 30, "http::photo1") == false);
}

void test_update_product(){
    //update a product
    Coat new_coat = services->get_coat(0);
    new_coat.set_quantity(10);
    services->update_product(services->get_coat(0), new_coat);
    assert(services->get_coat(0).get_quantity() == 10);
    //update a product that does not exist
    Coat coat1 = services->get_coat(0);
    coat1.set_quantity(5);
    assert(services->update_product(coat1, coat1) == false);
}

void test_get_size(){
    assert(services->get_size() == 1);
}

void test_add_to_shopping_basket(){
    //add a product to the shopping basket
    services->add_to_shopping_basket(services->get_coat(0));
    assert(services->get_shopping_basket()->size() == 1);
}

void test_get_shopping_basket(){
    //get the shopping basket
    assert(services->get_shopping_basket()->size() == 1);
}


void test_get_total_price(){
    //get the total price
    assert(services->get_total_price() == 20);
}

void test_get_products_of_size(){
    //get the products of a given size
    assert(services->get_products_of_size("S")->size() == 1);
}

void test_get_products_of_size_empty(){
    //get the products of an empty size
    assert(services->get_products_of_size(" ")->size() == 1);
}

void test_get_coat(){
    //get a coat
    assert(services->get_coat(0).get_size() == "S");
}

void test_read_from_file(){
    //read from file
    std::string file = "C:\\Users\\lari\\Desktop\\oop-a6-7-916-savoiu-larisa\\testfile";
    services->read_from_file(file);
    assert(services->get_size() == 1);
}

void test_write_to_file(){
    //write to file
    services->write_to_file("C:\\Users\\lari\\Desktop\\oop-a6-7-916-savoiu-larisa\\testfile");
    services->read_from_file("C:\\Users\\lari\\Desktop\\oop-a6-7-916-savoiu-larisa\\testfile");
    assert(services->get_size() == 1);
}
