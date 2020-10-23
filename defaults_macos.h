/*==============================================================
main_macos.cpp : contains main function, handles custom commands
automate_gcs_macos.cpp : contains parsing function
==============================================================*/

#ifndef DEFAULTS_MACOS_H_
#define DEFAULTS_MACOS_H_

#include <string>

const int MAX_PHAGE = 40; // number of phages per search
const int MAX_TAB = 5; // tabs opened threshold before warning is triggered
const std::string PHAGE_LIST = "phage_list.txt";
const std::string OTHER_LIST = "other_list.txt";

int AutomateGCS(int max_phage, bool full_auto = false);

#endif // DEFAULTS_MACOS_H_