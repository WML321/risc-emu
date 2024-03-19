#include "datamemoryviewer.h"
#include "ui_datamemoryviewer.h"
#include <QScrollBar>
#include <vector>
#include <sstream>
#include <iomanip>
#include <numeric>

DataMemoryViewer::DataMemoryViewer(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::DataMemoryViewer)
{
    ui->setupUi(this);
    connect(ui->hex_box->verticalScrollBar(), &QScrollBar::valueChanged, this, [this](int v){
        ui->ascii_box->verticalScrollBar()->setValue(v);
    });
    connect(ui->ascii_box->verticalScrollBar(), &QScrollBar::valueChanged, this, [this](int v){
        ui->hex_box->verticalScrollBar()->setValue(v);
    });

    std::vector<std::string> hex_data;
    std::vector<char> ascii_data;
    std::vector<int> DM = {1,2,3,4,5,6,7,2,324,245,2};
    for (auto val : DM) {
        std::stringstream hex_stream;
        hex_stream << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(val);
        hex_data.push_back(hex_stream.str());

        if (std::isprint(val) && val != '\n' && val != '\r' && val != '\t' && val != '\v') {
            ascii_data.push_back(val);
        } else {
            ascii_data.push_back('.');
        }
    }

    std::string hex_text = std::accumulate(hex_data.begin(), hex_data.end(), std::string(),
                                           [](const std::string& a, const std::string& b) {
                                               return a.empty() ? b : a + " " + b;
                                           });
    std::string ascii_text(ascii_data.begin(), ascii_data.end());

    ui->hex_box->setPlainText(QString::fromStdString(hex_text));
    ui->ascii_box->setPlainText(QString::fromStdString(ascii_text));
}

DataMemoryViewer::~DataMemoryViewer()
{
    delete ui;
}

Ui::DataMemoryViewer* DataMemoryViewer::getUi(){
    return this->ui;
}
