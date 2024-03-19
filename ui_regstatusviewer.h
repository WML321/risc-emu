/********************************************************************************
** Form generated from reading UI file 'regstatusviewer.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGSTATUSVIEWER_H
#define UI_REGSTATUSVIEWER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

#include <QVBoxLayout>
#include <QLabel>
#include <QTableWidget>
#include <QFont>
QT_BEGIN_NAMESPACE

class Ui_RegStatusViewer
{
public:
    QWidget* parent;
public:

    void setupUi(QWidget *RegStatusViewer)
    {
        if (RegStatusViewer->objectName().isEmpty())
            RegStatusViewer->setObjectName("RegStatusViewer");
        RegStatusViewer->resize(400, 300);
        this->parent = RegStatusViewer;
        RegStatusViewer->setLayout(new QVBoxLayout());
        RegStatusViewer->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);

        QLabel *title = new QLabel();
        title->setText("Registers Status Viewer:");
        RegStatusViewer->layout()->addWidget(title);

        QTableWidget *rs_table = new QTableWidget();
        rs_table->setColumnCount(64);
        rs_table->setRowCount(1);

        QStringList ql;
        ql.append("PC");
        ql.append("IR");
        for(int i=0; i<32;i++){
            ql.append("X"+QString::number(i));

        }
        for(int i=0; i<32;i++){
            ql.append("FP"+QString::number(i));
        }

        rs_table->setHorizontalHeaderLabels(ql);
        rs_table->setFont(QFont("monospace"));
        RegStatusViewer->layout()->addWidget(rs_table);


        retranslateUi(RegStatusViewer);

        QMetaObject::connectSlotsByName(RegStatusViewer);
    } // setupUi

    void retranslateUi(QWidget *RegStatusViewer)
    {
        RegStatusViewer->setWindowTitle(QCoreApplication::translate("RegStatusViewer", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegStatusViewer: public Ui_RegStatusViewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGSTATUSVIEWER_H
