#ifndef AVL_TREE_
#define AVL_TREE_

#pragma once
#include <iostream>

class avl_tree
{
	struct node
	{
		int data_;
		int height_;
		node* right_;
		node* left_;

		node() = default;

		explicit node(int data)
			: data_(data),
			height_(1),
			right_(nullptr),
			left_(nullptr)
		{
		}
	};

	unsigned long long comparison_count_;
	node* root_;

	node* insert(node* t, int key);
	node* destroy_tree(node* tree);
	static void print_in_order(node* tree);
	static void print_pre_order(node* tree);

public:

	avl_tree() : comparison_count_(0), root_(nullptr)
	{
	}
	~avl_tree()
	{
		root_ = destroy_tree(root_);
	}

	static int get_height(node* a)
	{
		return a == nullptr ? 0 : a->height_;
	}

	static int get_balance(node* a)
	{
		return a == nullptr ? -1 : (get_height(a->left_) - get_height(a->right_));
	}

	void reset_comparison_count();
	unsigned long long get_comparison_count() const;
	void insert(int key);
	node* rotate_left(node* a) const;
	node* rotate_right(node* a) const;
	node* rotate_left_right(node* b) const;
	node* rotate_right_left(node* b) const;
	void search(int key);

	void print()
	{
		print_pre_order(root_);
		std::cout << std::endl;
	}
};

#endif