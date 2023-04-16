#pragma once

#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

void read_menu_from_file(string food_list[][3]);
void choose_place(string &choice);
void in_a_restaurant(int &table_number);
bool to_delivery(string &address, string &delivery_time);
void cancel_an_order(vector<pair<string, int>> &order_list, int &total_price);
void add_order(vector<pair<string, int>> &order_list, string food_list[][3], int &total_price);
void print_food_list(string food_list[][3], const int &size);
void summary(string &name, string &address, string &delivery_time, int &total_price, string &choice, vector<pair<string, int>> &order_list, int &table_number);
void start_menu(int &answer);
void restaurant_data();
int return_size_of_menu();
string give_name();
bool validate();
string return_postfix(string &time_in_mins);
bool confirm_opening_time(string &delivery_time);
bool confirm_time(string &delivery_time, int &time_open, int &time_closed);
bool minute_check(int &time_open, int &time_closed , int &delivery_minute, int &delivery_hour);