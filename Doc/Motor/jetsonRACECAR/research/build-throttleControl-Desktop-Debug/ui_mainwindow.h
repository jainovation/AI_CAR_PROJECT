/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QLabel *label_2;
    QLabel *labelCurrentValue;
    QPushButton *neutralButton;
    QPushButton *decrementButton;
    QPushButton *incrementButton;
    QDoubleSpinBox *spinValue;
    QLabel *label_3;
    QComboBox *comboBox;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(791, 564);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(540, 10, 251, 151));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(180, 10, 181, 41));
        QFont font;
        font.setPointSize(18);
        label_2->setFont(font);
        labelCurrentValue = new QLabel(centralWidget);
        labelCurrentValue->setObjectName(QString::fromUtf8("labelCurrentValue"));
        labelCurrentValue->setGeometry(QRect(380, 10, 131, 41));
        QFont font1;
        font1.setPointSize(18);
        font1.setBold(true);
        font1.setWeight(75);
        labelCurrentValue->setFont(font1);
        neutralButton = new QPushButton(centralWidget);
        neutralButton->setObjectName(QString::fromUtf8("neutralButton"));
        neutralButton->setGeometry(QRect(240, 230, 151, 61));
        QFont font2;
        font2.setPointSize(12);
        font2.setBold(true);
        font2.setWeight(75);
        neutralButton->setFont(font2);
        decrementButton = new QPushButton(centralWidget);
        decrementButton->setObjectName(QString::fromUtf8("decrementButton"));
        decrementButton->setGeometry(QRect(30, 230, 151, 61));
        decrementButton->setFont(font2);
        incrementButton = new QPushButton(centralWidget);
        incrementButton->setObjectName(QString::fromUtf8("incrementButton"));
        incrementButton->setGeometry(QRect(450, 230, 151, 61));
        incrementButton->setFont(font2);
        spinValue = new QDoubleSpinBox(centralWidget);
        spinValue->setObjectName(QString::fromUtf8("spinValue"));
        spinValue->setGeometry(QRect(210, 330, 231, 61));
        spinValue->setFont(font);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 340, 161, 31));
        QFont font3;
        font3.setPointSize(15);
        label_3->setFont(font3);
        comboBox = new QComboBox(centralWidget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(10, 20, 141, 27));
        QFont font4;
        font4.setPointSize(12);
        comboBox->setFont(font4);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 791, 25));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "PWM Duty Cycle", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "  <html><head/><body><span style=\" font-weight:600;\">PWM Duty Cycle:</span><br>\n"
"<br>50 Hz, 20ms frame, 12 bit resolution\n"
"<br>\n"
"<br><span style=\" font-weight:600;\">Duty Cycle Reference</span>\n"
"<br>Full Reverse: 1.0 ms  - 204\n"
"<br>Neutral 1.5 ms&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;- 307\n"
"<br>Full Forward 2.0 ms  - 409\n"
"</body>\n"
"</html>", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Current Setting: ", 0, QApplication::UnicodeUTF8));
        labelCurrentValue->setText(QApplication::translate("MainWindow", "307", 0, QApplication::UnicodeUTF8));
        neutralButton->setText(QApplication::translate("MainWindow", "Neutral", 0, QApplication::UnicodeUTF8));
        decrementButton->setText(QApplication::translate("MainWindow", "Decrement", 0, QApplication::UnicodeUTF8));
        incrementButton->setText(QApplication::translate("MainWindow", "Increment", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "Set Duty Cycle", 0, QApplication::UnicodeUTF8));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Throttle ESC", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Steering", 0, QApplication::UnicodeUTF8)
        );
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
