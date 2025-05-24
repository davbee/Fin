#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>

double round2(double value) {
    return std::round(value * 100.0) / 100.0;
}

int main() {
    // Set up loan terms
    double loan = 100000.00;
    double rate = 10.0 / 100;
    double mrate = rate / 12;
    int years = 15;
    int months = years * 12;

    // Initialize totals
    double tinterest = 0.0;
    double tpayment = 0.0;
    double tprincipal = 0.0;

    // Calculate monthly payment using the formula:
    // payment = loan * [ mrate * (1+mrate)^months ] / [ (1+mrate)^months - 1 ]
    double payment = round2(loan * ((mrate * std::pow(1 + mrate, months)) / (std::pow(1 + mrate, months) - 1)));

    // Set up amortization table.
    // Row format: month, payment, total payment, interest, total interest, principal, total principal, loan balance
    std::vector<std::vector<double>> amortization;
    // First row with initial loan balance: seven zeros then the loan
    amortization.push_back({0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, loan});

    // Calculate payment, interest, principal, and loan balance for each month
    for (int month = 0; month < months; month++) {
        double interest = round2(loan * mrate);
        tinterest = round2(tinterest + interest);
        tpayment = round2(tpayment + payment);
        double principal = round2(payment - interest);
        tprincipal = round2(tprincipal + principal);
        loan = round2(loan - principal);

        // Assemble row of data
        std::vector<double> row = {
            static_cast<double>(month + 1), // Month number starting at 1
            payment,
            tpayment,
            interest,
            tinterest,
            principal,
            tprincipal,
            loan
        };
        amortization.push_back(row);
    }

    // Create csv file for the amortization table
    std::ofstream outfile("amortization.csv");
    if (!outfile) {
        std::cerr << "Error opening file for writing!" << std::endl;
        return 1;
    }

    // Write header row
    outfile << "month,payment,total payment,interest,total Interest,principal,total principal,loan balance\n";
    
    // Write data rows, formatting numbers to two decimals
    for (const auto &row : amortization) {
        for (size_t i = 0; i < row.size(); i++) {
            outfile << std::fixed << std::setprecision(2) << row[i];
            if (i != row.size() - 1)
                outfile << ",";
        }
        outfile << "\n";
    }
    
    outfile.close();
    std::cout << "Amortization schedule written to amortization.csv" << std::endl;
    
    return 0;
}
