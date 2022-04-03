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


QToolButton *MainWindow::createButton(int btnIndex)
{
    auto button = new QToolButton(ui->centralwidget);
    button->setMinimumSize(20, 20);
    button->setMaximumSize(1000, 1000);
    auto sizePolicy = button->sizePolicy();
    sizePolicy.setHorizontalPolicy(QSizePolicy::MinimumExpanding);
    sizePolicy.setVerticalPolicy(QSizePolicy::MinimumExpanding);
    sizePolicy.setRetainSizeWhenHidden(true);

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
        button = nullptr;
    }
    buttons.clear();
}

void MainWindow::createButtons()
{
    int size = 4;
    int sqauareCount = size * size;

    board = std::make_unique<CBoard>(size);
    CRandomShuffler shuffler;
    board->Shuffle(shuffler, 100);

    for (int i = 0; i < sqauareCount; ++i) {
        auto button = createButton(i);
        buttons.push_back(button);

        int row = i / size;
        int col = i % size;
        ui->gridLayoutBtns->addWidget(button, row, col);
    }
}

void MainWindow::newGame()
{
    clearButtons();

    createButtons();

    updateButtons();
}

void MainWindow::updateButtons(const std::vector<size_t> &buttonIdxs) {
    for (const auto &idx : buttonIdxs) {
        updateButton(idx);
    }
}

void MainWindow::updateButton(size_t i)
{
    auto button = buttons.at(i);
    auto square = board->at(i);
    button->setText(square.DisplayName().c_str());

    const QString styleBase = "font-size: 1.2em; background-color: %1;";
    if (board->isAtCorrectPlace(i)) {
        button->setStyleSheet(styleBase.arg("green"));
    } else {
        button->setStyleSheet(styleBase.arg("orange"));
    }

    if (square.IsEmpty()) {
        button->hide();
    } else {
        button->show();
    }
}

void MainWindow::updateButtons()
{
    for (size_t i = 0; i < buttons.size(); ++i) {
        updateButton(i);
    }
}

void MainWindow::onGridButtonClicked(int btnId)
{
    try {
        auto newSquarePosition = board->Move(btnId);
        updateButtons({ newSquarePosition, (size_t)btnId });

    } catch (std::invalid_argument &inv_arg) {
        QMessageBox::warning(ui->centralwidget,
                             "Wrong move!",
                             QStringLiteral("Wrong move attempted: %1").arg(inv_arg.what()));
    } catch (std::out_of_range &oor) {
        QMessageBox::critical(ui->centralwidget,
                             "Something is seriously wrong!",
                             QStringLiteral("This should never have happend: %1").arg(oor.what()));
    }

    if (board->isSolved()) {
        QMessageBox::information(
                    ui->centralwidget,
                    "Solved",
                    QStringLiteral("You've solved this puzzle in %1 moves").arg(board->MoveCount()));
        newGame();
    }
}

void MainWindow::on_actionNew_triggered()
{
    newGame();
}
