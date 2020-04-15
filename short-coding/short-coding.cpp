#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

vector<string> firstMonomials, secondMonomials, compareOperators;
vector<string> output;

vector<int> setElementIndex(string input) 
{
	vector<int> elementIndexes;
	elementIndexes.push_back(0);
	for (int i = 0; i < input.length(); i++) 
	{
		if(input.at(i) == '&' && input.at(i+1) == '&')
		{
			i += 2;
			elementIndexes.push_back(i);
		}
	}
	elementIndexes.push_back(input.length() + 2);
	return elementIndexes;
}


vector<string> setExpression(vector<int> &elementIndexes, string input)
{
	vector<string> expressions;
	for (int i = 0; i < elementIndexes.size() - 1; i++)
	{
		expressions.push_back(input.substr(elementIndexes.at(i), elementIndexes.at(i + 1) - elementIndexes.at(i) - 2));
	}
	return expressions;
}


void divideExpression(vector<string> &expressions)
{
	for (int i = 0; i < expressions.size(); i++)
	{
		string expression = expressions.at(i);
		for (int j = 0; j < expression.length(); j++)
		{
			if (expression.at(j) == '=') 
			{
				firstMonomials.push_back(expression.substr(0, j));
				secondMonomials.push_back(expression.substr(j + 2, expression.length() - j - 2));
				compareOperators.push_back(expression.substr(j, 2));
				break;
			}
			else if (expression.at(j) == '!')
			{
				output.push_back(expression);
				break;
			}
		}
	}
}


vector<string> setVariables() 
{
	vector<string> variables;
	for (int i = 0; i < firstMonomials.size(); i++)
	{
		string firstMonomial = firstMonomials.at(i);
		string secondMonomial = secondMonomials.at(i);
		
		if (!isdigit(firstMonomial.at(0)))
		{
			if(find(variables.begin(), variables.end(), firstMonomial) == variables.end())
			{
				variables.push_back(firstMonomial);
			}
				
		}
		
		if (!isdigit(secondMonomial.at(0)))
		{
			if(find(variables.begin(), variables.end(), secondMonomial) == variables.end())
			{
				variables.push_back(secondMonomial);
			}
		}
	}
	return variables;
}


bool compareLength(const string &str1, const string &str2) 
{
	return str1.length() < str2.length();
}

void sortVariables(vector<string> &variables)
{
	sort(variables.begin(), variables.end(), compareLength);

}


vector<string> setIntegers(vector<string> &variables)
{
	vector<string> integers;
	for (int i = 0; i < variables.size(); i++)
	{
		string variable = variables.at(i);
		
		for (int j = 0; j < firstMonomials.size(); j++)
		{
			string firstMonomial = firstMonomials.at(j);
			string secondMonomial = secondMonomials.at(j);
			string compareOperator = compareOperators.at(j);
			
			if (variable == firstMonomial && isdigit(secondMonomial.at(0)))
			{
				integers.push_back(secondMonomial);
				break;
			}
			else if (variable == secondMonomial && isdigit(firstMonomial.at(0)))
			{
				integers.push_back(firstMonomial);
				break;
			}
			if (j == firstMonomials.size() - 1)
			{
				integers.push_back("-");
			}

		}
	}
	return integers;
}



int main()
{
	string input; 
	cin >> input;
	
	vector<int> elementIndexes = setElementIndex(input);
	// 논리식이 1개 이하일 경우 input 그대로 출력
	if (elementIndexes.size() < 4) 
	{
		cout << input << endl;
		return 0;
	}
	
	vector<string> expressions = setExpression(elementIndexes, input);
	
	divideExpression(expressions);
	
	vector<string> variables = setVariables();
	sortVariables(variables);
	
	vector<string> integers = setIntegers(variables);

	
	for (int i = 0; i < firstMonomials.size(); i++)
	{
		string firstMonomial = firstMonomials.at(i);
		string secondMonomial = secondMonomials.at(i);

		if (!isdigit(firstMonomial.at(0)) && !isdigit(secondMonomial.at(0)))
		{
 			int firstMonomialIndex = distance(variables.begin(), find(variables.begin(), variables.end(), firstMonomial));
 			int secondMonomialIndex = distance(variables.begin(), find(variables.begin(), variables.end(), secondMonomial));
			if (integers.at(firstMonomialIndex) == "-")
				integers.at(firstMonomialIndex) = integers.at(secondMonomialIndex);
			if (integers.at(secondMonomialIndex) == "-")
				integers.at(secondMonomialIndex) = integers.at(firstMonomialIndex);
		}
	}
	
	
	vector<string> uniqueIntegers;
	vector<vector<string>> uniqueVariabales;
	
	for (int i = 0; i < variables.size(); i++)
	{
		string variable = variables.at(i);
		string integer = integers.at(i);
		
		if(find(uniqueIntegers.begin(), uniqueIntegers.end(), integer) == uniqueIntegers.end())
		{
			uniqueIntegers.push_back(integer);
			vector<string> temp;
			temp.push_back(variable);
			uniqueVariabales.push_back(temp);
		}
		else 
		{
			int originIndex = distance(uniqueIntegers.begin(), find(uniqueIntegers.begin(), uniqueIntegers.end(), integer));
			uniqueVariabales.at(originIndex).push_back(variable);
		}
	}
	
	
	for (int i = 0; i < uniqueIntegers.size(); i++)
	{
		
		if (uniqueVariabales.at(i).size() == 1)
		{
			string expression = uniqueVariabales.at(i).at(0) + "==" + uniqueIntegers.at(i);
			output.push_back(expression);
		}
		else
		{
			int integersLength = uniqueIntegers.at(i).length() * uniqueVariabales.at(i).size();
			int variablesLength = 0;
			for (int j = 0; j < uniqueVariabales.at(i).size(); j++)
			{
				variablesLength += uniqueVariabales.at(i).at(j).length();
			}
			
			if (integersLength < variablesLength)
			{
				for (int j = 0; j < uniqueVariabales.at(i).size(); j++)
				{
					string expression = uniqueVariabales.at(i).at(j) + "==" + uniqueIntegers.at(i);
					output.push_back(expression);
				}
			}
			else
			{
				if (uniqueIntegers.at(i) != "-") {
					string expression = uniqueVariabales.at(i).at(0) + "==" + uniqueIntegers.at(i);
					output.push_back(expression);
				}
				for (int j = 1; j < uniqueVariabales.at(i).size(); j++)
				{
					string expression = uniqueVariabales.at(i).at(0) + "==" + uniqueVariabales.at(i).at(j);
					output.push_back(expression);
				}
			}
		}
	}
	
	
	for (int i = 0; i < output.size(); i++)
	{
		cout << output.at(i);
		if (i != output.size() - 1) cout << "&&";
	}
}