/********************************************************************************
** Form generated from reading UI file 'tomasuloview.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TOMASULOVIEW_H
#define UI_TOMASULOVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>
#include <QSplitter>
#include <ui_codeeditor.h>
#include <ui_datamemoryviewer.h>
#include <ui_registerviewer.h>
#include <ui_regstatusviewer.h>
#include <ui_instbufferviewer.h>
#include <ui_resstationsviewer.h>
#include <QTabWidget>

QT_BEGIN_NAMESPACE

class Ui_TomasuloView: public QSplitter
{
public:
    //QLabel *label;
    Ui_CodeEditor* code_textbox; // 这个流程，应该是，由外部使用ui指针对这个属性进行赋值，然后在手动调用setupUi，只是这部分涉及到了UI，所以我先写出来
    Ui_DataMemoryViewer *datamemory_viewer;
    QTabWidget *code_pane;
    Ui_RegisterViewer *register_view;
    QFrame *status_pane;
    Ui_RegStatusViewer *regstatus_view;
    Ui_InstBufferViewer *instbuffer_view;
    Ui_ResStationsViewer* resstations_view;
    void setupUi(QSplitter *TomasuloView)
    {
        if (TomasuloView->objectName().isEmpty())
            TomasuloView->setObjectName("TomasuloView");
        // 我这里有两个想法，不知道只能试着做
        // 首先，TomasuloView作为code_textbox的父节点，即在使用code_textbox-ui-setupUi时，将TomasuloView作为参数
        // 或者是，在tomasuloview.cpp中提前调用code_textbox的setupUi
        // code_textbox = new Ui_CodeEditor();
        // code_textbox->setupUi(CodeTextBox);
        code_pane = new QTabWidget();
        code_pane->setMinimumWidth(250);
        code_pane->addTab(code_textbox->parent, "Code Editor");
        code_pane->addTab(instbuffer_view->parent, "Instruction Memory");

        status_pane = new QFrame();
        status_pane->setLayout(new QVBoxLayout());

        status_pane->layout()->addWidget(register_view->parent);
        status_pane->layout()->addWidget(regstatus_view->parent);
        status_pane->layout()->addWidget(resstations_view->parent);
        status_pane->layout()->addWidget(datamemory_viewer->parent);
        //TomasuloView->resize(400, 300);
        // label = new QLabel(TomasuloView);
        // label->setObjectName("label");
        // label->setGeometry(QRect(70, 200, 54, 16));

        TomasuloView->addWidget(code_pane);
        TomasuloView->setStretchFactor(0,1);
        TomasuloView->addWidget(status_pane);
        TomasuloView->setStretchFactor(1,3);
        //retranslateUi(TomasuloView);

        QMetaObject::connectSlotsByName(TomasuloView); // 这个函数的意思是，如果信号槽的名字以特定的格式命名的话，那么就不用手动写connect了
    } // setupUi

    void retranslateUi(QWidget *TomasuloView)
    {
        TomasuloView->setWindowTitle(QCoreApplication::translate("TomasuloView", "Form", nullptr));
        //label->setText(QCoreApplication::translate("TomasuloView", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TomasuloView: public Ui_TomasuloView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOMASULOVIEW_H
