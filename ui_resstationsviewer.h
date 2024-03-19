/********************************************************************************
** Form generated from reading UI file 'resstationsviewer.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESSTATIONSVIEWER_H
#define UI_RESSTATIONSVIEWER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QVBoxLayout>
#include <QLabel>
#include <QTableWidget>
#include <QStringList>
#include <QFont>

QT_BEGIN_NAMESPACE

class Ui_ResStationsViewer
{
public:
    QFrame* parent;
public:

    void setupUi(QFrame *ResStationsViewer)
    {
        if (ResStationsViewer->objectName().isEmpty())
            ResStationsViewer->setObjectName("ResStationsViewer");
        ResStationsViewer->resize(400, 300);
        this->parent = ResStationsViewer;
        ResStationsViewer->setLayout(new QVBoxLayout());

        QLabel* title = new QLabel();
        title->setText("Reservation Stations:");
        retranslateUi(ResStationsViewer);
        ResStationsViewer->layout()->addWidget(title);

        QTableWidget* rs_table = new QTableWidget();
        rs_table->setColumnCount(10);

        QStringList ql = {"Cycles Left", "Tag", "Busy", "Instruction", "Vj", "Vk", "Qj", "Qk", "A", "Result"};
        rs_table->setHorizontalHeaderLabels(ql);
        rs_table->setFont(QFont("monospace"));
        ResStationsViewer->layout()->addWidget(rs_table);
        //QMetaObject::connectSlotsByName(ResStationsViewer);
    } // setupUi

    void retranslateUi(QFrame *ResStationsViewer)
    {
        ResStationsViewer->setWindowTitle(QCoreApplication::translate("ResStationsViewer", "Frame", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ResStationsViewer: public Ui_ResStationsViewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESSTATIONSVIEWER_H
