/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include <QSlider>
#include <QToolBar>
#include <QTabWidget>
#include <QTabBar>

QT_BEGIN_NAMESPACE

class MyTabWidget : public QTabWidget
{
public:
    MyTabWidget(QWidget *parent): QTabWidget(parent){}
    void setCustomTabBar(QTabBar *tabBar){
        setTabBar(tabBar);
    }
};

class Ui_MainWindow
{
public:
    // QWidget *centralwidget;
    QLabel *label;
    // QMenuBar *menubar;
    // QStatusBar *statusbar;
    QAction *startAction;
    QAction *stepAction;
    QAction *confAction;
    QSlider *delay_slider;
    QAction *addProgAction;
    QAction *delProgAction;
    QToolBar *toolbar;
    MyTabWidget *programs_tab;

    QList<int> emulators;
    qint8 emulators_delay;

    void setupUi(QMainWindow *MainWindow)
    {
        MainWindow->setMinimumSize(MainWindow->sizeHint());
        MainWindow->setWindowTitle("RISC-emV");
        initUI(MainWindow);

        // MainWindow->resize(800, 600);
        // centralwidget = new QWidget(MainWindow);
        // centralwidget->setObjectName("centralwidget");
        // label = new QLabel(centralwidget);
        // label->setObjectName("label");
        // label->setGeometry(QRect(140, 170, 54, 16));
        // MainWindow->setCentralWidget(centralwidget);
        // menubar = new QMenuBar(MainWindow);
        // menubar->setObjectName("menubar");
        // menubar->setGeometry(QRect(0, 0, 800, 21));
        // MainWindow->setMenuBar(menubar);
        // statusbar = new QStatusBar(MainWindow);
        // statusbar->setObjectName("statusbar");
        // MainWindow->setStatusBar(statusbar);

        //retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void initUI(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");

        startAction = new QAction(QIcon::fromTheme("media-playback-start"), "Start", MainWindow);
        startAction->setShortcut(QKeySequence("Ctrl+R"));

        delay_slider = new QSlider(Qt::Horizontal);

        delay_slider->setFixedWidth(200);
        delay_slider->setMinimum(0);
        delay_slider->setMaximum(1000);
        delay_slider->setTickInterval(50);
        delay_slider->setTickPosition(QSlider::TicksBelow);

        stepAction = new QAction(QIcon::fromTheme("go-next"), "Step Forward", MainWindow);
        stepAction->setShortcut(QKeySequence("Ctrl+Shift+R"));

        confAction = new QAction(QIcon::fromTheme("preferences-system"), "Configuration", MainWindow);
        confAction->setShortcut(QKeySequence("Alt+C"));

        addProgAction = new QAction(QIcon::fromTheme("list-add"), "Add program", MainWindow);
        addProgAction->setShortcut(QKeySequence("Ctrl+N"));

        delProgAction = new QAction(QIcon::fromTheme("list-remove"), "Delete selected program", MainWindow);
        delProgAction->setShortcut(QKeySequence("Ctrl+D"));

        toolbar = MainWindow->addToolBar("HomeToolbar");
        toolbar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        toolbar->addAction(startAction);
        toolbar->addWidget(delay_slider);
        toolbar->addAction(stepAction);
        toolbar->addAction(confAction);
        toolbar->addSeparator();
        toolbar->addAction(addProgAction);
        toolbar->addAction(delProgAction);

        programs_tab = new MyTabWidget(MainWindow);
        programs_tab->setCustomTabBar(new QTabBar(programs_tab));
        MainWindow->setCentralWidget(programs_tab);
    }

    void add_program_tab(QMainWindow *MainWindow){
        emulators << 1; // 这部分先这么些，emulators中的元素应当是一个对象，但是那个class我还没弄明白是什么意思，先吧UI做出啦再说
        //programs_tab->addTab(tab, "Thread #" + str(0));
    }
    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
