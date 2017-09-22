#ifndef BIN_TREE_
#define BIN_TREE_

#pragma once
#include <iostream>

class binary_tree
{
	struct node
	{
		int data_;
		node* right_;
		node* left_;

		node() = default;

		explicit node(int data)
			: data_(data),
			right_(nullptr),
			left_(nullptr)
		{
		}
	};

	unsigned long long comparison_count_;
	node* root_;

	static node* destroy_tree(node* tree);
	static void print_in_order(node* tree);
	static void print_pre_order(node* tree);

public:

	binary_tree() : comparison_count_(0), root_(nullptr)
	{
	}
	~binary_tree()
	{
		root_ = destroy_tree(root_);
	}

	void reset_comparison_count();
	unsigned long long get_comparison_count() const;

	void insert(int key);
	void search(int key);
	void print() const
	{
		print_pre_order(root_);
		std::cout << std::endl;
	}
};

#endif
