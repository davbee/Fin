#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <tuple>

using namespace std;

// Convert a date (year, month, day) to time_t.
time_t dateToTimeT(int year, int month, int day)
{
    tm time_in = {0};
    time_in.tm_year = year - 1900; // years since 1900
    time_in.tm_mon = month - 1;    // months [0, 11]
    time_in.tm_mday = day;
    time_in.tm_hour = 0;
    time_in.tm_min = 0;
    time_in.tm_sec = 0;
    return mktime(&time_in);
}

// XIRR calculation using Newton's method.
// years: vector of year fractions (difference from the first date)
// amounts: corresponding cash flow amounts
double xirr(const vector<double> &amounts, const vector<double> &years, double guess = 0.1)
{
    const double tol = 1e-7;
    const int max_iter = 1000;
    double rate = guess;
    for (int iter = 0; iter < max_iter; iter++)
    {
        double npv = 0.0;
        double dNPV = 0.0;
        for (size_t i = 0; i < amounts.size(); i++)
        {
            double denom = pow(1.0 + rate, years[i]);
            npv += amounts[i] / denom;
            dNPV -= years[i] * amounts[i] / (denom * (1.0 + rate));
        }
        double new_rate = rate - npv / dNPV;
        if (fabs(new_rate - rate) < tol)
        {
            return new_rate;
        }
        rate = new_rate;
    }
    return rate;
}

int main()
{
    // First example
    vector<tuple<int, int, int>> dateTuples = {
        {2020, 1, 1},
        {2020, 3, 1},
        {2020, 10, 30},
        {2021, 2, 15}};
    vector<double> amounts = {-10000, 1000, 5000, 5000};

    // Calculate year fractions from the first date.
    time_t base_time = dateToTimeT(get<0>(dateTuples[0]), get<1>(dateTuples[0]), get<2>(dateTuples[0]));
    vector<double> yearsDifferences;
    for (const auto &d : dateTuples)
    {
        time_t cur_time = dateToTimeT(get<0>(d), get<1>(d), get<2>(d));
        double diff_days = difftime(cur_time, base_time) / (60 * 60 * 24);
        yearsDifferences.push_back(diff_days / 365.0);
    }

    double result1 = xirr(amounts, yearsDifferences);
    cout << fixed << setprecision(6);
    cout << "XIRR for first example: " << result1 << "\n";

    // Second example
    vector<tuple<int, int, int>> dateTuples2 = {
        {2020, 1, 1},
        {2021, 1, 1},
        {2022, 1, 1}};
    vector<double> amounts2 = {-1000, 500, 1000};

    base_time = dateToTimeT(get<0>(dateTuples2[0]), get<1>(dateTuples2[0]), get<2>(dateTuples2[0]));
    vector<double> yearsDifferences2;
    for (const auto &d : dateTuples2)
    {
        time_t cur_time = dateToTimeT(get<0>(d), get<1>(d), get<2>(d));
        double diff_days = difftime(cur_time, base_time) / (60 * 60 * 24);
        yearsDifferences2.push_back(diff_days / 365.0);
    }

    double result2 = xirr(amounts2, yearsDifferences2);
    cout << "XIRR for second example: " << result2 << "\n";

    return 0;
}