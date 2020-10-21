#ifndef GCS_PARSER_H_
#define GCS_PARSER_H_

const int MAX_PHAGE = 40; // number of phages per search
const int MAX_TAB = 5; // tabs opened threshold before warning is triggered
const std::string PHAGE_LIST = "phage_list.txt";
const std::string OTHER_LIST = "other_list.txt";

int automateGCS(int max_phage, bool full_auto = false);

#endif // GCS_PARSER_H_