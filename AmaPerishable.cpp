#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstring>
#include "AmaPerishable.h"

using namespace std;

namespace sict
{
	AmaPerishable::AmaPerishable() : AmaProduct('P'){
		
	}
	const Date& AmaPerishable::expiry() const{
		return expiry_;
	}
	void AmaPerishable::expiry(const Date &value){
		expiry_ = value;
	}


	std::fstream& AmaPerishable::store(std::fstream& file, bool addNewLine) const{
		AmaProduct::store(file, false);
		file << "," << expiry_;
		if (addNewLine){
			file << endl;
		}
		return file;
	}
	
	std::fstream& AmaPerishable::load(std::fstream& file){
		AmaProduct::load(file);
		expiry_.read(file);
		file.ignore();
		return file;
	}
	
	std::ostream& AmaPerishable::write(std::ostream& os, bool linear) const{
		AmaProduct::write(os, linear);
		if (err_.isClear() && !isEmpty()){
			if (linear){
				os << expiry_;
			}else{
				os << endl << "Expiry date: " << expiry_;
				//os << "Expiry Date: " << expiry_;
			}
		}
		return os;

	}
	
	std::istream& AmaPerishable::read(std::istream& istr){
		Date temp;
		AmaProduct::read(istr);
		if (err_.isClear()){
			cout << "Expiry date (YYYY/MM/DD): ";
			cin >> temp;//uses overloaded insertion operator from date class

			if (temp.errCode() != 0){
				switch (temp.errCode()){
				case 1:
				{
						  
						  err_.message("Invalid Date Entry");
				}
				break;
				
				case 2:
				{

						  err_.message("Invalid Year in Date Entry");
				}
				break;
				
				case 3:
				{

						  err_.message("Invalid Month in Date Entry");
				}
				break;
				
				case 4:
				{

						  err_.message("Invalid Day in Date Entry");
				}
				}
				istr.setstate(ios::failbit);//not sure
			}if (!istr.fail()){
				expiry(temp);
			}
		}
		return istr;
	}
}
