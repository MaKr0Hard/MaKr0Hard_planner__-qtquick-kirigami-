#ifndef FUNC_CLASS_H
#define FUNC_CLASS_H

#include <QObject>

typedef struct {

} Day;

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
//signals:

};

#endif // FUNC_CLASS_H
