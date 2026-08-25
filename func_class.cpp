//#include <nlohmann/json.hpp>
#include "func_class.h"
#include <iostream>
#include <ctime>


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
