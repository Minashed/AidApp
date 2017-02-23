#include <cstring>
#include <new>
#include <iomanip>
#include "AidApp.h"

using namespace std;

namespace sict{
	
	//Done
	AidApp::AidApp(const char* filename){
		strncpy(filename_, filename, 300);
		filename_[255] = '\0';

		for (int i = 0; i < MAX_NO_RECS; i++){
			product_[i] = nullptr;
		}
		
		noOfProducts_ = 0;

		loadRecs();
	}

	//Done
	void AidApp::pause() const{
		std::cout << "Press Enter to continue..." << endl;
		cin.ignore(1000, '\n');
	}

	//Done
	int AidApp::menu(){

		//Two variables to get the menu option. Followed by printing the menu option.
		int option;
		std::cout << "Disaster Aid Supply Management Program" << endl;
		std::cout << "1- List products" << endl;
		std::cout << "2- Display product" << endl;
		std::cout << "3- Add non-perishable product" << endl;
		std::cout << "4- Add perishable product" << endl;
		std::cout << "5- Add to quantity of purchased products" << endl;
		std::cout << "0- Exit program" << endl;
		std::cout << "> ";
		cin >> option;
		cin.ignore(2000, '\n');
		//After getting the option. If its between 0 and 5 it will return that value if not
		//it returns -1;
		if (option < 0 && option > 5){
			option = -1;
		}

		return option;
	}

	void AidApp::loadRecs(){
		//Set read index to 0
		int readIndex = 0;
		char Id;

		//Open the file for reading
		datafile_.open(filename_, ios::in);
		
		//If the file is in fail state it will do the following: clear the fail, close the file, open the file for writing, close the file.
		if (datafile_.fail()){
			datafile_.clear();
			datafile_.close();
			datafile_.open("aidapp.txt", ios::out);
			datafile_.close();
		}else{
			//Until it fails loop, deallocate memory in pointers, read on char P or N from file
			do{
				//Load P or N from datafile_
				datafile_ >> Id;

				//Check and do required outcome
				if (Id == 'P'){
					delete product_[readIndex];

					product_[readIndex] = new AmaPerishable;
				}else if (Id == 'N'){
					//Dynamic creation of AmaProduct class
					delete product_[readIndex];

					product_[readIndex] = new AmaProduct;
				}

				//Skip the comma in the file
				datafile_.get();

				//Load the product from the file (using the load method)
				product_[readIndex]->load(datafile_);

				//Add one to read index
				readIndex++;
				
			} while (!datafile_.fail());
		}
		//Set noOfProducts_ to readIndex.
		noOfProducts_ = readIndex;

		//Close file
		datafile_.close();
	}
	
	void AidApp::saveRecs(){
		//Open file for writing.
		datafile_.open(filename_, ios::out);

		if (!datafile_.fail()){
			//Loops through the product_ array up to noOfProducts_ and stores them in the datafile_
			for (int i = 0; i < noOfProducts_ - 1; i++){
				product_[i]->store(datafile_, true);
			}
		}

		//Close file
		datafile_.close();
	}

	void AidApp::listProducts()const{
		double total = 0;

		//Prints table table top
		std::cout << " Row | SKU    | Product Name       | Cost  | QTY| Unit     |Need| Expiry   " << endl;
		std::cout << "-----|--------|--------------------|-------|----|----------|----|----------" << endl;
		
		//Loops through products_ up to noOfProducts_ and prints out the table

		for (int row = 0; row < noOfProducts_ - 1; row++){
			std::cout << setw(4) << right << row + 1 << " | ";
			
			product_[row]->write(cout, true);

			cout << endl;

			total += *product_[row];

			if ((row+1)%10 == 0){
				pause();
			}
		}
		std::cout << "---------------------------------------------------------------------------" << endl;
		std::cout << "Total cost of support: $" << fixed << setprecision(2) << total << endl;
		cout << endl;
		pause();
	}

	int AidApp::SearchProducts(const char* sku)const{
		int found = -1;
		for (int row = 0; row < noOfProducts_ - 1; row++){
			if (*product_[row] == sku){
				found = row;
				break;
			}
		}
		return found;
	}

	void AidApp::addQty(const char* sku){
		int add;
		int i = SearchProducts(sku);

		if (i == -1){
			cout << endl;
			cout << "Not found!" << endl;
		}
		else{
			cout << endl;
			product_[i]->write(cout, false);
			cout << endl;
			cout << endl;
			cout << "Please enter the number of purchased items: ";
			cin >> add;
			if (cin.fail()){
				cout << "Invalid quantity value!" << endl;
			}else{
				if (add <= (product_[i]->qtyNeeded() - product_[i]->quantity())){
					*product_[i] += add;
					cout << endl;
				}else{
					int x = add + product_[i]->quantity();
					int y = x - product_[i]->qtyNeeded();
					cout << "Too many items; only " << (product_[i]->qtyNeeded() - product_[i]->quantity()) << " is needed,";
					cout << " please return the extra " << y << " items." << endl;
					cout << endl;
					*product_[i] += (product_[i]->qtyNeeded() - product_[i]->quantity());
				}
				saveRecs();
				cout << "Updated!" << endl;
				cout << endl;
			}
		}
	}
		
	void AidApp::addProduct(bool isPerishable){
		
		//Creats product depending on argument
		if (isPerishable){
			product_[noOfProducts_ - 1] = new AmaPerishable;
		}else{
			product_[noOfProducts_ - 1 ] = new AmaProduct;
		}

		//Gets the values from the user
		cin.clear();
		product_[noOfProducts_ - 1]->read(cin);
		cout << endl;
		cout << "Product added";
		cout << endl;
		if (!cin.fail()){
			noOfProducts_++;
			saveRecs();
		}else{
			product_[noOfProducts_ - 1]->write(cout, true);
			delete product_[noOfProducts_ - 1];
			product_[noOfProducts_ - 1] = nullptr;
		}
	}

	int AidApp::run(){
		int option;
		

		do{
			char sku[MAX_SKU_LEN];
			int found;
			option = menu();
			cout << endl;

			if (option == 1){
				listProducts();

			}
			else if (option == 2){
				cout << "Please enter the SKU: ";
				cin >> sku;
				cout << endl;
				found = SearchProducts(sku);

				if (found != -1){
					product_[found]->write(std::cout, false);
					cout << endl;
					cout << endl;
				}
				else if (found == -1){
					cout << "Not found!" << endl;
				}
				cin.get();
				pause();
			}
			else if (option == 3){
				addProduct(false);
				loadRecs();
				cin.clear();
			}
			else if (option == 4){
				
				addProduct(true);
				loadRecs();
				cin.clear();
				cout << endl;
			}
			else if (option == 5){
				cout << "Please enter the SKU: ";
				cin >> sku;
				

				addQty(sku);
			}
			else if (option <= -1 || option >= 6){
				cout << "===Invalid Selection, try again.===" << endl;
				pause();
			}
		} while (option != 0);

		cout << "Goodbye!!";
		cout << endl;
		return 0;
	}
}


/* Menu output
 Disaster Aid Supply Management Program
 1- List products
 2- Display product
 3- Add non-perishable product
 4- Add perishable product
 5- Add to quantity of purchased products
 0- Exit program
 >
 
 
 List title
 
 Row | SKU    | Product Name       | Cost  | QTY| Unit     |Need| Expiry
 ----|--------|--------------------|-------|----|----------|----|----------
 
 Liste footter
 ---------------------------------------------------------------------------
 Total cost of support: $1187.53
 
 */