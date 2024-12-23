/********************************************************************************
** Form generated from reading UI file 'hw.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HW_H
#define UI_HW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_hwClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *hwClass)
    {
        if (hwClass->objectName().isEmpty())
            hwClass->setObjectName("hwClass");
        hwClass->resize(600, 400);
        menuBar = new QMenuBar(hwClass);
        menuBar->setObjectName("menuBar");
        hwClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(hwClass);
        mainToolBar->setObjectName("mainToolBar");
        hwClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(hwClass);
        centralWidget->setObjectName("centralWidget");
        hwClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(hwClass);
        statusBar->setObjectName("statusBar");
        hwClass->setStatusBar(statusBar);

        retranslateUi(hwClass);

        QMetaObject::connectSlotsByName(hwClass);
    } // setupUi

    void retranslateUi(QMainWindow *hwClass)
    {
        hwClass->setWindowTitle(QCoreApplication::translate("hwClass", "hw", nullptr));
    } // retranslateUi

};

namespace Ui {
    class hwClass: public Ui_hwClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HW_H
