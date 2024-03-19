/********************************************************************************
** Form generated from reading UI file 'datamemoryviewer.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATAMEMORYVIEWER_H
#define UI_DATAMEMORYVIEWER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QPushButton>
#include <QVBoxLayout>
#include <QPlainTextEdit>
#include <QLabel>


QT_BEGIN_NAMESPACE

class Ui_DataMemoryViewer: public QFrame
{
public:
    QVBoxLayout* layout;
    QPlainTextEdit* hex_box;
    QPlainTextEdit* ascii_box;
    QFrame* parent;

    void setupUi(QFrame *DataMemoryViewer)
    {
        if (DataMemoryViewer->objectName().isEmpty())
            DataMemoryViewer->setObjectName("DataMemoryViewer");
        layout = new QVBoxLayout(this);
        DataMemoryViewer->setLayout(layout);

        this->parent = DataMemoryViewer;
        QLabel* title = new QLabel("Data Memory Viewer:");
        layout->addWidget(title);

        QFrame* sub_frame = new QFrame;
        QHBoxLayout* sub_layout = new QHBoxLayout(sub_frame);
        sub_layout->setContentsMargins(0, 0, 0, 0);
        layout->addWidget(sub_frame);

        hex_box = new QPlainTextEdit;
        hex_box->setFont(QFont("monospace"));
        hex_box->setOverwriteMode(true);
        hex_box->setMinimumWidth(210);

        ascii_box = new QPlainTextEdit;
        ascii_box->setFont(QFont("monospace"));
        ascii_box->setOverwriteMode(true);
        ascii_box->setMinimumWidth(70);

        sub_layout->addWidget(hex_box, 3);
        sub_layout->addWidget(ascii_box, 1);

        retranslateUi(DataMemoryViewer);

        //QMetaObject::connectSlotsByName(DataMemoryViewer);
    } // setupUi

    void retranslateUi(QFrame *DataMemoryViewer)
    {
        DataMemoryViewer->setWindowTitle(QCoreApplication::translate("DataMemoryViewer", "Frame", nullptr));
        //pushButton->setText(QCoreApplication::translate("DataMemoryViewer", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DataMemoryViewer: public Ui_DataMemoryViewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATAMEMORYVIEWER_H
