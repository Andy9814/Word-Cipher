/*
Name:Andy Singh
Purpose: Book cipher decoder
takes a book file and a coded file and decodes the coded file to produce a message file
*/

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <istream>
#include <cstring>
#include <sstream>
#include <iterator>
using namespace std;

//data types (aliases) used in this project
//book size
using book_size_type = uintmax_t;

//encoding book types
using book_location_type = pair<book_size_type, book_size_type>;
using book_location_list_type = vector < book_location_type>;
using encoding_book_type = vector <book_location_list_type>;

//decoding book type
using decoding_book_type = vector<vector<char>>;


int main(int argc, char* argv[])
{
	
	ofstream messageFile("messagefile.txt");
	ifstream inputBook("bookfile.txt");
	ifstream codedMessage("codedfile.txt");

	//Use input validation error messages to make sure the files can be read
	if (inputBook.is_open() && inputBook.good())
	{
		cout << "The bookfile is now open" << endl;
	}
	else
	{
		cout << "Unable to open bookfile!" << endl;
	}

	if (codedMessage.is_open() && codedMessage.good())
	{
		cout << "The message file is now open" << endl;
	}
	else
	{
		cout << "Unable to open messagefile" << endl;
	}


	string messagefile = "";

	//Put message file in a string
	getline(codedMessage, messagefile);



	stringstream ss(messagefile);
	istream_iterator<string> begin(ss);
	istream_iterator<string> end;
	vector<string> messageStrings(begin, end);
	//copy(messageStrings.begin(), messageStrings.end(), ostream_iterator<string>(cout, "\n"));
	int count = 0;
	int yy = 0;

	//Create two vectors to hold the offset value and the line number value
	vector<string>line;
	vector<string>offset;

	for (auto i = 0; i < messageStrings.size(); i++)
	{
		if (i % 2 == 0)
		{
			line.push_back(messageStrings[i]);
		}
		else
			offset.push_back(messageStrings[i]);
	}

	for (auto i = 0; i < line.size(); i++)
	{
		cout << "The contents of the line vector are: " << line[i] << endl;
	}

	for (auto i = 0; i < offset.size(); i++)
	{
		cout << "The contents of the offset vector are: " << offset[i] << endl;
	}

	//Remove the 'x' from the contents of both vectors
	for (auto i = 0; i < line.size(); i++)
	{
		line[i].erase(remove(line[i].begin(), line[i].end(), 'x'), line[i].end());
	}

	for (auto i = 0; i < offset.size(); i++)
	{
		offset[i].erase(remove(offset[i].begin(), offset[i].end(), 'x'), offset[i].end());
	}

	//Create two vector ints to hold the line number and offset
	vector <int> lineNums;
	vector <int> offsetNums;

	//load the vectors with the integer values
	for (auto i = 0; i < line.size(); i++)
	{
		lineNums.push_back(stoi(line[i]));
	}

	for (auto i = 0; i < offset.size(); i++)
	{
		offsetNums.push_back(stoi(offset[i]));
	}

	for (auto i = 0; i < lineNums.size(); i++)
	{
		cout << "the new values of lines are: " << lineNums[i] << endl;
	}

	for (auto i = 0; i < offsetNums.size(); i++)
	{
		cout << "the new values of offsets are: " << offsetNums[i] << endl;
	}

	//Put bookfile into char vector
	char bookChar;
	vector <char> bookcharA;
	while (inputBook.get(bookChar))
	{
		bookcharA.push_back(bookChar);
	}

	vector <char> answer;
	//stores number of lines in book
	vector<int>myCount;

	
	int cLine = 0;
	

	for (auto i = 0; i < lineNums.size(); ++i) {

	
		 cLine = 0;

		int CoffS = 0;
		for (auto t = 0; t < bookcharA.size(); ++t) //a
		{
			
			if (cLine == lineNums[i]) 
			{
				if (bookcharA[t] == bookcharA[offsetNums[i]])
				{
				answer.push_back(bookcharA[t]);
				break;
				}
				if (CoffS == offsetNums[i]) 
				{

				answer.push_back(bookcharA[t]);
				break;
				}

		    }

			
			CoffS++;
			if (bookcharA[t] == '\n') 
			{
				cLine++;
				CoffS = 0;

			}

		}

	}



	for (int x = 0; x < answer.size(); x++)
	{

		messageFile << answer[x];


	}
	messageFile.close();
	cout << endl;
}