// Final Project Milestone 3
// Date   Nov 19, 2018
// Author Tian Zheng 155394174

#ifndef AMA_GOOD_H
#define AMA_GOOD_H

#include <iostream>
#include <fstream>
#include "iGood.h"
#include "Error.h"

namespace aid {
	const int max_sku_length = 7;
	const int max_unit_length = 10;
	const int max_name_length = 75;
	const double taxRate = 0.13;

	class Good: public iGood {
		char type;
		char stockKeepingUnit[max_sku_length + 1];
		char goodUnit[max_unit_length + 1];
		char* goodName;
		int goodOnhand;
		int goodNeeded;
		double priceBeTax;
		bool taxable;
		Error errorState;

	public:
		Good(const char type = 'N');
		Good(const char* sku, const char* gn, const char* gu, int h = 0, bool ts = true, double p = 0.00, int n = 0);
		Good(const Good&);
		Good& operator=(const Good&);
		~Good();

		std::fstream& store(std::fstream& file, bool newLine = true) const;
		std::fstream& load(std::fstream&);
		std::ostream& write(std::ostream&, bool) const;
		std::istream& read(std::istream&);
		bool operator==(const char*) const;
		double total_cost() const;
		void quantity(int);
		bool isEmpty() const;
		int qtyNeeded() const;
		int quantity() const;
		bool operator>(const char*) const;
		bool operator>(const iGood&) const;
		int operator+=(int);

	protected:
		void name(const char*);
		const char* name() const;
		const char* sku() const;
		const char* unit() const;
		bool taxed() const;
		double itemPrice() const;
		double itemCost() const;
		void message(const char*);
		bool isClear() const;
	};

	std::ostream& operator<<(std::ostream&, const iGood&);
	std::istream& operator>>(std::istream&, iGood&);
	double operator+=(double&, const iGood&);

}
#endif