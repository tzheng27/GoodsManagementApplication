

#include<iostream>
#include<fstream>
#include"Perishable.h"

namespace aid {
	Perishable::Perishable() : Good('P') {
		expirydate = Date();
	}

	std::fstream& Perishable::store(std::fstream& file, bool newLine) const {
		Good::store(file, false);
		file << ',';
		expirydate.write(file);
		

		if (newLine)
			file << std::endl;
		return file;
	}

	std::fstream& Perishable::load(std::fstream& file) {
		Good::load(file);
		expirydate.read(file);
		file.get();

		return file;
	}

	
	std::ostream& Perishable::write(std::ostream& os, bool linear) const {
		Good::write(os, linear);
		if (expirydate.ifEmpty() && !expirydate.bad()) {
			if (linear) 
				expirydate.write(os);
			else {
				os << std::endl;
				os << " Expiry date: ";
				expirydate.write(os);
			}
		}
		return os;
	}
	std::istream& Perishable::read(std::istream& is) {
		*this = Perishable();
		this->Good::read(is);

		if (!is.fail()) {
			Date tempdate;
			std::cout << " Expiry date (YYYY/MM/DD): ";
			tempdate.read(is);
			if (tempdate.bad()) {
				if (tempdate.errCode() == CIN_FAILED)
					this->message("Invalid Date Entry");
				else if (tempdate.errCode() == YEAR_ERROR)
					this->message("Invalid Year in Date Entry");
				else if (tempdate.errCode() == MON_ERROR)
					this->message("Invalid Month in Date Entry");
				else if (tempdate.errCode() == DAY_ERROR)
					this->message("Invalid Day in Date Entry");
				else 
					this->message("Invalid Expiry in Date Entry");

				is.std::istream::setstate(std::ios::failbit);
			}
			else {
				expirydate = tempdate;
			}
		}
		return is;
	}
	const Date& Perishable::expiry() const {
		return expirydate;
	}
}
