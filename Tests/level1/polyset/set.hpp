#pragma once

#include "searchable_bag.hpp"

class set
{

	private:
		searchable_bag& bag_;

	public:
		set(searchable_bag& baggy): bag_(baggy) {}
		~set(){}
	
	void insert (int item)
	{
		if(!bag_.has(item))
			bag_.insert(item);
	}

	void insert (int *arr, int size)
	{
		for (int i = 0; i < size; i++)
		{
			if(!bag_.has(arr[i]))
				bag_.insert(arr[i]);
		}
	}

	void print() const
	{
		bag_.print();
	}

	void clear()
	{
		bag_.clear();
	}

	void has(int item)
	{
		bag_.has(item);
	}

	const searchable_bag& get_bag()const{ return bag_;}
};