// Final Project Milestone 3
// Date   Nov 19, 2018
// Author Tian Zheng 155394174
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include "Good.h"
#include "Error.h"

namespace aid {
	//protected member functions
	void Good::name(const char* gn) {
		goodName = nullptr;
		if (gn != nullptr && gn[0] != '\0') {
			goodName = new char[strlen(gn) + 1];
			int position;
			for (int i = 0; gn[i] != '\0'; i++) {
				goodName[i] = gn[i];
				position = i;
			}
			goodName[position + 1] = '\0';
		}
	}//function name(const char*)

	const char* Good::name() const {
		return goodName;
	}//function name()

	const char* Good::sku() const {
		return stockKeepingUnit;
	}//function sku()

	const char* Good::unit() const {
		return goodUnit;
	}//function unit()

	bool Good::taxed() const {
		return taxable;
	}//function taxed()

	double Good::itemPrice() const {
		return priceBeTax;
	}//function itemPrice()

	double Good::itemCost() const {
		return priceBeTax * (1 + taxRate);
	}//function itemCost()

	void Good::message(const char* e) {
		errorState.message(e);
	}//function message(const char*)

	bool Good::isClear() const {
		return errorState.isClear();
	}//function isClear()

	 //public member functions
	Good::Good(const char t) {
		type = t;
		strcpy(stockKeepingUnit, "\0");
		strcpy(goodUnit, "\0");
		goodName = nullptr;
		goodOnhand = 0;
		goodNeeded = 0;
		priceBeTax = 0.00;
		taxable = true;
		errorState.message(nullptr);
	}//0-1-constructor

	Good::Good(const char* sku, const char* gn, const char* gu, int h, bool ts, double p, int n) {
		*this = Good();

		if (sku == nullptr || strcmp(sku, "\0") == 0)
			strcpy(stockKeepingUnit, "\0");
		else {
			strncpy(stockKeepingUnit, sku, max_sku_length);
			stockKeepingUnit[max_sku_length] = '\0';
		}

		this->name(gn);

		if (gu == nullptr || strcmp(gu, "\0") == 0)
			strcpy(goodUnit, "\0");
		else {
			strncpy(goodUnit, gu, max_unit_length);
			goodUnit[max_unit_length] = '\0';
		}

		if (h > 0)
			goodOnhand = h;
		else
			goodOnhand = 0;

		taxable = ts;

		if (p > 0)
			priceBeTax = p;
		else
			priceBeTax = 0.00;

		if (n > 0)
			goodNeeded = n;
		else
			goodNeeded = 0;

	}//7-constructor

	Good::Good(const Good& src) {
		goodName = nullptr;
		*this = src;
	}//copy constructor

	Good& Good::operator=(const Good& src) {
		if (this != &src) {
			type = src.type;
			strcpy(stockKeepingUnit, src.stockKeepingUnit);
			strcpy(goodUnit, src.goodUnit);
			goodOnhand = src.goodOnhand;
			goodNeeded = src.goodNeeded;
			priceBeTax = src.priceBeTax;
			taxable = src.taxable;
			errorState.message(src.errorState.message());
			if (src.goodName != nullptr) {
				int length = strlen(src.goodName) + 1;
				goodName = new char[length];
				for (int i = 0; i < length - 1; i++)
					goodName[i] = src.goodName[i];
			}
			else {
				goodName = nullptr;
			}
		}
		return *this;
	}//assignment operator

	Good::~Good() {
		delete[] goodName;
	}//destructor


	std::fstream& Good::store(std::fstream& file, bool newLine) const {
		file << this->type << ',' << this->sku() << ',' << this->name() << ',' << this->unit() << ','
			<< this->taxable << ',' << this->itemPrice() << ',' << this->quantity() << ',' << this->qtyNeeded();
		if (newLine)
			file << std::endl;

		return file;
	}//store(write) to a file

	std::fstream& Good::load(std::fstream& file) {
		char temp_name[max_name_length + 1];
		char ctempTax;

		file.get(this->stockKeepingUnit, max_sku_length + 1, ',');
		this->stockKeepingUnit[max_sku_length] = '\0';
		file.ignore();
		file.get(temp_name, max_name_length + 1, ',');
		temp_name[max_name_length] = '\0';
		file.ignore();
		file.get(this->goodUnit, max_unit_length + 1, ',');
		this->goodUnit[max_unit_length] = '\0';
		file.ignore();
		file.get(ctempTax);
		file.ignore();
		file >> this->priceBeTax;
		file.ignore();
		file >> this->goodOnhand;
		file.ignore();
		file >> this->goodNeeded;
		file.ignore();

		if (ctempTax == '1')
			this->taxable = true;
		else
			this->taxable = false;

		this->name(temp_name);

		return file;
	}//load(read) from a file

	std::ostream& Good::write(std::ostream& os, bool linear) const {
		if (this->errorState.isClear()) {
			
			if (linear) {

				os.setf(std::ios::left);
				os.width(max_sku_length);
				os << this->sku() << "|";

				
				if (!this->isEmpty()) {
					os.width(20);
					os << this->name() << "|";
				}
				else {
					os.width(20);
					os << "" << "|";
				}
					

				os.unsetf(std::ios::left);
				os.setf(std::ios::right);

				os.width(7);
				os.setf(std::ios::fixed);
				os.precision(2);
				if (this->taxable)
					os << this->itemCost() << "|";
				else
					os << this->itemPrice() << "|";


				os.width(4);
				os << this->quantity() << "|";

				os.unsetf(std::ios::right);
				os.setf(std::ios::left);
				os.width(10);
				os << this->unit() << "|";

				os.unsetf(std::ios::left);
				os.setf(std::ios::right);
				os.width(4);
				os << this->qtyNeeded() << "|";

				os.unsetf(std::ios::right);

			}
			else {
				os << " Sku: " << this->sku() << std::endl;
				os << " Name (no spaces): " << this->name() << std::endl;
				os << " Price: " << this->itemPrice() << std::endl;
				if (this->taxable)
					os << " Price after tax: " << this->itemCost() << std::endl;
				else
					os << " Price after tax:  N/A" << std::endl;
				os << " Quantity on Hand: " << this->quantity() << " " << this->unit() << std::endl;
				os << " Quantity needed: " << this->qtyNeeded();
			}
		}
		else {
			os << errorState;
		}
		return os;
	}//ostream

	std::istream& Good::read(std::istream& is) {
		char tempSku[max_sku_length + 1];
		char temp_name[max_name_length + 1];
		char tempUnit[max_unit_length + 1];
		char tempTax;
		
		int tempOnhand;
		int tempNeeded;
		double tempPrice;
		bool fail = false;

		errorState.clear();

		std::cout << " Sku: ";
		is >> tempSku;
		strncpy(this->stockKeepingUnit, tempSku, max_sku_length);
		this->stockKeepingUnit[max_sku_length] = '\0';

		std::cout << " Name (no spaces): ";
		is >> temp_name;
		this->name(temp_name);

		std::cout << " Unit: ";
		is >> tempUnit;
		strncpy(this->goodUnit, tempUnit, max_unit_length);
		this->goodUnit[max_unit_length] = '\0';

		if (!fail) {
			std::cout << " Taxed? (y/n): ";
			is >> tempTax;
			if (is.std::istream::fail()) {
				this->errorState.message("Only (Y)es or (N)o are acceptable"); 
				is.setstate(std::ios::failbit);
				fail = true;
			}
			else {
				bool invalid = tempTax != 'N' && tempTax != 'Y'&& tempTax != 'n' && tempTax != 'y';
				if (invalid) {
					this->errorState.message("Only (Y)es or (N)o are acceptable");
					is.setstate(std::ios::failbit);
					fail = true;
				}
				else {
					if (tempTax == 'N' || tempTax == 'n')
						this->taxable = false;
					else
						this->taxable = true;
				}
			}
		}
		
		if (!fail) {
			std::cout << " Price: ";
			is >> tempPrice;
			if (is.std::istream::fail() || tempPrice < 0) {
				is.std::istream::setstate(std::ios::failbit);
				
				errorState.message("Invalid Price Entry");
				fail = true;
			}
			else
				this->priceBeTax = tempPrice;
		}
		
		if (!fail) {
			std::cout << " Quantity on hand: ";
			is >> tempOnhand;
			if (is.std::istream::fail() || tempOnhand < 0) {
				is.std::istream::setstate(std::ios::failbit);
				
				errorState.message("Invalid Quantity Entry");
				fail = true;
			}
			else
				this->goodOnhand = tempOnhand;
		}
		
		if (!fail) {
			std::cout << " Quantity needed: ";
			is >> tempNeeded;
			if (is.std::istream::fail() || tempNeeded < 0) {
				is.std::istream::setstate(std::ios::failbit);
				errorState.message("Invalid Quantity Needed Entry");
				fail = true;
			}
			else
				this->goodNeeded = tempNeeded;
		}
		
		if (!fail) {
			is.clear();
			is.ignore(1000, '\n');
		}
		return is;
	}//istream

	bool Good::operator==(const char* test_sku) const {
		return strcmp(stockKeepingUnit, test_sku) == 0;
	}//==

	double Good::total_cost() const {
		double finalPrice = this->itemCost();
		return finalPrice * goodOnhand;
	}//function total_cost

	void Good::quantity(int test_onhand) {
		if (test_onhand > 0)
			goodOnhand = test_onhand;
	}//function reset quantity

	bool Good::isEmpty() const {
		return goodName == nullptr;
	}//function isEmpty

	int Good::qtyNeeded() const {
		return goodNeeded;
	}//function qtyNeeded

	int Good::quantity() const {
		return goodOnhand;
	}//query function quantity

	bool Good::operator>(const char* test_sku) const {
		return strcmp(stockKeepingUnit, test_sku) > 0;
	}//>

	bool Good::operator>(const iGood& test_good) const {
		return strcmp(goodName, test_good.name()) > 0;
	}//<

	int Good::operator+= (int addingValue) {
		if (addingValue > 0)
			goodOnhand += addingValue;
		return goodOnhand;
	}//+=

	std::ostream& operator<<(std::ostream& os, const iGood& good) {
		return good.write(os, true);
	}//<<

	std::istream& operator>>(std::istream& is, iGood& good) {
		return good.read(is);
	}//>>

	double operator+=(double& p, const iGood& g) {
		p += g.total_cost();
		return p;
	}//+=

}//namespace aid