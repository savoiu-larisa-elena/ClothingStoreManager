#pragma once

#include <assert.h>
#include "services.h"
#include "domain.h"
#include "validator.h"

void testAll();

void test_add_product();

void test_delete_product();

void test_update_product();

void test_get_size();

void test_get_shopping_basket();

void test_add_to_shopping_basket();

void test_get_total_price();

void test_get_products_of_size();

void test_get_products_of_size_empty();

void test_get_coat();

void test_read_from_file();

void test_write_to_file();
