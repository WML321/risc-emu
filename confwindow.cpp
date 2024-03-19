#include "confwindow.h"
#include "ui_confwindow.h"

ConfWindow::ConfWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ConfWindow)
{
    ui->setupUi(this);
}

ConfWindow::~ConfWindow()
{
    delete ui;
}
