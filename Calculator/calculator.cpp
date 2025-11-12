#include "calculator.h"
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

Calculator::Calculator(QWidget *parent)
    : QDialog(parent), currentValue(0.0), waitingForOperand(true)
{
    setWindowTitle("Calculator");
    
    // Create display
    display = new QLineEdit("0");
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMaxLength(15);
    
    QFont font = display->font();
    font.setPointSize(font.pointSize() + 8);
    display->setFont(font);
    display->setMinimumHeight(50);
    
    // Create grid layout for buttons
    QGridLayout *buttonLayout = new QGridLayout;
    
    // Row 0: [<-][/][*][-]
    QPushButton *backspaceButton = createButton("←", SLOT(backspaceClicked()));
    buttonLayout->addWidget(backspaceButton, 0, 0);
    buttonLayout->addWidget(createButton("/", SLOT(operatorClicked())), 0, 1);
    buttonLayout->addWidget(createButton("*", SLOT(operatorClicked())), 0, 2);
    buttonLayout->addWidget(createButton("-", SLOT(operatorClicked())), 0, 3);
    
    // Row 1: [7][8][9][+]
    buttonLayout->addWidget(createButton("7", SLOT(digitClicked())), 1, 0);
    buttonLayout->addWidget(createButton("8", SLOT(digitClicked())), 1, 1);
    buttonLayout->addWidget(createButton("9", SLOT(digitClicked())), 1, 2);
    buttonLayout->addWidget(createButton("+", SLOT(operatorClicked())), 1, 3, 2, 1);
    
    // Row 2: [4][5][6]
    buttonLayout->addWidget(createButton("4", SLOT(digitClicked())), 2, 0);
    buttonLayout->addWidget(createButton("5", SLOT(digitClicked())), 2, 1);
    buttonLayout->addWidget(createButton("6", SLOT(digitClicked())), 2, 2);

    // Row 3: [1][2][3][=]
    buttonLayout->addWidget(createButton("1", SLOT(digitClicked())), 3, 0);
    buttonLayout->addWidget(createButton("2", SLOT(digitClicked())), 3, 1);
    buttonLayout->addWidget(createButton("3", SLOT(digitClicked())), 3, 2);
    buttonLayout->addWidget(createButton("=", SLOT(equalClicked())), 3, 3, 2, 1);
    
    // Row 4: [C][0][.]
    buttonLayout->addWidget(createButton("C", SLOT(clearClicked())), 4, 0);
    buttonLayout->addWidget(createButton("0", SLOT(digitClicked())), 4, 1);
    buttonLayout->addWidget(createButton(".", SLOT(decimalClicked())), 4, 2);

    // Main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(display);
    mainLayout->addLayout(buttonLayout);
    
    setLayout(mainLayout);
}

Calculator::~Calculator() {}

QPushButton *Calculator::createButton(const QString &text, const char *member)
{
    QPushButton *button = new QPushButton(text);
    button->setMinimumSize(60, 60);
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); //
    QFont font = button->font();
    font.setPointSize(font.pointSize() + 4);
    button->setFont(font);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}


void Calculator::digitClicked()
{
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    QString digitValue = clickedButton->text();
    
    if (waitingForOperand) {
        display->setText(digitValue);
        waitingForOperand = false;
    } else {
        if (display->text() == "0") {
            display->setText(digitValue);
        } else {
            display->setText(display->text() + digitValue);
        }
    }
}

void Calculator::operatorClicked()
{
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    QString clickedOperator = clickedButton->text();
    double operandValue = display->text().toDouble();
    
    if (!pendingOperator.isEmpty()) {
        // Perform pending operation
        if (pendingOperator == "+") {
            currentValue += operandValue;
        } else if (pendingOperator == "-") {
            currentValue -= operandValue;
        } else if (pendingOperator == "*") {
            currentValue *= operandValue;
        } else if (pendingOperator == "/") {
            if (operandValue != 0.0) {
                currentValue /= operandValue;
            }
        }
        display->setText(QString::number(currentValue));
    } else {
        currentValue = operandValue;
    }
    
    pendingOperator = clickedOperator;
    waitingForOperand = true;
}

void Calculator::equalClicked()
{
    double operandValue = display->text().toDouble();
    
    if (!pendingOperator.isEmpty()) {
        if (pendingOperator == "+") {
            currentValue += operandValue;
        } else if (pendingOperator == "-") {
            currentValue -= operandValue;
        } else if (pendingOperator == "*") {
            currentValue *= operandValue;
        } else if (pendingOperator == "/") {
            if (operandValue != 0.0) {
                currentValue /= operandValue;
            }
        }
        display->setText(QString::number(currentValue));
        pendingOperator.clear();
    }
    
    currentValue = 0.0;
    waitingForOperand = true;
}

void Calculator::backspaceClicked()
{
    if (waitingForOperand) {
        return;
    }
    
    QString text = display->text();
    if (text.length() > 1) {
        text.chop(1);
        display->setText(text);
    } else {
        display->setText("0");
        waitingForOperand = true;
    }
}

void Calculator::clearClicked()
{
    display->setText("0");
    currentValue = 0.0;
    pendingOperator.clear();
    waitingForOperand = true;
}

void Calculator::decimalClicked()
{
    if (waitingForOperand) {
        display->setText("0.");
        waitingForOperand = false;
    } else {
        if (!display->text().contains('.')) {
            display->setText(display->text() + ".");
        }
    }
}
