#include "bigint.hpp"


bigint::bigint()
{
	number = "0";
}

bigint::bigint(unsigned int num)
{
	if (num  == 0 )
	{
		number = "0";
		return ;
	}
	else
	{
		number.clear();
		while(num > 0)
		{
			number.push_back(char((num % 10) + '0'));
			num = num / 10;
		}
		std::reverse(number.begin(), number.end());
	}
}

bigint::bigint(std::string num)
{
	number = num;
}

bigint::bigint(const bigint& copy)
{
	number = copy.number;
}

bigint& bigint::operator=(const bigint& other)
{
	if(*this == other)
		return *this;
		
	number = other.number;
	return *this;
}



//getter
const std::string	bigint::getNum() const
{
	return number;
}

// addition
bigint	bigint::operator+(const bigint& other)const
{
	std::string stra = this->number;
	std::string strb = other.number;


	int alen = stra.size() - 1;
	int blen = strb.size() - 1;

	std::string sum;
	sum.reserve(alen > blen ? alen + 1 : blen + 1);

	int carry = 0;
	while (alen >= 0 || blen >= 0 || carry)
	{
		int a = alen >= 0 ? stra[alen] - '0' : 0;
		int b = blen >= 0 ? strb[blen] - '0' : 0;
		
		int s = a + b + carry;

		sum.push_back((s % 10) + '0');

		carry = s / 10;

		alen--;
		blen--;
	}

	std::reverse(sum.begin(), sum.end());

	bigint summation(sum);
	return summation;
}

bigint	bigint::operator+=(const bigint& other)
{
	*this = *this + other;
	return *this;
}

bigint	bigint::operator++(void)
{
	*this = *this + bigint(1);
	return *this;
}

bigint	bigint::operator++(int)
{
	bigint temp(*this);
	*this = *this + bigint(1);
	return temp;
}




// comparision
bool	bigint::operator>(const bigint& other) const
{
	if (this->number.size() > other.number.size())
			return true;
	if (this->number.size() == other.number.size())
			return (this->number == other.number);

	return false;
}

bool	bigint::operator<(const bigint& other) const
{
	return (other > *this);
}


bool	bigint::operator>=(const bigint& other) const
{
	if (this->number.size() > other.number.size())
			return true;
	if (this->number.size() == other.number.size())
			return (this->number >= other.number);

	return false;
}

bool	bigint::operator<=(const bigint& other) const
{
	return (other >= *this);
}

		
bool	bigint::operator==(const bigint& other) const
{
	return (this->number == other.number);
}

bool	bigint::operator!=(const bigint& other) const
{
	return (this->number != other.number);
}



		// shifter
bigint	bigint::operator<<(unsigned int shift)
{
	bigint temp(*this);
	while (shift)
	{
		temp.number.push_back('0');
		shift--;
	}

	return temp;
}

bigint	bigint::operator>>(unsigned int shift)
{
	if (shift >= this->number.size())
		return (bigint("0"));

	bigint temp(*this);
	while(shift)
	{
		temp.number.pop_back();
		shift--;
	}
	return temp;
}

		
bigint	bigint::operator<<=(unsigned int shift)
{
	*this = *this << shift;
	return *this;
}

bigint	bigint::operator>>=(unsigned int shift)
{
	*this = *this >> shift;
	return *this;
}

std::ostream&	operator<<(std::ostream& os, bigint toPrint)
{
	os << toPrint.getNum();
	return os;
}