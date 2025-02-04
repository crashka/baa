#ifndef __FINANCES_HPP__
#define __FINANCES_HPP__

#include <string>

#ifdef USE_ODB
#  include <odb/core.hxx>
#endif

class Finances{
private:
#ifdef USE_ODB
    friend class odb::access;
#endif

    // the identifiers of the user
    int digits;
    std::string name;

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
    void setName( std::string);
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
    std::string getName();
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

#ifdef USE_ODB
#  pragma db object(Finances)
#  pragma db member(Finances::digits) id
#endif

#endif // __FINANCES_HPP__
