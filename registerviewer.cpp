#include "registerviewer.h"
#include "ui_registerviewer.h"

RegisterViewer::RegisterViewer(QFrame *parent)
    : QFrame(parent)
    , ui(new Ui::RegisterViewer)
{
    ui->setupUi(this);
}

RegisterViewer::~RegisterViewer()
{
    delete ui;
}

Ui::RegisterViewer* RegisterViewer::getUi(){
    return this->ui;
}
