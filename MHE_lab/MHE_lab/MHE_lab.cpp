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
#include <list>

using namespace std;

/*class solutionv2 {
public:
	class path {
	public:
		bool directconnection;
		int value;
	};
	int size;
	std::vector<int> locations;
	std::vector<std::vector<int>>flows;
	std::vector<std::vector<path>>distances;
	solutionv2(int size) {
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
};*/

/*void creategraph(solutionv2 object, int seed) {
	srand(seed);
	for (int i = 0; i < object.size; i++) {
		object.distances[i][i].value = 0;
		object.distances[i][i].directconnection = true;
		int firstconnect = rand() % i;
		object.distances[i][firstconnect].value = rand() % 10 + 1;
		object.distances[i][firstconnect].directconnection = true;
		for (int j = 0; j < i; j++) {
			if (j != firstconnect) {
				if (rand() % i == 0) {
					object.distances[i][j].value = rand() % 10 + 1;
					object.distances[i][j].directconnection = true;
				}
				else {

				}
			}
		}

	}
}*/


// -------------------


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


//------------------


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

void generate_solution(solution &x, int seed) {
	srand(seed);
	for (int i = 0; i < x.size; i++) {
		x.locations[i] = i;
		for (int j = 0; j <= i; j++) {
			if (i == j) {
				x.flows[j][i] = 0;
			}
			else {
				x.flows[j][i] = rand() % 4;
				x.distances[j][i] = rand() % 90 + 10;
				x.flows[i][j] = x.flows[j][i];
				x.distances[i][j] = x.distances[j][i];
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

// ----- lab 5 -----

// returns x solutions close to original solution

void swap_s(solution &object, int a, int b) {
	object.locations[a] += object.locations[b];
	object.locations[b] = object.locations[a] - object.locations[b];
	object.locations[a] -= object.locations[b];
}

list<solution> nearby_list(solution object) {

	list<solution> nearbysolutions;

	for (int i = 0; i < object.size; i++) {
		for (int j = i + 1; j < object.size; j++) {
			swap_s(object, i, j);
			nearbysolutions.push_front(object);
			swap_s(object, i, j);
		}
	}
	return nearbysolutions;
}



solution climb_a(solution object, int repeats) {
	solution best_solution = object;
	int best = evaluate(object);
	int current;
	for (int i = 0; i < repeats; i++) {
		list<solution> nearbysolutions = nearby_list(object);
		for (int j = 0; j < nearbysolutions.size(); i++) {
			current = evaluate(nearbysolutions.back());
			if (best > current) {
				best = current;
				best_solution = nearbysolutions.back();
			}
			nearbysolutions.pop_back();
		}
	}
	return best_solution;
}

solution tabu(solution object) {
	solution bestCandidate = object;
	list<solution> tabuList;
	for (int i = 0; i < 100; i++) {
		list<solution> sNeighborhood = nearby_list(object);
		for (i = 0; i < sNeighborhood.size(); i++) {
			if (/*!tabulist contains neighboor && */ evaluate(bestCandidate))
		}
	}
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
		generate_solution(object, time(NULL));
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
	if (input._Equal("climb_a")) {
		cout << "Repeat this many times: ";
		int i;
		cin >> i;
		object = climb_a(object, i);
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