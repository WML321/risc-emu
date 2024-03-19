#ifndef REGISTERVIEWER_H
#define REGISTERVIEWER_H

#include <QWidget>
#include <QFrame>

namespace Ui {
class RegisterViewer;
}

class RegisterViewer : public QFrame
{
    Q_OBJECT

public:
    explicit RegisterViewer(QFrame *parent = nullptr);
    ~RegisterViewer();
    Ui::RegisterViewer* getUi();

private:
    Ui::RegisterViewer *ui;
};

#endif // REGISTERVIEWER_H
