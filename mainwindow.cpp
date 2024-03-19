#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->add_program_tab();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::add_program_tab()
{
    int thread_id = this->ui->programs_tab->currentIndex();
    this->tab = new TomasuloView(this);
    this->tab->setThreadId(thread_id);
    this->ui->programs_tab->addTab(this->tab, "Thread #1");
}
