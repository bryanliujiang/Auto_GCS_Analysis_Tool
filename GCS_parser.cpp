#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

const int MAX_PHAGE = 40; // number of phages per search
const int MAX_TAB   = 5; // tabs opened threshold before warning is triggered

int automateGCS();

int main()
{
    // Return 0: Success
    // Return 1: Test Run
    // Return -1: Error

    cout << "Welcome to Semi-Auto GCS Analysis Tool (v1.0)!\n\n"
        "Start the program by pressing ENTER or RETURN." << endl;
    cin.ignore();

    return automateGCS();
}

int automateGCS()
{
    string phage_name;
    string response;
    string phage_list = "phage_list.txt";
    string other_list = "other_list.txt";

    cout << "Processing . . ." << endl;

    ifstream pha(phage_list);
    if (!pha)
    {
        cerr << "Data failed to load!" << endl;
        return -1;
    }

    ifstream oth(other_list);
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

    string url_phages;
    int count_phage_master       = 0, // total number of phages in phage_list.txt
        count_other_master       = 0, // grand total number of comparisons made across all rounds
        count_other_total        = 0, // total number of phages in other_list.txt successfully compared in one round
        count_other_total_report = 0, // total number of phages in other_list.txt
        count_other              = 0, // tracks phages compared in one tab before overflowing to a new tab
        count_tab                = 0, // tracks tabs opened for the first round before triggering tab warning
        count_tab_master         = 0, // grand total number of tabs opened across all rounds
        count_tab_total          = 0; // total number of tabs opened in one round

    while (getline(pha, line))
    {
        istringstream iss_pha(line);
        string phage;
        iss_pha >> phage;
        phage_name = phage;

        ++count_phage_master;

        while (getline(oth, line))
        {
            if (count_other == MAX_PHAGE)
            {
                string url_master = "https://phagesdb.org/genecontent/compare/?phages=" + phage_name + url_phages;
                system(std::string("start " + url_master).c_str());
                ++count_tab_master;
                ++count_tab_total;
                ++count_tab;
                url_phages.clear();
                count_other = 0;
                if (count_tab == MAX_TAB)
                {
                    while (true)
                    {
                        cout << MAX_TAB << " tabs have opened, but more phages still need processing. Still continue? (y/n)" << endl;
                        cin >> response;
                        if (response == "Y" || response == "N" || response == "y" || response == "n")
                        {
                            cout << "Processing . . ." << endl;
                            break;
                        }
                        cout << "Invalid input. Valid inputs are either the single letter 'y' (yes) or 'n' (no)." << endl;
                    }
                    if (response == "N" || response == "n")
                    {
                        cout << "User has terminated processing early.\n"
                            "The total number of phages successfully compared to '" << phage_name << "' was " << count_other_total << ".\n"
                            "You may close the program or press ENTER or RETURN to exit." << endl;
                        cin.get();
                        cin.ignore();
                        exit(1);
                    }
                    count_tab = 0;
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

        cout << "The total number of phages successfully compared to '" << phage_name << "' was " << count_other_total << ".\n" 
            "The total number of tabs opened from comparing to '" << phage_name << "' was " << count_tab_total << "." << endl;
        count_other_total_report = count_other_total; // to prevent resetting count during report

        while (true)
        {
            if (count_phage_master == num_phages)
                break;
            cout << "Proceed to the next phage in " << phage_list << " to compare to? (y/n)" << endl;
            cin >> response;
            if (response == "Y" || response == "N" || response == "y" || response == "n")
            {
                cout << "Processing . . ." << endl;
                break;
            }
            cout << "Invalid input. Valid inputs are either the single letter 'y' (yes) or 'n' (no)." << endl;
        }
        if (response == "N" || response == "n")
        {
            cout << "User has terminated processing early.\n"
                "The total number of phages in " << phage_list << " successfully compared to was " << count_phage_master << ".\n"
                "You may close the program or press ENTER or RETURN to exit." << endl;
            cin.get();
            cin.ignore();
            exit(1);
        }

        oth.clear();
        oth.seekg(0, ios::beg);
        url_phages.clear();
        count_other = 0;
        count_other_total = 0;
        count_tab_total = 0;
        count_tab = -9999; // only count tabs during first loop
    }

    cout << "\n=========================================================================="
        "\nProgram was successful!\n\n"
        "The total number of comparisons made from the " << count_other_total_report << " phage(s) in " << other_list << "\nto the "
        << count_phage_master << " phage(s) in " << phage_list << " was " << count_other_master << ".\n\n"
        "The total number of tabs opened was " << count_tab_master << ".\n\n"
        "You may close the program or press ENTER or RETURN to exit." << endl;
    cin.get();
    cin.ignore();

    return 0;
}