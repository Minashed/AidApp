#ifndef SICT_PRODUCT_H_
#define SICT_PRODUCT_H_

#include "Streamable.h"
#include "general.h"

namespace sict{
    class Product: public Streamable
	{
    private:
		//DONE!
		char sku_[MAX_SKU_LEN + 1];
		char* name_;
		double price_;
		bool taxed_;
		int quantity_;
		int qtyNeeded_;
        
    public:
		//Constructors - DONE!
		Product();
		Product(const char*, const char*, double = 0, int = 0, bool = true);
		
		/*RULE OF THREE*/
		Product(const Product&);
		Product& operator=(const Product&);
		virtual ~Product();
		/*RULE OF THREE*/


		//Setters - DONE!
		void sku(const char*);
		void price(double);
		void name(const char*);
		void taxed(bool);
		void quantity(int);
		void qtyNeeded(int);

		//Getters - DONE!
		const char* sku()const;
		double price()const;
		const char* name()const;
		bool taxed()const;
		int quantity()const;
		int qtyNeeded()const;

		bool isEmpty()const;
		double cost()const;

		//Memeber Operator Overloading - DONE!
		bool operator==(const char*)const;
		int operator+=(int);
		int operator-=(int);


	};
	//Non-Member Operator Overloading - DONE!
	double operator+=(double&, const Product&);
    
    //Non-Member IO Operator Overload
	std::ostream& operator<<(std::ostream&, const Product&);
	std::istream& operator>>(std::istream&, Product&);
}

#endif