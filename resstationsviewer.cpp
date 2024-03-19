#include "resstationsviewer.h"
#include "ui_resstationsviewer.h"

ResStationsViewer::ResStationsViewer(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::ResStationsViewer)
{
    ui->setupUi(this);
}

ResStationsViewer::~ResStationsViewer()
{
    delete ui;
}
