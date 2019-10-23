#include "pch.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <conio.h>
#include <chrono>
#include <string>

using namespace std;

class solution {
public:
	int size;
	std::vector<int> locations;
	std::vector<std::vector<int>>flows;
	std::vector<std::vector<int>>distances;
	solution(int size) {
		this->size = size;
		locations.resize(size);

		flows.resize(size);
		distances.resize(size);

		for (int i = 0; i < size; i++)
		{
			flows[i].resize(size);
			distances[i].resize(size);
		}
	}
	void resize_s(int size) {
		this->size = size;
		locations.resize(size);

		flows.resize(size);
		distances.resize(size);

		for (int i = 0; i < size; i++)
		{
			flows[i].resize(size);
			distances[i].resize(size);
		}
	}
};


int factorial(int n)
{
	if (n > 1)
		return n * factorial(n - 1);
	else
		return 1;
}

int evaluate(solution s) {
	int sum = 0;
	int i;
	for (i = 0; i < s.size - 1; i++) {
		for (int j = i + 1; j < s.size; j++) {
			int factory1 = s.locations[i];
			int factory2 = s.locations[j];
			sum += s.distances[i][j] * s.flows[factory1][factory2];
		}
	}
	return sum;
}

solution next(solution &x) {
	next_permutation(x.locations.begin(), x.locations.end());
	return x;
}

solution brute_force(solution k) {
	int best = evaluate(k);
	int current;
	solution result = k;

	for (int i = 0; i < factorial(k.size); i++) {
		current = evaluate(k);
		if (current < best) {
			result = k;
			best = current;
		}
		next(k);
	}
	return result;
}

void initialize(solution &x, int seed) {
	srand(seed);
	for (int i = 0; i < x.size; i++) {
		x.locations[i] = i;
		for (int j = 0; j < x.size; j++) {
			x.flows[i][j] = rand() % 10 + 0;
			x.distances[i][j] = rand() % 10 + 0;
		}
	}
}

void initializev2(solution &x, int seed, int range) {
	srand(seed);
	for (int i = 0; i < x.size; i++) {
		x.locations[i] = i;
		for (int j = 0; j < x.size; j++) {
			if (i == j) {
				x.flows[j][i] = 0;
			}
			if (i < j) {
				x.flows[j][i] = rand() % 10 + 1;
				x.distances[j][i] = rand() % 10 + 1;
			}
			if (i > j) {
				x.flows[j][i] = x.flows[i][j];
				x.distances[j][i] = x.distances[i][j];
			}
		}
	}
}

ostream& operator<<(std::ostream& os, solution const& x) {
	os << x.size << endl;
	for (int i = 0; i < x.size; i++) {
		for (int j = 0; j < x.size; j++) {
			os << x.distances[i][j] << " ";
		}
		os << endl;
	}
	os << endl;
	for (int i = 0; i < x.size; i++) {
		for (int j = 0; j < x.size; j++) {
			os << x.flows[i][j] << " ";
		}
		os << endl;
	}
	os << endl;
	for (int i = 0; i < x.size; i++) {
		os << x.locations[i] << " ";
	}
	os << endl;
	return os;
}

istream& operator>> (istream& stream, solution& x) {
	stream >> x.size;
	x.resize_s(x.size);
	for (int i = 0; i < x.size; i++) {
		for (int j = 0; j < x.size; j++) {
			stream >> x.distances[i][j];
		}
	}
	for (int i = 0; i < x.size; i++) {
		for (int j = 0; j < x.size; j++) {
			stream >> x.flows[i][j];
		}
	}
	for (int i = 0; i < x.size; i++) {
		stream >> x.locations[i];
	}
	return stream;
}

void save_solution_tofile(solution tosave, string file) {
	ofstream ofile_obj;
	ofile_obj.open(file, ios::trunc | ios::out);
	ofile_obj << tosave;
	ofile_obj.close();
}

void load_solution_fromfile(solution &toload, string file) {
	ifstream ifile_obj;
	ifile_obj.open(file, ios::in);
	ifile_obj >> toload;
	ifile_obj.close();
}

void input_function(string &input, solution &object) {
	if (input._Equal("load")) {
		cout << "Enter file name: ";
		std::cin >> input;
		load_solution_fromfile(object, input);
	}
	if (input._Equal("save")) {
		cout << "Enter file name: ";
		std::cin >> input;
		save_solution_tofile(object, input);
	}
	if (input._Equal("generate")) {
		cout << "Enter size of solution: ";
		std::cin >> input;
		object.resize_s(stoi(input));
		initializev2(object, time(NULL), 10);
	}
	if (input._Equal("evaluate")) {
		cout << evaluate(object) << endl;
	}
	if (input._Equal("brute")) {
		cout << "Count time?(y/n): ";
		cin >> input;
		auto start = std::chrono::high_resolution_clock::now();
		object = brute_force(object);
		if (input._Equal("y")) {
			auto end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> diff = end - start;
			std::cout << "Done in: " << diff.count() << " s" << endl;
		}
	}
	if (input._Equal("print")) {
		cout << object;
	}
	if (input._Equal("brutetime")) {

	}


}

int main()
{
	solution object(1);
	string input;
	while (!input._Equal("q")) {
		cin >> input;
		input_function(input, object);
	}
}