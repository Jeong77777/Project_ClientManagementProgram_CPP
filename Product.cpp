#include "Product.h"
#include <iostream>
#include <iomanip>


Product::Product(int id, int classif, string name, int stock, int price)
    :prodID(id), prodClassif(classif), prodName(name), prodStock(stock), prodPrice(price)
{
}

int Product::getProdID() const
{
    return prodID;
}

string Product::getProdName() const
{
    return prodName;
}

void Product::setProdName(string& name)
{
    prodName = name;
}

int Product::getProdPrice() const
{
    return prodPrice;
}

void Product::setProdPrice(int& price)
{
    prodPrice = price;
}

int Product::getProdClassif() const
{
    return prodClassif;
}

void Product::setProdClassif(int& classif)
{
    prodClassif = classif;
}

int Product::getProdStock() const
{
    return prodStock;
}

void Product::setProdStock(int& stock)
{
    prodStock = stock;
}

void Product::ShowProdInfo() const
{
    cout << setw(8) << left << prodID;
    if (prodClassif == 1) {
        cout << setw(10) << left << "치과장비";
    }
    else if (prodClassif == 2) {
        cout << setw(10) << left << "치과재료";
    }
    else if(prodClassif == 3){
        cout << setw(10) << left << "위생용품";
    }
    cout << setw(20) << left << prodName;
    cout << setw(10) << left << prodStock;
    cout << setw(10) << left << prodPrice << endl;
}