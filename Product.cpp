#include "Product.h"
#include <iostream>
#include <iomanip>


Product::Product(int id, int classif, string name, int stock, int price)
    :prodID(id), prodClassif(classif), prodName(name), prodStock(stock), prodPrice(price)
{
}

int Product::GetProdID() const
{
    return prodID;
}

string Product::GetProdName() const
{
    return prodName;
}

void Product::SetProdName(string& name)
{
    prodName = name;
}

int Product::GetProdPrice() const
{
    return prodPrice;
}

void Product::SetProdPrice(int& price)
{
    prodPrice = price;
}

int Product::GetProdClassif() const
{
    return prodClassif;
}

void Product::SetProdClassif(int& classif)
{
    prodClassif = classif;
}

int Product::GetProdStock() const
{
    return prodStock;
}

void Product::SetProdStock(int& stock)
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