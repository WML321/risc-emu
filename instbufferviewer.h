#ifndef INSTBUFFERVIEWER_H
#define INSTBUFFERVIEWER_H

#include <QFrame>

namespace Ui {
class InstBufferViewer;
}

class InstBufferViewer : public QFrame
{
    Q_OBJECT

public:
    explicit InstBufferViewer(QWidget *parent = nullptr);
    ~InstBufferViewer();
    Ui::InstBufferViewer* getUi(){
        return this->ui;
    }

private:
    Ui::InstBufferViewer *ui;
};

#endif // INSTBUFFERVIEWER_H
