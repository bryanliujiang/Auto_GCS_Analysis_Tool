#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int MAX_PHAGE = 40; // number of phages per search
int MAX_TAB = 5; // tabs opened threshold before warning is triggered

int automateGCS(string phage_name, string dataset, string response);

int main()
{
	string phage_name;
	string dataset;
	string response;
	int option;

	cout << "Welcome to Semi-Auto GCS Analysis Tool (v1.0)!\n" << endl;

	cin >> option;
	switch (option)
	{
	case 1:
		while (true)
		{
			cout << "Enter the name of phage that the phage list will be compared to." << endl;
			cin >> phage_name;

			string is_correct;

			while (true)
			{
				cout << "You entered: '" << phage_name << "'. \n"
					"Is this correct? (y/n)" << endl;
				cin >> is_correct;
				if (is_correct == "Y" || is_correct == "N" || is_correct == "y" || is_correct == "n")
					break;
				cout << "Invalid input. Valid inputs are either the single letter 'y' (yes) or 'n' (no)." << endl;
			}

			if (is_correct == "Y" || is_correct == "y")
				break;
		}

		while (true)
		{
			cout << "Enter the file name containing the list of phages.\n"
				"Windows must have file extension '.txt' like 'phage_list.txt'.\n"
				"" << endl;
			cin >> dataset;

			string is_correct;

			while (true)
			{
				cout << "You entered: '" << dataset << "'. \n"
					"Is this correct? (y/n)" << endl;
				cin >> is_correct;
				if (is_correct == "Y" || is_correct == "N" || is_correct == "y" || is_correct == "n")
					break;
				cout << "Invalid input. Valid inputs are either the single letter 'y' (yes) or 'n' (no)." << endl;
			}

			if (is_correct == "Y" || is_correct == "y")
				break;
		}

		while (true)
		{
			cout << "Would you like tabs to open in your browser? (y/n)" << endl;
			cin >> response;
			if (response == "Y" || response == "N" || response == "y" || response == "n")
				break;
			cout << "Invalid input. Valid inputs are either the single letter 'y' (yes) or 'n' (no)." << endl;
		}

		break;
	default:
		response = "Y";
	}

	
	
	// Return 0: Success
	// Return 1: Test Run
	// Return -1: Error
	return automateGCS(phage_name, dataset, response);
}

int automateGCS(string phage_name, string dataset, string response)
{
	ifstream inf(dataset);
	if (!inf)
	{
		cerr << "Data failed to load!" << endl;
		return -1;
	}

	ofstream myfile;
	string line;

	myfile.open("horizontal.txt");
	while (getline(inf, line))
	{
		istringstream iss(line);
		string phage;
		iss >> phage;
		myfile << phage << "\t";
	}
	myfile.close();
	inf.clear();
	inf.seekg(0, ios::beg);

	myfile.open("vertical.txt");
	while (getline(inf, line))
	{
		istringstream iss(line);
		string phage;
		iss >> phage;
		myfile << phage << endl;
	}
	myfile.close();
	inf.clear();
	inf.seekg(0, ios::beg);

	if (response == "Y" || response == "y")
	{
		string url_phages;
		int count_phage = 0;
		int count_tab = 0;
		int count_phage_total = 0;
		
		while (getline(inf, line))
		{
			if (count_phage == MAX_PHAGE)
			{
				string url_master = "https://phagesdb.org/genecontent/compare/?phages=" + phage_name + url_phages;
				system(std::string("start " + url_master).c_str());
				url_phages.clear();
				count_phage = 0;
				++count_tab;
				if (count_tab == MAX_TAB)
				{
					while (true)
					{
						cout << MAX_TAB << " tabs have opened, but more phages still need processing. Still continue? (y/n)" << endl;
						cin >> response;
						if (response == "Y" || response == "N" || response == "y" || response == "n")
							break;
						cout << "Invalid input. Valid inputs are either the single letter 'y' (yes) or 'n' (no)." << endl;
					}
					if (response == "N" || response == "n")
					{
						cout << "User has terminated processing early.\n"
							"The total number of phages successfully compared to '" << phage_name << "' was " << count_phage_total << ".\n" 
							"You may close the program or press ENTER or RETURN to exit." << endl;
						cin.get();
						cin.ignore();
						exit(1);
					}
					count_tab = 0;
				}
			}
			istringstream iss(line);
			string phage;
			iss >> phage;
			url_phages = url_phages + ",%20" + phage;
			++count_phage;
			++count_phage_total;
		}

		string url_master = "https://phagesdb.org/genecontent/compare/?phages=" + phage_name + url_phages;
		system(std::string("start " + url_master).c_str());
		
		cout << "The total number of phages successfully compared to '" << phage_name << "' was " << count_phage_total << "." << endl;
	}

	cout << dataset << " was processed successfully!\n"
		"You may close the program or press ENTER or RETURN to exit." << endl;
	cin.get();
	cin.ignore();

	return 0;
}