

#ifndef AMA_ERR_H
#define AMA_ERR_H

#include<iostream>

namespace aid {

	class Error {
		char* errorMsg;

	public:
		Error();
		explicit Error(const char*);
		Error(const Error&) = delete;
		Error& operator=(const Error&) = delete;
		virtual ~Error();
		void clear();
		bool isClear() const;
		void message(const char*);
		const char* message() const;
	};

	std::ostream& operator<<(std::ostream&, const Error&);

}

#endif
