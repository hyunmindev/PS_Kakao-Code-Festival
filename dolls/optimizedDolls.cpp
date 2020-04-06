#include <iostream>
#include <cmath>

using namespace std;

int main(){
	int n, k;
	cin >> n >> k;
	
	unsigned long long int numbers[n];
	for (int i = 0; i < n; i++) 
		cin >> numbers[i];
	
	unsigned long long int accumulatesOfNumbers[n+1] = {0, };
	for (int i = 1; i < n+1; i++) 
		accumulatesOfNumbers[i] = accumulatesOfNumbers[i - 1] + numbers[i - 1];
	
	unsigned long long int powers[n];
	for (int i = 0; i < n; i++) 
		powers[i] = numbers[i] * numbers[i];
	
	unsigned long long int accumulatesOfPowers[n + 1]={0, };
	for (int i = 1; i < n+1; i++) 
		accumulatesOfPowers[i] = accumulatesOfPowers[i - 1] + powers[i - 1];
	
	double min = 987654321;
	for(int i = k; i <= n; i++) {
		for (int j = 0; j < n - i + 1; j++) {
			long double averageOfNumbers = (accumulatesOfNumbers[j + i] - accumulatesOfNumbers[j]) / (long double)i;
			long double averageOfPowers = (accumulatesOfPowers[j + i] - accumulatesOfPowers[j]) / (long double)i;
			long double variance=averageOfPowers - (averageOfNumbers * averageOfNumbers);
			long double standardDeviation = sqrt(variance);
			if (min > standardDeviation) 
				min = standardDeviation;
		}
	}
	
	cout << fixed;
	cout.precision(11);
	cout << min << endl;
}