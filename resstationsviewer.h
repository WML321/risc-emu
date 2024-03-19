#ifndef RESSTATIONSVIEWER_H
#define RESSTATIONSVIEWER_H

#include <QFrame>

namespace Ui {
class ResStationsViewer;
}

class ResStationsViewer : public QFrame
{
    Q_OBJECT

public:
    explicit ResStationsViewer(QWidget *parent = nullptr);
    ~ResStationsViewer();
    Ui::ResStationsViewer* getUi(){
        return this->ui;
    }

private:
    Ui::ResStationsViewer *ui;
};

#endif // RESSTATIONSVIEWER_H
