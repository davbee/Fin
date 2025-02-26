import pandas as pd


# set up load term
loan: float = 100000.00
rate: float = 10.0 / 100
mrate: float = rate / 12
years: int = 15
months: int = years * 12

# initialize
tinterest: float = 0.0
tpayment: float = 0.0
tprincipal: float = 0.0

# calculate annual loan payment amount
# M = P [ I (1 + I)N ] / [ (1 + I)N − 1]
payment: float = round(
    loan * ((mrate * (1 + mrate) ** months) / ((1 + mrate) ** months - 1)), 2
)

# set up the original loan balance in mortgage table
amortization = [[0.0] * 7 + [loan]]

# calculate payment, interest, principal, and loan balance for each month
for month in range(months):
    interest = round(loan * mrate, 2)
    tinterest += interest
    tpayment += payment
    principal: float = payment - interest
    tprincipal += principal
    loan = loan - principal

    # assemble row of data as a list and append it in [[]]
    aamort = [month, payment, tpayment, interest, tinterest, principal,
              tprincipal, loan]
    amortization.append(aamort)

# create a dataframe for amortization table and round numbers to 2 digits
am = pd.DataFrame(amortization).round(2)

# create column headers for the dataframe
am.columns = pd.Index(
    [
        "month",
        "payment",
        "total payment",
        "interest",
        "total Interest",
        "principal",
        "total principal",
        "loan balance",
    ]
)

# create csv file for the dataframe
am.to_csv("amortization.csv", index=False)
