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
#include <random>
#include <numeric>
#include <sstream>

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
	averagedata.bruteScore = averagedata.bruteScore/ repeats;
	averagedata.bruteTime = averagedata.bruteTime / repeats;
	averagedata.climbScore = averagedata.climbScore / repeats;
	averagedata.climbTime = averagedata.climbTime / repeats;
	averagedata.tabuScore = averagedata.tabuScore / repeats;
	averagedata.tabuTime = averagedata.tabuTime / repeats;
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

//----- genetic algorithm -----

class specimen {
public:
	std::vector<int> locations;
	int fitness;
	int size;
	/*specimen(int newsize) {
		locations.resize(newsize);
		this->size = newsize;
	}*/
	void resize(int newsize) {
		locations.resize(newsize);
		this->size = newsize;
	}
};
class Population {
public:
	std::vector<specimen> pop;
	int generation;
	int size;
	int h_fitness;
	int h_fitness_pop;
	Population(int size, int specsize) {
		this->generation = 0;
		this->size = size;
		pop.resize(size);
		for (int i=0;i<size;i++)
			pop[i].resize(specsize);
	}
};
vector<specimen> cross(specimen x, specimen y) {
	vector<specimen> children;
	children.resize(2);
	children[0] = x;
	children[1] = x;

	vector<int> cross;
	cross.resize(x.size);
	cross = y.locations;
	
	for (int g = 0; g < children.size(); g++) {
		for (int i = 0; i < children[g].size / 2; i++) {
			int j = 0;
			bool cond = false;
			while (j < cross.size() && !cond) {
				if (children[g].locations[i] == cross[j]) {
					cross.erase(cross.begin() + j);
					cond = true;
					j--;
				}
				j++;
			}
		}
		cross.shrink_to_fit();
		for (int i = 0; i < cross.size(); i++) {
			children[g].locations[children[g].locations.size() - i-1] = cross[cross.size() - i-1];
		}
	}
	
	return children;
}
vector<specimen> crosstwo(specimen x, specimen y){
	vector<specimen> children;
	children.resize(2);
	children[0] = x;
	children[1] = x;

	vector<int> cross;
	cross.resize(x.size);
	cross = y.locations;
	

	for (int g = 0; g < children.size(); g++) {
		int crosspoint = rand() % children[g].size;
		int crosspointtwo = rand() % (children[g].size -crosspoint) + crosspoint;
		for (int i = 0; i < crosspoint; i++) {
			int j = 0;
			bool cond = false;
			while (j < cross.size() && !cond) {
				if (children[g].locations[i] == cross[j]) {
					cross.erase(cross.begin() + j);
					cond = true;
					j--;
				}
				j++;
			}
		}
		for (int i = crosspoint; i < crosspointtwo; i++) {
			int j = 0;
			bool cond = false;
			while (j < cross.size() && !cond) {
				if (children[g].locations[i] == cross[j]) {
					cross.erase(cross.begin() + j);
					cond = true;
					j--;
				}
				j++;
			}
		}
		cross.shrink_to_fit();
		for (int i = 0; i < cross.size(); i++) {
			children[g].locations[children[g].locations.size() - i - 1] = cross[cross.size() - i - 1];
		}
	}

	return children;
}
int fitness(specimen x, solution starting) {
	starting.locations = x.locations;
	return evaluate(starting);
}
specimen mutate(specimen x) {
	int a = rand() % x.size;
	int b = a;
	while (b == a) {
		b = rand() % x.size;
	}
	int temp = x.locations[a];
	x.locations[a] = x.locations[b];
	x.locations[b] = temp;
	return x;
}

bool evaluate_pop(Population population, int genlimit, int minscore, string type) {
	if (type._Equal("gen")) {
		if (population.generation > genlimit)
			return false;
	}
	else if (type._Equal("score")) {
		if (population.h_fitness < minscore)
			return false;
	}
	else
		return false;

	return true;
}
void set_h_fitness(Population &population, solution sol) {
	for (int i = 0; i < population.size; i++) {
		population.pop[i].fitness = fitness(population.pop[i], sol);
	}
	population.h_fitness = population.pop[0].fitness;
	population.h_fitness_pop = 0;
	for (int i = 0; i < population.size; i++) {
		population.pop[i].fitness = fitness(population.pop[i], sol);
		if (population.pop[i].fitness < population.h_fitness) {
			population.h_fitness = population.pop[i].fitness;
			population.h_fitness_pop = i;
		}
	}
}
void generatepop(Population &population, solution sol) {
	vector<int> genes;
	genes.resize(population.pop[0].size);
	std::iota(genes.begin(), genes.end(), 0);
	std::random_device rd;
	std::mt19937 g(rd());

	for (int j = 0; j < population.size; j++) {
		std::shuffle(genes.begin(), genes.end(), g);
		population.pop[j].locations = genes;
	}
	set_h_fitness(population, sol);
}
int ruletka(Population population, solution sol) {
	int sum=0;
	for (specimen k : population.pop) {
		sum += 1000000/k.fitness;
	}
	// lepsze generatory losowe
	int roll = rand() % sum;
	int sum_f = 0;
	bool cond = false;
	int i = 0;
	while (!cond) {
		sum_f += 1000000/population.pop[i].fitness;
		if (sum_f > roll || i == population.size - 1) {
			cond = true;
			return i;
		}
		i++;
	}
}
specimen turniej(Population &population, solution sol, int t_size) {
	vector<int> t_pop;
	t_pop.resize(t_size);
	for (int i = 0; i < t_size; i++) {
		t_pop[i] = rand()%population.size;
	}
	int best = 0;
	for (int i = 0; i < t_size; i++) {
		if (population.pop[i].fitness < population.pop[best].fitness)
			best = i;
	}
	return population.pop[best];
}

solution genetic(solution starting, int popsize, string cross_type, string select_type, string finish_type, int cross_prob, int mut_prob, int genlimit, int minscore) {
	srand(time(NULL));

	int t_size = 20;
	specimen adam;
	adam.locations = starting.locations;
	
	Population population(popsize, starting.size);
	generatepop(population, starting);
	Population copypop = population;
	while (evaluate_pop(population, minscore, genlimit, finish_type)) {
		for (int i = 0; i < population.size; i++) {
			if (rand() % 100 < cross_prob) {
				if (cross_type._Equal("one")) {
					if (select_type._Equal("rul"))
						copypop.pop[i] = cross(population.pop[ruletka(population, starting)], population.pop[ruletka(population, starting)])[0];
					if (select_type._Equal("turney"))
						copypop.pop[i] = cross(turniej(population, starting, population.size / 2), turniej(population, starting, population.size / 2))[0];
				}
				if (cross_type._Equal("two")) {
					if (select_type._Equal("rul"))
						copypop.pop[i] = crosstwo(population.pop[ruletka(population, starting)], population.pop[ruletka(population, starting)])[0];
					if (select_type._Equal("turney"))
						copypop.pop[i] = crosstwo(turniej(population, starting, population.size / 2), turniej(population, starting, population.size / 2))[0];
				}
			}

		}
		population = copypop;
		for (int i = 0; i < population.size; i++) {
			if (rand() % 100 < mut_prob) {
				population.pop[i] = mutate(population.pop[i]);
			}
			
		}
		
		population.generation++;
	}

	starting.locations = population.pop[population.h_fitness_pop].locations;
	return starting;
}

//----- genetic eksperyment-----
void gen_exp_part(string savefile, string file, string cross_type, string select_type, int mut_prob,int crossprob, int popsize) {
	solution object(1);
	solution temp(1);
	load_solution_fromfile(object, file);
	auto start = std::chrono::high_resolution_clock::now();
	temp = genetic(object, popsize, cross_type, select_type, "gen", crossprob, mut_prob, 15, 0);
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;
	ofstream ofile_obj;
	ofile_obj.open(savefile, ios::app | ios::out);
	ofile_obj << "cross type: " << cross_type << " | ";
	ofile_obj << "select type: " << select_type << " | ";
	ofile_obj << "mutation probability: " << mut_prob << "% | ";
	ofile_obj << "cross probability: " << crossprob << "% | ";
	ofile_obj << "population size: " << popsize << " | ";
	ofile_obj << "time: " << diff.count() << " | ";
	ofile_obj << "score: " << evaluate(temp)<<endl;
	ofile_obj.close();
}


void gen_exp(string file, string savefile) {
	
	for (int popsize = 25; popsize < 250; popsize += 25) {
		for (int mut_prob=0; mut_prob < 100; mut_prob += 10) {
			for (int cross_prob = 0; cross_prob < 100; cross_prob += 10) {
				gen_exp_part(savefile, file, "one", "rul", mut_prob, cross_prob, popsize);
				gen_exp_part(savefile, file, "one", "turney", mut_prob, cross_prob, popsize);
				gen_exp_part(savefile, file, "two", "rul", mut_prob, cross_prob, popsize);
				gen_exp_part(savefile, file, "two", "turney", mut_prob, cross_prob, popsize);
			}
		}
	}
	
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
	if (input._Equal("genetic")) {
		cout << "population size ";
		cin >> input;
		stringstream popsizes(input);
		int popsize = 0;
		popsizes >> popsize;
		cout << "cross type ";
		string cross_type;
		cin >> cross_type;
		cout << "select type ";
		string select_type;
		cin >> select_type;
		cout << "finish type ";
		string finish_type;
		cin >> finish_type;
		cout << "cross probability ";
		cin >> input;
		stringstream cross_p(input);
		int cross_prob = 0;
		cross_p >> cross_prob;
		cout << "cross probability ";
		cin >> input;
		stringstream mut_p(input);
		int mut_prob = 0;
		mut_p >> mut_prob;
		int genl = 0;
		if (finish_type._Equal("gen"))
		{
			cout << "generation limit ";
			cin >> input;
			stringstream gen(input);
			gen >> genl;
		}
		int scorel = 0;
		if (finish_type._Equal("score"))
		{
			cout << "generation limit ";
			cin >> input;
			stringstream score(input);
			score >> scorel;
		}
		object = genetic(object, popsize, cross_type, select_type, finish_type, cross_prob,mut_prob, genl, scorel);
		//linia komend zamiast soutin
	}
	if (input._Equal("genexp")) {
		gen_exp("genexp.txt", "gensave.txt");
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