#include "instbufferviewer.h"
#include "ui_instbufferviewer.h"
#include <QTableWidgetItem>

InstBufferViewer::InstBufferViewer(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::InstBufferViewer)
{
    ui->setupUi(this);
    ui->ib_table->setRowCount(5);

    ui->ib_table->setItem(0,0, new QTableWidgetItem("add x1, x2, x3"));
    ui->ib_table->setItem(0,1, new QTableWidgetItem("1"));
    ui->ib_table->setItem(0,2, new QTableWidgetItem("2"));
    ui->ib_table->setItem(0,3, new QTableWidgetItem("3"));
}

InstBufferViewer::~InstBufferViewer()
{
    delete ui;
}
