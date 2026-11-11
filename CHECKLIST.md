# Budget Tracker: Function Checklist

Last updated: 11 November 2026

## Overall progress

**30 of 52 functions done: 58% complete**

```
[#############################.....................]  58%
```

| Teammate | Areas | Done | Progress |
|---|---|---|---|
| **Aamna** | Display, File, Date, Add, Edit, Budget, Menu | 18 / 25 | `[##############......]` 72% |
| **Hania** | View, Delete | 12 / 12 | `[####################]` 100% |
| **Mehreen** | Input, Search, Settings | 0 / 15 | `[....................]` 0% |
| **Total** | | **30 / 52** | `[############........]` **58%** |

---

# Aamna: 18 of 25 done (72%)

## Display: 2 / 2

- [x] `showHeading`: prints a bold, underlined screen title
- [x] `showSubHeading`: prints a bold label inside a screen

## File: 5 / 5

- [x] `findCategoryByName`: turns a category word back into its number 0 to 7
- [x] `saveExpensesToFile`: writes every expense to Expenses.csv
- [x] `loadExpensesFromFile`: reads Expenses.csv back into the list
- [x] `saveSettingsToFile`: writes income and limit to Settings.csv
- [x] `loadSettingsFromFile`: reads Settings.csv, or creates it with 0 and 0

## Date: 3 / 3

- [x] `dateToNumber`: turns a date into one number like 20261108
- [x] `getTodayDate`: gets today's date from the clock
- [x] `isDateReal`: checks the date exists, is 2000 or later, and is not in the future

## Add: 5 / 6

- [ ] `addExpense`: asks for one expense, stores it, saves, shows the warning. *Waits on Mehreen's Input.*
- [x] `generateNextId`: biggest ID plus one
- [x] `removeCommas`: turns commas into spaces so the CSV is safe
- [x] `showCategoryList`: prints the 8 categories numbered 1 to 8
- [x] `calculateMonthSpending`: total spent in one month
- [x] `showBudgetWarning`: ON TRACK, CAREFUL or OVER LIMIT with the numbers

## Edit: 2 / 3

- [ ] `editExpense`: finds an expense by ID and changes one field. *Waits on Mehreen's Input.*
- [x] `findById`: position of an ID in the list, or -1
- [x] `showOneExpense`: prints one expense with bold labels

## Budget: 1 / 2

- [ ] `showBudget`: the monthly budget screen. *Waits on Mehreen's `inputWholeNumber` and `filterByMonth`.*
- [x] `calculateRemaining`: income minus spending

## Menu: 0 / 4

- [ ] `showMenu`: prints the title and the 8 options
- [ ] `clearScreen`: clears the terminal
- [ ] `pauseScreen`: waits for Enter
- [ ] `main`: loads both files, then runs the menu loop

---

# Hania: 12 of 12 done (100%)

## View: 10 / 10

- [x] `viewExpenses`: asks sort order, then shows table, chart and summary
- [x] `sortExpenses`: bubble sort on a copy of the list
- [x] `isBefore`: decides order by ID, date or amount
- [x] `showExpenseTable`: aligned table of expenses
- [x] `calculateCategoryTotals`: total per category
- [x] `showCategoryChart`: coloured bar per category
- [x] `showSummary`: total, this month, biggest category and expense
- [x] `calculateTotal`: sum of all amounts
- [x] `findBiggestExpense`: position of the largest amount
- [x] `findBiggestCategory`: category with the largest total

## Delete: 2 / 2

- [x] `deleteExpense`: finds an expense, asks y/n, removes it, saves
- [x] `removeAtIndex`: closes the gap left by a deleted expense

---

# Mehreen: 0 of 15 done (0%)

## Input: 0 / 6

- [ ] `inputWholeNumber`: asks until it gets a whole number in range
- [ ] `inputAmount`: asks until it gets a number at or above a minimum
- [ ] `inputText`: reads a full line of text
- [ ] `inputYesNo`: returns 1 for y, 0 for n
- [ ] `inputDate`: asks day, month, year until `isDateReal` accepts it
- [ ] `inputCategory`: shows the list, returns the choice as 0 to 7

## Search: 0 / 7

- [ ] `searchExpenses`: asks how to search, then shows the results
- [ ] `searchByCategory`: expenses in one category
- [ ] `searchByMonth`: asks a month, then calls `filterByMonth`
- [ ] `filterByMonth`: expenses in one month. *Aamna's Budget screen also uses this.*
- [ ] `searchByDescription`: expenses whose description contains a word
- [ ] `containsIgnoreCase`: word search that ignores capital letters
- [ ] `showSearchResults`: prints the results table

## Settings: 0 / 2

- [ ] `changeSettings`: change income or limit, then save
- [ ] `showSettings`: prints income and limit

---

## Blocking order

Mehreen's Input functions block the most work. Until `inputWholeNumber` exists, nothing that asks the user a question can run, including the main menu and the sort question in View.

1. **Input** (Mehreen) first: unblocks `addExpense`, `editExpense`, `showBudget`, `main`, and View's sort question.
2. **`filterByMonth`** (Mehreen) next: unblocks `showBudget`.
3. **Menu and `main`** (Aamna) last: the program runs end to end.

## Tidy-up before the demo

- [ ] Put back the `//DATE END` and `//ADD` markers after `dateToNumber`.
- [ ] Fix the three ordering warnings: move `isDateReal` below `dateToNumber`, or add one prototype line per function near the top of the file.
- [ ] Update the PDF or tell the team that the files are now `Expenses.csv` and `Settings.csv`.
- [ ] Tell the team that `showBudgetStatus` was dropped; `showBudgetWarning` does that job.
- [ ] Remove the duplicate `//VIEW` marker.
- [ ] Test the colours in the terminal used for the demo.
