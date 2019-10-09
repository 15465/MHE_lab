#include "pch.h"
#include <iostream>

using namespace std;


#define size 5
int distance_matrix[size][size];
int flows_matrix[size][size];

float quality(int flow, int ideal_flow) {
	return flow / ideal_flow;
}

int calculate_ideal() {
	return NULL;
}

int main()
{


}
