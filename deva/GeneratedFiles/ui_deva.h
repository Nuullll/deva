/********************************************************************************
** Form generated from reading UI file 'deva.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEVA_H
#define UI_DEVA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_devaClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *devaClass)
    {
        if (devaClass->objectName().isEmpty())
            devaClass->setObjectName(QStringLiteral("devaClass"));
        devaClass->resize(600, 400);
        menuBar = new QMenuBar(devaClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        devaClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(devaClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        devaClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(devaClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        devaClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(devaClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        devaClass->setStatusBar(statusBar);

        retranslateUi(devaClass);

        QMetaObject::connectSlotsByName(devaClass);
    } // setupUi

    void retranslateUi(QMainWindow *devaClass)
    {
        devaClass->setWindowTitle(QApplication::translate("devaClass", "deva", 0));
    } // retranslateUi

};

namespace Ui {
    class devaClass: public Ui_devaClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEVA_H
