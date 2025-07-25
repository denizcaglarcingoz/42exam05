#pragma once

#include "searchable_bag.hpp"
#include "tree_bag.hpp"


class searchable_tree_bag : public searchable_bag, public tree_bag
{
	public:
			searchable_tree_bag(){}
			searchable_tree_bag(const tree_bag& bag_) : bag(bag_) {}
			~searchable_tree_bag(){}
			searchable_tree_bag& operator=(const searchable_tree_bag& other)
			{
				if (this == &other)
					return *this;
				this->tree = other.tree;			
				return *this;
			}

			bool has(int item) const
			{
				node* curr = tree;

				while(curr)
				{
					if (item == curr->value)
						return true;
					else if (item > curr->value)
						curr = curr->r;
					else
						curr = curr->l;
				}
				return false;
			}

};