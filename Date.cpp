#include <iomanip>
#include <iostream>
#include "Date.h"
#include "general.h"
using namespace std;


namespace sict
{
	//Member functions
    int Date::value()const
    {
        return year_ * 372 + mon_ * 31 + day_;
    }
    
    int Date::mdays()const
    {
        int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
        int mon = mon_ >= 1 && mon_ <= 12 ? mon_ : 13;
        mon--;
        return days[mon] + int((mon == 1)*((year_ % 4 == 0) && (year_ % 100 != 0)) || (year_ % 400 == 0));
    }

	void Date::errCode(int errorCode){
		readErrorCode_ = errorCode;
	}
	//Getter functions
	int Date::errCode()const{
		return readErrorCode_;
	}

	bool Date::bad()const{
		if (readErrorCode_ != NO_ERROR){
			return true;
		}else{
			return false;
		}
	}

	//Constructors
	Date::Date(){
		year_ = 0;
		mon_ = 0;
		day_ = 0;
		readErrorCode_ = NO_ERROR;
	}

	Date::Date(int y, int m, int d){
		year_ = y;
		mon_ = m;
		day_ = d;
		readErrorCode_ = NO_ERROR;
	}

	//Overloading Operators
	bool Date::operator==(const Date& D)const{
		return value() == D.value();
	}

	bool Date::operator!=(const Date& D)const{
		return value() != D.value();
	}

	bool Date::operator<(const Date& D)const{
		return value() < D.value();
	}

	bool Date::operator>(const Date& D)const{
		return value() > D.value();
	}

	bool Date::operator<=(const Date& D)const{
		return value() <= D.value();
	}

	bool Date::operator>=(const Date& D)const{
		return value() >= D.value();
	}

	std::istream& Date::read(std::istream& istr){
	
		istr >> year_; 
		istr.ignore(); 
		istr >> mon_; 
		istr.ignore(); 
		istr >> day_;

		if (istr.fail()){
			readErrorCode_ = CIN_FAILED;
		}else{
			if (year_ >= MIN_YEAR && year_ <= MAX_YEAR){
				if (mon_ >= 1 && mon_ <= 12){
					if (mdays() && day_ >= 1 && day_ <= 31){
					}else{
						readErrorCode_ = DAY_ERROR;
					}
				}else{
					readErrorCode_ = MON_ERROR;
				}
			}else{
				readErrorCode_ = YEAR_ERROR;
			}
		}
	
		return istr;
	}

	std::ostream& Date::write(std::ostream& ostr)const{
		
		ostr << setw(1) << setfill('0') << right << year_ << "/"
			 << setw(2) << setfill('0') << mon_ << "/"
			 << setw(2) << setfill('0') << day_ << setfill(' ');

		return ostr;
	}

	std::istream& operator>>(std::istream& istr, Date& d){
		d.read(istr);

		return istr;
	}
	std::ostream& operator<<(std::ostream& ostr, const Date& d){
		d.write(ostr);

		return ostr;

	}
	
}
