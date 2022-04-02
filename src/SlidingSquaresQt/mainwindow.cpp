#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QToolButton>
#include <cboard.h>
#include <crandomshuffler.h>
#include <stdexcept>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , board(nullptr)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


QToolButton *MainWindow::createButton(int btnIndex, std::string displayName)
{
    auto button = new QToolButton(ui->centralwidget);
    button->setMinimumSize(50, 50);
    button->setMaximumSize(1000, 1000);
    auto sizePolicy = button->sizePolicy();
    sizePolicy.setHorizontalPolicy(QSizePolicy::MinimumExpanding);
    sizePolicy.setVerticalPolicy(QSizePolicy::MinimumExpanding);
    sizePolicy.setRetainSizeWhenHidden(true);

    button->setText(displayName.c_str());

    QObject::connect(button, &QToolButton::clicked, this, [=]() {
        onGridButtonClicked(btnIndex);
    });

    return button;
}

void MainWindow::clearButtons()
{
    while (!buttons.empty()) {
        auto button = buttons.back();
        buttons.pop_back();
        ui->gridLayoutBtns->removeWidget(button);
        delete button;
    }
    buttons.clear();
}

void MainWindow::on_pushButton_clicked()
{
    clearButtons();

    int size = 4;
    int sqauareCount = size * size;

    board = std::make_unique<CBoard>(size);
    CRandomShuffler shuffler;
    board->Shuffle(shuffler, 100);

    for (int i = 0; i < sqauareCount; ++i) {
        auto square = board->at(i);
        auto button = createButton(i, square.DisplayName());
        buttons.push_back(button);

        int row = i / size;
        int col = i % size;
        ui->gridLayoutBtns->addWidget(button, row, col);

        if (square.IsEmpty()) {
            button->hide();
        }
    }
}

void MainWindow::onGridButtonClicked(int btnId)
{
    try {
        board->Move(btnId);
    } catch (std::invalid_argument &inv_arg) {
        QMessageBox::warning(ui->centralwidget,
                             "Wrong move!",
                             QStringLiteral("Wrong move attempted: %1").arg(inv_arg.what()));
    } catch (std::out_of_range &oor) {
        QMessageBox::critical(ui->centralwidget,
                             "Something is seriously wrong!",
                             QStringLiteral("This should never hve happend: %1").arg(oor.what()));
    }

    for (size_t i = 0; i < buttons.size(); ++i) {
        auto button = buttons.at(i);
        auto square = board->at(i);
        button->setText(square.DisplayName().c_str());
        if (square.IsEmpty()) {
            button->hide();
        } else {
            button->show();
        }
    }
}
