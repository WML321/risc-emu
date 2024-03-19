#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include "qframe.h"
#include <QWidget>
#include <QFrame>
#include <QSplitter>
#include <ui_codeeditor.h>

namespace Ui {
class CodeEditor;
}
typedef void (*FunctionPtr)(int, ...);
class CodeEditor : public QFrame
{
    Q_OBJECT

public:
    explicit CodeEditor(QSplitter *parent = nullptr);
    ~CodeEditor();

public slots:
    void open_document();
    void load_program();
private:
    Ui::CodeEditor *ui;

public:
    void setText(QString txt);
    QString readFromFile(const QString &filename);
    void setDM(qint16 DM);
    void setFunctionPtr(FunctionPtr ptr);
    Ui::CodeEditor* getUi();
    void highlight_line(int line_num);

public:
    QString filename;
    qint16 DM; // 不知道哪个项目中的DM是什么类型的值，所以这里先使用整数代替一下
    FunctionPtr prog_loaded_callback;

};

#endif // CODEEDITOR_H
