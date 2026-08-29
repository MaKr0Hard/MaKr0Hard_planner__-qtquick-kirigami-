#ifndef FUNC_CLASS_H
#define FUNC_CLASS_H

#include <QObject>

typedef struct {

} Day;

typedef struct {
    QString name;
    int day;
    int month;
    int year;
} Holiday;

class Func_class : public QObject
{
    Q_OBJECT
public:
    explicit Func_class(QObject *parent = nullptr);
    Q_INVOKABLE void print_smth(QString str);
    Q_INVOKABLE QVector<QString> get_events();
    Q_INVOKABLE int dayOfMonth();
    Q_INVOKABLE int number_of_days_before_holiday();
    Q_INVOKABLE int month();
    Q_INVOKABLE int dayOfWeek();
    Q_INVOKABLE QVector<Holiday> get_all_holidays();
    Q_INVOKABLE QString name_holiday(Holiday holiday);
    Q_INVOKABLE int day_holiday(Holiday holiday);
    Q_INVOKABLE int month_holiday(Holiday holiday);
    Q_INVOKABLE int year_holiday(Holiday holiday);
    Q_INVOKABLE QVector<QString> name_holiday_2();
    Q_INVOKABLE QString get_json_of_all_holidays();
    Q_INVOKABLE QString get_json_elements(QString filename);
    Q_INVOKABLE int day_from_timestamp(long timestamp);
    Q_INVOKABLE int month_from_timestamp(long timestamp);
    Q_INVOKABLE int year_from_timestamp(long timestamp);
    Q_INVOKABLE void save_to_json(QString name, long timestamp, QString description, QString filename);
    Q_INVOKABLE void save_to_planner(QString name, long timestamp, QString description, int priority, QString subject, long time_needed_to_study);
    Q_INVOKABLE int number_of_days_before_timestamp(long timestamp);
//signals:

private:
    void write_to_file(std::string filename, std::string stuff);
};

#endif // FUNC_CLASS_H
