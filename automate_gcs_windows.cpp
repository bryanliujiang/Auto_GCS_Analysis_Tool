#include "defaults_windows.h"

#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int AutomateGCS(int max_phage, bool full_auto)
{
    cout << "\nProcessing . . .\n" << endl;

    ifstream pha(PHAGE_LIST);
    if (!pha)
    {
        cerr << "Data failed to load!" << endl;
        return -1;
    }

    ifstream oth(OTHER_LIST);
    if (!oth)
    {
        cerr << "Data failed to load!" << endl;
        return -1;
    }

    ofstream myfile;
    string line;

    myfile.open("horizontal.txt");
    int num_phages = 0;
    while (getline(pha, line))
    {
        istringstream iss_pha(line);
        string phage;
        iss_pha >> phage;
        myfile << phage << "\t";
        ++num_phages;
    }
    myfile.close();
    pha.clear();
    pha.seekg(0, ios::beg);

    myfile.open("vertical.txt");
    while (getline(oth, line))
    {
        istringstream iss_oth(line);
        string phage;
        iss_oth >> phage;
        myfile << phage << endl;
    }
    myfile.close();
    oth.clear();
    oth.seekg(0, ios::beg);

    int count_phage_master = 0, // total number of phages in phage_list.txt
        count_other_master = 0, // grand total number of comparisons made across all rounds
        count_other_total = 0, // total number of phages in other_list.txt successfully compared in one round
        count_other_total_report = 0, // total number of phages in other_list.txt
        count_other = 0, // tracks phages compared in one tab before overflowing to a new tab
        count_tab_master = 0, // grand total number of tabs opened across all rounds
        count_tab_total = 0; // total number of tabs opened in one round
    string phage_name;
    string response = "y";
    string url_phages;

    while (getline(pha, line))
    {
        istringstream iss_pha(line);
        string phage;
        iss_pha >> phage;
        phage_name = phage;

        ++count_phage_master;

        while (getline(oth, line))
        {
            if (count_other == max_phage)
            {
                string url_master = "https://phagesdb.org/genecontent/compare/?phages=" + phage_name + url_phages;
                system(std::string("start " + url_master).c_str());
                ++count_tab_master;
                ++count_tab_total;
                url_phages.clear();
                count_other = 0;
                if (count_tab_master == MAX_TAB)
                {
                    while (!full_auto)
                    {
                        cout << MAX_TAB << " tabs have opened, but more phages still need processing. Still continue? (y/n)" << endl;
                        cin >> response;
                        if (response == "Y" || response == "N" || response == "y" || response == "n")
                            break;
                        cout << "Invalid input. Valid inputs are either the single letter 'y' (yes) or 'n' (no)." << endl;
                    }
                    if (response == "N" || response == "n")
                    {
                        cout << "\nUser has terminated processing early.\n"
                            "The total number of phages successfully compared to '" << phage_name << "' was " << count_other_total << ".\n"
                            "\nYou may close the program or press ENTER or RETURN to exit." << endl;
                        cin.get();
                        cin.ignore();
                        return 1;
                    }
                    cout << "\nProcessing . . .\n" << endl;
                }
            }

            istringstream iss_oth(line);
            string other;
            iss_oth >> other;

            url_phages = url_phages + ",%20" + other;

            ++count_other;
            ++count_other_total;
            ++count_other_master;
        }

        string url_master = "https://phagesdb.org/genecontent/compare/?phages=" + phage_name + url_phages;
        system(std::string("start " + url_master).c_str());

        ++count_tab_master;
        ++count_tab_total;
        count_other_total_report = count_other_total; // to prevent resetting count during output report

        cout << "The total number of phages successfully compared to '" << phage_name << "' was " << count_other_total << ".\n"
            "The total number of tabs opened from comparing to '" << phage_name << "' was " << count_tab_total << "." << endl;

        if (count_phage_master != num_phages)
        {
            while (!full_auto)
            {
                cout << "\nProceed to the next phage in " << PHAGE_LIST << " to compare to? (y/n)" << endl;
                cin >> response;
                if (response == "Y" || response == "N" || response == "y" || response == "n")
                    break;
                cout << "Invalid input. Valid inputs are either the single letter 'y' (yes) or 'n' (no)." << endl;
            }
            if (response == "N" || response == "n")
            {
                cout << "\nUser has terminated processing early.\n"
                    "The total number of phages in " << PHAGE_LIST << " successfully compared to was " << count_phage_master << ".\n"
                    "\nYou may close the program or press ENTER or RETURN to exit." << endl;
                cin.get();
                cin.ignore();
                return 1;
            }
            cout << "\nProcessing . . .\n" << endl;
            oth.clear();
            oth.seekg(0, ios::beg);
            url_phages.clear();
            count_other = 0;
            count_other_total = 0;
            count_tab_total = 0;
        }
    }

    cout << "\n=========================================================================="
        "\nProgram was successful!\n\n"
        "The total number of comparisons made from the " << count_other_total_report << " phage(s) in " << OTHER_LIST << "\nto the "
        << count_phage_master << " phage(s) in " << PHAGE_LIST << " was " << count_other_master << ".\n\n"
        "The total number of tabs opened was " << count_tab_master << ".\n\n"
        "You may close the program or press ENTER or RETURN to exit." << endl;
    cin.get();
    cin.ignore();

    return 0;
}