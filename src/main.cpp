#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdio>
#include <iomanip>

#include "finances.hpp"
#ifdef USE_ODB
#  include <odb/database.hxx>
#  include <odb/transaction.hxx>
#  include <odb/pgsql/database.hxx>
#  include "finances-odb.hpp"
#endif

using namespace std;
#ifdef USE_ODB
using namespace odb::core;
#endif

// Note that command line arguments are passed through to the `odb::database` constructor
// for the USE_ODB case (otherwise ignored)
int main(int argc, char* argv[]){

  // initializing all variables that will be included in the file
  int digits, userIncome, userExpend, userRemBudget, userMonthBudget, langCode, weekCounter, moneySpent, percentSave, percentWarning;
  string name;

  // Pointer to the Finances record for the current user; this points to the user's element
  // within personalInfo in the file-based database case, but represents dynamic (i.e. heap)
  // storage in the USE_ODB case
  Finances *userInfo;

#ifndef USE_ODB
  ifstream database( "readFile.txt");

  vector<Finances> personalInfo;

  // Text file contains data in order of digits, guaIncome, guaExpend, userRemBudget, userMonthBudget, weekCounter, percentSave, percentWarning, name

  database >> digits;

  while( !database.eof())
  {
    // getting the values from inside the file and placing them into variables
    database >> userIncome;
    database >> userExpend;
    database >> userRemBudget;
    database >> userMonthBudget;
    database >> weekCounter;
    database >> percentSave;
    database >> percentWarning;

    getline( database, name);

    Finances prevFinances;

    // setting the variables taken from the file into the class object
    prevFinances.setDigits( digits);
    prevFinances.setGuaIncome( userIncome);
    prevFinances.setGuaExpend(userExpend);
    prevFinances.setRemBudget( userRemBudget);
    prevFinances.setMonthBudget();
    prevFinances.setWeekCounter( weekCounter);
    prevFinances.setPercentSave(percentSave);
    prevFinances.setPercentWarning(percentWarning);
    prevFinances.setName(name);

    // once all the info is in the class, the info is placed into the vector
    personalInfo.push_back( prevFinances);

    database >> digits;
  }
#else
  unique_ptr<database> db(new odb::pgsql::database(argc, argv));
#endif


  cout << "Hi! Welcome to B.A.A., the Budgetary Analytical Advisory hotline. We are here to help with your budgetary needs." << endl;

  cout << " What language would you like to continue in? Enter: 0 for Mandarin, 1 for Spanish, 2 for English" << endl;

  cin >> langCode;

  cout << "Using your keypad please enter your phone number not including country code: " << endl;

  cin >> digits;

#ifndef USE_ODB
  // using a bool and for loop, we try to find whether or not the user already has an account
  bool found = false;
  int userIndex;

  for(int i = 0; i < personalInfo.size(); i++){

    if(personalInfo[i].getDigits() == digits){
      userIndex = i;
      userInfo = &personalInfo[userIndex];
      found = true;
    }

  }
#else
  try {
    transaction t(db->begin());
    userInfo = db->find<Finances>(digits);
    t.commit();
  }
  catch (const odb::exception& e) {
    cerr << e.what() << endl;
    return 1;
  }
  bool found = (userInfo != NULL);
#endif

  // is when you dont have an account, allows user to set up account
  if( !found){
    string firstName, lastName;
    Finances newFinances;

    cout << "Please enter your first name and last name: " << endl;
    cin >> firstName >> lastName;
    name = firstName + " " + lastName;
    newFinances.setName(name); // adds the name to the new finances class

    newFinances.setDigits(digits); // gets the user phone number and stores it in the new finances class as part of an identifier for the user

    cout << "Thank You for your patience, an account has been created. Our job is to help you manage your finances and give recommended solutions based on your spending habits. " << endl;

    cout << "First, please enter your monthly income: ";
    cin >> userIncome;
    cout << endl;
    newFinances.setGuaIncome(userIncome);// adds user input of income to the new finances class category

    cout << "What are your monthly set expenditures, such as mandatory bills and taxes: " << endl;
    cin >> userExpend;
    newFinances.setGuaExpend( userExpend);

    cout << "Finally, please enter your preferred percentage of monthly income you'd like to save, and the percentage of monthly income you'd like to recieve a warning when you spend over, as a number between one and one hundred." << endl;

    cin >> percentSave >> percentWarning; // gathers user input to put into multiple variables

    // place all the inputted user variables into a class
    newFinances.setPercentSave(percentSave);
    newFinances.setPercentWarning(percentWarning);

    newFinances.setMonthBudget();
    newFinances.setRemBudget(newFinances.getMonthBudget());
    newFinances.setWeekCounter(4);

#ifndef USE_ODB
    // the class is placed into the function
    personalInfo.push_back( newFinances);

    userIndex = personalInfo.size() - 1;
    userInfo = &personalInfo[userIndex];
#else
    try {
      int new_id;
      transaction t(db->begin());
      new_id = db->persist(newFinances);
      t.commit();
    }
    catch (const odb::exception& e) {
      cerr << e.what() << endl;
      return 1;
    }
    // create a copy on the heap for updating below
    userInfo = new Finances(newFinances);
#endif
  }
  else{

    cout << "Your account has been found!" << endl;

    // the bools handle if you want to make changes to your values
    bool incChange = false, expChange = false, saveChange = false, warnChange = false;

    //assigns yes or no values to variables and then uses the values for if statements to either update the variables or pass by the statement
    cout << "Has your monthly income changed since last week? Input 1 for yes and 0 for no." << endl;
    cin >> incChange;
    cout << "Have your monthly expenditures changed since last week? Input 1 for yes and 0 for no" << endl;
    cin >> expChange;
    cout << "Would you like to change your desired percentage of monthly income to save? Input 1 for yes and 0 for no." << endl;
    cin >> saveChange;
    cout << "Would you like to change your desired percentage for your spending warning? Input 1 for yes and 0 for no." << endl;
    cin >> warnChange;

    // the following if statements, handle the changes the user wants to make
    if(incChange){
      cout << "What is your new monthly income?" << endl;
      cin >> userIncome;
      userInfo->setGuaIncome(userIncome);
    }

    if(expChange){
      cout << "What is your new monthly expenditures?" << endl;
      cin >> userExpend;
      userInfo->setGuaExpend(userExpend);
    }
    if(saveChange){
      cout << "What is your new desired percentage of monthly income to save?" << endl;
      cin >> percentSave;
      userInfo->setPercentSave(percentSave);
    }
    if(warnChange){
      cout << "What is your new desired percentage of monthly income to issue a warning?" << endl;
      cin >> percentWarning;
      userInfo->setPercentWarning(percentWarning);
    }

    // decrementing week counter to use in calculations later on
    userInfo->setWeekCounter(userInfo->getWeekCounter() - 1);

    // once the week counter is 0, it signals that it's a new month and resets
    if(userInfo->getWeekCounter() == 0){
      userInfo->resetMonth();
    }
  }

  bool spend = false;
  cout << "Have you spent anything this week? Input 1 for yes and 0 for no." << endl;
  cin >> spend;
  // how much spent

  // handles the calculation of the remaining budget
  if(spend){
    cout << "How much did you spend this week?" << endl;
    cin >> moneySpent;
    if(userInfo->isViolatingWarning(moneySpent)){
      cout << "Careful! You've passed your spending warning threshold for the month." << endl;
    }
      userInfo->calcRemBudget(moneySpent);
  }

#ifndef USE_ODB
  // Open the file with the argument to write onto it
  fopen("writeFile.txt", "w");
  // Store the file in a variable name for conventional use
  ofstream toWrite("writeFile.txt");
  // For each index in the vector of Financial Classes, copy all of the previous items in the database back into the database.
  for(int i = 0; i < personalInfo.size(); i++){
    toWrite << personalInfo[i].getDigits() << " ";
    toWrite << personalInfo[i].getGuaIncome() << " ";
    toWrite << personalInfo[i].getGuaExpend() << " ";
    toWrite << personalInfo[i].getRemBudget() << " ";
    toWrite << personalInfo[i].getMonthBudget() << " ";
    toWrite << personalInfo[i].getWeekCounter() << " ";
    toWrite << personalInfo[i].getPercentSave() << " ";
    toWrite << personalInfo[i].getPercentWarning() << " ";
    toWrite << personalInfo[i].getName();
    toWrite << endl;
  }
  userInfo->menu(langCode);

  // Implemented a tri way substitution to preserve the values stored within the text files, using an intermediate placeholder
  char readFile[] = "readFile.txt";
  char writeFile[] = "writeFile.txt";
  char placeholder[] = "placeholder.txt";
  rename(writeFile, placeholder);
  char newWrite[] = "writeFile.txt";
  rename(readFile, newWrite);
  char newRead[] = "readFile.txt";
  rename(placeholder, newRead);
#else
  try {
    transaction t(db->begin());
    db->update(*userInfo);
    t.commit();
  }
  catch (const odb::exception& e) {
    cerr << e.what() << endl;
    return 1;
  }

  userInfo->menu(langCode);
  // this points to a heap object in both the new and existing user cases (different
  // construction methods)
  delete userInfo;
#endif

  // Make main happy
  return 0;

}
