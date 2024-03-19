#ifndef REGSTATUSVIEWER_H
#define REGSTATUSVIEWER_H

#include <QWidget>

namespace Ui {
class RegStatusViewer;
}

class RegStatusViewer : public QWidget
{
    Q_OBJECT

public:
    explicit RegStatusViewer(QWidget *parent = nullptr);
    ~RegStatusViewer();
    Ui::RegStatusViewer *getUi();
private:
    Ui::RegStatusViewer *ui;
};

#endif // REGSTATUSVIEWER_H
