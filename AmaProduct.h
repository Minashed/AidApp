#ifndef SICT_AMAPRODUCT_H_
#define SICT_AMAPRODUCT_H_

#include "Product.h"
#include "ErrorMessage.h"
#include "Streamable.h"

namespace sict
{
	class AmaProduct : public Product
    {
    private:
		char fileTag_;
		char unit_[11];
    protected:
		ErrorMessage err_;
	

    public:
		AmaProduct(const char = 'N');
		const char* unit() const;
		void unit(const char*);

		/*Four Pure Virtual Functions of the Class Streamable*/
		virtual std::fstream& store(std::fstream& file, bool addNewLine = true) const;
		virtual std::fstream& load(std::fstream& file);
		virtual std::ostream& write(std::ostream& os, bool linear) const;
		virtual std::istream& read(std::istream& istr);
		/*Four Pure Virtual Functions of the Class Streamable*/
	};
}

#endif


