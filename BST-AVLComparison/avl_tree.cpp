#include "stdafx.h"
#include "avl_tree.h"
#include <iostream>
#include <algorithm>

void avl_tree::reset_comparison_count()
{
	comparison_count_ = 0;
}

unsigned long long avl_tree::get_comparison_count() const
{
	return comparison_count_;
}

avl_tree::node* avl_tree::insert(node* t, int key)
{
	if (t == nullptr)
	{
		return new node(key);
	}

	if (key < t->data_)
	{
		comparison_count_++;
		t->left_ = insert(t->left_, key);
	}
	else
	{
		comparison_count_++;
		t->right_ = insert(t->right_, key);
	}

	t->height_ = 1 + std::max(get_height(t->left_), get_height(t->right_));
	const int balance = get_balance(t);

	if (balance == 2)
	{
		if (key < t->left_->data_)
		{
			comparison_count_++;
			t = rotate_right(t);
		}
		else
		{
			comparison_count_++;
			t = rotate_left_right(t);
		}
	}
	else if (balance == -2)
	{
		if (key > t->right_->data_)
		{
			comparison_count_++;
			t = rotate_left(t);
		}
		else
		{
			comparison_count_++;
			t = rotate_right_left(t);
		}
	}
	return t;
}

avl_tree::node* avl_tree::rotate_left(node* b) const
{
	node* a = b->right_;
	b->right_ = a->left_;
	a->left_ = b;

	b->height_ = 1 + std::max(get_height(b->left_), get_height(b->right_));
	a->height_ = 1 + std::max(get_height(a->right_), b->height_);

	return a;
}

avl_tree::node* avl_tree::rotate_right(node* b) const
{
	node* a = b->left_;
	b->left_ = a->right_;
	a->right_ = b;

	b->height_ = 1 + std::max(get_height(b->left_), get_height(b->right_));
	a->height_ = 1 + std::max(get_height(a->left_), b->height_);

	return a;
}

avl_tree::node* avl_tree::rotate_left_right(node* c) const
{
	c->left_ = rotate_left(c->left_);
	return rotate_right(c);
}

avl_tree::node* avl_tree::rotate_right_left(node* c) const
{
	c->right_ = rotate_right(c->right_);
	return rotate_left(c);
}

void avl_tree::search(int key)
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

void avl_tree::insert(int key)
{
	root_ = insert(root_, key);
}

avl_tree::node* avl_tree::destroy_tree(node* tree)
{
	if (tree != nullptr)
	{
		destroy_tree(tree->left_);
		destroy_tree(tree->right_);
		delete tree;
	}
	return nullptr;
}

void avl_tree::print_in_order(node* tree)
{
	if (tree != nullptr)
	{
		print_in_order(tree->left_);
		std::cout << tree->data_ << " ";
		print_in_order(tree->right_);
	}
}

void avl_tree::print_pre_order(node* tree)
{
	if (tree != nullptr)
	{
		std::cout << tree->data_ << " ";
		print_pre_order(tree->left_);
		print_pre_order(tree->right_);
	}
}