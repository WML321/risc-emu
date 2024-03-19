/********************************************************************************
** Form generated from reading UI file 'instbufferviewer.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INSTBUFFERVIEWER_H
#define UI_INSTBUFFERVIEWER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QTableWidget>
#include <QStringList>
#include <QFont>

QT_BEGIN_NAMESPACE

class Ui_InstBufferViewer
{
public:
    //QPushButton *pushButton;

    QFrame *parent;
    QTableWidget *ib_table;

    void setupUi(QFrame *InstBufferViewer)
    {
        if (InstBufferViewer->objectName().isEmpty())
            InstBufferViewer->setObjectName("InstBufferViewer");
        InstBufferViewer->resize(400, 300);
        parent = InstBufferViewer;
        InstBufferViewer->setLayout(new QVBoxLayout());
        QLabel* title = new QLabel();
        title->setText("Instruction Buffer Inspector:");
        InstBufferViewer->layout()->addWidget(title);

        ib_table = new QTableWidget();
        ib_table->setMinimumSize(600, 150);
        ib_table->setColumnCount(4);

        QStringList ql = {"Instruction", "Issue", "Execute", "Write Result"};
        ib_table->setHorizontalHeaderLabels(ql);
        ib_table->setRowCount(8);
        ib_table->setFont(QFont("monospace"));
        InstBufferViewer->layout()->addWidget(ib_table);

        // pushButton = new QPushButton(InstBufferViewer);
        // pushButton->setObjectName("pushButton");
        // pushButton->setGeometry(QRect(80, 120, 80, 24));

        retranslateUi(InstBufferViewer);

        QMetaObject::connectSlotsByName(InstBufferViewer);
    } // setupUi
    void load_content(QTableWidget *ib_table){

    }
    void retranslateUi(QFrame *InstBufferViewer)
    {
        InstBufferViewer->setWindowTitle(QCoreApplication::translate("InstBufferViewer", "Frame", nullptr));
        //pushButton->setText(QCoreApplication::translate("InstBufferViewer", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InstBufferViewer: public Ui_InstBufferViewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INSTBUFFERVIEWER_H
