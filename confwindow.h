#ifndef CONFWINDOW_H
#define CONFWINDOW_H

#include <QWidget>

namespace Ui {
class ConfWindow;
}

class ConfWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ConfWindow(QWidget *parent = nullptr);
    ~ConfWindow();
public:
    Ui::ConfWindow* getUi(){
        return this->ui;
    }

private:
    Ui::ConfWindow *ui;
};

#endif // CONFWINDOW_H
