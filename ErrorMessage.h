#ifndef SICT_ERRORMESSAGE_H__
#define SICT_ERRORMESSAGE_H__
#include <iostream>

namespace sict{
	class ErrorMessage{
		private:
			char* message_;

		public:
			//Constructors
			ErrorMessage();
			ErrorMessage(const char*);
			ErrorMessage(const ErrorMessage&) = delete;

			//Operator Overload
			ErrorMessage& operator=(const ErrorMessage&) = delete; 
			ErrorMessage& operator=(const char* errorMessage);

			//Deconstructor
			~ErrorMessage();

			//Public member functions
			void clear();
			bool isClear()const;
			void message(const char* value);
			const char* message()const;

	};
	//Helper Function
	std::ostream& operator<<(std::ostream&, const ErrorMessage&);
}

#endif

