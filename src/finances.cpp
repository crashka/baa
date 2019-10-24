#include <iostream>
#include <string>

#include "finances.hpp"

using namespace std;

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
