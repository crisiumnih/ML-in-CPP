// ML in CPP2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <random>
#include<vector>
float train[][2] = {
	{0,0},
	{1,2},
	{2,4},
	{3,6},
	{4,8},
};
#define train_count (sizeof(train)/sizeof(train[0]))
float rand_float(void) {
	std::random_device rd;
	std::mt19937 gen(rd());
	
	std::uniform_real_distribution<float> distribution(1, 10);
	float randNum = distribution(gen);
	return randNum;
}

//cost function
float cost(float w, float b) {
	
	float result = 0.0f;
	for (size_t i = 0;i < train_count;i++) {
		float x = train[i][0];
		float y = x * w+ b;
		float d = y - train[i][1];
		result += d * d;
		//std::cout << "actual: " << y << ",expected: " << train[i][1] << std::endl;
	}
	result /= train_count;
	return result;
}


int main() {
	float w = rand_float();
	float b = rand_float()/5;
	//std::cout << w << std::endl;
	float eps = 1e-3;
	float rate = 1e-3;
	for (size_t i = 0;i < 2000;i++) {
		float c = cost(w, b);
		float dw = (cost(w + eps,b) - c) / eps;
		float db = (cost(w ,b+ eps) - c) / eps;
		b -= rate * db;
		w -= rate * dw;

		std::cout <<"w: "<< w <<" b: "<< b <<" cost: "<< cost(w, b) << std::endl;
		

	}
	for (size_t i = 0;i < train_count;i++) {
		float x = train[i][0];
		float y = x * w+b;
		float d = y - train[i][1];
		
		std::cout << "actual: " << y << ",expected: " << train[i][1] << std::endl;
	}

	


	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
