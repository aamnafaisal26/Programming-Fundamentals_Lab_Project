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

// Colour codes: print one before text, print RESET after it.
#define RED            "\033[31m"   // kept for the over-budget warning only
#define GREEN          "\033[32m"
#define YELLOW         "\033[33m"
#define MAGENTA        "\033[35m"
#define GREY           "\033[90m"
#define BRIGHT_YELLOW  "\033[93m"
#define BRIGHT_BLUE    "\033[94m"
#define BRIGHT_MAGENTA "\033[95m"
#define BRIGHT_CYAN    "\033[96m"
#define BOLD           "\033[1m"
#define UNDERLINE      "\033[4m"
#define RESET          "\033[0m"    // turns off colour, bold and underline

// One colour per category, in the same order as CATEGORY_NAMES.
const char *CATEGORY_COLORS[NUM_CATEGORIES] = {
    GREEN, BRIGHT_CYAN, BRIGHT_MAGENTA, YELLOW,
    BRIGHT_BLUE, BRIGHT_YELLOW, MAGENTA, GREY
};


//DISPLAY

void showHeading(const char *text)
{
    // Screen title: bold and underlined, with a blank line above.
    printf("\n" BOLD UNDERLINE "%s" RESET "\n", text);
}

void showSubHeading(const char *text)
{
    // Smaller label inside a screen: bold only.
    printf("\n" BOLD "%s" RESET "\n", text);
}

//DISPLAY END


//FILE


int findCategoryByName(const char name[]){
    for(int i=0;i<NUM_CATEGORIES;i++){
        if(strcmp(name,CATEGORY_NAMES[i])==0){
            return i;       
        }
    }
    return -1;              
}

int loadExpensesFromFile(struct Expense list[]){
    FILE *file=fopen("Expenses.csv","r");
    if(file==NULL){
        return 0;
    }
    char line[200];
    int count=0;
    fgets(line, 200, file);
    while(count < MAX_EXPENSES){
        if(fgets(line, 200, file)==NULL){
            break;
        }
        struct Expense e;
        char categoryName[20];
        int got=sscanf(line,"%d,%d/%d/%d,%19[^,],%lf,%49[^\n]",&e.id,&e.day,&e.month,&e.year,categoryName,&e.amount,e.description);
        e.category=findCategoryByName(categoryName);
        if(got==7&&e.category!=-1){
            list[count]=e;
            count++;
        }
    }
    fclose(file);
    return count;
}


void saveExpensesToFile(struct Expense list[], int count){
    FILE *file=fopen("Expenses.csv","w");
    if (file == NULL) {
    printf(RED BOLD"Could not open the file.\n"RESET);
    return;
    }
    fprintf(file,"ID,Date,Category,Amount,Description\n");
    for(int i=0;i< count;i++){
        fprintf(file,"%d,%d/%d/%d,%s,%.2f,%s\n",list[i].id,list[i].day,list[i].month,list[i].year,CATEGORY_NAMES[list[i].category],list[i].amount,list[i].description);
    }
    fclose(file);


}


void saveSettingsToFile(struct Settings *s){
    FILE *file=fopen("Settings.csv","w");
    if(file==NULL){
        printf(RED BOLD "Could not save settings.\n" RESET);
        return;
    }
    fprintf(file,"monthly income,monthly limit\n");
    fprintf(file,"%.2f,%.2f\n",s->monthlyIncome,s->monthlyLimit);
    fclose(file);
}

void loadSettingsFromFile(struct Settings *s){
    FILE *file=fopen("Settings.csv","r");
    if(file==NULL){
        s->monthlyIncome=0;
        s->monthlyLimit=0;
        saveSettingsToFile(s);
        return;
    }
    char line[200];
    fgets(line,200,file);
    int got=0;
    if(fgets(line,200,file)!=NULL){
        got=sscanf(line,"%lf,%lf",&s->monthlyIncome,&s->monthlyLimit);
    }
    if(got!=2){
        s->monthlyIncome=0;
        s->monthlyLimit=0;
    }
    fclose(file);
}

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
// Shows the category list, asks for 1-8, returns the (answer minus 1).

//INPUT END


//DATE

int isDateReal(int day, int month, int year){
    int date=dateToNumber(day,month,year);
    int max_day,max_month,max_year;
    getTodayDate(&max_day,&max_month,&max_year);
    int maxdate=dateToNumber(max_day,max_month,max_year);
    int leastdate=dateToNumber(1,1,2000);
    int days_in_month[12]={31,((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))? 29:28,31,30,31,30,31,31,30,31,30,31};
    return (date>=leastdate&&date<=maxdate&&(month>=1&&month<=12)&&(day>=1&&day<=days_in_month[month-1]))?1:0;



}
void getTodayDate(int *day, int *month, int *year){
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    *day= t->tm_mday;
    *month= t->tm_mon + 1;
    *year=t->tm_year + 1900;

}

int dateToNumber(int day, int month, int year){
    int date;
    date=(year*10000)+(month*100)+(day);
    return date;
}
//END

int addExpense(struct Expense list[], int count, struct Settings *s);
// Stops if list is full. Fills one record using the input functions,
// adds it to list, saves the file, prints "Added", shows the budget warning.
// Returns the new count.

int generateNextId(struct Expense list[], int count){
    int biggest=0;
    for(int i=0;i<count;i++){
        if(list[i].id>biggest){
            biggest=list[i].id;
        }
    }
    return biggest+1;
}

void removeCommas(char string[]){
    for(int i=0;string[i]!='\0';i++){
        if (string[i]==','){
            string[i]=' ';
        }
    }
}

void showCategoryList(){
    for (int i=0;i<NUM_CATEGORIES;i++){
        printf("%d. %s\n",i+1,CATEGORY_NAMES[i]);
    }
}

double calculateMonthSpending(struct Expense list[], int count, int month, int year){
    double total=0;
    for(int i=0;i<count;i++){
        if(list[i].month==month && list[i].year==year){
            total+=list[i].amount;
        }
    }
    return total;
}

void showBudgetWarning(struct Expense list[], int count, struct Settings *s, int month, int year){
    if (s->monthlyLimit<=0){
        return;
    }
    double total=calculateMonthSpending(list,count,month,year);
    double limit=s->monthlyLimit;

    if (total>limit){
        printf("\n" BOLD RED "OVER LIMIT" RESET "\n");
        printf("Monthly budget : %.2f\n",limit);
        printf("Your spending  : %.2f\n",total);
        printf("Used           : %.1f%%\n",total/limit*100);
        printf("Over by        : %.2f\n",total-limit);
    }
    else if (total>=limit*0.8){
        printf("\n" BOLD YELLOW "CAREFUL" RESET "\n");
        printf("Monthly budget : %.2f\n",limit);
        printf("Your spending  : %.2f\n",total);
        printf("Used           : %.1f%%\n",total/limit*100);
        printf("Remaining      : %.2f\n",limit-total);
    }
    else{
        printf("\n" BOLD GREEN "ON TRACK" RESET "\n");
        printf("Monthly budget : %.2f\n",limit);
        printf("Your spending  : %.2f\n",total);
        printf("Used           : %.1f%%\n",total/limit*100);
        printf("Remaining      : %.2f\n",limit-total);
    }
}

//ADD END


//VIEW


//VIEW

double calculateTotal(struct Expense list[], int count)
{
    double total = 0;

    for (int i = 0; i < count; i++) {
        total += list[i].amount;
    }

    return total;
}

int findBiggestExpense(struct Expense list[], int count)
{
    if (count == 0)
        return -1;

    int biggest = 0;

    for (int i = 1; i < count; i++) {
        if (list[i].amount > list[biggest].amount)
            biggest = i;
    }

    return biggest;
}

void calculateCategoryTotals(struct Expense list[], int count, double totals[])
{
    for (int i = 0; i < NUM_CATEGORIES; i++) {
        totals[i] = 0;
    }

    for (int i = 0; i < count; i++) {
        if (list[i].category >= 0 &&
            list[i].category < NUM_CATEGORIES) {
            totals[list[i].category] += list[i].amount;
        }
    }
}

int findBiggestCategory(struct Expense list[], int count)
{
    if (count == 0)
        return -1;

    double totals[NUM_CATEGORIES];

    calculateCategoryTotals(list, count, totals);

    int biggest = 0;

    for (int i = 1; i < NUM_CATEGORIES; i++) {
        if (totals[i] > totals[biggest])
            biggest = i;
    }

    return biggest;
}

int isBefore(struct Expense a, struct Expense b, int mode)
{
    if (mode == 1)
        return a.id < b.id;

    if (mode == 2)
        return dateToNumber(a.day, a.month, a.year) <
               dateToNumber(b.day, b.month, b.year);

    if (mode == 3)
        return a.amount > b.amount;

    return 0;
}

void sortExpenses(struct Expense list[], int count, int mode)
{
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {

            if (isBefore(list[j + 1], list[j], mode)) {
                struct Expense temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            }
        }
    }
}

void showExpenseTable(struct Expense list[], int count)
{
    printf("\n" BOLD "%-5s %-12s %-15s %12s  %s" RESET "\n",
           "ID", "Date", "Category", "Amount", "Description");

    printf("-------------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%-5d %02d/%02d/%-6d %-15s %12.2f  %.30s\n",
               list[i].id,
               list[i].day,
               list[i].month,
               list[i].year,
               CATEGORY_NAMES[list[i].category],
               list[i].amount,
               list[i].description);
    }

    printf("-------------------------------------------------------------------------------\n");
}

void showCategoryChart(struct Expense list[], int count)
{
    double totals[NUM_CATEGORIES];
    double total = calculateTotal(list, count);
    double biggest = 0;

    calculateCategoryTotals(list, count, totals);

    for (int i = 0; i < NUM_CATEGORIES; i++) {
        if (totals[i] > biggest)
            biggest = totals[i];
    }

    showHeading("CATEGORY SPENDING CHART");

    if (biggest == 0 || total == 0) {
        printf("No spending to display.\n");
        return;
    }

    // every category is listed, even one with no spending
    for (int i = 0; i < NUM_CATEGORIES; i++) {
        int bars = (int)(totals[i] / biggest * 20);
        double percent = totals[i] / total * 100;

        printf("%-16s ", CATEGORY_NAMES[i]);

        printf("%s", CATEGORY_COLORS[i]);   // colour on

        for (int j = 0; j < bars; j++) {
            printf("*");
        }

        int printed = bars;

        if (bars == 0 && totals[i] > 0) {
            printf(".");    // spent something, but too small for a full star
            printed = 1;
        }

        printf(RESET);                      // colour off, before the padding

        // fill the rest of the 20-wide bar area with spaces
        for (int j = printed; j < 20; j++) {
            printf(" ");
        }

        printf(" %12.2f  %5.1f%%\n", totals[i], percent);
    }
}

void showSummary(struct Expense list[], int count)
{
    if (count == 0) {
        printf("\nNo expenses to summarize.\n");
        return;
    }

    int day, month, year;

    getTodayDate(&day, &month, &year);

    double total = calculateTotal(list, count);
    double monthly = calculateMonthSpending(list, count, month, year);

    int biggestExpense = findBiggestExpense(list, count);
    int biggestCategory = findBiggestCategory(list, count);

    double totals[NUM_CATEGORIES];

    calculateCategoryTotals(list, count, totals);

    showHeading("EXPENSE SUMMARY");
    printf("Total spent: %.2f\n", total);
    printf("This month's spending: %.2f\n", monthly);

    if (biggestCategory != -1) {
        printf("Biggest category: %s (%.2f)\n",
               CATEGORY_NAMES[biggestCategory],
               totals[biggestCategory]);
    }

    if (biggestExpense != -1) {
        printf("Biggest single expense: %s (%.2f)\n",
               list[biggestExpense].description,
               list[biggestExpense].amount);
    }
}

void viewExpenses(struct Expense list[], int count)
{
    if (count == 0) {
        printf("\nNo expenses found.\n");
        return;
    }

    struct Expense copy[MAX_EXPENSES];

    for (int i = 0; i < count; i++) {
        copy[i] = list[i];
    }

    printf("\n1. Sort by ID");
    printf("\n2. Sort by Date");
    printf("\n3. Sort by Amount\n");

    int mode = inputWholeNumber("Choose sort order: ", 1, 3);

    sortExpenses(copy, count, mode);

    showExpenseTable(copy, count);
    showCategoryChart(copy, count);
    showSummary(copy, count);
}

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

int findById(struct Expense list[], int count, int id){
    for(int i=0;i<count;i++){
        if(list[i].id==id){
            return i;
        }
    }
    return -1;
}

void showOneExpense(struct Expense e){
    printf(BOLD"ID          : "RESET"%d\n",e.id);
    printf(BOLD"Date        : "RESET"%02d/%02d/%d\n",e.day,e.month,e.year);
    printf(BOLD"Category    : "RESET"%s\n",CATEGORY_NAMES[e.category]);
    printf(BOLD"Amount      : "RESET"%.2f\n",e.amount);
    printf(BOLD"Description : "RESET"%s\n",e.description);
}

//EDIT END



//DELETE

void removeAtIndex(struct Expense list[], int count, int index)
{
    for (int i = index; i < count - 1; i++) {
        list[i] = list[i + 1];
    }
}

int deleteExpense(struct Expense list[], int count)
{
    if (count == 0) {
        printf("\nNo expenses to delete.\n");
        return count;
    }

    int id = inputWholeNumber("Enter expense ID to delete: ", 1, 999999);
    int index = findById(list, count, id);

    if (index == -1) {
        printf("\nExpense not found.\n");
        return count;
    }

    showSubHeading("Expense found:");
    showOneExpense(list[index]);

    int confirm = inputYesNo("Are you sure you want to delete? (y/n): ");

    if (confirm == 0) {
        printf("\nDeletion cancelled.\n");
        return count;
    }

    removeAtIndex(list, count, index);

    count--;

    saveExpensesToFile(list, count);

    printf("\nExpense deleted successfully!\n");

    return count;
}

//DELETE END


//BUDGET

void showBudget(struct Expense list[], int count, struct Settings *s);
// Asks month and year. Prints income, spent, remaining, limit, status,
// and a category chart for that month only.

double calculateRemaining(struct Settings *s, double spent){
    return (s->monthlyIncome-spent);
}

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
