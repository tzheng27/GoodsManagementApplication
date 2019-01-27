//Name: Tian Zheng     155 394 174
//ms5

#include <iostream>
#include <fstream>
#include "Good.h"
#include "Date.h"

namespace aid {
	class Perishable : public Good {
		Date expirydate;
	public:
		Perishable();
		std::fstream& store(std::fstream& file, bool newLine = true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& is);
		const Date& expiry() const;
	};
}