#ifndef DATAMEMORYVIEWER_H
#define DATAMEMORYVIEWER_H

#include <QFrame>

namespace Ui {
class DataMemoryViewer;
}

class DataMemoryViewer : public QFrame
{
    Q_OBJECT

public:
    explicit DataMemoryViewer(QWidget *parent = nullptr);
    ~DataMemoryViewer();
    Ui::DataMemoryViewer* getUi();

private:
    Ui::DataMemoryViewer *ui;
};

#endif // DATAMEMORYVIEWER_H
