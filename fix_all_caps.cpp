// run with ````./programname.out (string)filename (int)linecount````
// changes each line to all lowercase, except the first letter which is capitalized.
// great for line seperated list of names

#include <fstream>
#include <ostream>
#include <iostream>
#include <regex>
#include <ctype.h>
#include <algorithm>

int main(int argc, char *argv[])
{
	bool DEBUG = true;
	std::regex number_reg ("([0-9]).*");
	int lines;
	std::string filename;

	//make sure the argv[] is mostly correct (check first 2 values)
	if (argc >= 2)
	{
		filename = argv[1];

		if (std::regex_match(argv[2], number_reg))
		{
			lines = atoi(argv[2]);
		}
		else
		{
			std::cout << "\nInvalid argument. Second item should be a positive Integer.\nExecute with the string of the filename path followed by the number of lines in the file";
			exit(-2);
		}
	}
	else
	{
		std::cout << "\nInvalid argument.To few arguments given to the program.\nExecute with the string of the filename path followed by the number of lines in the file";
		exit(-1);
	}


	if (DEBUG) std:: cout << "\nDEBUG: lines = " << lines;
	if (DEBUG) std:: cout << "\nDEBUG: filename = " << filename;

	if (DEBUG) std::cout << std::endl;
	
	//open file and change all caps to first character caps only
	std::ifstream fileOfNames;
	std::ofstream save_to_file;
	std::string tmpName;
	std::string fileoutputname = "testoutput1.txt";
	std::vector<std::string> all_last_names;
	fileOfNames.open(filename);
	save_to_file.open(fileoutputname);

	if (fileOfNames.is_open())
	{

		if (!save_to_file)
		{
			std::cout << "Could not open to save. Check code or file.\n\n";
			exit(-3);
		}

		for (auto i = 1; i < lines; i++)
		{
			getline(fileOfNames, tmpName, '\n');
			std::transform(tmpName.begin(), tmpName.end(), tmpName.begin(), ::tolower);
			tmpName[0] = toupper(tmpName[0]);
			all_last_names.push_back(tmpName);
		}
	}
	else
	{
		tmpName = "error with incoming file - check code or that you entered the right file path";
		std::cout << "error grabbing name\n";
	}

	//save data to file now
	if (all_last_names.size() < 1)
	{
		std::cout << "Nothing to save.\n.";
		exit(-4);
	}
	for (auto &it : all_last_names)
	{ 
		save_to_file << it << "\n";
	}
	save_to_file.close();

	return 0;
}
