#include <cstring>
#include "Product.h"
#include "general.h"

using namespace std;

namespace sict{
	//Constructors
	//1-Arg
	Product::Product(){
		sku_[0] = '\0';
		name_= nullptr;
		price_ = 0;
		quantity_ = 0;
		qtyNeeded_ = 0;
	}

	//5-Arg
	Product::Product(const char* s, const char* n, double p, int qn, bool t){
		sku(s);
		name(n);
		quantity_ = 0;
		price(p);
		qtyNeeded(qn);
		taxed(t);
	}

	/*RULE OF THREE*/
	Product::Product(const Product& src){
		quantity(src.quantity_);
		price(src.price_);
		qtyNeeded(src.qtyNeeded_);
		sku(src.sku_);
		name(src.name_);
		taxed(src.taxed_);
	}
	Product& Product::operator=(const Product& src){
		if (this != &src){
			quantity(src.quantity_);
			price(src.price_);
			qtyNeeded(src.qtyNeeded_);
			sku(src.sku_);
			taxed(src.taxed_);

			if (src.name_ != nullptr){
				name_ = new char[strlen(src.name_) + 1];
				std::strcpy(name_, src.name_);
			}else{
				name_ = nullptr;
			}
		}
		return *this;
	}
	Product::~Product(){
		delete[] name_;
	}
	/*RULE OF THREE*/


	//Setters
	void Product::sku(const char* s){
		strncpy(sku_, s, MAX_SKU_LEN);
		sku_[MAX_SKU_LEN] = '\0';
	}
	void Product::price(double p){
		price_ = p;
	}
	void Product::name(const char* n){
		if (n != nullptr){
			name_ = new char[strlen(n) + 1];
			std::strcpy(name_, n);
		}else{
			name_ = nullptr;
		}
	}
	void Product::taxed(bool t){
		taxed_ = t;
	}
	void Product::quantity(int q){
		quantity_ = q;
	}
	void Product::qtyNeeded(int qn){
		qtyNeeded_ = qn;
	}

	//Getters
	const char* Product::sku()const{
		return sku_;
	}
	double Product::price()const{
		return price_;
	}
	const char* Product::name()const{
		return name_;
	}
	bool Product::taxed()const{
		return taxed_;
	}
	int Product::quantity()const{
		return quantity_;
	}
	int Product::qtyNeeded()const{
		return qtyNeeded_;
	}

	bool Product::isEmpty()const{
		return name_ == nullptr && price_ == 0 && quantity_ == 0 && sku_[0] == '\0' && qtyNeeded_ == 0;
	}
	double Product::cost()const{
		double temp = price_;
		return taxed() ? temp = temp * (TAX + 1) : price_;
	}

	//Memeber Operator Overloading
	bool Product::operator==(const char* sku)const{
		return std::strcmp(sku, sku_) == 0;
	}

	int Product::operator+=(int quantity){
		return quantity_ = quantity_ + quantity;
	}
	int Product::operator-=(int quantity){
		return quantity_ = quantity_ - quantity;
	}

	//Non-Member Operator Overloading
	double operator+=(double& a, const Product& Psrc){
		return a += (Psrc.cost() * Psrc.quantity());
	}

	//Non-Member IO Operator Overload
	std::ostream& operator<<(std::ostream& os, const Product& src){
		src.write(os, true);
		return os;
	}
	
	std::istream& operator>>(std::istream& is, Product& src){
		src.read(is);
		return is;
	}
}