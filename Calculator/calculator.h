#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QDialog>

class Calculator : public QDialog
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();
};
#endif // CALCULATOR_H
