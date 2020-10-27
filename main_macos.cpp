/***WARNING FOR MAC USERS*** : For the time being, the program folder MUST be placed on the Desktop 
                              and CANNOT be renamed. If the program folder is not on the Desktop 
                              and/or is renamed, the program will fail to run.                     */

/*============================================ WELCOME ==============================================
This tool was designed to supplement the GCS analysis process. It will help alleviate the manual work 
required to conduct mass comparisons using the 'Explore Gene Content' forms on PhagesDB.org 
(https://phagesdb.org/genecontent/). However, at this time, the user will still have to manually 
extract the GCS output numbers on PhagesDB.org themselves. Tested on Windows and MacOS.
=====================================================================================================

============================================== CAUTION ==============================================
When conducting a large number of phage comparisons, a corresponding large number of tabs in your 
default browser will be opened. A courtesy warning will be triggered if a comparison session exceeds 
five tabs opened. However, after that, no more warnings will be given. It is the user's 
responsibility to check memory usage to ensure nothing crashes.

This program has only been tested on MacOS versions '10.15', '10.14' and '10.13'. However, it should 
run on versions as old as '10.7'. Be sure to email 'bryanjiang@ucla.edu' if there are any problems 
with the program on MacOS versions prior to '10.13'.
=====================================================================================================

============================================ INSTRUCTIONS ===========================================
The only steps the user is responsible for is modifying TWO provided text files ('phage_list.txt' 
and 'other_list.txt'). The user should paste the shorter list of phages in 'phage_list.txt' and the 
longer list of phages in 'other_list.txt'. The reason for this is that a new tab in the browser will 
be opened for each phage in 'phage_list.txt'. After this, launch the program.

Note that the program requires user input each time a new phage in 'phage_list.txt' is compared to 
all the phages in 'other_list.txt' (however, this can be overridden if the user inputs the keyword 
"auto" when the program opens).

Additionally, custom commands can be entered right after the program is launched. Refer to the 
'CUSTOM SETTINGS' section below for valid custom commands.

*MAC USERS ONLY* : For the time being, the program folder MUST be placed on the Desktop and CANNOT 
                   be renamed. If the program folder is not on the Desktop and/or is renamed, the 
                   program will fail to run.

Below is a summary of the inputs and outputs.

INPUTS (what the user will modify):
'other_list.txt': contains the list of phages that will AUTOMATICALLY be compared to one other phage; 
                  if in doubt, paste the LONGER list of phages here

'phage_list.txt': contains the list of phages that all phages from 'other_list.txt' will compare to; 
                  if in doubt, paste the SHORTER list of phages here

OUTPUTS:
'horizontal.txt': contains the phage names from 'other_list.txt', separated by tabs to be immediately 
                  copy-and-paste-able to Excel as the horizontal row for heatmap/table formatting

'vertical.txt': contains the phage names from 'phage_list.txt', each on a new line to be immediately 
                copy-and-paste-able to Excel as the vertical row for heatmap/table formatting

In addition to these output files, tabs will open in the user's default browser with the GCS score 
outputs on PhagesDB.
=====================================================================================================

======================================== TROUBLESHOOTING/FAQs =======================================
Q: My tabs are not loading! I get a 504 Gateway Timeout error.
A: This happened because PhagesDB was not able to process the URL request in time, mostly likely 
   due to there being too many phages being compared in one tab (by default, 40 comparisons are made 
   per tab). Try to refresh the page. After two or three tries if the tabs still do not load, you can 
   change the default number of comparisons made per tab. Refer to the 'CUSTOM SETTINGS' section 
   below on how to do this.

Q: I am getting the "Data failed to load!" error!
A: Be sure the 'phage_list.txt' and 'other_list.txt' files were neither moved away from the program 
   folder NOR renamed. If this was the case, you can create new text files with the same respective 
   names and place them into the program folder. If you are on Mac, be sure the program folder is on 
   the Desktop with its original naming.

Q: I am getting the "Error: OS version incompatibility!" error!
A: If you are on Mac, report this error by emailing 'bryanjiang@ucla.edu' and include your MacOS 
   version in the email. Your version can be found by clicking the Apple Inc. logo in the very top 
   left corner and then clicking 'About This Mac'. If you are on Windows, you downloaded the MacOS 
   version of the program. Be sure to download the Windows version.

Q: I am getting the "Error: OS incompatibility!" error!
A: If you are on Mac, report this error by emailing 'bryanjiang@ucla.edu'. If you are on Windows, 
   you downloaded the MacOS version of the program. Be sure to download the Windows version.

Q: How can I make the program automatically make all the comparisons without my having to make manual 
   inputs for each phage?
A: Enter "auto" (without the quotation marks) when the program first opens. Refer to the 'CUSTOM 
   SETTINGS' section below for other valid custom commands.

Q: I have a problem/question that isn't here!
A: Email me at 'bryanjiang@ucla.edu'.
=====================================================================================================

========================================== CUSTOM SETTINGS ==========================================
The following are valid custom commands that the user can enter upon the program opening. Ignore the 
quotation marks.

[Pressing ENTER or RETURN key] : runs the tool with default settings

"auto" : bypasses the manual confirmation required every time a new phage in 'phage_list.txt' is 
         compared to; also bypasses the warning given when more than five tabs will be opened

"1" : sets the number of phage comparisons per tab to 10 (default is 40)

"2" : sets the number of phage comparisons per tab to 20 (default is 40)

"3" : sets the number of phage comparisons per tab to 30 (default is 40)

"5" : sets the number of phage comparisons per tab to 50, exceeding the default (default is 40)

"max" : *EXPERIMENTAL* removes any limit to the number of phage comparisons per tab; however, a new 
                       tab will still be opened for each phage in 'phage_list.txt'

"auto max" or "max auto" : *EXPERIMENTAL* combines the 'auto' and 'max' commands, essentially 
                                          removing phage comparison and tab limits as well as 
                                          bypassing the need for manual confirmation every time 
                                          a new phage in 'phage_list.txt' is compared to
=====================================================================================================

============================================= RESOURCES =============================================
PhagesDB.org GCS Tool: https://phagesdb.org/genecontent/
Contact Me: email bryanjiang@ucla.edu
Source Code (any suggestions welcome!): https://github.com/bryanliujiang/Auto_GCS_Analysis_Tool
===================================================================================================*/

#include "defaults_macos.h"

#include <iostream>
#include <string>
using namespace std;

int main()
{
    // Return -3: Error: OS version incompatibility
    // Return -2: Error: OS incompatibility
    // Return -1: Error: file extraction failure
    // Return 0: Success: normal termination
    // Return 1: Success: early termination
    // Return 2: Success: debug termination

    string custom;

    cout << "Welcome to Auto GCS for MacOS (v1.0)!\n\n"
        "Instructions and troubleshooting options are in the 'README.txt' file.\n"
        "Start the program by pressing ENTER or RETURN." << endl;

    while (true)
    {
        getline(cin, custom);

        if (custom == "1")
            return AutomateGCS(10);
        else if (custom == "2")
            return AutomateGCS(20);
        else if (custom == "3")
            return AutomateGCS(30);
        else if (custom == "5")
            return AutomateGCS(50);
        else if (custom == "6")
            return AutomateGCS(60);
        else if (custom == "7")
            return AutomateGCS(70);
        else if (custom == "8")
            return AutomateGCS(80);
        else if (custom == "9")
            return AutomateGCS(90);
        else if (custom == "max")
            return AutomateGCS(INT_MAX);
        else if (custom == "auto")
            return AutomateGCS(MAX_PHAGE, true);
        else if (custom == "auto max" || custom == "max auto")
            return AutomateGCS(INT_MAX, true);
        else if (custom == "debug")
            return AutomateGCS(MAX_PHAGE, false, true);
        else
            return AutomateGCS(MAX_PHAGE);
    }
}