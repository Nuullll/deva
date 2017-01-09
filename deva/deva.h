#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_deva.h"

class deva : public QMainWindow
{
    Q_OBJECT

public:
    deva(QWidget *parent = Q_NULLPTR);

private:
    Ui::devaClass ui;
};
