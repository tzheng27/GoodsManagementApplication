
#ifndef AMA_DATE_H
#define AMA_DATE_H

#include<iostream>

#define NO_ERROR 0
#define CIN_FAILED 1
#define DAY_ERROR 2
#define MON_ERROR 3
#define YEAR_ERROR 4
#define PAST_ERROR 5

namespace aid {

	const int min_year = 2018;
	const int max_year = 2038;
	const int min_date = 751098;
	const int min_month = 1;
	const int max_month = 12;
	const int min_day = 1;
	const int max_position = 10;

	class Date {
		int year;
		int month;
		int day;
		int comparator;
		int errState;

		int mdays(int, int)const;
		void errCode(int);

	public:
		Date();
		Date(int, int, int);
		bool ifEmpty() const;
		void set(int, int, int);
		bool operator== (const Date&) const;
		bool operator!= (const Date&) const;
		bool operator< (const Date&) const;
		bool operator> (const Date&) const;
		bool operator<= (const Date&) const;
		bool operator>= (const Date&) const;
		int errCode() const;
		bool bad() const;
		std::istream& read(std::istream&);
		std::ostream& write(std::ostream&) const;
		/*int getyear() const;
		int getmonth() const;
		int getdate() const;*/
	};

	std::ostream& operator<<(std::ostream&, const Date&);
	std::istream& operator>>(std::istream&, Date&);

}
#endif
