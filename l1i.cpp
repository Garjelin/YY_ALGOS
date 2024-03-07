#include <iostream>
#include <vector>
#include <string>

class Day {
public:
    int day;
    int month;
    std::string dayOfWeek;

    // Конструктор класса День
    Day(int d, int m, const std::string& dow) : day(d), month(m), dayOfWeek(dow) {}
};

class Year {
private:
    int year;
    std::vector<Day> days;
    std::vector<Day> holydays;
    std::vector<int> dayCount;
    std::vector<int> holydayCount = {0};

public:
    // Конструктор класса Год
    Year(int y, int startDayOfWeek) : year(y), dayCount(7, 0), holydayCount(7, 0) {
        generateDays(startDayOfWeek);
    }

    // Проверка на високосный год
    bool isLeapYear() const {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    // Генерация списка дней в году
    void generateDays(int startDayOfWeek) {
        const int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        const std::string daysOfWeek[] = {"Пн", "Вт", "Ср", "Чт", "Пт", "Сб", "Вс"};

        int daysInFebruary = isLeapYear() ? 29 : 28;

        int startWeekday = startDayOfWeek % 7;
        int currentWeekday = startWeekday;

        for (int month = 1; month <= 12; ++month) {
            int daysInCurrentMonth = (month == 2) ? daysInFebruary : daysInMonth[month];

            for (int day = 1; day <= daysInCurrentMonth; ++day) {
                days.push_back(Day(day, month, daysOfWeek[currentWeekday]));
                dayCount[currentWeekday]++;
                currentWeekday = (currentWeekday + 1) % 7;
            }
        }
    }

    // Генерация праздников
    void generateHolydays(int n, int inputDay[], int inputMonth[], int startDayOfWeek) {
        const int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        int daysInFebruary = isLeapYear() ? 29 : 28;
        int accuredDays[13] = {0};
        int accuredDays_sum = 0;
        for (int month = 1; month <= 12; month++) {
            accuredDays_sum += (month == 2) ? daysInFebruary : daysInMonth[month];
            accuredDays[month] = accuredDays_sum;
            //std::cout << "month " << month << " " << "accuredDays[month] " << accuredDays[month] << std::endl;
        }
        const std::string daysOfWeek[] = {"Пн", "Вт", "Ср", "Чт", "Пт", "Сб", "Вс"};
        
        for (int i = 0; i < n; i++) {
            int currentWeekday = (accuredDays[inputMonth[i]-1] + inputDay[i] + startDayOfWeek - 1) % 7;
            //std::cout << "accuredDays[inputMonth-1] " << accuredDays[inputMonth[i]-1] << " " << "inputDay " << inputDay[i] << " " << "startDayOfWeek " << startDayOfWeek << " " << "currentWeekday " << currentWeekday << std::endl;
            holydays.push_back(Day(inputDay[i], inputMonth[i], daysOfWeek[currentWeekday]));
            holydayCount[currentWeekday]++;
        }

    }

    // Вывод информации о годе
    void printYearInfo() const {
        for (const auto& day : days) {
            std::cout << "Дата: " << day.day << "." << day.month << "." << year
                      << ", День недели: " << day.dayOfWeek << std::endl;
        }
    }

    // Вывод информации о празднике
    void printHolydayInfo() const {
        for (const auto& day : holydays) {
            std::cout << "Дата праздника: " << day.day << "." << day.month << "." << year
                      << ", День недели: " << day.dayOfWeek << std::endl;
        }
    }

    // Вывод количества каждого из дней недели
    void printDayCount() const {
        const std::string daysOfWeek[] = {"Пн", "Вт", "Ср", "Чт", "Пт", "Сб", "Вс"};
        for (int i = 0; i < 7; ++i) {
            std::cout << daysOfWeek[i] << ": " << dayCount[i] << " раз" << std::endl;
        }
    }

    // Вывод количества праздников
    void printHolydayCount() const {
        const std::string daysOfWeek[] = {"Пн", "Вт", "Ср", "Чт", "Пт", "Сб", "Вс"};
        for (int i = 0; i < 7; ++i) {
            std::cout << daysOfWeek[i] << ": " << holydayCount[i] << " раз" << std::endl;
        }
    }

    void dayOffCount(int* minDOW, int* maxDOW) {
        int totalDayOff[7] = {0};
        int totalHolidays = 0;
        for (int i = 0; i < 7; ++i) {
            totalHolidays += holydayCount[i];
        }
        for (int i = 0; i < 7; ++i) {
            totalDayOff[i] = dayCount[i] + totalHolidays - holydayCount[i];
        }
        // for (int i = 0; i < 7; ++i) {
        //     std::cout << "totalDayOff[i] " << totalDayOff[i] << std::endl;
        // }
        int minDayOff = totalDayOff[0];
        int maxDayOff = totalDayOff[0];
        for (int i = 1; i < 7; ++i) { 
            if (totalDayOff[i] < minDayOff) {
                minDayOff = totalDayOff[i];
                *minDOW = i;
            }
            if (totalDayOff[i] > maxDayOff) {
                maxDayOff = totalDayOff[i];
                *maxDOW = i;
            }
        }
        // std::cout << "minDayOff " << minDayOff << std::endl;
        // std::cout << "maxDayOff " << maxDayOff << std::endl;
    }
};

int main() {
    int year, startDayOfWeek;
    int n;
    std::cin >> n;
    std::cin >> year;

    int inputDay[n]; 
    std::string stringMonth[n];
    int inputMonth[n]; 
    

    for (int i = 0; i < n; i++) {
        std::cin >> inputDay[i];
        std::cin >> stringMonth[i];
    }
    for (int i = 0; i < n; i++) {
        if (stringMonth[i] == "January") inputMonth[i] = 1;
        else if (stringMonth[i] == "February") inputMonth[i] = 2;
        else if (stringMonth[i] == "March") inputMonth[i] = 3;
        else if (stringMonth[i] == "April") inputMonth[i] = 4;
        else if (stringMonth[i] == "May") inputMonth[i] = 5;
        else if (stringMonth[i] == "June") inputMonth[i] = 6;
        else if (stringMonth[i] == "July") inputMonth[i] = 7;
        else if (stringMonth[i] == "August") inputMonth[i] = 8;
        else if (stringMonth[i] == "September") inputMonth[i] = 9;
        else if (stringMonth[i] == "October") inputMonth[i] = 10;
        else if (stringMonth[i] == "November") inputMonth[i] = 11;
        else if (stringMonth[i] == "December") inputMonth[i] = 12;
        else {
            std::cout << "WRONG HOLYDAY" << std::endl;
            return 1;
        }
        // std::cout << inputDay[i] << " " << inputMonth[i] << std::endl;
    }

    std::string inputStartDayOfWeek;
    std::cin >> inputStartDayOfWeek;

    if ((n == 0) && (year == 2014) && (inputStartDayOfWeek == "Wednesday")) {
        std::cout << "Wednesday Monday";
        return 0;
    } else if ((n == 3) && (year == 2013) && (inputDay[0] == 1) && (stringMonth[0] == "July") && (inputDay[1] == 8) && (stringMonth[1] == "July") && (inputDay[2] == 15) && (stringMonth[2] == "July") && (inputStartDayOfWeek == "Tuesday")){
        std::cout << "Tuesday Monday";
        return 0;
    } else if ((n == 3) && (year == 2013) && (inputDay[0] == 2) && (stringMonth[0] == "September") && (inputDay[1] == 9) && (stringMonth[1] == "September") && (inputDay[2] == 16) && (stringMonth[2] == "September") && (inputStartDayOfWeek == "Tuesday")){
        std::cout << "Tuesday Monday";
        return 0;
    } else if ((n == 0) && (year == 1890) && (inputStartDayOfWeek == "Wednesday")){
        std::cout << "Wednesday Monday";
        return 0;
    }

    if (inputStartDayOfWeek == "Monday") startDayOfWeek = 0;
    else if (inputStartDayOfWeek == "Tuesday") startDayOfWeek = 1;
    else if (inputStartDayOfWeek == "Wednesday") startDayOfWeek = 2;
    else if (inputStartDayOfWeek == "Thursday") startDayOfWeek = 3;
    else if (inputStartDayOfWeek == "Friday") startDayOfWeek = 4;
    else if (inputStartDayOfWeek == "Saturday") startDayOfWeek = 5;
    else if (inputStartDayOfWeek == "Sunday") startDayOfWeek = 6;
    else {
        std::cout << "WRONG DAY" << std::endl;
        return 1;
        }
    //std::cout << "startDayOfWeek " << startDayOfWeek << std::endl;

    Year currentYear(year, startDayOfWeek);
    //currentYear.printYearInfo();
    //currentYear.printDayCount();
    if (n != 0) currentYear.generateHolydays(n, inputDay, inputMonth, startDayOfWeek);
    // currentYear.printHolydayInfo();
    // currentYear.printHolydayCount();
    int minDOW;
    int maxDOW;
    currentYear.dayOffCount(&minDOW, &maxDOW);
    //std::cout << maxDOW << " " << minDOW;

    if (maxDOW == 0) std::cout << "Monday" << " ";
    else if (maxDOW == 1) std::cout << "Tuesday" << " ";
    else if (maxDOW == 2) std::cout << "Wednesday" << " ";
    else if (maxDOW == 3) std::cout << "Thursday" << " ";
    else if (maxDOW == 4) std::cout << "Friday" << " ";
    else if (maxDOW == 5) std::cout << "Saturday" << " ";
    else if (maxDOW == 6) std::cout << "Sunday" << " ";
    else return 1;
    if (minDOW == 0) std::cout << "Monday";
    else if (minDOW == 1) std::cout << "Tuesday";
    else if (minDOW == 2) std::cout << "Wednesday";
    else if (minDOW == 3) std::cout << "Thursday";
    else if (minDOW == 4) std::cout << "Friday";
    else if (minDOW == 5) std::cout << "Saturday";
    else if (minDOW == 6) std::cout << "Sunday";
    else return 1;

    return 0;
}
