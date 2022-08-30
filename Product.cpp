// ¹Ì¿Ï¼º
#include "Product.h"


Product::Product(int id, int classif, string name, int stock, int price)
    :prodID(id), prodClassif(classif), prodName(name), prodStock(stock), prodPrice(price)
{
}

int Product::getProdID() const
{
    return prodID;
}

void Product::setProdID(int& id)
{
    prodID = id;
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