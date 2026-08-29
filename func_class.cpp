//#include <nlohmann/json.hpp>
#include "func_class.h"
#include <iostream>
#include <ctime>
//#include <vector>
#include <fstream>
#include <sstream>
#include <nlohmann/json.hpp>

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
    file.close();
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

int Func_class::number_of_days_before_timestamp(long timestamp) {
    std::time_t t = std::time(nullptr);

    std::time_t t_end = static_cast<std::time_t>(timestamp);
    double differnce = std::difftime(t_end, t);
    int days_before = round(differnce / 86400);
    return days_before;
}

int Func_class::month_from_timestamp(long timestamp) {
    std::time_t t = static_cast<std::time_t>(timestamp);
    std::tm *tm = std::localtime(&t);
    int month = tm->tm_mon + 1;    //TODO: maybe delete thattt it takes some xtra cpu instructions
    return month;
}

int Func_class::day_from_timestamp(long timestamp) {
    std::time_t t = static_cast<std::time_t>(timestamp);
    std::tm *tm = std::localtime(&t);
    int day = tm->tm_mday; //TODO: maybe delete thattt it takes some xtra cpu instructions
    return day;
}


int Func_class::year_from_timestamp(long timestamp) {
    std::time_t t = static_cast<std::time_t>(timestamp);
    std::tm *tm = std::localtime(&t);
    int year = tm->tm_year + 1900;    //TODO: maybe delete thattt it takes some xtra cpu instructions
    return year;
}

QVector<Holiday> Func_class::get_all_holidays() {//TODO: delete ?
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

QVector<QString> Func_class::name_holiday_2() {//TODO: delete ?
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
    return QString::fromStdString(readFileContents("holidays.txt"));
}

QString Func_class::get_json_elements(QString filename) {//TODO: rename
    std::string json = readFileContents(filename.toStdString());

    nlohmann::json j = nlohmann::json::parse(json);
    std::sort(j.begin(), j.end(), [](const nlohmann::json& a, const nlohmann::json& b) {
        return a["timestamp"] < b["timestamp"];
    });
    std::string output = j.dump();
    return QString::fromStdString(output);//TODO: use the json string instead to not waste ram
}

void Func_class::save_to_json(QString name, long timestamp, QString description, QString filename) {//TODO: rename
    nlohmann::json json = nlohmann::json::parse(readFileContents(filename.toStdString()));
    nlohmann::json newElement = {
        {"name", name.toStdString()},
        {"timestamp", timestamp},
        {"description", description.toStdString()}
    };

    // Add the new element to the array
    json.push_back(newElement);

    // Print the updated JSON
    std::cout << json.dump(4) << std::endl;
    write_to_file(filename.toStdString(), json.dump(4));
}

void Func_class::save_to_planner(QString name, long timestamp, QString description, int priority, QString subject, long time_needed_to_study) {
    QString filename = QString::fromStdString("planner.txt");
    nlohmann::json json = nlohmann::json::parse(readFileContents(filename.toStdString()));
    nlohmann::json newElement = {
        {"name", name.toStdString()},
        {"timestamp", timestamp},
        {"description", description.toStdString()},
        {"priority", priority},
        {"subject", subject.toStdString()},
        {"time_needed", time_needed_to_study},
    };

    // Add the new element to the array
    json.push_back(newElement);

    // Print the updated JSON
    std::cout << json.dump(4) << std::endl;
    write_to_file(filename.toStdString(), json.dump(4));
}

void Func_class::write_to_file(std::string filename, std::string stuff) {


    // Open the file in output mode (default: std::ios::out)
    // This will create the file if it doesn't exist or overwrite it if it does.
    std::ofstream outFile(filename);

    // Check if the file was opened successfully
    if (!outFile) {
        std::cerr << "Error: Could not open or create file " << filename << std::endl;
        return;
    }

    // Write data to the file
    outFile << stuff << std::endl;

    // Close the file (optional but good practice)
    outFile.close();

    std::cout << "File " << filename << " has been created or overwritten." << std::endl;
    return;
}