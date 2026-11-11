# Budget Tracker: Function Checklist

Last updated: 11 November 2026

## Overall progress

**37 of 52 functions done: 71% complete**

```
[####################################..............]  71%
```

| Teammate | Areas | Done | Progress |
|---|---|---|---|
| **Aamna** | Display, File, Date, Add, Edit, Budget, Menu | 25 / 25 | `[####################]` 100% |
| **Hania** | View, Delete | 12 / 12 | `[####################]` 100% |
| **Mehreen** | Input, Search, Settings | 0 / 15 | `[....................]` 0% |
| **Total** | | **37 / 52** | `[##############......]` **71%** |

Everything except Mehreen's 15 functions is written and tested. The full program was run end to end with stand-ins for Mehreen's functions: adding, viewing, editing, deleting, the budget screen and settings all worked, and the data survived a restart.

---

# Aamna: 25 of 25 done (100%)

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

## Add: 6 / 6

- [x] `addExpense`: asks for one expense, stores it, saves, shows the warning
- [x] `generateNextId`: biggest ID plus one
- [x] `removeCommas`: turns commas into spaces so the CSV is safe
- [x] `showCategoryList`: prints the 8 categories numbered 1 to 8
- [x] `calculateMonthSpending`: total spent in one month
- [x] `showBudgetWarning`: ON TRACK, CAREFUL or OVER LIMIT with the numbers

## Edit: 3 / 3

- [x] `editExpense`: shows the table, finds an expense by ID, changes one field
- [x] `findById`: position of an ID in the list, or -1
- [x] `showOneExpense`: prints one expense with bold labels

## Budget: 2 / 2

- [x] `showBudget`: the monthly budget screen, with Saved in red when negative
- [x] `calculateRemaining`: income minus spending

## Menu: 4 / 4

- [x] `showMenu`: prints the title and the 8 options
- [x] `clearScreen`: clears the terminal
- [x] `pauseScreen`: waits for Enter
- [x] `main`: loads both files, then runs the menu loop

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

- [ ] `changeSettings`: change income or limit, then save. *Change only `monthlyIncome` or `monthlyLimit`, then call `saveSettingsToFile(s)`. Settings.csv also stores `lastId`, the ID counter, and it must not be reset.*
- [ ] `showSettings`: prints income and limit

---

## What is blocking the finished program

Only Mehreen's functions. Every other piece is already written and waiting for them.

1. **Input** first: the menu, Add, Edit, the Budget screen and View's sort question all ask the user through these. Until they exist, the program cannot run.
2. **`filterByMonth`** next: the Budget screen needs it for that month's chart.
3. **Settings and the rest of Search**: after those, every menu option works.

Once Mehreen pushes, the whole team should run the program once from start to finish.

## Tidy-up before the demo

- [ ] Put back the `//DATE END` and `//ADD` markers after `dateToNumber`.
- [ ] Fix the ordering warnings: add one prototype line per function near the top of the file.
- [ ] Update the PDF or tell the team that the files are now `Expenses.csv` and `Settings.csv`.
- [ ] Tell the team that `showBudgetStatus` was dropped; `showBudgetWarning` does that job.
- [ ] Remove the duplicate `//VIEW` marker.
- [x] Show the expense table before asking for an ID in Delete, as Edit already does.
- [ ] Use `showHeading` for the Budget screen's title, to match the other screens.
- [ ] Test the colours in the terminal used for the demo.
