/*
Name:Andy Sing
Purpose: Book cipher encoder
Takes a book file and a message file and encodes the message using line and offset values from the book file and produces a coded file

*/

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <istream>

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

void validation(string message, string bookstr);
void send_output(vector <int> offsetCount, vector <int> newLines);

int main(int argc, char* argv[])
{
	
	ifstream inputBook("bookfile.txt");
	ifstream inputMessage("messagefile.txt");

	//Use input validation error messages to make sure the files can be read
	if (inputBook.is_open() && inputBook.good())
	{
		cout << "The bookfile is now open" << endl;
	}
	else
	{
		cout << "Unable to open bookfile!" << endl;
	}

	if (inputMessage.is_open() && inputMessage.good())
	{
		cout << "The message file is now open" << endl;
	}
	else
	{
		cout << "Unable to open messagefile" << endl;
	}



	// convert the whole book into Chars 
	char bookChar;
	vector <char> bookcharV;
	while (inputBook.get(bookChar)) {
		bookcharV.push_back(bookChar);
	}
	
	// convert the message file into chars
	vector<char> messageCharV;
	char  messageChar;
	while (inputMessage.get(messageChar))
	{
		messageCharV.push_back(messageChar);
	}

	

	//Call validation function
	//validation(message, bookstr);

	int countOff = 0;
	int newLine = 0;

	vector<int> offSets;
	vector<int> newLines;

	// loop throught the message chars
	for (auto i = 0; i < messageCharV.size(); ++i) {

		// loop thu the book char see if it finds the char from message
		for (auto t = 0; t < bookcharV.size(); ++t) //a
		{
			
			if (bookcharV[t] == messageCharV[i]) {

				offSets.push_back(countOff);

				countOff = 0;


				newLines.push_back(newLine);
				newLine = 0;
				break;
			}

			countOff++;

			if (bookcharV[t] == '\n') {
				countOff = 0;
				newLine++;
				
			}


		}

	}



	//Call function that will take the numbers and put it in a text file
	send_output(offSets, newLines);
}
//This function will create the proper format for the output
void send_output(vector <int> offSetCount, vector <int> newLines)
{
	ofstream codedFile("codedfile.txt");

	vector <string> outOffSet;
	vector <string> newLinesCount;

	for (int i = 0; i < newLines.size(); i++)
	{
		if (newLines[i] >= 100000)
		{
			string strr = "";

			strr = to_string(newLines[i]);

			string greaterThanHun = "0x00";

			newLinesCount.push_back(greaterThanHun + strr);

		}
		if (newLines[i] >= 10000)
		{
			string strr = "";

			strr = to_string(newLines[i]);

			string greaterThanHun = "0x000";

			newLinesCount.push_back(greaterThanHun + strr);

		}
		if (newLines[i] >= 1000)
		{
			string strr = "";

			strr = to_string(newLines[i]);

			string greaterThanHun = "0x0000";

			newLinesCount.push_back(greaterThanHun + strr);

		}

		if (newLines[i] >= 100)
		{
			string strr = "";

			strr = to_string(newLines[i]);

			string greaterThanHun = "0x00000";

			newLinesCount.push_back(greaterThanHun + strr);

		}
		if (newLines[i] >= 10)
		{
			string strr = "";

			strr = to_string(newLines[i]);

			string greaterThanten = "0x000000";

			newLinesCount.push_back(greaterThanten + strr);

		}
		if (newLines[i] < 10)
		{
			string strr = "";


			string s = to_string(newLines[i]);

			string lessThanten = "0x0000000";


			newLinesCount.push_back(lessThanten + to_string(newLines[i]));

		}
	}







	for (int i = 0; i < offSetCount.size(); i++)
	{
		if (offSetCount[i] >= 100000)
		{
			string str = "";

			str = to_string(offSetCount[i]);

			string greaterThanHun = "0x00";

			outOffSet.push_back(greaterThanHun + str);

		}
		if (offSetCount[i] >= 10000)
		{
			string str = "";

			str = to_string(offSetCount[i]);

			string greaterThanHun = "0x000";

			outOffSet.push_back(greaterThanHun + str);

		}

		if (offSetCount[i] >= 1000)
		{
			string str = "";

			str = to_string(offSetCount[i]);

			string greaterThanHun = "0x0000";

			outOffSet.push_back(greaterThanHun + str);

		}

		if (offSetCount[i] >= 100)
		{
			string str = "";

			str = to_string(offSetCount[i]);

			string greaterThanHun = "0x00000";

			outOffSet.push_back(greaterThanHun + str);

		}
		if (offSetCount[i] >= 10)
		{
			string str = "";

			str = to_string(offSetCount[i]);

			string greaterThanten = "0x000000";

			outOffSet.push_back(greaterThanten + str);

		}
		if (offSetCount[i] < 10)
		{
			string str = "";

			str = to_string(offSetCount[i]);

			string lessThanten = "0x0000000";

			outOffSet.push_back(lessThanten + to_string(offSetCount[i]));

		}
	}


	for (int x = 0; x < newLinesCount.size(); x++)
	{

		codedFile << newLinesCount[x] << " " << outOffSet[x] << " ";


	}
	codedFile.close();
}
//void validation(string message, string bookstr)
//{
//	//Input validation to make sure both the message file and book file have common characters
//	string result;
//	set_intersection(
//		begin(bookstr), end(bookstr),
//		begin(message), end(message),
//		back_inserter(result)
//	);
//
//	int length1 = result.size();
//	int length2 = message.size();
//	if (length1 != length2)
//	{
//		cout << "Character(s) in the message file are not found in the book file!" << endl;
//		EXIT_FAILURE;
//	}
//}