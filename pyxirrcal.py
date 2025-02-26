from datetime import date
from pyxirr import xirr


dates = [date(2020, 1, 1), date(2020, 3, 1), date(2020, 10, 30), date(2021, 2, 15)]
values = [-10_000, 1000, 5000, 5000]
a = xirr(dates, values)
print(a)

dates2 = [date(2020, 1, 1), date(2021, 1, 1), date(2022, 1, 1)]
amounts = [-1000, 500, 1000]
b = xirr(dates2, amounts)
print(b)
