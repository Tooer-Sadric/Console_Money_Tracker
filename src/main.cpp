/**
 * @author  Sadric Koh
 * @date    27 July 2026
 * @brief   The main runner for the program
 * @par     compile line: g++ -std=c++20 src/main.cpp src/helper.cpp -Iincludes -o build/main
 */

#include "user.hpp"
#include "helper.hpp"
#include <iostream>
#include <iomanip>
#include <numeric>
#include <limits>
#include <fstream>
#include <vector>

#define new_line "\n";

int main(){
    std::string const sep{"====================================="};

    std::cout << sep << new_line;
    std::cout << std::setw(13) << ' ' << "User Input" << std::setw(13) << ' ' << new_line;
    std::cout << sep << new_line;
    //user input
    std::cout << "input your username here: ";
    std::string name{};
    std::getline(std::cin,name);
    std::cout << new_line;
    //set new user
    User newUser{name};

    std::string const fileName = "../data/" + newUser.GetName() + ".txt";
    
    FileCheck(fileName);
    
    idx = findNextIdx(fileName);
    //open close the file

    std::cout << "Username " << newUser.GetName() << " confirmed." << new_line;

    std::cout << new_line;

    std::vector<Data> dataVal;
    char again = 'y';
    std::string month;
    std::string year;
    std::cout << "Please enter the current month: ";
    std::getline(std::cin,month);
    
    std::cout << "Please enter the current year: ";
    std::getline(std::cin,year);

    std::cout << "you have inputted " << month << " " << year << new_line;

    do{
        std::cout << "What item are you logging today?: ";
        std::string item;
        std::getline(std::cin,item);
        
        std::cout << "How much was the item?: ";
        double price;
        std::string tmpPrice;
        std::getline(std::cin,tmpPrice);
        price = std::stod(tmpPrice);

        std::cout << "How many did you buy?: ";
        int quantity;
        std::string tmpQual;
        std::getline(std::cin,tmpQual);
        quantity = std::stoi(tmpQual);

        std::cout << "You have inputted " << quantity << " " << item << " with the price of $" << price << new_line;

        Data tmp{item,price,quantity};
        dataVal.emplace_back(tmp);

        std::cout << "Would you like to log another item? (y/n): ";
        std::string response;
        std::getline(std::cin, response);

        again = response.empty() ? 'n' : std::tolower(response[0]);

    }while(again == 'y');
    
    //write after collating all the data
    FileWrite(sep.size(),fileName,month,year, sep,dataVal);

    //exit prog
    std::cout << "\nPress Enter to exit...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}