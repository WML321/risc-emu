#include "codeeditor.h"
#include "ui_codeeditor.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QTextCharFormat>
#include <QBrush>
#include <QTextBlock>
#include <QTextCursor>
CodeEditor::CodeEditor(QSplitter *parent)
    : QFrame(parent)
    , ui(new Ui::CodeEditor) // 在这里还需要有其他的参数，现在做的事情是，把UI界面做出来，而不关系逻辑，所有脱离逻辑的UI设计都卸载ui_xxx.h中，而与逻辑
//相关的一切内容都在这里写。
{
    ui->setupUi(this);
    connect(ui->btn_open, &QPushButton::clicked, this, &::CodeEditor::open_document);
    connect(ui->btn_load, &QPushButton::clicked, this, &::CodeEditor::load_program);
}

CodeEditor::~CodeEditor()
{
    delete ui;
}

void CodeEditor::open_document()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open File", "D:\\QT\\Program\\risv-gui", "All Files (*.*)");
    if(!filename.isEmpty())
    {
        this->filename = filename;
        QFileInfo fileInfo(this->filename);
        QString ext = fileInfo.suffix(); //读取拓展名

        if(ext.compare(".s"))
        {
            // setText
            this->setText(this->readFromFile(filename));
        }else if(ext.compare(".o")){ //ELF file
            // setText
            this->setText("Press \"Load Program\" to disassemble and display.\n");
        }else{
            throw std::invalid_argument("Unsupported file type");
        }
    }
}

void CodeEditor::load_program(){
    // 这部分需要有一些逻辑代码，所以我先空着
    this->setText("Load_program");
}

void CodeEditor::setText(QString txt)
{
    ui->text_edit->setText(txt);
}

QString CodeEditor::readFromFile(const QString &filename)
{
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        // 如果文件读取失败
       QString errorMsg = "Failed to open file: " + filename;
        throw std::ios_base::failure(errorMsg.toStdString());
    }

    QTextStream in(&file);
    QString content = in.readAll();
    file.close();
    return content;
}

void CodeEditor::setDM(qint16 DM)
{
    this->DM = DM;
}

void CodeEditor::setFunctionPtr(FunctionPtr ptr)
{
    this->prog_loaded_callback = ptr;
}

void CodeEditor::highlight_line(int line_num)
{
    QTextCharFormat fmt;
    QColor color(220,0,0,255);
    QBrush brush(color);
    fmt.setForeground(brush);
    QTextBlock block = this->ui->text_edit->document()->findBlockByLineNumber(line_num);
    int blockPos = block.position();
    QTextCursor cursor(this->ui->text_edit->document());
    cursor.setPosition(blockPos);
    cursor.select(QTextCursor::LineUnderCursor);
    cursor.setCharFormat(fmt);
}

// void CodeEditor::setUi(Ui::CodeEditor *ui)
// {
//     this->ui = ui;
// }

Ui::CodeEditor* CodeEditor::getUi()
{
    return this->ui;
}
