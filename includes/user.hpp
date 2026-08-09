/**
 * @author  Sadric Koh
 * @date    27 July 2026
 * @brief   A file to hold the class of user and to keep track of things
 */

#ifndef USER
#define USER

#include <string>
#include <algorithm>
#include <utility>
#include <exception>
#include <iostream>

#pragma once
class User{
    private:
        std::string userName;
    public:
        User() 
            : userName{}
        {}
        //target ctor
        User(std::string const& name)
            : userName{name}
        {}

        User(User const& other)
            : userName{other.userName}
        {}

        User(User&& other)
            : userName{other.userName}
        {}

        User& operator=(User&& other){
            userName = other.userName;
            return *this;
        }

        User& operator=(User& other){
            std::swap(userName,other.userName);
            return *this;
        }

        std::string GetName() const noexcept{
            return userName;
        }

        ~User(){
            //empty by default
        }
 };

static short idx{};

struct Data{
    short d_idx;
    std::string item;
    double price;
    int quantity;
    //ctors and stuff
    Data()
        : d_idx{},item{},price{},quantity{}
    {}
    Data(std::string _item, double _price, int _quantity)
      try  : item{_item}, price{_price}, quantity{_quantity}
    {
        d_idx = idx;
        idx++;
    }catch(std::exception const& e){
        std::cout << "Error initializing data: " << e.what() << std::endl;
    }
    
};

 #endif