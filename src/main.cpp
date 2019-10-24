#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdio>
#include <iomanip>

using namespace std;

class Finances{
private:
    
    // the identifiers of the user
    int digits;
    string name;

    // guaranteed values set by the users
    int guaIncome;
    int guaExpend;

    // budget values used for later
    int remBudget;
    int monthBudget;

    // counts the number of weeks in the month
    int weekCounter;
    
    // the user decides on current percentage savings,
    //   default 20 percent
    int percentSave;
    int percentWarning;

public:
    // default constructor
    Finances()
    {
        guaIncome =  guaExpend = remBudget = monthBudget = weekCounter = percentSave = percentWarning = 0;

    }
    
    // set functions declarations, information for each is where 
    // the function gets used
    void setName( string);
    void setDigits( int);
    void setWeekCounter( int);
    void setGuaIncome( int);
    void setGuaExpend( int);
    void setRemBudget( int);
    void setMonthBudget( );
    void calcRemBudget( int);
    void setPercentSave(int);
    void setPercentWarning(int);

    // get functions declarations, information for each is where 
    // the function gets used
    string getName();
    int getDigits();
    int getWeekCounter();
    int getGuaIncome();
    int getGuaExpend();
    int getRemBudget();
    int getMonthBudget();
    int getPercentSave();
    int getPercentWarning();
    
    //math functions 
    int weekly_budget();
    void danger_zone();
    void resetMonth();
    bool isViolatingWarning(int);

    //user interface and experience functions
    void menu( int);
};

//--------------------------set functions-----------------------//
// sets the name value
void Finances::setName( string userName) { name = userName;}
//--------------------------------------------------------------//
// sets the digit value
void Finances::setDigits( int newDigit) { digits = newDigit;}
//--------------------------------------------------------------//
// sets the week counter value
void Finances::setWeekCounter( int newWeek) { weekCounter = newWeek;}
//--------------------------------------------------------------//
// sets the month budget value by substracting guaranteed income 
// value and gauranteed expenditures
void Finances::setMonthBudget(){ monthBudget = (double)(guaIncome - guaExpend) - ((guaIncome - guaExpend) *  ((double)percentSave / 100.0));}
//--------------------------------------------------------------//
// sets the remaining budget value
void Finances::setRemBudget( int newRemBudget) { remBudget = newRemBudget;}
//--------------------------------------------------------------//
// sets the guaranteed income value
void Finances::setGuaIncome(int income){ guaIncome = income;}
//--------------------------------------------------------------//
// sets the guaranteed expenditure value 
void Finances::setGuaExpend(int expend){ guaExpend = expend;}
//--------------------------------------------------------------//
// sets the desired save percentage
void Finances::setPercentSave(int save){percentSave = save;}
//--------------------------------------------------------------//
// sets the desired warning percentage
void Finances::setPercentWarning(int warn){percentWarning = warn;}
//--------------------------get functions-----------------------//
// gets the name value
string Finances::getName(){ return name;}
//--------------------------------------------------------------//
// gets the digit value
int Finances::getDigits() { return digits;}
//--------------------------------------------------------------//
// gets the week counter value
int Finances::getWeekCounter(){ return weekCounter;}
//--------------------------------------------------------------//
// gets the guaranteed income value
int Finances::getGuaIncome(){ return guaIncome;}
//--------------------------------------------------------------//
// gets the guaranteed expenditure value
int Finances::getGuaExpend(){ return guaExpend;}
//--------------------------------------------------------------//
// gets the remaining budget value
int Finances::getRemBudget(){ return remBudget;}
//--------------------------------------------------------------//
// gets the month budget value
int Finances::getMonthBudget(){ return monthBudget;}
//--------------------------------------------------------------//
// gets the percentage save information
int Finances::getPercentSave(){ return percentSave;}
//--------------------------------------------------------------//
// gets the percentage warning information
int Finances::getPercentWarning(){ return percentWarning;}

 
//--------------- Math calculations methods --------------------//
//--------------------------------------------------------------//
void Finances::resetMonth(){
  monthBudget = guaIncome;
  remBudget = monthBudget;
  weekCounter = 4;
}
// calculates the remaining budget by substracting the remBudget with
// the
void Finances::calcRemBudget( int moneySpent) { remBudget = remBudget - moneySpent;}
//--------------------------------------------------------------//
// calculating maths stuff functions  
int Finances::weekly_budget(){  
  // weekly budget = remaining budget / weekly counter
  int weekbudge = remBudget/getWeekCounter();
  return weekbudge;
}

void Finances::danger_zone (){
  // danger zone = when monthly budget is at designated warning zone 
   double percentage = (double)percentWarning / 100.0;
   double danger_zone = percentage * ((double)monthBudget);
   cout << danger_zone;
 }
bool Finances::isViolatingWarning(int spendAmount){
  if((remBudget - spendAmount) <= (int)((double)  monthBudget * (double)percentWarning / 100.0)){
  return true;
  }
  else{
    return false;
  }
}

//--------------------------------------------------------------//
// The menu function prints out the values that the user will need
// including the user's weekly budget, monthly budget, and danger zone
// It involves using a switch case to switch languages based on the 
// user's langCode input
void Finances::menu(int langCode){
  // this creates a switch case which outputs different 'Current Report' in the 3 different languages when the language code is selected at the beginning 
  switch (langCode){
    case 0:
  cout << " ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n"
          "  当前报告  					                            " 
          "                  					                            \n"   
          "  当前月收入: " << getGuaIncome() << "\n" <<
          "  当前每月支出: " << getGuaExpend() <<"\n"<<
          "  剩余资金:	" << getRemBudget() << "\n" <<
          "  建议的每周预算: " << weekly_budget() << "\n"; 
          
  cout << 	"\n" <<
          "  当前每月预算: " << getMonthBudget() <<	"\n" <<
          "  当前储蓄百分比: " << getPercentSave() <<	 "\n" <<
          "  当前警告百分比: " << getPercentWarning() << "\n"
          "  危险区值: " << ((guaIncome - guaExpend) *  ((double)percentWarning / 100.0))  << "\n"
          " ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n";
      break;
      
    // this case handles the spanish translation of the menu
    case 1:
  
      cout << " ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n"
          "  Informe actual    \n" <<  
          "  Ingresos Mensuales Corrientes: " << getGuaIncome() << "\n" <<
          "  Gasto mensual corriente: " << getGuaExpend() <<"\n"<<
          "  Fondos restantes:	" << getRemBudget() << "\n" <<
          "  Presupuesto semanal sugerido: " << weekly_budget() << "\n"; 
          
  cout  << 	"\n" <<
          "  Presupuesto mensual actual: " << getMonthBudget() <<	"\n" <<
          "  Porcentaje de Ahorro Corriente: " << getPercentSave() <<	 "\n" <<
          "  Porcentaje de Advertencias Actuales: " << getPercentWarning() << "\n"
          "  Valor de la zona de peligro: " << ((guaIncome - guaExpend) *  ((double)percentWarning / 100.0)) <<  "\n"
          " ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n";
  
      break;

  // this case handles the English translation of the menu
    case 2:
  cout << " ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n"
          "  Current Report  					                            \n" 
          "                  					                            "   
          "  Current Monthly Income: " << getGuaIncome() << "\n" <<
          "  Current Monthly Expenditure: " << getGuaExpend() <<"\n"<<
          "  Remaining Funds:	" << getRemBudget() << "\n" <<
          "  Suggested Weekly Budget: " << weekly_budget(); 
          
  cout << 	"\n" <<
          "  Current Monthly Budget: " << getMonthBudget() <<	"\n" <<
          "  Current Savings Percentage: " << getPercentSave() <<	 "\n" <<
          "  Current Warnings Percentage: " << getPercentWarning() << "\n"
          "  Danger Zone Value: " <<((guaIncome - guaExpend) *  ((double)percentWarning / 100.0)) <<  "\n"
          " ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n";
      break;
  }
  

}



int main(){

  // initializing all variables that will be included in the file
  int digits, userIncome, userExpend, userRemBudget, userMonthBudget, langCode, weekCounter, moneySpent, percentSave, percentWarning;
  string name;

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


  cout << "Hi! Welcome to B.A.A., the Budgetary Analytical Advisory hotline. We are here to help with your budgetary needs." << endl;

  cout << " What language would you like to continue in? Enter: 0 for Mandarin, 1 for Spanish, 2 for English" << endl;
  
  cin >> langCode;

  cout << "Using your keypad please enter your phone number not including country code: " << endl;

  cin >> digits;

  // using a bool and for loop, we try to find whether or not the user already has an account
  bool found = false;
  int userIndex;
  
  for(int i = 0; i < personalInfo.size(); i++){

    if(personalInfo[i].getDigits() == digits){
      userIndex = i;
      found = true;
    } 

  }
  
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

    // the class is placed into the function
    personalInfo.push_back( newFinances);

    userIndex = personalInfo.size() - 1;
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
      personalInfo[userIndex].setGuaIncome(userIncome);
    }

    if(expChange){
      cout << "What is your new monthly expenditures?" << endl;
      cin >> userExpend;
      personalInfo[userIndex].setGuaExpend(userExpend);
    }
    if(saveChange){
      cout << "What is your new desired percentage of monthly income to save?" << endl;
      cin >> percentSave;
      personalInfo[userIndex].setPercentSave(percentSave);
    }
    if(warnChange){
      cout << "What is your new desired percentage of monthly income to issue a warning?" << endl;
      cin >> percentWarning;
      personalInfo[userIndex].setPercentWarning(percentWarning);
    }

    // decrementing week counter to use in calculations later on
    personalInfo[userIndex].setWeekCounter(personalInfo[userIndex].getWeekCounter() - 1);

    // once the week counter is 0, it signals that it's a new month and resets
    if(personalInfo[userIndex].getWeekCounter() == 0){
      personalInfo[userIndex].resetMonth();
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
    if(personalInfo[userIndex].isViolatingWarning(moneySpent)){
      cout << "Careful! You've passed your spending warning threshold for the month." << endl;
    }
      personalInfo[userIndex].calcRemBudget(moneySpent);
  }


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
  personalInfo[userIndex].menu(langCode);
  
  // Implemented a tri way substitution to preserve the values stored within the text files, using an intermediate placeholder
  char readFile[] = "readFile.txt";
  char writeFile[] = "writeFile.txt"; 
  char placeholder[] = "placeholder.txt";
  rename(writeFile, placeholder);
  char newWrite[] = "writeFile.txt";
  rename(readFile, newWrite);
  char newRead[] = "readFile.txt";
  rename(placeholder, newRead);
  
  // Make main happy
  return 0;

}