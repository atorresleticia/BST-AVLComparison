#include "stdafx.h"
#include "binary_tree.h"
#include <iostream>

void binary_tree::reset_comparison_count()
{
	comparison_count_ = 0;
}

unsigned long long binary_tree::get_comparison_count() const
{
	return comparison_count_;
}

void binary_tree::insert(int key)
{
	if (root_ == nullptr)
	{
		root_ = new node(key);
		return;
	}

	node* it = root_;

	while (true)
	{
		if (key < it->data_)
		{
			comparison_count_++;
			if (it->left_ != nullptr)
			{
				it = it->left_;
				continue;
			}
			it->left_ = new node(key);
			break;
		}

		if (key > it->data_)
		{
			comparison_count_++;
			if (it->right_ != nullptr)
			{
				it = it->right_;
				continue;
			}

			it->right_ = new node(key);
			break;
		}
	}
}

void binary_tree::search(int key)
{
	node* it = root_;

	while (it != nullptr && it->data_ != key)
	{
		if (key < it->data_)
		{
			it = it->left_;
			comparison_count_++;
		}
		else if (key > it->data_)
		{
			it = it->right_;
			comparison_count_++;
		}
	}
}

binary_tree::node* binary_tree::destroy_tree(node* tree)
{
	if (tree != nullptr)
	{
		destroy_tree(tree->left_);
		destroy_tree(tree->right_);
		delete tree;
	}
	return nullptr;
}

void binary_tree::print_in_order(node* tree)
{
	if (tree != nullptr)
	{
		print_in_order(tree->left_);
		std::cout << tree->data_ << " ";
		print_in_order(tree->right_);
	}
}

void binary_tree::print_pre_order(node* tree)
{
	if (tree != nullptr)
	{
		std::cout << tree->data_ << " ";
		print_pre_order(tree->left_);
		print_pre_order(tree->right_);
	}
}
