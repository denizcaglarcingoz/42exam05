#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>
#include <algorithm>

class bigint
{
	private:
		std::string number;

	public:
		bigint();
		bigint(unsigned int num);
		bigint(std::string num);
		bigint(const bigint& copy);
		bigint& operator=(const bigint& other);


		//getter
		const std::string	getNum()const;

		// addition
		bigint	operator+(const bigint& ohter)const;
		bigint	operator+=(const bigint& ohter);
		bigint	operator++(void);
		bigint	operator++(int);



		// comparision
		bool	operator>(const bigint& ohter) const;
		bool	operator<(const bigint& ohter) const;
		
		bool	operator>=(const bigint& ohter) const;
		bool	operator<=(const bigint& ohter) const;
		
		bool	operator==(const bigint& ohter) const;
		bool	operator!=(const bigint& ohter) const;


		// shifter
		bigint	operator<<(unsigned int shift);
		bigint	operator>>(unsigned int shift);
		
		bigint	operator<<=(unsigned int shift);
		bigint	operator>>=(unsigned int shift);

};

std::ostream&	operator<<(std::ostream& os, bigint toPrint);

#endif