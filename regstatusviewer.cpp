#include "regstatusviewer.h"
#include "ui_regstatusviewer.h"

RegStatusViewer::RegStatusViewer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RegStatusViewer)
{
    ui->setupUi(this);
}

RegStatusViewer::~RegStatusViewer()
{
    delete ui;
}

Ui::RegStatusViewer *RegStatusViewer::getUi(){
    return this->ui;
}
