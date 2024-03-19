#ifndef TOMASULOVIEW_H
#define TOMASULOVIEW_H

#include <QWidget>
#include <QSplitter>
#include "codeeditor.h"
#include "tomasulo.h"
#include "instructionbuffer.h"
#include "registerviewer.h"
#include "datamemoryviewer.h"
#include "regstatusviewer.h"
#include "instbufferviewer.h"
#include "resstationsviewer.h"
namespace Ui {
class TomasuloView;
}

class TomasuloView : public QSplitter
{
    Q_OBJECT

public:
    explicit TomasuloView(QWidget *parent = nullptr);
    ~TomasuloView();

private:
    Ui::TomasuloView *ui;

public:
    CodeEditor *code_textbox;
    DataMemoryViewer *datamemory_view;
    RegisterViewer *register_view;
    RegStatusViewer *regstatus_view;
    InstBufferViewer *instbuffer_view;
    ResStationsViewer *resstations_view;
    int thread_id;

public:
    void setThreadId(int thread_id);
};

#endif // TOMASULOVIEW_H
