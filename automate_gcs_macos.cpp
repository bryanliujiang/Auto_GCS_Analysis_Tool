#include "defaults_macos.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>
using namespace std;

int AutomateGCS(int max_phage, bool full_auto, bool debug)
{
    cout << "\nProcessing . . .\n" << endl;
    
    int MAXPATHLEN = 256;
    char buffer[MAXPATHLEN];
    string curPath;

    char* path = getcwd(buffer, MAXPATHLEN);
    if (!path)
    {
        cerr << "Error: OS incompatibility!";
        return -2;
    }
    else
        curPath = path;
   
    if (debug)
    {
        cerr << "current path is: " << curPath << endl;

        string newPath = curPath + "/Desktop/" + FOLDER_NAME; // tested for 10.15, 10.14
        int rc = chdir(newPath.c_str());
        if (rc < 0)
        {
            cerr << "Error: OS version incompatibility!";
            return -3;
        }

        cerr << "new path is: " << newPath << endl;

        ofstream myfile;
        myfile.open("test.txt");
        myfile.close();

        cerr << "done\n";

        return 2;
    }

    string newPath = curPath + "/Desktop/" + FOLDER_NAME; // relies on the program folder being on the Deskop
    int rc = chdir(newPath.c_str());
    if (rc < 0)
    {
        cerr << "Error: OS version incompatibility!";
        return -3;
    }

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
        if (phage.empty())
            continue;
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
        if (phage.empty())
            continue;
        myfile << phage << endl;
    }
    myfile.close();
    oth.clear();
    oth.seekg(0, ios::beg);

    int count_other_total_report = 0, // total number of phages in other_list.txt
        count_phage_master = 0, // total number of phages in phage_list.txt
        count_other_master = 0, // grand total number of comparisons made across all rounds
        count_other_total = 0, // total number of phages in other_list.txt successfully compared in one round
        count_tab_master = 0, // grand total number of tabs opened across all rounds
        count_tab_total = 0, // total number of tabs opened in one round
        count_other = 0; // tracks phages compared in one tab before overflowing to a new tab

    string phage_name, // primary phage that 'other_list.txt' phages will compare to
           url_phages, // the 'other_list.txt' phages that will be compared to the primary phage
           response; // stores user input responses

    while (getline(pha, line))
    {
        istringstream iss_pha(line);
        string phage;
        iss_pha >> phage;
        if (phage.empty())
            continue;
        phage_name = phage;

        ++count_phage_master;

        while (getline(oth, line))
        {
            if (count_other == max_phage)
            {
                string url_master = "https://phagesdb.org/genecontent/compare/?phages=" + phage_name + url_phages;
                system(string("open " + url_master).c_str());
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
            if (other.empty())
                continue;

            url_phages = url_phages + ",%20" + other;

            ++count_other;
            ++count_other_total;
            ++count_other_master;
        }

        string url_master = "https://phagesdb.org/genecontent/compare/?phages=" + phage_name + url_phages;
        system(string("open " + url_master).c_str());

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