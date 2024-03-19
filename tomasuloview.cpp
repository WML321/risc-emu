#include "tomasuloview.h"
#include "ui_tomasuloview.h"
#include "codeeditor.h"

TomasuloView::TomasuloView(QWidget *parent)
    : QSplitter(parent)
    , ui(new Ui::TomasuloView)
{
    this->code_textbox = new CodeEditor(this);
    ui->code_textbox = this->code_textbox->getUi(); // 和下一行的位置不能反，因为在setupUi中使用到了code_textbox，如果不先进行这一步，那么在setupUi中的这个属性就是空的，会导致崩溃

    this->datamemory_view = new DataMemoryViewer(this);
    ui->datamemory_viewer = this->datamemory_view->getUi();

    this->register_view = new RegisterViewer(this);
    ui->register_view = this->register_view->getUi();

    this->regstatus_view = new RegStatusViewer(this);
    ui->regstatus_view = this->regstatus_view->getUi();

    this->instbuffer_view = new InstBufferViewer(this);
    ui->instbuffer_view = this->instbuffer_view->getUi();

    this->resstations_view = new ResStationsViewer(this);
    ui->resstations_view = this->resstations_view->getUi();

    ui->setupUi(this);

    //connect(ui->code_textbox->btn_open, &QPushButton::clicked, this->code_textbox, &::CodeEditor::open_document);
    //因为这里的ui和第三个参数不匹配第三个参数不匹配
    //在这个槽函数中，使用到了ui中的按钮，但是如果CodeEditor中没有调用setupUi，则按钮是空的，而且，CodeEditor中指向的ui中的各个按钮和
    // tomasuloview中的ui中的按钮根本就没有指向一个内容
    //connect(ui->code_textbox->btn_load, &QPushButton::clicked, this->code_textbox, &::CodeEditor::load_program);

}

TomasuloView::~TomasuloView()
{
    delete ui;
}

void TomasuloView::setThreadId(int thread_id)
{
    this->thread_id = thread_id;
}
