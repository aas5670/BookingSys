// Rooms

//////////////////////////////Header\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// Name: w15007083                       Date Created: 02/12/2016 \\
// Fully Tested: Yes                   Date Completed: 12/01/2017 \\
////////////////////////////////|\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

// Include the following libraries

#include <iostream>
#include <fstream>

#include <string>
#include <locale>

#include <vector>

#include <algorithm>
#include <cctype>
#include <iomanip>

// Instead of having to wrtie std::cout you can just write cout

using namespace std;

// Creates a struct with the name SESSIONS
// This will store all the informaiton relating to the sessions
struct SESSIONS
{
  // Creates variables that will be allocated to the struct
  string sName, sRoom;
  int iTime, iSpaces, iID;

  // Creates an operation which will allow for two inputs
  // from the stuct and will return if the iTime is less than
  // the second iTime
  bool operator() (SESSIONS i, SESSIONS j)
  {
    return i.iTime < j.iTime;
  }
};

// Creates a struct with the name CHOSENSESSIONS
// This will store all the informaiton relating to the chosen sessions
struct CHOSENSESSIONS
{
  // Creates variables that will be allocated to the struct
  string sName, sRoom;
  int iTime, iSpaces, iID;

  // Creates an operation which will allow for two inputs
  // from the stuct and will return if the iTime is less than
  // the second iTime
  bool operator() (CHOSENSESSIONS i, CHOSENSESSIONS j)
  {
    return i.iTime < j.iTime;
  }
};

// Creates a struct with the name PACKAGEINFOATTEND
// This will be a sub struct for the stuct PACKAGEINFO
struct PACKAGEINFOATTEND
{
  // Creates two vectors which will be allocated to the struct
  vector<int> vsMustSessions;
  vector<int> vsNullSessions;
  vector<string> vsMustRooms;
  vector<string> vsNullRooms;
};


// Creates a struct with the name PACKAGEINFO
// This will store all the informaiton relating to the chosen sessions
struct PACKAGEINFO
{
  // Creates variables that will be allocated to the struct
  string sName;
  int iNoSessions;
  // Creates a vector of the struct PACKAGEINFOATTEND,
  // this will allow for easy access and storing of 
  // the data contained within the sub struct
  vector<PACKAGEINFOATTEND> vsSessionsMN;
};

// Ensures the the functions that need to be used inside the main code
// can be used in the main code by delcaring them before

void sysStateZero(vector<SESSIONS>& vsSession,
  SESSIONS& stSession, vector<SESSIONS>& vsUnsortedSession,
  int& iCurrentState,
  bool& bSysRun);

void sysStateOne(int& iCurrentState, bool& bSysRun);

void sysStateTwo(int& iCurrentState, bool& bSysRun,
  int& iPackageNo, string& sCustomerName,
  vector<PACKAGEINFO>& vsPackageInfo,
  PACKAGEINFO& stPackageInfo);

void sysStateThree(int& iCurrentState, bool& bSysRun,
  int iPackageNo, CHOSENSESSIONS& stChosenSessions,
  vector<CHOSENSESSIONS>& vsChosenSessions,
  vector<SESSIONS> vsSession,
  vector<PACKAGEINFO> vsPackageInfo);

void sysStateFour(int& iCurrentState, bool& bSysRun,
  vector<CHOSENSESSIONS> vsChosenSessions,
  string sCustomerName, vector<SESSIONS>& vsSession,
  vector<SESSIONS>& vsUnsortedSession);

// Main Code
int main()
{
  // Creates a vector of the struct SESSIONS,
  // this allows for the easy access and easy storing
  // of each individual struct and gives it an name for
  // accessing the name is vsSession
  vector<SESSIONS> vsSession;

  // Creates a vector of the struct SESSIONS,
  // this allows for the easy access and easy storing
  // of each individual struct and gives it an name for
  // accessing the name is vsUnSortedSession
  vector<SESSIONS> vsUnSortedSession;

  // Gives the struct a name, the name is stSession
  SESSIONS stSession;

  // Creates a vector of the struct CHOSENSESSIONS,
  // this allows for the easy access and easy storing
  // of each individual struct and gives it an name for
  // accessing the name is vsChosenSessions
  vector<CHOSENSESSIONS> vsChosenSessions;

  // Gives the struct a name, the name is stChosenSessions
  CHOSENSESSIONS stChosenSessions;

  // Creates a vector of the struct PACKAGEINFO,
  // this allows for the easy access and easy storing
  // of each individual struct and gives it an name for
  // accessing the name is vsPackageInfo
  vector<PACKAGEINFO> vsPackageInfo;

  // Gives the struct a name, the name is stPackageInfo
  PACKAGEINFO stPackageInfo;

  // Ensures the system runs in a loop and only stops
  // if the loop is broken
  bool bSysRun = true;

  // Creates a state to select which code will be ran
  int iCurrentState = 0;

  // Creates a storage for the package numbers and sets it to -1
  int iPackageNo = -1;

  // Ensures that some code is only ran once or after one time
  bool bRanOnce = false;

  // Initialzes the string sCustomerName
  string sCustomerName;

  // While the system is running run the contained code
  while (bSysRun)
  {
    // If the curentstate is 0 run the contained code
    // happens for all if statements
    if (iCurrentState == 0)
    {
      sysStateZero(vsSession, stSession, vsUnSortedSession,
        iCurrentState, bSysRun);
    }
    else if (iCurrentState == 1)
    {
      sysStateOne(iCurrentState, bSysRun);
    }
    else if (iCurrentState == 2)
    {
      // Runs the contained code when bRanOnce is true
      if (bRanOnce)
      {
        // Clears the vector vsPackageInfo of data
        vsPackageInfo.clear();
        // Sets the struct stPackageInfo to contain no data
        stPackageInfo = {};
      }
      sysStateTwo(iCurrentState, bSysRun, iPackageNo, sCustomerName,
        vsPackageInfo, stPackageInfo);
      // When bRanOnce is false
      if (bRanOnce != true)
      {
        // Set bRanOnce to true
        bRanOnce = true;
      }
    }
    else if (iCurrentState == 3)
    {
      // Runs the contained code when bRanOnce is true
      if (bRanOnce)
      {
        // Sets the struct stChosenSessions to contain no data
        stChosenSessions = {};
        // Clears the vector vsChosenSessions of data
        vsChosenSessions.clear();
      }
      sysStateThree(iCurrentState, bSysRun,
        iPackageNo, stChosenSessions,
        vsChosenSessions,
        vsSession,
        vsPackageInfo);
    }
    else if (iCurrentState == 4)
    {
      sysStateFour(iCurrentState, bSysRun, vsChosenSessions,
        sCustomerName, vsSession, vsUnSortedSession);
    }
  }
}

// Need to comment //

int systemNumberOfSpaces(string sInput)
{
  // Counts the number of spaces in the string
  return count(sInput.begin(), sInput.end(), ' ');
}

string systemTransformToupper(string sUserInput)
{
  // Transforms the string to all uppercase and returns the result
  transform(sUserInput.begin(), sUserInput.end(), sUserInput.begin(), toupper);
  return sUserInput;
}

int systemLengthNumber(int iNumber)
{
  // Sets a counter and sets it 0
  int iCounter = 0;

  // While iNumber is valid
  while (iNumber)
  {
    // Divide iNumber by 10
    iNumber = iNumber / 10;
    // Add to the counter
    iCounter++;
  }

  // Return the counter (length of number)
  return iCounter;
}

void systemOutputSpacesNeeded(string sInput, int iInput, int iLengthOfGap)
{
  // Creates the variable iLength and sets it to 0
  int iLength = 0;
  // If iInput equals -1024, which means it is a string
  if (iInput == -1024)
  {
    // Send sInput to the console
    cout << sInput;
    // Set iLength equal to the lengt of gap minus the length of the string
    iLength = iLengthOfGap - sInput.length();
  }
  else
  {
    // Else means it is an int
    // Send Sinput to the console
    cout << iInput;
    // Set iLength to the length of gap minus the length of the number
    iLength = iLengthOfGap - systemLengthNumber(iInput);
  }
  // Loop for all of iLengths
  for (int i = 0; i < iLength; i++)
  {
    // Send spaces to the console
    cout << " ";
  }
}

void systemErrorMessages(string sError)
{
  // System Errors

  // Recieves the error number and sends text to the console relating to
  // that error number
  if (sError == "S01")
  {
    cout << "** System Error Please contact Administrator ERROR: S01"
      "(Unable to open File)" << endl;
  }
  // Recieves the error number and sends text to the console relating to
  // that error number
  if (sError == "S02")
  {
    cout << "** System Error Please contact Administrator ERROR: S02"
      "(Random Error)" << endl;
  }
  // User errors

  // Recieves the error number and sends text to the console relating to
  // that error number
  if (sError == "U01")
  {
    cout << endl << "* Error name must have one space" <<
      endl << "-Enter the name"
      << " of the customer"
      << endl << "|";
  }
  // Recieves the error number and sends text to the console relating to
  // that error number
  if (sError == "U02")
  {
    cout << endl << "* Please enter Y or N" << endl;
    cout << "|";
  }
  // Recieves the error number and sends text to the console relating to
  // that error number
  if (sError == "U03")
  {
    cout << endl << "* Input must be YES" << endl;
    cout << "-Please enter YES" << endl;
    cout << "|";
  }
  // Recieves the error number and sends text to the console relating to
  // that error number
  if (sError == "U04")
  {
    cout << endl << "* Input must be either YES or HELP" << endl;
    cout << "-Please enter YES or HELP" << endl;
    cout << "|";
  }
  // Recieves the error number and sends text to the console relating to
  // that error number
  if (sError == "U05")
  {
    cout << endl << "* Input must be in the list of package names" << endl;
    cout << "-Please enter the package name" << endl;
    cout << "|";
  }
  // Recieves the error number and sends text to the console relating to
  // that error number
  if (sError == "U06")
  {
    cout << endl << "* Cannot attend two sessions with the same name";
    cout << "-Please enter a new session ID" << endl;
    cout << "|";
  }
  // Recieves the error number and sends text to the console relating to
  // that error number
  if (sError == "U07")
  {
    cout << endl << "* Cannot attend two sessions at the same time";
    cout << "-Please enter a new session ID" << endl;
    cout << "|";
  }
  // Recieves the error number and sends text to the console relating to
  // that error number
  if (sError == "U08")
  {
    cout << endl << "* Cannot attend exactly the same session";
    cout << "-Please enter a new session ID" << endl;
    cout << "|";
  }
  // Recieves the error number and sends text to the console relating to
  // that error number
  if (sError == "U09")
  {
    cout << endl << "* Session ID not valid, must enter a session ID in"
      "the list";
    cout << "-Please enter a new session ID" << endl;
    cout << "|";
  }
  // Recieves the error number and sends text to the console relating to
  // that error number
  if (sError == "U10")
  {
    cout << endl << "* Error please enter an interger value" << endl;
    cout << "-Please enter a new session ID" << endl
      << "|";
  }
  // Recieves the error number and sends text to the console relating to
  // that error number
  if (sError == "U11")
  {
    cout << endl << "* Input must be CONFIRM or RESET" << endl;
    cout << "-Please CONFIRM the selection or RESET to start again" << endl
      << "|";
  }
  // Recieves the error number and sends text to the console relating to
  // that error number
  if (sError == "U12")
  {
    cout << endl << "* Cannot attend a package with 0 spaces" << endl;
    cout << "-Please enter a new session ID" << endl;
    cout << "|";
  }
  // Recieves the error number and sends text to the console relating to
  // that error number
  if (sError == "U13")
  {
    cout << endl << "* Session is not allowed for selected package" << endl;
    cout << "-Please enter a new session ID" << endl;
    cout << "|";
  }
  // Recieves the error number and sends text to the console relating to
  // that error number
  if (sError == "U14")
  {
    cout << endl << "* Session cannot be in this room due to package choice"
      << endl;
    cout << "-Please enter a new session ID" << endl;
    cout << "|";
  }
}

void systemInformationMessage()
{
  cout << "~Welcome to the conference session booking system" << endl << endl;
}

void systemHelpfulInformation()
{
  cout << endl << "~This is a list of all the helpful information"
    " that you will need" << endl << endl
    << "~All inputs can be entered in uppercase, lowercase or with the first"
    << " letter capitalised" << endl << endl
    << "~Here are a list of keywords that will be useful to you" << endl
    << "~You can type in the keywords at anypoint in the system" << endl << endl
    << "KEYWORD   USE" << endl
    << "-------   ---" << endl
    << "RESET     Start back at the customers name" << endl
    << "EXIT      Exit the booking system" << endl
    << "HELP      Will display all relevant helpful information" << endl
    << endl
    << "~Here are a list of symbols that will be useful to you" << endl << endl
    << "SYMBOL    MEANING" << endl
    << "------    -------" << endl
    << "~         General information" << endl
    << "?         Information on the requirements of the input" << endl
    << "-         Telling you what is required for the input" << endl
    << "|         Asking you for an input" << endl
    << "*         User Error will tell you what error has been made" << endl
    << "**        System error will tell you what error and to contact admin"
    << endl
    << endl;
}

bool systemIsNumber(const string& s)
{
  return !s.empty() && find_if(s.begin(),
    s.end(), [](char c) { return !isdigit(c); }) == s.end();
}

void systemListPackages(vector<PACKAGEINFO> vsPackageInfo)
{
  cout << endl << endl << "~List of avaliable packages" << endl;
  systemOutputSpacesNeeded("NAME", -1024, 20);
  systemOutputSpacesNeeded("NO SESSSIONS", -1024, 20);
  systemOutputSpacesNeeded("MUST ATTEND ID", -1024, 20);
  cout << "CANT ATTEND ID" << endl;

  for (int q = 0; q < vsPackageInfo.size(); q++)
  {
    systemOutputSpacesNeeded(vsPackageInfo[q].sName, -1024, 20);
    systemOutputSpacesNeeded("", vsPackageInfo[q].iNoSessions, 20);

    for (int b = 0; b < vsPackageInfo[q].vsSessionsMN[q].vsMustSessions.size(); b++)
    {
      if (vsPackageInfo[q].vsSessionsMN[q].vsMustSessions[b] == -1)
      {
        systemOutputSpacesNeeded("None", -1024, 20);
      }
      else
      {
        systemOutputSpacesNeeded("", vsPackageInfo[q].vsSessionsMN[q].vsMustSessions[b], 20);
      }
    }

    for (int c = 0; c < vsPackageInfo[q].vsSessionsMN[q].vsNullSessions.size(); c++)
    {
      if (vsPackageInfo[q].vsSessionsMN[q].vsNullSessions[c] == -1)
      {
        systemOutputSpacesNeeded("None", -1024, 20);
      }
      else
      {
        systemOutputSpacesNeeded("", vsPackageInfo[q].vsSessionsMN[q].vsNullSessions[c], 20);
      }
    }

    cout << endl;
  }
}

int systemListSessionsCheckMustNull(vector<PACKAGEINFO> vsPackageInfo,
  int iSessionID, int iPackageNo)
{
  for (int i = 0; i < vsPackageInfo[iPackageNo].vsSessionsMN[iPackageNo].vsNullSessions.size(); i++)
  {
    if (iSessionID == vsPackageInfo[iPackageNo].vsSessionsMN[iPackageNo].vsNullSessions[i])
    {
      return 1;
    }
  }
  return 0;
}

int systemListSessionsCheckMust(vector<PACKAGEINFO> vsPackageInfo,
  int iSessionID, int iPackageNo)
{
  for (int i = 0; i < vsPackageInfo[iPackageNo].vsSessionsMN[iPackageNo].vsMustSessions.size(); i++)
  {
    if (iSessionID == vsPackageInfo[iPackageNo].vsSessionsMN[iPackageNo].vsMustSessions[i])
    {
      return 1;
    }
  }
  return 0;
}

void systemListSessions(vector<SESSIONS> vsSession,
  vector<PACKAGEINFO> vsPackageInfo,
  int iPackageNo, vector<int> viSesssionIDRemoved)
{
  cout << endl << "~List of available Sessions" << endl;
  systemOutputSpacesNeeded("NAME", -1024, 20);
  systemOutputSpacesNeeded("TIME", -1024, 6);
  systemOutputSpacesNeeded("SPACES", -1024, 8);
  systemOutputSpacesNeeded("ROOM", -1024, 6);
  cout << "ID" << endl;

  vector<int> viIDsNeedToBeRemoved;

  bool bRunOnce = true;

  for (int i = 0; i < vsSession.size(); i++)
  {
    if (vsSession[i].iSpaces > 0)
    {
      if (systemListSessionsCheckMustNull(vsPackageInfo, vsSession[i].iID,
        iPackageNo) != 1)
      {
        if (systemListSessionsCheckMust(vsPackageInfo, vsSession[i].iID,
          iPackageNo) != 1)
        {
          systemOutputSpacesNeeded(vsSession[i].sName, -1024, 20);
          systemOutputSpacesNeeded("", vsSession[i].iTime, 6);
          systemOutputSpacesNeeded("", vsSession[i].iSpaces, 8);
          systemOutputSpacesNeeded(vsSession[i].sRoom, -1024, 6);
          cout << vsSession[i].iID << endl;
        }
      }
    }
  }

  cout << endl;
}

int systemStateGeneralFuncs(string stndString,
  int& iCurrentState, bool& bSysRun,
  int& iCurrentSubState)
{
  // This whole function will contain keywords which
  // can be entered at anypoint in the system
  // Each keyword has code assoicated with it which will
  // run if the keyword has been activated
  // if a keyword has not been activated it will just return 0
  stndString = systemTransformToupper(stndString);

  if (stndString == "RESET")
  {
    if (iCurrentState == 2 || iCurrentState == 3)
    {
      bool bUserCheck = true;

      cout << endl <<
        "Are you sure you want to start back at the customers name? Enter Y or N"
        << endl << "|";

      string sUserInput;
      getline(cin, sUserInput);

      // Changes the string to all uppercase
      sUserInput = systemTransformToupper(sUserInput);

      while (bUserCheck)
      {
        if (sUserInput == "Y" || sUserInput == "YES")
        {
          iCurrentSubState = 0;
          iCurrentState = 2;
          bUserCheck = false;
          return 1;
        }
        else if (sUserInput == "N" || sUserInput == "NO")
        {
          bUserCheck = false;
          return 2;
        }
        else
        {
          systemErrorMessages("U02");
          getline(cin, sUserInput);
          // Changes the string to all uppercase
          sUserInput = systemTransformToupper(sUserInput);
        }
      }
    }
  }

  if (stndString == "EXIT")
  {
    bool bUserCheck = true;

    cout << endl << "Are you sure you want to EXIT? Enter Y or N" << endl;
    cout << "|";

    string sUserInput;
    getline(cin, sUserInput);

    // Changes the string to all uppercase
    sUserInput = systemTransformToupper(sUserInput);

    while (bUserCheck)
    {
      if (sUserInput == "Y" || sUserInput == "YES")
      {
        bSysRun = false;
        bUserCheck = false;
        return 1;
      }
      else if (sUserInput == "N" || sUserInput == "NO")
      {
        bUserCheck = false;
        return 2;
      }
      else
      {
        systemErrorMessages("U02");
        getline(cin, sUserInput);
        // Changes the string to all uppercase
        sUserInput = systemTransformToupper(sUserInput);
      }
    }
  }

  if (stndString == "HELP")
  {
    if (iCurrentState != 1){
      systemHelpfulInformation();

      cout << endl << "-When you want to continue type YES" << endl;
      cout << "|";

      string sUserInput;
      getline(cin, sUserInput);

      bool bUserCheck = true;
      while (bUserCheck)
      {
        int iSysCheck = systemStateGeneralFuncs(sUserInput,
          iCurrentState, bSysRun, iCurrentSubState);

        if (iSysCheck == 1)
        {
          bUserCheck = false;
          return 1;
        }
        else
        {
          sUserInput = systemTransformToupper(sUserInput);
          if (sUserInput == "YES")
          {
            bUserCheck = false;
            return 2;
          }
          else
          {
            if (iSysCheck == 2)
            {
              cout << endl << endl << "-When you want to continue type YES" << endl;
              cout << "|";
            }
            else if (iSysCheck == 0)
            {
              systemErrorMessages("U03");
            }
            getline(cin, sUserInput);
            sUserInput = systemTransformToupper(sUserInput);
          }
        }
      }
    }
  }

  return 0;
}

// End of need to comment //

void sysStateZero(vector<SESSIONS>& vsSession,
  SESSIONS& stSession, vector<SESSIONS>& vsUnsortedSession,
  int& iCurrentState,
  bool& bSysRun)
{
  /*------------------------------------------------------------
  function: sysStateZeroLoadFile(vector<SESSIONS>& vsSession,
  SESSIONS& stSession, int& iCurrentState,
  bool& bSysRun)
  created: 05 / 01 / 2017
  author: w15007083
  tested: Yes
  description: This function will load the file sessions, when
  the file is loaded the function will go through each line
  and store each individual column (or piece of data) in a
  struct then it will push each indiudal struct into a vector
  which will then store every struct that has been created*
  parameters: All paramenters are being passed by reference
  which means that when the value is changed it wil be changed
  at its original location
  ------------------------------------------------------------*/

  // Sets the file length as -1 in order to make the file length
  // start at 0
  int iFileLength = -1;

  //Associates the read stream with sesfile
  ifstream sesfile;

  // Opens the file "sessions.txt"
  sesfile.open("sessionrooms.txt");

  // Checks if the file is open then will run
  // the contained code
  if (sesfile.is_open())
  {
    // While there is still data to be stored in the struct run
    // the contained code. The >> inidcated to move onto the next
    // column and to store the data from the sesfile into the struct
    while (sesfile >> stSession.sName >> stSession.iTime
      >> stSession.iSpaces >> stSession.sRoom)
    {
      // Adds one onto the file length
      iFileLength += 1;

      // Uses the file length to set the ID for each struct
      // Note* This is not the best way to set an ID as it 
      // is technically a temporay ID but cannot do any other
      // way since the data in the file cannot be changed
      stSession.iID = iFileLength;

      // Stores the complete struct into the vector vsSession
      // the push_back is son it adds it onto the end of the 
      // vector
      vsUnsortedSession.push_back(stSession);
      vsSession.push_back(stSession);
    }

    // Closes the file
    sesfile.close();

    // Sorts the vsSession vector by the function in stSession
    // In other words sorts all the sessions in ascending time
    sort(vsSession.begin(), vsSession.end(), stSession);
    cout << "Loop";
    iCurrentState = 1;
  }
  else
  {
    // Displays relevant error messages and stops the system
    systemErrorMessages("S01");
    bSysRun = false;
  }
}

void sysStateOneSubStateOne(int& iCurrentSubState,
  int& iCurrentState, bool& bSysRun)
{
  /*------------------------------------------------------------
  function: sysStateOneSubStateOne(int& iCurrentSubState,
  int& iCurrentState, bool& bSysRun)
  created: 05 / 01 / 2017
  author: w15007083
  tested: Yes
  description: This function will determine if the user wants to
  start the booking system or wants to read the help shet
  parameters: All paramenters are being passed by reference
  which means that when the value is changed it wil be changed
  at its original location
  ------------------------------------------------------------*/

  // Sets the check for the user input to true
  bool bUserCheck = true;

  // Asks the user if they want to start or read the help sheet
  cout << "-Do you want to start or read the help sheet? (Start/Help)" << endl;
  cout << "|";

  // Assigns the user input to a string
  string sUserCheck;
  // Asks the user for an input
  getline(cin, sUserCheck);

  // Changes the string to all uppercase
  sUserCheck = systemTransformToupper(sUserCheck);

  // While the check for the user input is true run the contained code
  while (bUserCheck)
  {
    // Set the return value from the function (which checks if the user has
    // entered a keyword which will stall the programme) to a variable
    int iSysCheck = systemStateGeneralFuncs(sUserCheck,
      iCurrentState, bSysRun, iCurrentSubState);
    // If the user has entered a keyword it will stop the user check
    if (iSysCheck == 1)
    {
      // Stops the user check
      bUserCheck = false;
    }
    else
    {
      // Checks if the user has inputted Start
      if (sUserCheck == "START")
      {
        // Changes the current state to 2
        iCurrentState = 2;
        // Stops the user check
        bUserCheck = false;
      }
      // Checks if the user has inputted Help
      else if (sUserCheck == "HELP")
      {
        // Changes the current state to 2
        iCurrentSubState = 2;
        // Stops the user check
        bUserCheck = false;
      }
      else
      {
        // Checks if the user is returning from the general function
        // statements 
        if (iSysCheck == 2)
        {
          // Asks the user if they want to start or read the help sheet
          cout << endl
            << "-Do you want to start or read the help sheet? (Start/Help)"
            << endl;
          cout << "|";
        }
        else if (iSysCheck = 0)
        {
          // Prints out a error message
          systemErrorMessages("U04");
        }
        // Asks the user for another input
        getline(cin, sUserCheck);
        // Changes the string to all uppercase
        sUserCheck = systemTransformToupper(sUserCheck);
      }
    }
  }
}

void sysStateOneSubStateTwo(int& iCurrentSubState,
  int& iCurrentState, bool& bSysRun)
{
  /*------------------------------------------------------------
  function: sysStateOneSubStateTwo(int& iCurrentSubState,
  int& iCurrentState, bool& bSysRun)
  created: 05 / 01 / 2017
  author: w15007083
  tested: Yes
  description: This will only be ran when the user wants to
  open the help page, it will then ask the user to type in YES
  when they want to start the main programme
  parameters: All paramenters are being passed by reference
  which means that when the value is changed it wil be changed
  at its original location
  ------------------------------------------------------------*/

  // Sets the check for the user input to true
  bool bUserCheck = true;

  // Calls the helpful information text
  systemHelpfulInformation();

  // Asks the user to type YES when they want to start
  cout << endl << "-When you want to start type YES" << endl << "|";

  // Assigns the user input to a string
  string sUserCheck;
  // Asks the user for an input
  getline(cin, sUserCheck);

  // Changes the string to all uppercase
  sUserCheck = systemTransformToupper(sUserCheck);

  // While the check for the user input is true run the contained code
  while (bUserCheck)
  {
    // Set the return value from the function (which checks if the user has
    // entered a keyword which will stall the programme) to a variable
    int iSysCheck = systemStateGeneralFuncs(sUserCheck,
      iCurrentState, bSysRun, iCurrentSubState);
    // If the user has entered a keyword it will stop the user check
    if (iSysCheck == 1)
    {
      // Stops the user check
      bUserCheck = false;
    }
    else
    {
      // Checks if the user has inputted YES
      if (sUserCheck == "YES" || sUserCheck == "Yes" || sUserCheck == "yes")
      {
        // Changes the current state to two
        iCurrentState = 2;
        // Stops the user check
        bUserCheck = false;
      }
      else
      {
        // Checks if the user is returning from the general function
        // statements 
        if (iSysCheck == 2)
        {
          // Asks the user to type YES when they want to start
          cout << endl << "-When you want to start type YES" << endl << "|";
        }
        else if (iSysCheck = 0)
        {
          // Print out an error message
          systemErrorMessages("U03");
        }
        // Ask the user for a new input
        getline(cin, sUserCheck);
        // Changes the string to all uppercase
        sUserCheck = systemTransformToupper(sUserCheck);
      }
    }
  }
}

void sysStateOne(int& iCurrentState, bool& bSysRun)
{
  /*------------------------------------------------------------
  function: sysStateOne(int& iCurrentState, bool& bSysRun)
  created: 05 / 01 / 2017
  author: w15007083
  tested: Yes
  description: Controls which sub states need to be ran,
  initally only sub state one is ran and if substate two needs
  to be ran it will run
  parameters: All paramenters are being passed by reference
  which means that when the value is changed it wil be changed
  at its original location
  ------------------------------------------------------------*/

  // Sets the inital sub state as 1
  int iCurrentSubState = 1;

  // If the sub state is one calls the sub state one function
  if (iCurrentSubState == 1)
  {
    sysStateOneSubStateOne(iCurrentSubState, iCurrentState, bSysRun);
  }
  // If the sub state is two calls the sub state two function
  if (iCurrentSubState == 2)
  {
    sysStateOneSubStateTwo(iCurrentSubState, iCurrentState, bSysRun);
  }
}

// System State Two // Need to comment //

void sysStateTwoSubStateZero(vector<PACKAGEINFO>& vsPackageInfo,
  PACKAGEINFO& stPackageInfo, int& iCurrentSubState)
{
  /*------------------------------------------------------------
  function: sysStateTwoSubStateZero(vector<PACKAGEINFO>&
  vsPackageInfo,
  PACKAGEINFO& stPackageInfo, int& iCurrentSubState)
  created: 05 / 01 / 2017
  author: w15007083
  tested: Yes
  description:
  parameters: All paramenters are being passed by reference
  which means that when the value is changed it wil be changed
  at its original location
  ------------------------------------------------------------*/

  vector<PACKAGEINFOATTEND> vsPackageAttend;
  PACKAGEINFOATTEND stPackageAttend;

  // Load Package Info
  int iPackageNumber = 0;



  if (iPackageNumber == 0)
  {
    stPackageInfo.sName = "STANDARD";
    stPackageInfo.iNoSessions = 4;
    stPackageAttend.vsMustSessions.push_back(-1);
    stPackageAttend.vsNullSessions.push_back(0);
    stPackageAttend.vsMustRooms.push_back("Null");
    stPackageAttend.vsNullRooms.push_back("D");
    stPackageInfo.vsSessionsMN.push_back(stPackageAttend);
    vsPackageInfo.push_back(stPackageInfo);

    iPackageNumber += 1;
  }
  if (iPackageNumber == 1)
  {
    vsPackageAttend.clear();
    stPackageAttend = {};
    stPackageInfo.sName = "GOLD";
    stPackageInfo.iNoSessions = 6;
    stPackageAttend.vsMustSessions.push_back(0);
    stPackageAttend.vsNullSessions.push_back(-1);
    stPackageAttend.vsMustRooms.push_back("D");
    stPackageAttend.vsNullRooms.push_back("Null");
    stPackageInfo.vsSessionsMN.push_back(stPackageAttend);
    vsPackageInfo.push_back(stPackageInfo);
  }

  iCurrentSubState = 1;
}

void sysStateTwoSubStateOne(string& sCustomerName, int& iCurrentState,
  int& iCurrentSubState, bool& bSysRun)
{

  cout << endl << "~Booking system started" << endl
    << endl
    << "-Enter the name of the customer below" << endl
    << "?Customer name must be in the format:" <<
    " forename SPACE surname e.g. Fred Miller"
    << endl;
  cout << "|";

  bool bUserCheck = true;

  string sUserInput;
  getline(cin, sUserInput);


  while (bUserCheck)
  {
    int iSysCheck = systemStateGeneralFuncs(sUserInput,
      iCurrentState, bSysRun, iCurrentSubState);
    if (iSysCheck == 1)
    {
      // Stops the user check
      bUserCheck = false;
    }
    else
    {
      if (systemNumberOfSpaces(sUserInput) == 1)
      {
        cout << "UserInput: " << sUserInput;
        sCustomerName = sUserInput;
        iCurrentSubState = 2;
        bUserCheck = false;
      }
      else
      {
        if (iSysCheck == 2)
        {
          cout << endl << endl
            << "-Enter the name of the customer below" << endl
            << "?Customer name must be in the format:" <<
            " forename SPACE surname e.g. Fred Miller"
            << endl << "|";
        }
        else if (iSysCheck == 0)
        {
          systemErrorMessages("U01");
        }
        getline(cin, sUserInput);
      }
    }
  }
}

void sysStateTwoSubStateTwo(vector<PACKAGEINFO> vsPackageInfo,
  int& iCurrentSubState)
{
  systemListPackages(vsPackageInfo);
  iCurrentSubState = 3;
}

void sysStateTwoSubStateThree(int& iCurrentState, bool& bSysRun,
  vector<PACKAGEINFO> vsPackageInfo, int& iPackageNo,
  int& iCurrentSubState)
{
  cout << endl << "-Enter the name of the package:" << endl << "|";

  string sUserInput;
  getline(cin, sUserInput);

  // Changes the string to all uppercase
  sUserInput = systemTransformToupper(sUserInput);

  bool bUserCheck = true;

  while (bUserCheck)
  {
    int iSysCheck = systemStateGeneralFuncs(sUserInput,
      iCurrentState, bSysRun, iCurrentSubState);
    if (iSysCheck == 1)
    {
      // Stops the user check
      bUserCheck = false;
    }
    else
    {
      sUserInput = systemTransformToupper(sUserInput);

      for (int i = 0; i < vsPackageInfo.size(); i++)
      {
        if (vsPackageInfo[i].sName == sUserInput)
        {
          cout << endl << "~You have chosen the " <<
            sUserInput << " package" << endl;
          iPackageNo = i;
          cout << "iPACKAGENO: " << iPackageNo;
          iCurrentState = 3;
          bUserCheck = false;
        }
      }

      if (iPackageNo == -1)
      {
        if (iSysCheck == 2)
        {
          systemListPackages(vsPackageInfo);
          cout << endl << "-Enter the name of the package:" << endl << "|";
        }
        else if (iSysCheck == 0)
        {
          systemErrorMessages("U05");
        }

        getline(cin, sUserInput);
        // Changes the string to all uppercase
        sUserInput = systemTransformToupper(sUserInput);
      }
    }
  }
}

void sysStateTwo(int& iCurrentState, bool& bSysRun,
  int& iPackageNo, string& sCustomerName,
  vector<PACKAGEINFO>& vsPackageInfo,
  PACKAGEINFO& stPackageInfo)
{
  int iCurrentSubState = 0;

  if (iCurrentSubState == 0)
  {
    sysStateTwoSubStateZero(vsPackageInfo,
      stPackageInfo, iCurrentSubState);
  }
  if (iCurrentSubState == 1)
  {
    sysStateTwoSubStateOne(sCustomerName, iCurrentState, iCurrentSubState, bSysRun);
  }
  if (iCurrentSubState == 2)
  {
    sysStateTwoSubStateTwo(vsPackageInfo, iCurrentSubState);
  }
  if (iCurrentSubState == 3)
  {
    sysStateTwoSubStateThree(iCurrentState, bSysRun, vsPackageInfo,
      iPackageNo, iCurrentSubState);
  }
}

// End of system state two // End of Need to comment //

// System State Three //

void sysStateThreeSubStateOne(int& iCurrentSubState,
  vector<SESSIONS> vsSession,
  vector<PACKAGEINFO> vsPackageInfo,
  int iPackageNo, vector<int> viSesssionIDRemoved)
{
  // Calls the function systemListSessions and passes through needed variables
  systemListSessions(vsSession, vsPackageInfo, iPackageNo,
    viSesssionIDRemoved);
  // Changes the substate to one
  iCurrentSubState = 1;
}

string sysStateThreeSubStateTwoSessionAskInput(int iAskNumber)
{
  // If the iAskNumber is equal to the number set
  // return the string relating if not return a blank string
  if (iAskNumber == 0)
  {
    return " first ";
  }
  else if (iAskNumber == 1)
  {
    return " second ";
  }
  else if (iAskNumber == 2)
  {
    return " third ";
  }
  else if (iAskNumber == 3)
  {
    return " fourth ";
  }
  else if (iAskNumber == 4)
  {
    return " fifth ";
  }
  else if (iAskNumber == 5)
  {
    return " sixth ";
  }
  return "";
}

void sysStateThreeSubStateTwoSessCheckSessionErrorNo(
  int& iErrorNumber,
  int iErrorChange)
{
  // If the error numbers are 1 and 2 return the errornumber 3
  if (iErrorNumber == 1 && iErrorNumber == 2)
  {
    iErrorNumber = 3;
  }
  // Else return the normal error number
  else
  {
    iErrorNumber = iErrorChange;
  }
}

void sysStateThreeSubStateTwoSessCheckSesssionNames(
  vector<CHOSENSESSIONS> vsChosenSessions,
  vector<SESSIONS> vsSession,
  int iInputID,
  int& iErrorNumber)
{
  // Loop through the chosen sessions
  for (int i = 0; i < vsChosenSessions.size(); i++)
  {
    // Loop through the normal sessions
    for (int q = 0; q < vsSession.size(); q++)
    {
      // if the session ID is equal to the input ID
      if (vsSession[q].iID == iInputID)
      {
        // If the chosen session name is equal to the session
        // name
        if (vsChosenSessions[i].sName == vsSession[q].sName)
        {
          // Call the error function
          sysStateThreeSubStateTwoSessCheckSessionErrorNo(iErrorNumber, 1);
        }
      }
    }
  }
}

void sysStateThreeSubStateTwoSessCheckSessionTimes(
  vector<CHOSENSESSIONS> vsChosenSessions,
  vector<SESSIONS> vsSession,
  int iInputID,
  int& iErrorNumber)
{
  // Loop through the chosen sessions
  for (int q = 0; q < vsChosenSessions.size(); q++)
  {
    // Loop through the normal sessions
    for (int i = 0; i < vsSession.size(); i++)
    {
      // if the session ID is equal to the input ID
      if (vsSession[i].iID == iInputID)
      {
        // If the chosen session time is equal to the session
        // time
        if (vsChosenSessions[q].iTime == vsSession[i].iTime)
        {
          // Call the error function
          sysStateThreeSubStateTwoSessCheckSessionErrorNo(iErrorNumber, 2);
        }
      }
    }
  }
}

void sysStateThreeSubStateTwoSessCheckSessionIDRange(
  vector<SESSIONS> vsSession,
  int iInputID,
  int& iErrorNumber)
{
  // Declare the bool bolFoundID and set it ot false
  bool bolFoundID = false;

  // Loop through all the sessions
  for (int z = 0; z < vsSession.size(); z++)
  {
    // If the sesssion ID is equal to the input ID
    if (vsSession[z].iID == iInputID)
    {
      // Set bolFoundID to true
      bolFoundID = true;
    }
  }

  // If bolFoundID is false
  if (bolFoundID == false)
  {
    // Call the error function
    sysStateThreeSubStateTwoSessCheckSessionErrorNo(iErrorNumber, 4);
  }
}

void sysStateThreeSubStateTwoSessionCheckZero(int iSessionID,
  int& iErrorNumber)
{
  // If the session ID is less than one
  if (iSessionID < 1)
  {
    // Call the error function
    sysStateThreeSubStateTwoSessCheckSessionErrorNo(iErrorNumber, 5);
  }
}


void sysStateThreeSubStateTwoSessionCheckPackage(int iSessionID,
  int& iErrorNumber, int iPackageNo, vector<PACKAGEINFO> vsPackageInfo,
  vector<SESSIONS> vsSession)
{
  // Initalises a bool variable called bFirstFind and sets it to false
  bool bFirstFind = false;

  // Loops for how many sessions there are
  for (int q = 0; q < vsSession.size(); q++)
  {
    // if the bFirstFind is false
    if (bFirstFind == false)
    {
      // Check if the vsSession[q].iID q being the number the loop is currently
      // at, .iID being the data that is stored in the sturct located at the
      // the number q. Is equal to the session ID
      if (vsSession[q].iID == iSessionID)
      {
        // Set the session ID to where the session ID is located in the vector
        iSessionID = q;
        // Set bFirstFind to true so the session ID doesnt change
        bFirstFind = true;
      }
    }
  }

  // Gets all the sessions that the select package cannot use and loops
  // for how many sessions there are, getting all the sessions that the 
  // selected package cannot use
  for (int i = 0; i < vsPackageInfo[iPackageNo].vsSessionsMN[iPackageNo].
    vsNullSessions.size(); i++)
  {
    // Checks if the selected session ID is equal to any of the sesssions
    // that the package cannot use
    if (vsSession[iSessionID].iTime == vsPackageInfo[iPackageNo].
      vsSessionsMN[iPackageNo].vsNullSessions[i])
    {
      // Calls the function to check the error number against previous
      // error numbers to avoid duplicates
      sysStateThreeSubStateTwoSessCheckSessionErrorNo(iErrorNumber, 6);
    }
  }
}

void sysStateThreeSubStateTwoSessionCheckRoom(int iSessionID,
  int& iErrorNumber, int iPackageNo, vector<PACKAGEINFO> vsPackageInfo,
  vector<SESSIONS> vsSession)
{

  // Initalises a bool variable called bFirstFind and sets it to false
  bool bFirstFind = false;

  // Loops for how many sessions there are
  for (int q = 0; q < vsSession.size(); q++)
  {
    // if the bFirstFind is false
    if (bFirstFind == false)
    {
      // Check if the vsSession[q].iID q being the number the loop is currently
      // at, .iID being the data that is stored in the sturct located at the
      // the number q. Is equal to the session ID
      if (vsSession[q].iID == iSessionID)
      {
        // Set the session ID to where the session ID is located in the vector
        iSessionID = q;
        // Set bFirstFind to true so the session ID doesnt change
        bFirstFind = true;
      }
    }
  }

  // Gets all the rooms that the select package cannot use and loops
  // for how many rooms there are, getting all the rooms that the 
  // selected package cannot use
  for (int i = 0; i < vsPackageInfo[iPackageNo].
    vsSessionsMN[iPackageNo].vsNullRooms.size(); i++)
  {
    // Checks if the selected session ID is equal to any of the rooms
    // that the package cannot use
    if (vsSession[iSessionID].sRoom ==
      vsPackageInfo[iPackageNo].vsSessionsMN[iPackageNo].vsNullRooms[i])
    {
      // Calls the function to check the error number against previous
      // error numbers to avoid duplicates
      sysStateThreeSubStateTwoSessCheckSessionErrorNo(iErrorNumber, 7);
    }
  }
}

int sysStateThreeSubStateTwoSessionCheckSession(int iSessionID,
  int iPackageNo,
  vector<CHOSENSESSIONS> vsChosenSessions,
  vector<SESSIONS> vsSession,
  vector<PACKAGEINFO> vsPackageInfo)
{
  // Initalises and gives the error number a value
  int iErrorNumber = 0;

  // Calls the function to check the session ID against the specific rule
  sysStateThreeSubStateTwoSessCheckSesssionNames(vsChosenSessions,
    vsSession, iSessionID, iErrorNumber);

  // Calls the function to check the session ID against the specific rule
  sysStateThreeSubStateTwoSessCheckSessionTimes(vsChosenSessions,
    vsSession, iSessionID, iErrorNumber);

  // Calls the function to check the session ID against the specific rule
  sysStateThreeSubStateTwoSessCheckSessionIDRange(vsSession,
    iSessionID, iErrorNumber);

  // Calls the function to check the session ID against the specific rule
  sysStateThreeSubStateTwoSessionCheckZero(iSessionID, iErrorNumber);

  // Calls the function to check the session ID against the specific rule
  sysStateThreeSubStateTwoSessionCheckPackage(iSessionID,
    iErrorNumber, iPackageNo, vsPackageInfo, vsSession);

  // Calls the function to check the session ID against the specific rule
  sysStateThreeSubStateTwoSessionCheckRoom(iSessionID,
    iErrorNumber, iPackageNo, vsPackageInfo,
    vsSession);

  // Returns the error number 
  return iErrorNumber;
}

void sysStateThreeSubStateTwoSessionErrors(int iErrorNumber)
{
  // If the error number is equal to the number
  // Pass the relevant error message number to the function
  if (iErrorNumber == 1)
  {
    systemErrorMessages("U06");
  }
  if (iErrorNumber == 2)
  {
    systemErrorMessages("U07");
  }
  if (iErrorNumber == 3)
  {
    systemErrorMessages("U08");
  }
  if (iErrorNumber == 4)
  {
    systemErrorMessages("U09");
  }
  if (iErrorNumber == 5)
  {
    systemErrorMessages("U12");
  }
  if (iErrorNumber == 6)
  {
    systemErrorMessages("U13");
  }
  if (iErrorNumber == 7)
  {
    systemErrorMessages("U14");
  }
}

void sysStateThreeSubStateTwoStoreSession(int iSessionID,
  vector<SESSIONS> vsSession,
  CHOSENSESSIONS& stChosenSessions,
  vector<CHOSENSESSIONS>& vsChosenSessions)
{
  // Loops through the number of sesisons
  for (int a = 0; a < vsSession.size(); a++)
  {
    // If the session ID is equal to the user session ID
    if (vsSession[a].iID == iSessionID)
    {
      // Use the struct stChosenSessions to assign the current
      // Session ID values to each value in the stChosenSession
      // Then push back the struct to the vector vsChosenSessions
      // which will then store that struct, which can be used at a
      // later date
      stChosenSessions.iID = vsSession[a].iID;
      stChosenSessions.iSpaces = vsSession[a].iSpaces;
      stChosenSessions.iTime = vsSession[a].iTime;
      stChosenSessions.sName = vsSession[a].sName;
      stChosenSessions.sRoom = vsSession[a].sRoom;
      vsChosenSessions.push_back(stChosenSessions);
    }
  }
}

void sysStateThreeSubStateTwo(int& iCurrentState, int& iCurrentSubState,
  bool& bSysRun, int iPackageNo, vector<PACKAGEINFO> vsPackageInfo,
  vector<SESSIONS> vsSession, CHOSENSESSIONS& stChosenSessions,
  vector<CHOSENSESSIONS>& vsChosenSessions)
{
  // This function will allow the user to input the session ID's

  // Declare the vector<int> vsViSessionIDRemoved;
  vector<int> vsViSessionIDRemoved;

  // Initalise the int variable iSessionIDStartNo and set it to 0
  int iSessionIDStartNo = 0;

  // Loop through the specific Package must Sessions
  for (int q = 0; q < vsPackageInfo[iPackageNo].vsSessionsMN[iPackageNo].
    vsMustSessions.size(); q++)
  {
    // If the specific must session is > -1 (-1 being no must session);
    if (vsPackageInfo[iPackageNo].vsSessionsMN[iPackageNo].
      vsMustSessions[q] > -1)
    {
      // Add one to the session ID start no
      iSessionIDStartNo += 1;
    }
  }

  // Loop through the specific package must sessions
  for (int b = 0; b < vsPackageInfo[iPackageNo].vsSessionsMN[iPackageNo].
    vsMustSessions.size(); b++)
  {
    // If the package must session is >-1
    if (vsPackageInfo[iPackageNo].vsSessionsMN[iPackageNo].
      vsMustSessions[b] > -1)
    {
      // Send text to the console stating that the specific must session 
      // has been automatically booked
      cout << endl << "~Session with the ID: " <<
        vsPackageInfo[iPackageNo].vsSessionsMN[iPackageNo].vsMustSessions[b]
        << " automatically booked" << endl;
      // Call the storing function and pass the relevant data through
      sysStateThreeSubStateTwoStoreSession(
        vsPackageInfo[iPackageNo].vsSessionsMN[iPackageNo].vsMustSessions[b],
        vsSession, stChosenSessions, vsChosenSessions);
      // Push back the ID that has been removed ++
      vsViSessionIDRemoved.push_back(vsPackageInfo[iPackageNo].
        vsSessionsMN[iPackageNo].vsMustSessions[b]);
      // List the sessions
      systemListSessions(vsSession, vsPackageInfo, iPackageNo,
        vsViSessionIDRemoved);
    }
  }

  // Loop through the number of sessions that the package can have
  for (int i = iSessionIDStartNo; i < vsPackageInfo[iPackageNo].
    iNoSessions; i++)
  {
    // Create the variable bool bUserCheck and set it to true, this ensures
    // that the users input will be checked until it is not nesscary
    bool bUserCheck = true;

    // Asks the user to input a session ID
    cout << "-Please enter" <<
      sysStateThreeSubStateTwoSessionAskInput(i) <<
      "session ID"
      << endl << "|";

    // Creates the user input store
    string sSessionID;
    // Collects the input from the user
    getline(cin, sSessionID);

    // While bUserCheck is true
    while (bUserCheck)
    {
      // Set the return value from the function (which checks if the user has
      // entered a keyword which will stall the programme) to a variable
      int iSysCheck = systemStateGeneralFuncs(sSessionID,
        iCurrentState, bSysRun, iCurrentSubState);
      // If the user has entered a keyword it will stop the user check
      if (iSysCheck == 1)
      {
        // Stops the user check
        i = vsPackageInfo[iPackageNo].iNoSessions + 1;
        bUserCheck = false;
      }
      else
      {
        // If the session ID is a number
        if (systemIsNumber(sSessionID))
        {
          // Check the session ID by calling the function
          // stoi means that it converts the string to an int since we have
          // already confirmed it is an int, creates a variable to store the
          // outcome of the function
          int iCheckSessionID = sysStateThreeSubStateTwoSessionCheckSession(
            stoi(sSessionID), iPackageNo,
            vsChosenSessions, vsSession, vsPackageInfo);
          // Checks to see if the variable is equal to 0
          if (iCheckSessionID == 0)
          {
            // This means it is correct and pass all the rules
            // Calls the function to store the session
            sysStateThreeSubStateTwoStoreSession(stoi(sSessionID),
              vsSession, stChosenSessions,
              vsChosenSessions);
            // Pushes back the ID
            vsViSessionIDRemoved.push_back(stoi(sSessionID));
            // Lists the sessions
            systemListSessions(vsSession, vsPackageInfo, iPackageNo,
              vsViSessionIDRemoved);
            // Sets bUserCheck to false to ensure that the user will be asked
            // for another session ID
            bUserCheck = false;
          }
          else
          {
            // Use the function to call the error message
            sysStateThreeSubStateTwoSessionErrors(iCheckSessionID);
            // Asks the user for another input
            getline(cin, sSessionID);
          }
        }
        else
        {
          // Calls a specific error message
          systemErrorMessages("U10");
          // Asks the user for another input
          getline(cin, sSessionID);
        }
      }
    }
  }
  // Changes the current substate to two
  iCurrentSubState = 2;
}

void sysStateThreeSubStateThree(int& iCurrentSubState,
  vector<CHOSENSESSIONS> vsChosenSessions)
{
  cout << endl << "~List of chosen Sessions" << endl;
  // Uses the function to output what you want to ouput
  // And have equal amount of spacing. Outputs the headers
  // to the console
  systemOutputSpacesNeeded("NAME", -1024, 20);
  systemOutputSpacesNeeded("TIME", -1024, 6);
  systemOutputSpacesNeeded("SPACES", -1024, 8);
  systemOutputSpacesNeeded("ROOM", -1024, 6);
  cout << "ID" << endl;

  // Loops through the chosen sessions
  for (int i = 0; i < vsChosenSessions.size(); i++)
  {
    // Uses the function to output what you want to ouput
    // And have equal amount of spacing. Outputs each piece of
    // data that is stored in the selected location to the console
    systemOutputSpacesNeeded(vsChosenSessions[i].sName, -1024, 20);
    systemOutputSpacesNeeded("", vsChosenSessions[i].iTime, 6);
    systemOutputSpacesNeeded("", vsChosenSessions[i].iSpaces, 8);
    systemOutputSpacesNeeded(vsChosenSessions[i].sRoom, -1024, 6);
    cout << vsChosenSessions[i].iID << endl;
  }
  // Changes the sub state to 3
  iCurrentSubState = 3;
}

void sysStateThreeSubStateFour(int& iCurrentState,
  int& iCurrentSubState, bool& bSysRun)
{
  // Confirms the users booking

  // Sends text to the console
  cout << endl << "?Type CONFIRM to confirm the selection " <<
    "or type RESET to start from the beginning" << endl
    << "-Confirm the above selection of sessions" <<
    endl;
  cout << "|";

  string sUserInput;
  getline(cin, sUserInput);
  sUserInput = systemTransformToupper(sUserInput);

  bool bUserCheck = true;

  while (bUserCheck)
  {
    // Set the return value from the function (which checks if the user has
    // entered a keyword which will stall the programme) to a variable
    int iSysCheck = systemStateGeneralFuncs(sUserInput,
      iCurrentState, bSysRun, iCurrentSubState);
    // If the user has entered a keyword it will stop the user check
    if (iSysCheck == 1)
    {
      // Stops the user check
      bUserCheck = false;
    }
    else
    {
      if (sUserInput == "CONFIRM")
      {
        iCurrentState = 4;
        bUserCheck = false;
      }
      else
      {
        systemErrorMessages("U11");
        getline(cin, sUserInput);
        sUserInput = systemTransformToupper(sUserInput);
      }
    }
  }
}

void sysStateThree(int& iCurrentState, bool& bSysRun,
  int iPackageNo, CHOSENSESSIONS& stChosenSessions,
  vector<CHOSENSESSIONS>& vsChosenSessions,
  vector<SESSIONS> vsSession,
  vector<PACKAGEINFO> vsPackageInfo)
{
  vector<int> viSesssionIDRemoved;
  int iCurrentSubState = 0;

  if (iCurrentSubState == 0)
  {
    sysStateThreeSubStateOne(iCurrentSubState, vsSession, vsPackageInfo,
      iPackageNo, viSesssionIDRemoved);
  }
  if (iCurrentSubState == 1)
  {
    sysStateThreeSubStateTwo(iCurrentState, iCurrentSubState, bSysRun,
      iPackageNo,
      vsPackageInfo, vsSession, stChosenSessions, vsChosenSessions);
  }
  if (iCurrentSubState == 2)
  {
    sort(vsChosenSessions.begin(), vsChosenSessions.end(), stChosenSessions);

    sysStateThreeSubStateThree(iCurrentSubState, vsChosenSessions);
  }
  if (iCurrentSubState == 3)
  {
    sysStateThreeSubStateFour(iCurrentState, iCurrentSubState, bSysRun);
  }
}

// End of System State Three //

// Start of System State Four //

void sysStateFourSubStateOne(string sCustomerName,
  vector<CHOSENSESSIONS> vsChosenSessions,
  int& iCurrentSubState)
{
  // This function stores the customers booking

  // Creates two variables named sFirstName and sLastName
  string sFirstName;
  string sLastName;

  // Loops thorugh the length of the sCustomerName
  for (int i = 0; i < sCustomerName.length(); i++)
  {
    // 
    if (sCustomerName[i] == ' ')
    {
      sFirstName.append(sCustomerName.substr(0, i));
      sLastName += sCustomerName.substr(i + 1, sCustomerName.length() - 1);
    }
  }

  // Ensures that custDataStore uses ofstream
  ofstream custDataStore;

  // Changes the sLastName to all uppercase
  sLastName = systemTransformToupper(sLastName);

  // Opens the file and gives it a name
  custDataStore.open("custbooking" + sLastName + ".txt");

  // Stores the headers to the file intialliy
  custDataStore << setw(16) << "NAME";
  custDataStore << setw(8) << "TIME";
  custDataStore << setw(8) << "ID";
  custDataStore << setw(8) << "ROOM";
  custDataStore << "\n";

  // Loops through the amount of chosen sessions
  for (int i = 0; i < vsChosenSessions.size(); i++)
  {
    // For every Session store each piece of data
    // The setw() ensures that each piece of data is evenly spaced
    // out and has a set width
    custDataStore << setw(16) << vsChosenSessions[i].sName;
    custDataStore << setw(8) << vsChosenSessions[i].iTime;
    custDataStore << setw(8) << vsChosenSessions[i].iID;
    custDataStore << setw(8) << vsChosenSessions[i].sRoom;
    custDataStore << "\n";
  }

  // Closes the file
  custDataStore.close();

  // Confirms the customers booking is saved
  cout << endl << "~Customer Booking Saved" << endl;

  // Changes the substate to one
  iCurrentSubState = 1;
}

void sysStateFourStateTwo(vector<SESSIONS>& vsSession,
  vector<CHOSENSESSIONS> vsChosenSessions,
  int& iCurrentState, bool& bSysRun,
  int& iCurrentSubState,
  vector<SESSIONS>& vsUnsortedSession)
{
  // This function removes one from the session spaces

  // Loops through all the chosen sessisons
  for (int q = 0; q < vsChosenSessions.size(); q++)
  {
    // Loops through all the unsorted sessions
    for (int i = 0; i < vsUnsortedSession.size(); i++)
    {
      // Checks if the current session ID is equal to the
      // current chosen ID
      if (vsUnsortedSession[i].iID == vsChosenSessions[q].iID)
      {
        // If it is it will remove one from the Spaces
        vsUnsortedSession[i].iSpaces -= 1;
      }
    }

    // Loops through all the sessions
    for (int p = 0; p < vsSession.size(); p++)
    {
      // Checks if the current session ID is equal to the
      // current chosen session ID
      if (vsSession[p].iID == vsChosenSessions[q].iID)
      {
        // If it is it will rmeove one from the spaces
        vsSession[p].iSpaces -= 1;
      }
    }
  }

  // Changes the sub state to two
  iCurrentSubState = 2;
}

void sysStateFourStateThree(vector<SESSIONS>& vsUnsortedSession,
  int& iCurrentState, bool& bSysRun,
  int& iCurrentSubState)
{
  // Ensures sesssionData is used as ofstream
  ofstream sessionData;

  // Opens the file and gives it a name
  sessionData.open("sessionrooms.txt");

  // Loops through the original unsorted data 
  for (int i = 0; i < vsUnsortedSession.size(); i++)
  {
    // Wrties each data to the file and adds a new line after
    // each indivdual data has been written
    // The setw ensures the the file is organised by setting
    // each column a width
    sessionData << setw(16) << vsUnsortedSession[i].sName;
    sessionData << setw(8) << vsUnsortedSession[i].iTime;
    sessionData << setw(8) << vsUnsortedSession[i].iSpaces;
    sessionData << setw(8) << vsUnsortedSession[i].sRoom;
    sessionData << "\n";
  }

  // Closes the file
  sessionData.close();

  // Changes the Current State to two which means that the
  // program will begin from the customer name input
  iCurrentState = 2;
}

void sysStateFour(int& iCurrentState, bool& bSysRun,
  vector<CHOSENSESSIONS> vsChosenSessions,
  string sCustomerName, vector<SESSIONS>& vsSession,
  vector<SESSIONS>& vsUnsortedSession)
{
  // Initalises the variable iCurrentSubState and sets it to 0
  int iCurrentSubState = 0;

  // If the variable is equal to the number
  // Run the contained code
  if (iCurrentSubState == 0)
  {
    // Calls the function and passes through relevant variables
    sysStateFourSubStateOne(sCustomerName, vsChosenSessions,
      iCurrentSubState);
  }
  if (iCurrentSubState == 1)
  {
    sysStateFourStateTwo(vsSession, vsChosenSessions,
      iCurrentState, bSysRun, iCurrentSubState,
      vsUnsortedSession);
  }
  if (iCurrentSubState == 2)
  {
    sysStateFourStateThree(vsUnsortedSession, iCurrentState,
      bSysRun, iCurrentSubState);
  }
}

// End of System State Four //