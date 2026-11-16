# Budget Tracker: Function Checklist

Last updated: 16 November 2026

## Overall progress

**53 of 53 functions done: 100% complete**

```
[##################################################]  100%
```

| Teammate | Areas | Done | Progress |
|---|---|---|---|
| **Aamna** | Display, File, Date, Add, Edit, Budget, Menu | 25 / 25 | `[####################]` 100% |
| **Hania** | View, Delete | 12 / 12 | `[####################]` 100% |
| **Mehreen** | Input, Search, Settings | 16 / 16 | `[####################]` 100% |
| **Total** | | **53 / 53** | `[####################]` **100%** |

Every function is written. The finished program was run end to end on 16 November: settings, adding (with bad dates, categories, amounts and empty text all rejected), viewing, all four searches, editing, deleting and the budget screen worked, and the data survived a restart. It also closes cleanly if the input ends suddenly.

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

# Mehreen: 16 of 16 done (100%)

## Input: 6 / 6

- [x] `inputWholeNumber`: asks until it gets a whole number in range
- [x] `inputAmount`: asks until it gets a number at or above a minimum
- [x] `inputText`: reads a full line of text
- [x] `inputYesNo`: returns 1 for y, 0 for n
- [x] `inputDate`: asks day, month, year until `isDateReal` accepts it
- [x] `inputCategory`: shows the list, returns the choice as 0 to 7

## Search: 8 / 8

- [x] `searchExpenses`: asks how to search, then shows the results
- [x] `searchByCategory`: expenses in one category
- [x] `searchByMonth`: asks a month, then calls `filterByMonth`
- [x] `searchByYear`: expenses in one year, with a total. *Extra feature, not in the original plan.*
- [x] `filterByMonth`: expenses in one month. *Aamna's Budget screen also uses this.*
- [x] `searchByDescription`: expenses whose description contains a word
- [x] `containsIgnoreCase`: word search that ignores capital letters
- [x] `showSearchResults`: prints the results table

## Settings: 2 / 2

- [x] `changeSettings`: change income or limit, then save, keeping the ID counter
- [x] `showSettings`: prints income and limit

---

## Next: test as a team

Every function is written, so nothing is blocking the program any more. Before the demo, each teammate should pull, build and run it once from start to finish:

```bash
git pull
gcc -Wall budgetTracker.c -o budgetTracker.exe
./budgetTracker.exe
```

## Tidy-up before the demo

- [x] Put back the `//DATE END` and `//ADD` markers after `dateToNumber`.
- [x] Fix the ordering warnings: a function list near the top of the file has one promise line per function, so functions can stay in any order inside their sections.
- [ ] Update the PDF or tell the team that the files are now `Expenses.csv` and `Settings.csv`.
- [ ] Tell the team that `showBudgetStatus` was dropped; `showBudgetWarning` does that job.
- [x] Remove the duplicate `//VIEW` marker.
- [x] Show the expense table before asking for an ID in Delete, as Edit already does.
- [x] Use `showHeading` for the Budget screen's title, to match the other screens.
- [x] Put `0. Exit` with the other menu options, and say what 0 does in every prompt that accepts it.
- [x] The Settings prompt that accepts 0 says what it does.
- [x] Input functions close the program cleanly if the input ends suddenly, instead of looping forever.
- [ ] Optional: let Search go back with 0, like Edit and Settings.
- [ ] Optional: reject numbers with letters after them, such as `5abc`, instead of reading them as 5.
- [ ] Test the colours in the terminal used for the demo.
