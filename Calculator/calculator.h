#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QDialog>

class QLineEdit;
class QPushButton;

class Calculator : public QDialog
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private slots:
    void digitClicked();
    void operatorClicked();
    void equalClicked();
    void backspaceClicked();
    void clearClicked();
    void decimalClicked();

private:
    QPushButton *createButton(const QString &text, const char *member);
    
    QLineEdit *display;
    
    double currentValue;
    QString pendingOperator;
    bool waitingForOperand;
};
#endif // CALCULATOR_H
