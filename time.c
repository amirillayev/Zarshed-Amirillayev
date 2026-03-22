#include <stdio.h>
#include <time.h>

typedef struct { // creating the new data type "date"
    int day;
    int month;
    int year;
} date;

int is_valid_date(date d) {      // what if user enters "162272 74y34 7364736"
    if (d.year < 1900 || d.year > 2025) return 0;
    if (d.month < 1 || d.month > 12) return 0;
    int days_in_month[] = {31,28,29,31,30,31,30,31,31,30,31,30,31};
    // Leap year check
    if (d.year % 4 == 0 && (d.year % 100 != 0 || d.year % 400 == 0))
        days_in_month[2] = 29;
    if (d.day < 1 || d.day > days_in_month[d.month]) return 0;
    return 1;
}

int calculate(date birth, struct tm *today ) {  // How old is he
    int age = today->tm_year + 1900 - birth.year;
    if (today->tm_mon +1 < birth.month || (today->tm_mon +1 == birth.month && today->tm_mday < birth.day)){
        age --;
    }
    return age;


}

int days_until_birthday(date birth, struct tm *today) {    //How many yyears until nect aging 
    int bday_day = birth.day;            
    int bday_month = birth.month;        
    int cur_year = today->tm_year + 1900; 
    int cur_mon = today->tm_mon + 1;      

    struct tm bday = {0};
    bday.tm_year = cur_year - 1900;
    bday.tm_mon = bday_month - 1;
    bday.tm_mday = bday_day;
    mktime(&bday);
    
    struct tm now = *today;
    mktime(&now);

    time_t bday_time = mktime(&bday);
    time_t now_time = mktime(&now);

    int days = (int)((bday_time - now_time) / 86400);
    if (days < 0) {
        bday.tm_year++;
        bday_time = mktime(&bday);
        days = (int)((bday_time - now_time) / 86400);
    }
    return days;
}

long long days_alive(date birth, struct tm *today) { // !dead period
    struct tm bday = {0}; 
    bday.tm_year = birth.year - 1900;
    bday.tm_mon = birth.month - 1;
    bday.tm_mday = birth.day;
    time_t bday_time = mktime(&bday);
    time_t now_time = mktime(today);
    return (long long)((now_time - bday_time) / 86400);
}

const char* day_of_week(date birth) {   // day of week ( the name)
    struct tm bday = {0};
    bday.tm_year = birth.year - 1900;
    bday.tm_mon = birth.month - 1;
    bday.tm_mday = birth.day;
    mktime(&bday);
    const char *days[] = {"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
    return days[bday.tm_wday];
}



int main() {                           // THIS IS WHERE MAGIC HAPPENS!
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    printf("Current date and time: %s", asctime(t));



    date birth_date;                 // introducing ; 'birth_date'
    int valid = 0;
    while (!valid) {
        printf("Enter your day of birth(DD MM YYYY): \n");
        if (scanf("%d %d %d", &birth_date.day, &birth_date.month, &birth_date.year) !=3) {   //valid date time
            printf("Invalid format! Please use DD MM YYYY.\n");
            while (getchar() != '\n'); // clear buffer
            continue;

        }
        if (!is_valid_date(birth_date)) {
            printf("Invalid date! Please enter a real date! \n");
        }

        else {
            valid = 1;
        }
    }

    
    printf("Your date of birth is: %02d/%02d/%04d\n", birth_date.day, birth_date.month, birth_date.year);  // the printing
    
    printf("You are %d years old!\n", calculate(birth_date, t));                                          // where the age reveals

    int choice = 0;
    while (choice != 4) {                                     // choices
        printf("\n=== What would you like to know? ===\n");
        printf("1. Days until your next birthday\n");
        printf("2. Day of the week you were born\n");
        printf("3. How many days you've been alive\n");
        printf("4. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Your next birthday is in %d days!\n", days_until_birthday(birth_date, t));
                break;
            case 2:
                printf("You were born on a %s!\n", day_of_week(birth_date));
                break;
            case 3:
                printf("You have been alive for %lld days!\n", days_alive(birth_date, t));
                break;
            case 4:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice, try again.\n");
        }
    }

    return 0;             // КОНЕЦЬ
}

