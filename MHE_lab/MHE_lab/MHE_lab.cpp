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

	for (int i = 0; i < object.size-1; i++) {
			swap_s(object, i, i+1);
			nearbysolutions.push_front(object);
			swap_s(object, i, i+1);
	}
	return nearbysolutions;
}


// lab 5 climb algoryth
solution climb_a(solution object, int repeats) {
	solution best_solution = object;
	int best = evaluate(object);
	int current;
	for (int i = 0; i < repeats; i++) {
		list<solution> nearbysolutions = nearby_list(object);
		for (solution &x : nearbysolutions){//int j = 0; j < nearbysolutions.size(); j++) {
			current = evaluate(x);
			if (best > current) {
				best = current;
				best_solution = x;
			}
		}
	}
	return best_solution;
}
//-----lab 6 tabu algorytm-----
bool tabucontains(solution object, list<solution> container) {
	bool contains = false;
	for (solution &x : container) {
		if (x.locations == object.locations) {
			contains = true;
			break;
		}
	}
	return contains;
}

solution tabu(solution object) {
	solution sBest = object;
	int sBestEv = evaluate(sBest);
	solution bestCandidate = object;
	int bestCandidateEv = evaluate(bestCandidate);
	list<solution> tabuList;
	tabuList.push_back(object);
	for (int i = 0; i < object.size * 10; i++) {
		list<solution> sNeighborhood = nearby_list(object);
		
		for (solution &x : sNeighborhood) {
			int xev = evaluate(x);
			if (!tabucontains(x, tabuList) &&  xev < bestCandidateEv) {
				bestCandidate = x;
				bestCandidateEv = xev;
			}
				
		}
		if (bestCandidateEv < sBestEv) {
			sBest = bestCandidate;
			sBestEv = bestCandidateEv;
		}
			
		tabuList.push_back(bestCandidate);
		if (tabuList.size() > 10)
			tabuList.pop_front();
	}
	return sBest;
}
//-----lab 7 eksperyment-----
class experimentData {
public:
	double bruteTime;
	double bruteScore;
	double climbTime;
	double climbScore;
	double tabuTime;
	double tabuScore;
	int size;

	experimentData() {
		this->bruteScore = 0;
		this->bruteTime = 0;
		this->climbScore = 0;
		this->climbTime = 0;
		this->tabuScore = 0;
		this->tabuTime = 0;
		this->size = 0;
	}
};

experimentData experimentPart(string file) {
	solution object(1);
	solution temp(1);
	load_solution_fromfile(object, file);
	experimentData data;
	data.size = object.size;

	auto start = std::chrono::high_resolution_clock::now();
	temp = brute_force(object);
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;
	data.bruteTime = diff.count();
	data.bruteScore = evaluate(temp);

	start = std::chrono::high_resolution_clock::now();
	temp = climb_a(object, 10);
	end = std::chrono::high_resolution_clock::now();
	diff = end - start;
	data.climbTime = diff.count();
	data.climbScore = evaluate(temp);

	start = std::chrono::high_resolution_clock::now();
	temp = tabu(object);
	end = std::chrono::high_resolution_clock::now();
	diff = end - start;
	data.tabuTime = diff.count();
	data.tabuScore = evaluate(temp);
	
	return data;
}

experimentData eksperymentBigPart(string file) { 
	experimentData data[1];
	int repeats = 1;
	experimentData averagedata;
	
	for (int i = 0; i < repeats; i++) {
		data[i] = experimentPart(file);
	}
	averagedata.size = data[0].size;
	for (int i = 0; i < repeats; i++) {
		averagedata.bruteScore += data[i].bruteScore;
		averagedata.bruteTime = data[i].bruteTime;
		averagedata.climbScore = data[i].climbScore;
		averagedata.climbTime = data[i].climbTime;
		averagedata.tabuScore = data[i].tabuScore;
		averagedata.tabuTime = data[i].tabuTime;
	}
	/*averagedata.bruteScore = averagedata.bruteScore/3;
	averagedata.bruteTime = averagedata.bruteTime / 3;
	averagedata.climbScore = averagedata.climbScore / 3;
	averagedata.climbTime = averagedata.climbTime / 3;
	averagedata.tabuScore = averagedata.tabuScore / 3;
	averagedata.tabuTime = averagedata.tabuTime / 3;*/
	return averagedata;
}

ostream& operator<<(std::ostream& os, experimentData const& x) {
	os << "Size: " << x.size << endl;
	os << "Brute Score: " << x.bruteScore << " | ";
	os << "Brute Time: " << x.bruteTime << endl;
	os << "Climb Score: " << x.climbScore << " | ";
	os << "Climb Time: " << x.climbTime << endl;
	os << "Tabu Score: " << x.tabuScore << " | ";
	os << "Tabu Time: " << x.tabuTime << endl;

	return os;
}

void saveData(experimentData data, string file) {
	//save the data to file
	ofstream ofile_obj;
	ofile_obj.open(file, ios::app | ios::out);
	ofile_obj << data;
	ofile_obj.close();
}

void eksperyment() {
	saveData(eksperymentBigPart("VI.txt"), "Vdata.txt");
	saveData(eksperymentBigPart("IV.txt"), "Vdata.txt");
	saveData(eksperymentBigPart("V.txt"), "Vdata.txt");
}
//-----funkcja interfejsu uzytkownika-----
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
	
	if (input._Equal("print")) {
		cout << object;
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
	if (input._Equal("climb")) {
		cout << "Repeat this many times: ";
		int i;
		cin >> i;
		cout << "Count time?(y/n): ";
		cin >> input;
		auto start = std::chrono::high_resolution_clock::now();
		object = climb_a(object, i);
		if (input._Equal("y")) {
			auto end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> diff = end - start;
			std::cout << "Done in: " << diff.count() << " s" << endl;
		}
	}
	if (input._Equal("tabu")) {
		cout << "Count time?(y/n): ";
		cin >> input;
		auto start = std::chrono::high_resolution_clock::now();
		object = tabu(object);
		if (input._Equal("y")) {
			auto end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> diff = end - start;
			std::cout << "Done in: " << diff.count() << " s" << endl;
		}
	}
	if (input._Equal("exp")) {
		eksperyment();
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