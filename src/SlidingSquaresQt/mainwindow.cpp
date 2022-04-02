#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QToolButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    buttons.clear();
    int size = 4;
    int sqauareCount = size * size;
    for (int i = 0; i < sqauareCount; ++i) {
        QString buttonName(std::to_string(i).c_str());
        auto button = new QToolButton(ui->centralwidget);
        QObject::connect(button, &QToolButton::clicked, [=]() {
             on_gridButton_clicked(i);
        });
        int row = i / size;
        int col = i % size;
        ui->gridLayoutBtns->addWidget(button, row, col);
        button->setMinimumSize(50, 50);
        button->setMaximumSize(1000, 1000);
        button->sizePolicy().setHorizontalPolicy(QSizePolicy::MinimumExpanding);
        button->sizePolicy().setVerticalPolicy(QSizePolicy::MinimumExpanding);
        button->sizePolicy().setRetainSizeWhenHidden(true);

        if (i == 5) {
            button->hide();
        }
    }
}

void MainWindow::on_gridButton_clicked(int btnId)
{
    QMessageBox::information(ui->centralwidget, "This is a title", QStringLiteral("My magic number is %1. That's all!").arg(btnId));
}
