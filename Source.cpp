#include <iostream>
#include <fstream>
#include <map>
#include <string>
using namespace std;

/*Function name		: roman_numbers_converter_validator
Description			: In this function the Roman number is converted to an Hindu Arabic number. 
					  If there is invalid inputs or invalid output returns a negative number.
Input Parameters	: string pass by reference
Return Type			: int*/
int roman_numbers_converter_validator(string &word_line)
{
	//map contain all incidents in the roman number which in lower case and upper case.
	map<char, int> value_returner;

	value_returner.insert({ 'i', 1 });
	value_returner.insert({ 'I', 1 });
	value_returner.insert({ 'v', 5 });
	value_returner.insert({ 'V', 5 });
	value_returner.insert({ 'x', 10 });
	value_returner.insert({ 'X', 10 });
	value_returner.insert({ 'l', 50 });
	value_returner.insert({ 'L', 50 });
	value_returner.insert({ 'c', 100 });
	value_returner.insert({ 'C', 100 });

	int number_of_V = 0;
	int number_of_L = 0;
	int answer = 0;

	//Count the number of 'V' and 'L' characters of the word
	for (int i = 0; i < word_line.length(); i++) {
		if (value_returner[word_line[i]] == 5) {
			number_of_V++;
		}

		else if (value_returner[word_line[i]] == 50) {
			number_of_L++;
		}

		//'V' or 'L' can not repeat twice in a number
		else if (number_of_V >= 2 || number_of_L >= 2) 
			return -1;
	}

	for (int i = 0; i < word_line.length(); i++)
	{
		//Substract previous value from next value if previoous value is less than next value.
		if (value_returner[word_line[i]] == 0) 
			return -2;

		//Two smaller values before a large value digits it should be an error
		else if (i > 0 && value_returner[word_line[i]] < value_returner[word_line[i + 1]] && 
					 value_returner[word_line[i - 1]] == value_returner[word_line[i]]) 
			return -3;

		//If a digit repeated in a succession more than thrice it should be an error
		else if (value_returner[word_line[i]] == value_returner[word_line[i + 1]] && 
			value_returner[word_line[i + 1]] == value_returner[word_line[i + 2]] &&
			value_returner[word_line[i + 2]] == value_returner[word_line[i + 3]]) 
			return -4;

		//If two digit pattern repeated twice it should be an error
		else if (word_line.length() >= 4 && i < word_line.length() - 4 && 
			value_returner[word_line[i]] == value_returner[word_line[i + 2]] &&
			value_returner[word_line[i + 1]] == value_returner[word_line[i + 3]]) 
			return -5;

		//'V' and 'L' digits should not come before higher value digit
		else if ((value_returner[word_line[i]] == 5 || value_returner[word_line[i]] == 50) && 
				  value_returner[word_line[i]] < value_returner[word_line[i + 1]])
			return -6;

		/*For a valid roman number if there is a smaller digit before a given digit
		   Substract the smaller digit value from the given digit value*/
		else if (value_returner[word_line[i]] < value_returner[word_line[i + 1]])
		{
			answer += value_returner[word_line[i + 1]] - value_returner[word_line[i]];
			i++;
			continue;
		}

		else 
			answer += value_returner[word_line[i]];
	}
	return answer;
}


int main()
{
	string file("numbers.txt");
	cout << endl;

	//read the .txt file
	string word_line;
	ifstream myfile(file);

	if (myfile.is_open())//check which the file is open or not
	{
		cout << "*******Roman to Hindu Arabic Converter*******\n\n";
		while (getline(myfile, word_line))
		{
			//get line by line of the text file
			if (roman_numbers_converter_validator(word_line) > 0)  cout << word_line << "\t\t-->\t" << roman_numbers_converter_validator(word_line) << '\n';

			else {
				cout << word_line << "\t\t-->\t" << "Error" << endl;
			}
		}
		myfile.close();//close the opened file
	}
	else 
		cout << "It is unable to open this file\n";
		
	return 0;
}
