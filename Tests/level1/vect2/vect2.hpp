#pragma once


#include <vector>
#include <iostream>

class vect2
{
	private:
		int x;
		int y;

		
		
	public:
		vect2() : x(0), y(0){}
		vect2(int a, int b) : x(a), y(b){}
		vect2(const vect2& copy)
		{
			x = copy.x;
			y = copy.y; 
		}
		vect2& operator=(const vect2& other)
		{
			if (this == &other)
				return *this;
			this->x = other.x;
			this->y = other.y;
			return *this;
		}

		int&	operator[](int item)
		{
			return (item == 0 ? x : y);
		}

		int	operator[](int item) const
		{
			return (item == 0 ? x : y);
		}


		friend std::ostream& operator<<(std::ostream& os, vect2 toPrint)
		{
			os << "{" << toPrint.x << ", " << toPrint.y << "}"; 
			return os;
		}


		vect2 operator++()
		{
			x++; y++;
			return *this;
		}
		vect2 operator++(int)
		{
			vect2 temp = *this;
			x++; y++;
			return temp;
		}
		
		vect2 operator--()
		{
			x--; y--;
			return *this;
		}
		vect2 operator--(int)
		{
			vect2 temp = *this;
			x--; y--;
			return temp;
		}

		vect2&	operator*=(int num)
		{
			x*=num; y*=num;
			return *this;
		}

		const vect2	operator*(int num) const
		{
			vect2 temp = *this;
			temp.x*=num; temp.y*=num;
			return temp;
		}


		vect2 operator+(const vect2& other) const
		{
			return vect2(x + other.x, y + other.y);
		}

		vect2& operator+=(const vect2& other)
		{
			x +=other.x; y += other.y;
			return *this;
		}
		vect2& operator-=(const vect2& other)
		{
			x -=other.x; y -= other.y;
			return *this;
		}
		vect2 operator-(const vect2& other)
		{
			return vect2(x - other.x, y - other.y);
		}

		vect2& operator-()
		{
			x = -x;
			y = -y;
			return *this;
		}
	
		friend const vect2  operator*(int num, const vect2 v)
		{
			return  vect2(v.x *num, v.y *num);
		}


		bool operator==(const vect2& other) const
		{
			return ((x == other.x && y == other.y) ? true : false);
		}

		bool operator!=(const vect2& other) const
		{
			return ((x == other.x && y == other.y) ? false : true);
		}

};

