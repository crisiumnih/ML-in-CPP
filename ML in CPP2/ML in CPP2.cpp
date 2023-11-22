// ML in CPP2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <random>
#include<fstream>
#include<cstdio>
#include<cstring>
#include<vector>
float train[][2] = {
	{0,0},
	{1,2},
	{2,4},
	{3,6},
	{4,8},
};
float sigmoidf(float x) {
	return 1.f / (1.f + expf(-x));
}
void plotC(const char* filename) {
	FILE* gnuplotPipe = _popen("gnuplot -persist", "w");
	if (gnuplotPipe == nullptr) {
#ifdef _WIN32
		perror("Error opening pipe to Gnuplot");
#else
		perror("Error opening pipe to Gnuplot");
#endif

	}
	fprintf(gnuplotPipe, "plot '%s' with lines title 'Data'\n", filename);
	fflush(gnuplotPipe);

#ifdef _WIN32
	_pclose(gnuplotPipe);
#else
	pclose(gnuplotPipe);
#endif
}
float train2[][3] = {
	{0,0,0},
	{1,0,1},
	{0,1,1},
	{1,1,1},
};
#define train_count (sizeof(train)/sizeof(train[0]))
#define train2_count (sizeof(train2)/sizeof(train2[0]))

float rand_float(void) {
	std::random_device rd;
	std::mt19937 gen(rd());
	
	std::uniform_real_distribution<float> distribution(1, 10);
	float randNum = distribution(gen);
	return randNum;
}

//cost function
float cost1(float w, float b) {
	
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
float cost2(float w1, float w2, float b) {

	float result = 0.0f;
	for (size_t i = 0;i < train2_count;i++) {
		float x1 = train2[i][0];
		float x2 = train2[i][1];

		float y = sigmoidf(x1 * w1 + x2 * w2+b);
		float d = y - train2[i][2];
		result += d * d;
	}
	result /= train2_count;
	return result;
}

void linear_reg() {
	float w = rand_float();
	float b = rand_float() / 5;
	//std::cout << w << std::endl;
	float eps = 1e-3;
	float rate = 1e-3;
	for (size_t i = 0;i < 2000;i++) {
		float c = cost1(w, b);
		float dw = (cost1(w + eps, b) - c) / eps;
		float db = (cost1(w, b + eps) - c) / eps;
		b -= rate * db;
		w -= rate * dw;

		std::cout << "w: " << w << " b: " << b << " cost: " << cost1(w, b) << std::endl;


	}
	for (size_t i = 0;i < train_count;i++) {
		float x = train[i][0];
		float y = x * w + b;
		float d = y - train[i][1];

		std::cout << "actual: " << y << ",expected: " << train[i][1] << std::endl;
	}
}

void linear_reg_or_gate() {
	std::ofstream file("gates.txt");
	
	float w1 = rand_float()/10;
	float w2 = rand_float()/10;
	float b = rand_float() / 10;
	//std::cout << w1 << " " << w2 << std::endl;


	float eps = 1e-1;
	float rate = 1e-1;
	//std::cout << "w1: " << w1 << " w2: " << w2 << " cost: " << cost2(w1, w2,b) << std::endl;

	for (size_t i = 0;i < 100*1000;i++) {
		float c = cost2(w1, w2,b);
		float dw1 = (cost2(w1 + eps, w2,b) - c) / eps;
		float dw2 = (cost2(w1, w2 + eps,b) - c) / eps;
		float db = (cost2(w1, w2 , b + eps) - c) / eps;

		w1 -= rate * dw1;
		w2 -= rate * dw2;
		b -= rate * db;

		if (file.is_open()) {
			file<< c << std::endl;
		}
		std::cout << c << std::endl;



	}
	file.close();
	plotC("gates.txt");
	
	
	//std::cout << "w1: " << w1 << " w2: " << w2 <<" bias: "<<b<<" cost: " << cost2(w1, w2,b) << std::endl;
	for (size_t i = 0;i < 2;i++) {
		for (size_t j = 0;j < 2;j++) {
			//std::cout << i << " | " << j <<" = " << sigmoidf(i * w1 + j * w2+b) << std::endl;
		}
	}

}
int main() {
	
	linear_reg_or_gate();
	return 0;
}

