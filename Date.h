#ifndef SICT_DATE_H__
#define SICT_DATE_H__
#include <iostream>

//Error options
#define NO_ERROR 0
#define CIN_FAILED 1
#define YEAR_ERROR 2
#define MON_ERROR 3
#define DAY_ERROR 4

namespace sict{
    class Date{
    private:
		int year_;
		int mon_;
		int day_;
		int readErrorCode_;

        int value()const;
		void errCode(int errorCode);

    public:
		//Constructors
		Date();
		Date(int y, int m, int d);
        
		//Operator Overloading
		bool operator==(const Date& D)const;
		bool operator!=(const Date& D)const;
		bool operator<(const Date& D)const;
		bool operator>(const Date& D)const;
		bool operator<=(const Date& D)const;
		bool operator>=(const Date& D)const;
		
		//Public member functions
		int mdays()const;

		//Getter functions
		int errCode()const;
		bool bad()const;

		//IO Member Functions
		std::istream& read(std::istream& istr);
		std::ostream& write(std::ostream& ostr)const;
	};

	std::istream& operator>>(std::istream&, Date&);
	std::ostream& operator<<(std::ostream&, const Date&);

}
#endif