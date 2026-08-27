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
//signals:

};

#endif // FUNC_CLASS_H
