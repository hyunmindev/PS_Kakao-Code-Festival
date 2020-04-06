#include <iostream>
#include <cmath>

using namespace std;


long double getStandardDeviation(long double variance) {
	return sqrt(variance);
}

long double getVariance(int* numbers, int startIndex, int endIndex, long double average) {
	long double sum = 0;
	for (int i = startIndex; i <= endIndex; i++)
		sum += pow(average-numbers[i],2);
	return sum/(endIndex-startIndex+1);
}

long double getAverage(int* numbers, int startIndex, int endIndex) {
	long double sum = 0;
	for (int i = startIndex; i <= endIndex; i++) 
		sum += numbers[i];
	return sum/(endIndex-startIndex+1);
}


int main(int argc, char* argv[]) {
	int n, k;
	cin >> n >> k;
	
	int numbers[n];
	for (int i = 0; i < n; i++)
		cin >> numbers[i];
	
	long double min = 987654321;
	
	for(int i = k; i <= n; i++) {
		for (int j = 0; j < n-i+1; j++) {
			long double average = getAverage(numbers, j, j+i-1);
			long double variance = getVariance(numbers, j, j+i-1, average);
			long double standardDeviation = getStandardDeviation(variance);
			if (min > standardDeviation)
				min = standardDeviation;
		}
	}
	cout << fixed;
	cout.precision(11);
	cout << min << endl;
	return 0;
}
