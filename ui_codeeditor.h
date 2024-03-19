/********************************************************************************
** Form generated from reading UI file 'codeeditor.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CODEEDITOR_H
#define UI_CODEEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include <QFrame>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QFont>
QT_BEGIN_NAMESPACE

class Ui_CodeEditor: public QFrame
{
public:
    QPushButton *btn_open;
    QPushButton *btn_load;
    QString filename;
    QTextEdit *text_edit;
    QFrame *toolbar;
    QFrame* parent;


    void setupUi(QFrame *CodeEditor)
    {
        if (CodeEditor->objectName().isEmpty())
            CodeEditor->setObjectName("CodeEditor");
        CodeEditor->resize(400, 300);
        CodeEditor->setLayout(new QVBoxLayout());

        this->parent = CodeEditor;
        QLabel *title = new QLabel();
        title->setText("Code Viewer:");
        CodeEditor->layout()->addWidget(title);

        toolbar = create_toolbar(CodeEditor);
        CodeEditor->layout()->addWidget(toolbar);
        text_edit = new QTextEdit();
        text_edit->setLineWrapMode(QTextEdit::NoWrap);
        text_edit->setFont(QFont("Monospace"));

        CodeEditor->layout()->addWidget(text_edit);
        retranslateUi(CodeEditor);

        QMetaObject::connectSlotsByName(CodeEditor);
    } // setupUi

    QFrame* create_toolbar(QWidget *CodeEditor)
    {
        QFrame *pane = new QFrame();
        pane->setLayout(new QHBoxLayout());

        btn_open = new QPushButton();
        btn_open->setText("Open");
        btn_open->setIcon(QIcon::fromTheme("document-open"));
        btn_open->setShortcut(QKeySequence("Ctrl+0"));

        pane->layout()->addWidget(btn_open);

        btn_load = new QPushButton();
        btn_load->setText("Load");
        btn_load->setIcon(QIcon::fromTheme("go-next"));
        pane->layout()->addWidget(btn_load);
        return pane;
    }
    void retranslateUi(QWidget *CodeEditor)
    {
        CodeEditor->setWindowTitle(QCoreApplication::translate("CodeEditor", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CodeEditor: public Ui_CodeEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CODEEDITOR_H
