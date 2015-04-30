#ifndef _DATE_H_
#define _DATE_H_

class Date {
    private:
        int month;
        int day;
        int year;

    public:
        Date(int month, int day, int year) {
            this->month = month;
            this->day = day;
            this->year = year;
        }

        int getMonth() const { return month; }
        int getDay() const { return day; }
        int getYear() const { return year; }

        bool equals(const Date &b) const {
            if (month == b.month
              && day == b.day
              && year == b.year)
                return true;
            else
                return false;
        }
};

#endif
