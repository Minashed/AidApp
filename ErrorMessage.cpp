#include "ErrorMessage.h"
#include <cstring>

namespace sict{

	//Constructors
	ErrorMessage::ErrorMessage(){
		message_ = nullptr;
	}

	ErrorMessage::ErrorMessage(const char* errorMessage){
		message_ = nullptr;

		message(errorMessage);
	}


	//Operator Overload
	ErrorMessage& ErrorMessage::operator=(const char* errorMessage){
		clear();
		
		message(errorMessage);

		return *this;
	}

	//Deconstructor
	ErrorMessage::~ErrorMessage(){
		clear();
	}

	//Public member functions
	void ErrorMessage::clear(){
		delete[] message_;
		message_ = nullptr;
	}

	bool ErrorMessage::isClear()const{
		return message_ == nullptr;
	}

	void ErrorMessage::message(const char* value){
		clear();
		
		message_ = new char[strlen(value) + 1];
		
		strcpy(message_, value);
	}

	const char* ErrorMessage::message()const{
		return message_;
	}

	//Helper Function
	std::ostream& operator<<(std::ostream& ostr, const ErrorMessage& em){
		if (em.isClear()){
			ostr << "";
		}else{
			ostr << em.message();
		}
		return ostr;
	}
}