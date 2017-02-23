#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstring>
#include "AmaProduct.h"

using namespace std;

namespace sict{
	AmaProduct::AmaProduct(const char ft){
		fileTag_ = ft;
	}

	const char* AmaProduct::unit() const{
		return unit_;
	}

	void AmaProduct::unit(const char* un){
		strncpy(unit_, un, 11);
		unit_[10] = '\0';
	}

	/*Four Pure Virtual Functions of the Class Streamable*/
	std::fstream& AmaProduct::store(std::fstream& file, bool addNewLine) const{
		file << fileTag_ << "," << sku() << "," << name() << "," << price() << ","
			<< taxed() << "," << quantity() << "," << unit_ << "," << qtyNeeded();
		if (addNewLine){
			file << endl;
		}
		return file;
	}

	std::fstream& AmaProduct::load(std::fstream& file){
		double tempd;
		int tempi;
		char tempc[2000] = "";

		file.getline(tempc, 1999, ',');

		sku(tempc);

		file.getline(tempc, 1999, ',');
		name(tempc);

		file >> tempd;
		file.ignore();
		price(tempd);

		file >> tempi;
		file.ignore();
		taxed(bool(tempi));

		file >> tempi;
		file.ignore();
		quantity(tempi);

		file.getline(tempc, 1999, ',');
		unit(tempc);

		file >> tempi;
		file.ignore();

		qtyNeeded(tempi);

		return file;
	}

	std::ostream& AmaProduct::write(std::ostream& os, bool linear) const{
		if (!err_.isClear()){
			os << err_;
		}
		else if (!isEmpty()){
			char nameTemp[75];
			if (linear){
				strncpy(nameTemp, name(), 20);
				nameTemp[20] = '\0';

				os << left << setw(7) << sku() << "|";
				os << left << setw(20) << nameTemp << "|";
				os << fixed << right << setw(7) << setprecision(2) << cost() << "|";

				os << right << setw(4) << quantity() << "|";
				os << left << setw(10) << unit() << "|";
				os << right << setw(4) << qtyNeeded() << "|";
			
			}else{
				
				strncpy(nameTemp, name(), 74);
				nameTemp[74] = '\0';
				os << "Sku: " << sku() << endl;
				os << "Name: " << nameTemp << endl;
				os << "Price: " << fixed << setprecision(2) << price() << endl;
				if (taxed()){
					os << "Price after tax: " << fixed << setprecision(2) << cost() << endl;
				}
				else{
					os << "Price after tax: N/A" << endl;
				}
				os << "Quantity On Hand: " << quantity() << " " << unit() << endl;
				os << "Quantity Needed: " << qtyNeeded();

			}
		}
		return os;
	}

	std::istream& AmaProduct::read(std::istream& istr){
		if (!istr.fail())
		{
			char tempsku[MAX_SKU_LEN + 1];
			char tempname[75];
			char tempunit[11];
			char temptax;
			double tempprice;
			int tempqty;
			int tempqtyneeded;

			if (!istr.fail()) err_.clear();
			cout << "Sku: ";
			istr.getline(tempsku, MAX_SKU_LEN, '\n');
			cout << "Name: ";
			istr.getline(tempname, 75, '\n');
			cout << "Unit: ";
			istr.getline(tempunit, 11, '\n');
			cout << "Taxed? (y/n): ";
			istr.get(temptax);//istream object to return a single char or set it to the argument

			if (temptax == 'y' || temptax == 'Y' || temptax == 'n' || temptax == 'N'){

				istr.ignore(2000, '\n');
				cout << "Price: ";
				istr >> tempprice;
				if (!istr.fail()){
					err_.clear();
					cout << "Quantity On hand: ";
					istr >> tempqty;

					if (!istr.fail()){
						err_.clear();
						cout << "Quantity Needed: ";
						istr >> tempqtyneeded;

						if (istr.fail()){
							err_.message("Invalid Quantity Needed Entry");
						}
					}
					else{
						err_.message("Invalid Quantity Entry");
					}
				}
				else{
					err_.message("Invalid Price Entry");
				}if (!istr.fail()){
					err_.clear();
					sku(tempsku);
					name(tempname);
					unit(tempunit);
					taxed(temptax == 'y' || temptax == 'Y');
					price(tempprice);
					quantity(tempqty);
					qtyNeeded(tempqtyneeded);
				}
			}
			else{
				istr.setstate(ios::failbit);
				err_.message("Only (Y)es or (N)o are acceptable");
			}

		}

		return istr;
	}

	
	/*Four Pure Virtual Functions of the Class Streamable*/
}