//#include <nlohmann/json.hpp>
#include "func_class.h"
#include <iostream>
#include <ctime>
#include <vector>
#include <fstream>
#include <sstream>

std::string readFileContents(const std::string& filePath) {
    std::ifstream file(filePath);

    // Check if the file was successfully opened
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filePath << std::endl;
        return "";
    }

    // Read the file's buffer into a stringstream
    std::ostringstream buffer;
    buffer << file.rdbuf();

    // Convert the stringstream buffer to a std::string
    return buffer.str();
}

Func_class::Func_class(QObject *parent)
    : QObject{parent}
{

}

void Func_class::print_smth(QString str) {
    std::cout << str.toStdString() << "\n";
}

QVector<QString> Func_class::get_events() {
    std::string json_text = R"({"numbers": [10, 20, 30, 40]})";
    std::string hello = "hello";
    //json data = json::parse(json_text);
    std::string hi = "hi";
    QVector<QString> vect;
    vect.append(QString::fromStdString(hello));
    vect.append(QString::fromStdString(hi));
    return vect;
}

int Func_class::dayOfMonth() {
    std::time_t t = std::time(nullptr);
    std::tm* tm = std::localtime(&t);
    return tm->tm_mday;
}

int Func_class::month() {
    std::time_t t = std::time(nullptr);
    std::tm* tm = std::localtime(&t);
    return tm->tm_mon;
}

int Func_class::dayOfWeek() {
    std::time_t t = std::time(nullptr);
    std::tm* tm = std::localtime(&t);
    return tm->tm_wday;
}

int Func_class::number_of_days_before_holiday() {
    std::time_t t = std::time(nullptr);
    std::tm tm_end = {0};
    tm_end.tm_mday = 19;
    tm_end.tm_mon = 9;
    tm_end.tm_year = 2026 - 1900;
    std::time_t t_end = std::mktime(&tm_end);
    double differnce = std::difftime(t_end, t);
    int days_before = round(differnce / 86400);
    return days_before;
}

QVector<Holiday> Func_class::get_all_holidays() {
    QVector<Holiday> holidays;
    holidays.push_back(Holiday{QString::fromStdString("Halloween"), 19, 10, 2026});
    QVector<Holiday> holidays_filtered;
    for (int i = 0; i < holidays.size(); i++) {
        holidays_filtered.push_back(holidays[i]);
    }
    return holidays_filtered;
}

QString Func_class::name_holiday(Holiday holiday) {
    return holiday.name;
}

QVector<QString> Func_class::name_holiday_2() {
    QVector<Holiday> holidays = get_all_holidays();
    QVector<QString> names;
    for (int i = 0; i < holidays.size(); i++) {
        names.push_back(holidays[i].name);
    }
    return names;
}

int Func_class::day_holiday(Holiday holiday) {
    return holiday.day;
}

int Func_class::month_holiday(Holiday holiday) {
    return holiday.month;
}

int Func_class::year_holiday(Holiday holiday) {
    return holiday.year;
}

QString Func_class::get_json_of_all_holidays() {
    return QString::fromStdString(readFileContents("example.txt"));
}