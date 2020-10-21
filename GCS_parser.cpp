/*======================================================== WELCOME ==========================================================
This tool was designed to supplement the GCS analysis process. It will help alleviate the manual work required to conduct 
mass comparisons. However, at this time, the user will still have to manually extract the GCS output numbers on PhagesDB 
themselves.
=============================================================================================================================

========================================================== CAUTION ==========================================================
When conducting a large number of phage comparisons, a corresponding large number of tabs in your default browser will be 
opened. A courtesy warning will be triggered if a comparison session exceeds five tabs opened. However, after that, no more 
warnings will be given. It is the user's reponsibility to check memory usage to ensure nothing crashes.
=============================================================================================================================

======================================================== INSTRUCTIONS =======================================================
The only steps the user is responsible for is modifying TWO provided text files ('phage_list.txt' and 'others_list.txt'). The 
user should paste the shorter list of phages in 'phage_list.txt' and the longer list of phages in 'others_list.txt'. The 
reason for this is that the program requires user input each time a new phage in 'phage_list.txt' is compared to all the
phages in 'others_list.txt' (this can be overridden if the user inputs the keyword "auto" when the program opens).

MAC USERS ONLY: The folder containing the program must be stored on the desktop to run correctly.

Below is a summary of the inputs and outputs.

INPUTS (what the user will modify):
'others_list.txt': contains the list of phages that will AUTOMATICALLY be compared to one other phage; if in doubt, paste the
	LONGER list of phages here

'phage_list.txt': contains the list of phages that all phages from 'other_list.txt' will compare to; if in doubt, paste the
	SHORTER list of phages here

OUTPUTS:
'horizontal.txt': contains the phage names from 'phage_list.txt', separated by tabs to be immediately copy-and-paste-able to
	Excel as the horizontal row for heatmap formatting.

'vertical.txt': contains the phage names from 'other_list.txt', each on a new line to be immediately copy-and-paste-able to
	Excel as the vertical row for heatmap formatting.

In addition to these output files, tabs will open in the user's default browser with the GCS score outputs on PhagesDB.
=============================================================================================================================

==================================================== TROUBLESHOOTING/FAQs ===================================================
Q: My tabs are not loading! I get a 504 Gateway Timeout error.
A: This happened because PhagesDB was not able to process the URL request in time, mostly likely due to there being too many 
   phages being compared in one tab (by default, 40 comparisons are made per tab). Try to refresh the page. After two or 
   three tries if the tabs still do not load, you can change the default number of comparisons made per tab. Refer to the 
   'CUSTOM SETTINGS' section of this 'README.txt' file on how to do this.

Q: I am getting the "Data failed to load!" error!
A: If you are on MAC, this is most likely due to the folder containing this program not being on the desktop. Try moving the 
   folder to the desktop and try again. If you are on Windows, try re-downloading the folder containing the program again.

Q: How can I make the program automatically make all the comparisons without my having to make manual inputs for each phage?
A: Enter "auto" (without the quotation marks) when the program first opens. Refer to the 'CUSTOM SETTINGS' section below for 
   other valid custom commands.

Q: I have a problem/question that isn't here!
A: Email me at 'bryanjiang@ucla.edu'.
=============================================================================================================================

====================================================== CUSTOM SETTINGS ======================================================
The following are valid custom commands that the user can enter upon the program opening. Ignore the quotation marks.

[Pressing ENTER or RETURN key] : This runs the tool with default settings.

"auto" : This will bypass the manual input steps required everytime a new phage in 'phage_list.txt' is compared to. This will
         also bypass the warning given when more than five tabs will be opened.

"1" : This will set the number of phage comparisons per tab to 10 (default is 40).

"2" : This will set the number of phage comparisons per tab to 20 (default is 40).

"3" : This will set the number of phage comparisons per tab to 30 (default is 40).

"5" : This will set the number of phage comparisons per tab to 50, exceeding the default (default is 40).
=============================================================================================================================

========================================================= RESOURCES =========================================================
PhagesDB GCS Tool: https://phagesdb.org/genecontent/
Contact Me: bryanjiang@ucla.edu
Source code (any suggestions welcome!): https://github.com/bryanliujiang/Semi-Auto_GCS_Analysis_Tool
===========================================================================================================================*/

#include <iostream>
#include <string>

#include "GCS_parser.h"
using namespace std;

int main()
{
    // Return 0: Success: normal termination
    // Return 1: Success: early termination
    // Return -1: Error

    string custom;

    cout << "Welcome to Semi-Auto GCS Analysis Tool (v1.0)!\n\n"
        "Instructions and troubleshooting options are in the 'README.txt' file.\n"
        "Start the program by pressing ENTER or RETURN." << endl;

    while (true)
    {
        getline(cin, custom);

        if (custom == "1")
            return automateGCS(10);
        else if (custom == "2")
            return automateGCS(20);
        else if (custom == "3")
            return automateGCS(30);
        else if (custom == "5")
            return automateGCS(50);
        else if (custom == "6")
            return automateGCS(60);
        else if (custom == "7")
            return automateGCS(70);
        else if (custom == "8")
            return automateGCS(80);
        else if (custom == "9")
            return automateGCS(90);
        else if (custom == "auto")
            return automateGCS(MAX_PHAGE, true);
        else
            return automateGCS(MAX_PHAGE);
    }
}