/********************************************************************************
** Form generated from reading UI file 'registerviewer.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERVIEWER_H
#define UI_REGISTERVIEWER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include <QFrame>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QLabel>
#include <QStringList>

QT_BEGIN_NAMESPACE

class Ui_RegisterViewer: public QFrame
{
public:
    QVBoxLayout* layout;
    QString format;
    QList<QPushButton*> fmt_buttons;
    QTableWidget* rf_int_table;
    QTableWidget* rf_fp_table;
    QFrame* parent;
public:
    //QPushButton *pushButton;

    void setupUi(QFrame *RegisterViewer)
    {
        if (RegisterViewer->objectName().isEmpty())
            RegisterViewer->setObjectName("RegisterViewer");
        //RegisterViewer->resize(400, 300);

        this->parent = RegisterViewer;
        layout = new QVBoxLayout(this);
        RegisterViewer->setLayout(layout);
        RegisterViewer->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);

        format = "BIN";

        QLabel* title = new QLabel("Registers Viewer:");
        layout->addWidget(title);

        QFrame* format_chooser = new QFrame;
        QHBoxLayout* format_layout = new QHBoxLayout(format_chooser);
        format_chooser->setLayout(format_layout);
        layout->addWidget(format_chooser);

        QLabel* fmt_label = new QLabel("Display:");
        format_layout->addWidget(fmt_label);

        QPushButton* fmt_bin = new QPushButton("BIN");
        fmt_bin->setDown(true);
        fmt_bin->setStyleSheet("QPushButton { padding: 1px 5px; }");
        // 这里应该有个连接
        format_layout->addWidget(fmt_bin);



        QPushButton* fmt_dec = new QPushButton("DEC");
        fmt_dec->setStyleSheet("QPushButton { padding: 1px 5px; }");
        //connect(fmt_dec, &QPushButton::clicked, this, &RegistersViewer::change_format);
        fmt_buttons.append(fmt_dec);
        format_layout->addWidget(fmt_dec);

        QPushButton* fmt_hex = new QPushButton("HEX");
        fmt_hex->setStyleSheet("QPushButton { padding: 1px 5px; }");
        //connect(fmt_hex, &QPushButton::clicked, this, &RegistersViewer::change_format);
        fmt_buttons.append(fmt_hex);
        format_layout->addWidget(fmt_hex);

        format_layout->addStretch(1);

        rf_int_table = new QTableWidget(1, 32 + 2);
        //rf_int_table->vertical
        //rf_int_table->setHorizontalHeaderLabels({"PC", "IR"} + QStringList({"X" + QString::number(r) for int r = 0; r < 32}));
        QStringList ql;
        ql.append("PC");
        ql.append("IR");
        for(int i=0; i<32;i++){
            ql.append("X"+QString::number(i));
        }
        rf_int_table->setHorizontalHeaderLabels(ql);
        rf_int_table->setFont(QFont("monospace"));
        layout->addWidget(rf_int_table);

        rf_fp_table = new QTableWidget(1, 32);
        //rf_fp_table->verticalHeader()->setVisible(false);
        QStringList ql_;
        for(int i=0; i<32;i++){
            ql_.append("FP"+QString::number(i));
        }
        rf_fp_table->setHorizontalHeaderLabels(ql_);
        rf_fp_table->setFont(QFont("monospace"));
        layout->addWidget(rf_fp_table);

        retranslateUi(RegisterViewer);

        //QMetaObject::connectSlotsByName(RegisterViewer);
    } // setupUi

    void retranslateUi(QWidget *RegisterViewer)
    {
        RegisterViewer->setWindowTitle(QCoreApplication::translate("RegisterViewer", "Form", nullptr));
        //pushButton->setText(QCoreApplication::translate("RegisterViewer", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegisterViewer: public Ui_RegisterViewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERVIEWER_H
