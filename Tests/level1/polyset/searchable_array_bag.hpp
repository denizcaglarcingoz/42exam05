#pragma once

#include "searchable_bag.hpp"
#include "array_bag.hpp"


class searchable_array_bag : public searchable_bag, public array_bag
{
	public:
			searchable_array_bag(){}
			searchable_array_bag(const array_bag& bag_) : bag(bag_) {}
			~searchable_array_bag(){}
			searchable_array_bag& operator=(const searchable_array_bag& other)
			{
				if (this == &other)
					return *this;
				
				this->data = other.data;
				this->size = other.size;
				return *this;
			}

			bool has(int item) const
			{
				for(int i = 0; i < size; i++)
				{
					if (item == data[i])
						return true;
				}
				return false;
			}

};