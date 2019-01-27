// Final Project Milestone 1
//
// Version 1.0
// Date   Oct 22, 2018
// Author Tian Zheng
// Description
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////
#include<iostream>
#include <cstring>
#include "Date.h"



// number of days in month mon and year year
//
namespace aid {
	int Date::mdays(int mon, int year)const {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int month = mon >= 1 && mon <= 12 ? mon : 13;
		month--;
		return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}

	void Date::errCode(int errorCode) { errState = errorCode; }

	Date::Date() {
		year = 0;
		month = 0;
		day = 0;
		comparator = 0;
		this->errCode(NO_ERROR);
	}

	Date::Date(int y, int m, int d) { this->set(y, m, d); }

	bool Date::ifEmpty() const { return comparator != 0; }

	bool Date::operator== (const Date& rhs) const {
		bool comparison = this->ifEmpty() && rhs.ifEmpty();
		if (comparison) {
			comparison = comparator == rhs.comparator;
			return comparison;
		}
		else return comparison;
	}

	void Date::set(int rhy, int rhm, int rhd) {
		int max_day = mdays(rhm, rhy);
		bool valid = rhy >= min_year && rhy <= max_year;

		if (valid) {
			valid = rhm >= min_month && rhm <= max_month;

			if (valid) {
				valid = rhd >= min_day && rhd <= max_day;

				if (valid) {
					comparator = rhy * 372 + rhm * 31 + rhd;
					valid = comparator >= min_date;

					if (valid) {
						year = rhy;
						month = rhm;
						day = rhd;
						this->errCode(NO_ERROR);
					}
					else {
						*this = Date();
						this->errCode(PAST_ERROR);
					}
				}
				else {
					*this = Date();
					this->errCode(DAY_ERROR);
				}
			}
			else {
				*this = Date();
				this->errCode(MON_ERROR);
			}
		}
		else {
			*this = Date();
			this->errCode(YEAR_ERROR);
		}
	}

	bool Date::operator!= (const Date& rhs) const {
		bool comparison = this->ifEmpty() && rhs.ifEmpty();
		if (comparison) {
			comparison = comparator != rhs.comparator;
			return comparison;
		}
		else return comparison;
	}

	bool Date::operator<(const Date& rhs) const {
		bool comparison = this->ifEmpty() && rhs.ifEmpty();
		if (comparison) {
			comparison = comparator < rhs.comparator;
			return comparison;
		}
		else return comparison;
	}

	bool Date::operator>(const Date& rhs) const {
		bool comparison = this->ifEmpty() && rhs.ifEmpty();
		if (comparison) {
			comparison = comparator > rhs.comparator;
			return comparison;
		}
		else return comparison;
	}

	bool Date::operator<=(const Date& rhs) const {
		bool comparison = this->ifEmpty() && rhs.ifEmpty();
		if (comparison) {
			comparison = comparator <= rhs.comparator;
			return comparison;
		}
		else return comparison;
	}

	bool Date::operator>= (const Date& rhs) const {
		bool comparison = this->ifEmpty() && rhs.ifEmpty();
		if (comparison) {
			comparison = comparator >= rhs.comparator;
			return comparison;
		}
		else return comparison;
	}

	int Date::errCode() const { return errState; }

	bool Date::bad() const { return errState != NO_ERROR; }


	std::istream& Date::read(std::istream& istr) {
		int tempYear, tempMon, tempDay;
		Date temp;
		char symbol;
		istr >> tempYear >> symbol >> tempMon >> symbol >> tempDay;
		if (istr.fail()) {
			this->errCode(CIN_FAILED);
		}
		else {
			temp.set(tempYear, tempMon, tempDay);
			if (temp.errCode() == NO_ERROR)
				*this = temp;
			else
				this->errCode(temp.errState);
		}
		return istr;
	}

	std::ostream& Date::write(std::ostream& ostr) const {
		ostr.fill('0');
		ostr << year << "/";
		ostr.width(2);
		ostr << month << "/";
		ostr.width(2);
		ostr << day;
		ostr.fill(' ');

		return ostr;
	}


	std::ostream& operator<< (std::ostream& os, const Date& date_a) {
		date_a.write(os);
		return os;
	}

	std::istream& operator>> (std::istream& is, Date& date_a) {
		date_a.read(is);
		return is;
	}

}