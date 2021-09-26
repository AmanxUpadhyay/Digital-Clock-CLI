#include <iostream>
#include <thread>

using namespace std;

enum Timezone {
    AM, PM
}Timezone;

class TwentyHour;

class Time {
public:
    int hour;
    int minute;
    int second;

    virtual void addOneHour() = 0;
    virtual void addOneMinute() = 0;
    virtual void addOneSecond() = 0;
};

class TwelveHour :public Time {
public:
    TwelveHour(int h, int m, int s) {
        hour = h;
        minute = m;
        second = s;
        Timezone = AM;
    }

    void addOneHour() {
        if (hour == 11) {
            hour = 0;
            Timezone = Timezone == AM ? PM : AM;
        }
        else {
            hour = hour + 1;
        }
    }

    void addOneMinute() {
        if (minute == 59) {
            minute = 0;
            addOneHour();
        }
        else {
            minute = minute + 1;
        }
    }

    void addOneSecond() {
        if (second == 59) {
            second = 0;
            addOneMinute();
        }
        else {
            second = second + 1;
        }
    }
    friend void displayTime(const TwelveHour&, const TwentyHour&);
};

class TwentyHour :public Time {
public:
    TwentyHour(int h, int m, int s) {
        hour = h;
        minute = m;
        second = s;
    }

    void addOneHour() {
        if (hour == 23) {
            hour = 0;
        }
        else {
            hour = hour + 1;
        }
    }

    void addOneMinute() {
        if (minute == 59) {
            minute = 0;
            addOneHour();
        }
        else {
            minute = minute + 1;
        }
    }

    void addOneSecond() {
        if (second == 59) {
            second = 0;
            addOneMinute();
        }
        else {
            second = second + 1;
        }
    }

    friend void displayTime(const TwelveHour&, const TwentyHour&);
};

void displayTime(const TwelveHour& TwelveTime, const TwentyHour& TwentyTime) {
    cout << "\n\n******************************" << "   " << "******************************\n";

    cout << "*       12-Hour Clock        *" << "   " << "*       24-Hour Clock        *\n";

    cout << "*       ";

    if (TwelveTime.hour < 10) cout << "0"; cout << TwelveTime.hour << ":";

    if (TwelveTime.minute < 10) cout << "0"; cout << TwelveTime.minute << ":";

    if (TwelveTime.second < 10) cout << "0"; cout << TwelveTime.second;

    if (Timezone == AM) cout << " A M"; else cout << " P M";

    cout << "         *   *       ";

    if (TwentyTime.hour < 10) cout << "0"; cout << TwentyTime.hour << ":";

    if (TwentyTime.minute < 10) cout << "0"; cout << TwentyTime.minute << ":";

    if (TwentyTime.second < 10) cout << "0"; cout << TwentyTime.second;

    cout << "             *\n";

    cout << "******************************" << "   " << "******************************\n";
}

int main() {
    TwelveHour ClockTime12(03, 22, 01);
    TwentyHour ClockTime24(15, 22, 01);

    // std::thread t1(displayTime, ClockTime12, ClockTime24);
    displayTime(ClockTime12, ClockTime24);

    while (true) {
        cout << "\n------------------------------\n";
        cout << "*      1. Add One Hour Time  *" << endl;
        cout << "*      2. Add One Minute     *" << endl;
        cout << "*      3. Add One Second     *" << endl;
        cout << "*      4. Exit Program       *" << endl;
        cout << "------------------------------\n";

        int choice;
        cout << " Please Enter Your Choice: ";
        cin >> choice;

        if (choice == 1) {
            ClockTime12.addOneHour();
            ClockTime24.addOneHour();
            displayTime(ClockTime12, ClockTime24);
        }
        else if (choice == 2) {
            ClockTime12.addOneMinute();
            ClockTime24.addOneMinute();
            displayTime(ClockTime12, ClockTime24);
        }
        else if (choice == 3) {
            ClockTime12.addOneSecond();
            ClockTime24.addOneSecond();
            displayTime(ClockTime12, ClockTime24);
        }
        else if (choice == 4) {
            cout << "Programmed Exited Successfully\n";
            exit(1);
        }
        else {
            cout << "Please Enter a valid number";
        }
    }

    return 0;
}