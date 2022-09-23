#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

void printMenu();
bool isInvalidOperation(string oper);                                               // check the input operation is valid or not.
bool isInvalidBrand(string b);                                                      // check the input brand is valid or not.
bool isInvalidVaccinedDays(int days);                                               // [DEPRECIATED] check the input days is valid or not.
bool isInvalidAge(int age);                                                         // check the input age is valid or not.
bool hasEnoughData(int age, int days, string b);                                    // check the data is enough.
double getAntiBodyConcentration(int age, int days, string b, bool prior_infection); // get antibody concentration round off to the 2nd decimal place.
bool isInvalidDate(long int date);                                                  // check the date is valid or not.
int getDaysBetweenTwoDates(long int date1, long int date2);                         // get the days between two dates.
int countLeapYears(int years, int months);                                          // count how many leap years.
int getTotalDays(int years, int months, int days);                                  // get total days.

const int monthDays[12] = {31, 28, 31, 30, 31, 30,
                           31, 31, 30, 31, 30, 31};

int main()
{
    bool exit = false;

    /* User data*/
    int age = -1;
    int days_pass_by_vaccinated = -1;
    string vaccine_brand = "";
    bool has_prior_infection = false;

    /* Date data */
    long int vaccinated_date;
    long int today_date;

    /* Anibody data*/
    double antibody = 0.0;

    while (!exit)
    {

        printMenu();

        string operation;
        cout << ">>>";
        cin >> operation;

        /* Check the input operation is valid or not. */
        while (isInvalidOperation(operation))
        {
            cout << "Invalid input !Please enter again" << endl;
            cout << ">>>";
            cin >> operation;
        }

        if (operation == "1") // input body data
        {
            cout << "Enter your age:";
            cin >> age;

            /* Check the input age is valid or not. */
            while (isInvalidAge(age))
            {
                cout << "Invalid input !Please enter again" << endl;
                cout << ">>>";
                cin >> age;
            }
            cout << "\n\n";
        }
        else if (operation == "2") // input vaccine data
        {
            cout << "Enter the date you were vaccinated(yyyymmdd): ";
            cin >> vaccinated_date;

            /* Check the input date is valid or not. */
            while (isInvalidDate(vaccinated_date))
            {
                cout << "Invalid input !Please enter again" << endl;
                cout << ">>>";
                cin >> vaccinated_date;
            }

            /* [DEPRECIATED] */
            // /* Check the input days is valid or not. */
            // while (isInvalidVaccinedDays(days_pass_by_vaccinated))
            // {
            //     cout << "Invalid input !Please enter again" << endl;
            //     cout << ">>>";
            //     cin >> days_pass_by_vaccinated;
            // }

            cout
                << "Enter the brand(A/B/M): ";
            cin >> vaccine_brand;

            /* Check the input brand is valid or not. */
            while (isInvalidBrand(vaccine_brand))
            {
                cout << "Invalid input !Please enter again" << endl;
                cout << ">>>";
                cin >> vaccine_brand;
            }

            cout << "\n\n";
        }
        else if (operation == "3") // input prior infection
        {

            cout << "Did you have a prior infection(y/n): ";
            string user_input;
            cin >> user_input;

            /* Check the input is valid or not. */
            while (user_input != "y" && user_input != "n")
            {
                cout << "Invalid input !Please enter again" << endl;
                cout << ">>>";
                cin >> user_input;
            }

            cout << "\n\n";

            /* Set has_prior_infection */
            if (user_input == "y")
            {
                has_prior_infection = true;
            }
            else if (user_input == "n")
            {
                has_prior_infection = false;
            }
        }
        else if (operation == "R") // calculate antibody
        {
            long int today_date;
            cout << "Enter the date today(yyyymmdd): ";
            cin >> today_date;

            /* Check the input date is valid or not. */
            while (isInvalidDate(today_date))
            {
                cout << "Invalid input !Please enter again" << endl;
                cout << ">>>";
                cin >> today_date;
            }

            days_pass_by_vaccinated = getDaysBetweenTwoDates(vaccinated_date, today_date);

            if (hasEnoughData(age, days_pass_by_vaccinated, vaccine_brand))
            {
                antibody = getAntiBodyConcentration(age, days_pass_by_vaccinated, vaccine_brand, has_prior_infection);
                cout << "Your antibody is " << std::fixed << std::setprecision(2) << antibody << endl;
                if (antibody < 50)
                {
                    cout << "Watch out! Antibody is low.\n\n\n";
                }
                else
                {
                    cout << "You are safe!\n\n\n";
                }
            }
            else
            {
                cout << "Data is not enough. \n\n\n";
            }
        }
        else if (operation == "0") // exit system
        {
            cout << "\n\n"
                 << "bye~";
            exit = true;
        }
    }
}

int getDaysBetweenTwoDates(long int date1, long int date2)
{
    // invalid case
    if (date2 < date1)
    {
        return -1;
    }

    int y1, m1, d1;
    int y2, m2, d2;

    long int date = date1;
    d1 = (int)date % 100;
    date = (long int)date / 100;
    m1 = (int)date % 100;
    date = (long int)date / 100;
    y1 = (int)date;

    date = date2;
    d2 = (int)date % 100;
    date = (long int)date / 100;
    m2 = (int)date % 100;
    date = (long int)date / 100;
    y2 = (int)date;

    long int n1 = getTotalDays(y1, m1, d1);
    long int n2 = getTotalDays(y2, m2, d2);

    return n2 - n1 + 1;
}

int getTotalDays(int years, int months, int days)
{
    int n = years * 365 + days;

    for (int i = 0; i < months - 1; i++)
    {
        n += monthDays[i];
    }

    n += countLeapYears(years, months);

    return n;
}

int countLeapYears(int years, int months)
{
    if (months <= 2)
        years--;

    return years / 4 - years / 100 + years / 400;
}

bool isInvalidDate(long int date)
{
    if (date < 20190101 || date > 20221231)
    {
        return true;
    }

    int y, m, d;

    d = (int)date % 100;
    date = (long int)date / 100;
    m = (int)date % 100;
    date = (long int)date / 100;
    y = (int)date;

    if (m < 0 || m > 12)
    {
        return true;
    }

    if (d > monthDays[m - 1])
    {
        return true;
    }

    return false;
}

double getAntiBodyConcentration(int age, int days, string b, bool prior_infection)
{
    float alpha = 0.0, slope = 0.0, beta = 1;
    int baseline = 0;
    double antibody = 0.123;

    /* Set alpha and slope by age. */
    if (age >= 81)
    {
        alpha = -0.05;
        slope = -3.5;
    }
    else if (age >= 41)
    {
        alpha = 0;
        slope = -3;
    }
    else if (age >= 1)
    {
        alpha = 0.05;
        slope = -2;
    }

    /* Set baseline by vaccine brand. */
    if (b == "A")
    {
        baseline = 300;
    }
    else if (b == "B")
    {
        baseline = 800;
    }
    else if (b == "M")
    {
        baseline = 900;
    }

    /* Set beta by prior infection. */
    if (prior_infection)
    {
        beta = 0.5;
    }

    /* Calculate antibody concentration. */
    if (days <= 14)
    {
        antibody = (double)(baseline * (1 + alpha) * (days / 14));
    }
    else
    {
        antibody = (double)(baseline * (1 + alpha) + slope * (days - 14) * beta);
    }

    if (antibody < 0)
    {
        antibody = 0.0;
    }

    return round(antibody * 100.0) / 100.0;
}

void printMenu()
{
    cout << "***Antibody Calculator***" << endl;
    cout << "Enter 1 to input body data" << endl;
    cout << "Enter 2 to input vaccine data" << endl;
    cout << "Enter 3 to input prior infeciton" << endl;
    cout << "Enter R to input calculate antibody" << endl;
    cout << "Enter 0 to exit system" << endl;
}

bool isInvalidOperation(string oper)
{
    if (oper == "1" || oper == "2" || oper == "3" || oper == "R" || oper == "0")
    {
        return false;
    }

    return true;
}

bool isInvalidVaccinedDays(int days)
{

    if (days >= 1 && days <= (1 << 31 - 1))
    {
        return false;
    }

    return true;
}

bool isInvalidBrand(string b)
{
    if (b == "A" || b == "B" || b == "M")
    {
        return false;
    }

    return true;
}

bool isInvalidAge(int age)
{
    if (age <= 120 && age >= 1)
    {
        return false;
    }

    return true;
}

bool hasEnoughData(int age, int days, string b)
{
    if (age != -1 && days != -1 && b != "")
    {
        return true;
    }

    return false;
}