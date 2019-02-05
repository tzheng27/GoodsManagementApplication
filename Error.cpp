

#include <iostream>
#include <cstring>
#include "Error.h"

namespace aid {
	Error::Error() {
		errorMsg = nullptr;
	}

	Error::Error(const char* errorMessage) {
		if (errorMessage == nullptr || errorMessage[0] == '\0')
			errorMsg = nullptr;
		else {
			errorMsg = new char[strlen(errorMessage) + 1];
			int position;
			for (int i = 0; errorMessage[i] != '\0'; i++) {
				errorMsg[i] = errorMessage[i];
				position = i;
			}
			errorMsg[position + 1] = '\0';
		}
	}

	Error::~Error() {
		delete[] errorMsg;
	}

	void Error::clear() {
		delete[] errorMsg;
		errorMsg = nullptr;
	}

	bool Error::isClear() const {
		return errorMsg == nullptr;
	}

	void Error::message(const char* str) {
		delete[] errorMsg;
		if (str == nullptr || str[0] == '\0')
			errorMsg = nullptr;
		else {
			errorMsg = new char[strlen(str) + 1];
			int position;
			for (int i = 0; str[i] != '\0'; i++) {
				errorMsg[i] = str[i];
				position = i;
			}
			errorMsg[position + 1] = '\0';
		}
	}

	const char* Error::message() const {
		return errorMsg;
	}


	std::ostream& operator<<(std::ostream& os, const Error& state) {
		if (!(state.isClear())) {
			os << state.message();
		}
		return os;
	}
}


