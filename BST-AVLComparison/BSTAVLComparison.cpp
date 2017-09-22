#include "stdafx.h"
#include "binary_tree.h"
#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <chrono>
#include <iomanip>
#include "avl_tree.h"

using namespace std;

chrono::high_resolution_clock::time_point init_build;
chrono::high_resolution_clock::time_point end_build;
chrono::high_resolution_clock::time_point init_search;
chrono::high_resolution_clock::time_point end_search;
unsigned long long build_comparisons;
unsigned long long search_comparisons;

pair<int*, int> get_data(string file)
{
	ifstream contents_file(file);
	string file_name = file.substr(file.find("\\") + 1);
	int size = stoi((file_name.substr(0, file_name.find_last_of("."))).erase(0, 1));

	int* data_array = new int[size];
	int i = 0;
	while (contents_file >> data_array[i++]);

	contents_file.close();
	return { data_array, size };
}

int* get_search_data(int size)
{
	const string file = "Busca\\b" + std::to_string(size) + ".txt";
	ifstream search_contents_file(file);

	int* search_data_array = new int[size];
	int i = 0;
	while (search_contents_file >> search_data_array[i++]);

	search_contents_file.close();
	return search_data_array;
}

template<typename Type> void tree_operations(Type* tree, int* data, int size)
{
	/*
	* 1. Tree builder/insertion
	*/
	tree->reset_comparison_count();

	init_build = chrono::high_resolution_clock::now();

	for (int i = 0; i < size; i++)
	{
		tree->insert(data[i]);
	}

	//tree->print();

	end_build = chrono::high_resolution_clock::now();

	build_comparisons = tree->get_comparison_count();

	/*
	* 2. Tree search using pre-loaded data
	*/
	int* search_data = get_search_data(size);

	tree->reset_comparison_count();

	init_search = chrono::high_resolution_clock::now();

	for (int i = 0; i < size; i++)
	{
		tree->search(99);
	}

	end_search = chrono::high_resolution_clock::now();

	search_comparisons = tree->get_comparison_count() + 1;
}

void save_info(string file, string tree_type)
{
	ofstream info("DATA_INFO.txt", ios::app);

	file = file.substr(file.find("\\") + 1);

	info << fixed;
	info << tree_type << "\t";
	info << file.front() << "\t";
	info << setw(5) << stoi((file.substr(0, file.find_last_of("."))).erase(0, 1)) << "\t\t";
	info << setw(5) << chrono::duration_cast<chrono::duration<double>>(end_build - init_build).count() << "\t";
	info << setw(10) << chrono::duration_cast<chrono::duration<double>>(end_search - init_search).count() << "\t";
	info << setw(10) << build_comparisons << "\t\t";
	info << setw(10) << search_comparisons << endl;

	info.close();
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "Arguments must be: [file_name] [bst | avl]" << endl;
		return 1;
	}

	pair<int*, int> data = get_data(argv[1]);

	if (!strcmp(argv[2], "bst"))
	{
		binary_tree* bin = new binary_tree();
		tree_operations(bin, data.first, data.second);
	}
	else if (!strcmp(argv[2], "avl"))
	{
		avl_tree* avl = new avl_tree();
		tree_operations(avl, data.first, data.second);
	}

	save_info(argv[1], argv[2]);

	return 0;
}
