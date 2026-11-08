// BUDGET TRACKER - PF Semester 1
// Build: gcc -Wall budgetTracker.c -o budget.exe

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_EXPENSES   1000
#define MAX_DESC       50
#define NUM_CATEGORIES 8

struct Expense {
    int    id;
    int    day, month, year;
    int    category;            // 0..7
    double amount;
    char   description[MAX_DESC];
};

struct Settings {
    double monthlyIncome;
    double monthlyLimit;        // 0 = no limit
};

const char *CATEGORY_NAMES[NUM_CATEGORIES] = {
    "Food", "Transport", "Rent", "Utilities",
    "Entertainment", "Education", "Health", "Other"
};


//FILE

int loadExpensesFromFile(struct Expense list[]);
// Opens ExpenseFile.csv, skips the header line, reads every row into list.
// Returns how many were read. If the file does not exist, returns 0.

void saveExpensesToFile(struct Expense list[], int count);
// Opens ExpenseFile.csv for writing, writes the header line,
// then one comma-separated line per record.

void loadSettingsFromFile(struct Settings *s);
// Reads monthly income and limit from settings.csv.
// If the file does not exist, sets both to 0 and creates it.

void saveSettingsToFile(struct Settings *s);
// Writes the header line and the two numbers to settings.csv.

//FILE END


//INPUT

int inputWholeNumber(const char *prompt, int min, int max);
// Shows the prompt, reads the typed line, pulls out a whole number.
// Keeps asking until the number is between min and max.

double inputAmount(const char *prompt, double min);
// Same as above but for a decimal number, only a minimum (expenses use 1).

void inputText(const char *prompt, char string[], int size);
// Reads a whole line with spaces into string, removes the newline.
// Asks again if the line is empty.

int inputYesNo(const char *prompt);
// Returns 1 for y/Y, 0 for n/N, asks again for anything else.

void inputDate(int *day, int *month, int *year);
// Asks day, month, year using inputWholeNumber.
// Asks all three again until isDateReal returns 1.

int inputCategory(void);
// Shows the category list, asks for 1-8, returns the answer minus 1.

//INPUT END


//DATE

int isDateReal(int day, int month, int year);
// Returns 1 if the day exists in that month (leap year included),
// the year is 2000 or later, and the date is not after today.

void getTodayDate(int *day, int *month, int *year);
// Gets today's date from the system clock (month +1, year +1900).

int dateToNumber(int day, int month, int year);
// Returns year*10000 + month*100 + day, e.g. 20261108, so dates can be compared.

//DATE END


//ADD

int addExpense(struct Expense list[], int count, struct Settings *s);
// Stops if list is full. Fills one record using the input functions,
// adds it to list, saves the file, prints "Added", shows the budget warning.
// Returns the new count.

int generateNextId(struct Expense list[], int count);
// Returns the biggest id in list plus 1. Empty list gives 1.

void removeCommas(char string[]);
// Replaces every comma in string with a space so the CSV does not break.

void showCategoryList(void);
// Prints the 8 categories numbered 1 to 8.

double calculateMonthSpending(struct Expense list[], int count, int month, int year);
// Adds up the amounts of all records in that month and year.

void showBudgetWarning(struct Expense list[], int count, struct Settings *s, int month, int year);
// Compares that month's spending with the limit.
// Prints over budget, or careful at 80%, or a normal status. Silent if limit is 0.

//ADD END


//VIEW

void viewExpenses(struct Expense list[], int count);
// Asks sort order, sorts a COPY of list, prints table, chart, summary.

void sortExpenses(struct Expense list[], int count, int mode);
// Bubble sort. Swaps neighbours when isBefore says the second should come first.

int isBefore(struct Expense a, struct Expense b, int mode);
// mode 1: a.id < b.id   mode 2: a date before b   mode 3: a.amount > b.amount

void showExpenseTable(struct Expense list[], int count);
// Prints a header, a dashed line, one aligned row per record, a dashed line.

void calculateCategoryTotals(struct Expense list[], int count, double totals[]);
// Sets totals[0..7] to 0, then adds each record's amount into totals[category].

void showCategoryChart(struct Expense list[], int count);
// For each category with spending: name, a bar of # scaled to the biggest,
// the amount, and its percent of the total.

void showSummary(struct Expense list[], int count);
// Prints total spent, this month's total, biggest category, biggest single expense.

double calculateTotal(struct Expense list[], int count);
// Adds up all amounts.

int findBiggestExpense(struct Expense list[], int count);
// Returns the index of the record with the largest amount.

int findBiggestCategory(struct Expense list[], int count);
// Returns the index of the category with the largest total.

//VIEW END


//SEARCH

void searchExpenses(struct Expense list[], int count);
// Asks 1 category / 2 month / 3 description, runs that search into a results
// array, shows the results. Total is shown only for a month search.

int searchByCategory(struct Expense list[], int count, struct Expense results[]);
// Asks a category, copies matching records into results, returns how many.

int searchByMonth(struct Expense list[], int count, struct Expense results[]);
// Asks month and year, then calls filterByMonth.

int filterByMonth(struct Expense list[], int count, int month, int year, struct Expense results[]);
// Copies records of that month into results, returns how many. Also used by Budget.

int searchByDescription(struct Expense list[], int count, struct Expense results[]);
// Asks a word, copies records whose description contains it, returns how many.

int containsIgnoreCase(const char text[], const char word[]);
// Returns 1 if word appears inside text, ignoring upper/lower case.

void showSearchResults(struct Expense results[], int found, int showTotal);
// Prints "nothing found", or the table of results, plus the total if showTotal is 1.

//SEARCH END


//EDIT

void editExpense(struct Expense list[], int count, struct Settings *s);
// Asks an id, finds it (-1 = not found, stop), shows it, asks which field
// to change (date / category / amount / description), changes it, saves, warns.

int findById(struct Expense list[], int count, int id);
// Returns the index of the record with that id, or -1 if none.

void showOneExpense(struct Expense e);
// Prints one record, each field on its own line.

//EDIT END


//DELETE

int deleteExpense(struct Expense list[], int count);
// Asks an id, finds it, shows it, asks y/n, removes it, saves.
// Returns the new count.

void removeAtIndex(struct Expense list[], int count, int index);
// Moves every record after index one slot to the left.

//DELETE END


//BUDGET

void showBudget(struct Expense list[], int count, struct Settings *s);
// Asks month and year. Prints income, spent, remaining, limit, status,
// and a category chart for that month only.

double calculateRemaining(struct Settings *s, double spent);
// Returns income minus spent.

void showBudgetStatus(double spent, struct Settings *s);
// Prints OK (green), CAREFUL at 80% (yellow), or OVER BUDGET (red).
// Prints "no limit set" if limit is 0.

//BUDGET END


//SETTINGS

void changeSettings(struct Settings *s);
// Shows settings, asks 1 income / 2 limit / 0 back, reads the new value, saves.

void showSettings(struct Settings *s);
// Prints monthly income and limit ("none" if 0).

//SETTINGS END


//MENU

void showMenu(void);
// Prints the title and options:
// 1 Add  2 View  3 Search  4 Edit  5 Delete  6 Budget  7 Settings  0 Exit

void clearScreen(void);
// system("cls")

void pauseScreen(void);
// Prints "Press Enter to continue" and waits for Enter.

int main(void);
// Loads both files. Loops: clearScreen, showMenu, read choice 0-7,
// call that option, pauseScreen. Add and Delete give back the new count.

//MENU END
