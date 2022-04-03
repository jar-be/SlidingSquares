#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <stdexcept>
#include <chrono>
#include <QMessageBox>
#include <QToolButton>
#include <QTimer>
#include "cboard.h"
#include "crandomshuffler.h"
#include "crandshufflerwithmemory.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , board(nullptr)
    , started(false)
{
    ui->setupUi(this);
    move_count_label = new QLabel(this);
    move_count_label->setText("Start a new game with Game->New");
    ui->statusbar->addWidget(move_count_label);
    ui->statusbar->addWidget(new QLabel(this), 1);
    timer_label = new QLabel(this);
    ui->statusbar->addWidget(timer_label);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=]() {
        update_timer_label();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_timer_label()
{
    namespace cr = std::chrono;
    auto end = cr::system_clock::now();
    auto diff = end - start;
    auto in_seconds = cr::duration_cast<cr::seconds>(diff).count();
    timer_label->setText(QString("Taken: %1s").arg(in_seconds));
}

QToolButton *MainWindow::create_button(int btnIndex)
{
    auto button = new QToolButton(ui->centralwidget);
    button->setMinimumSize(20, 20);
    button->setMaximumSize(1000, 1000);
    auto sizePolicy = button->sizePolicy();
    sizePolicy.setHorizontalPolicy(QSizePolicy::MinimumExpanding);
    sizePolicy.setVerticalPolicy(QSizePolicy::MinimumExpanding);
    sizePolicy.setRetainSizeWhenHidden(true);

    QObject::connect(button, &QToolButton::clicked, this, [=]() {
        on_grid_button_clicked(btnIndex);
    });

    return button;
}

void MainWindow::clear_buttons()
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

void MainWindow::create_buttons()
{
    int size = 3;
    int sqauareCount = size * size;

    board = std::make_unique<CBoard>(size);
    CRandomShuffler shuffler;
    board->shuffle(shuffler, 100);

    for (int i = 0; i < sqauareCount; ++i) {
        auto button = create_button(i);
        buttons.push_back(button);

        int row = i / size;
        int col = i % size;
        ui->gridLayoutBtns->addWidget(button, row, col);
    }
}

void MainWindow::new_game()
{
    move_count_label->setText("Moves: 0");
    timer_label->setText("");

    clear_buttons();

    create_buttons();

    update_buttons();
}

void MainWindow::update_buttons(const std::vector<size_t> &buttonIdxs)
{
    for (const auto &idx : buttonIdxs) {
        update_button(idx);
    }
}

void MainWindow::update_button(size_t i)
{
    auto button = buttons.at(i);
    auto square = board->at(i);
    button->setText(square.displayName().c_str());

    const QString styleBase = "font-size: 15px; font-weight: bold; background-color: %1;";
    if (board->is_at_correct_place(i)) {
        button->setStyleSheet(styleBase.arg("lightgreen"));
    } else {
        button->setStyleSheet(styleBase.arg("orange"));
    }

    if (square.is_empty()) {
        button->hide();
    } else {
        button->show();
    }
}

void MainWindow::update_buttons()
{
    for (size_t i = 0; i < buttons.size(); ++i) {
        update_button(i);
    }
}

void MainWindow::move_square(int btnId)
{
    try {
        auto newSquarePosition = board->move(btnId);
        update_buttons({ newSquarePosition, (size_t)btnId });
        move_count_label->setText(QString("Moves: %1").arg(board->moveCount()));
    } catch (std::invalid_argument &inv_arg) {
        QMessageBox::warning(ui->centralwidget,
                             "Wrong move!",
                             QStringLiteral("Wrong move attempted: %1").arg(inv_arg.what()));
    } catch (std::out_of_range &oor) {
        QMessageBox::critical(ui->centralwidget,
                             "Something is seriously wrong!",
                             QStringLiteral("This should never have happend: %1").arg(oor.what()));
    }
}

void MainWindow::set_disable_buttons(bool disabled)
{
    for (const auto &btn : buttons) {
        btn->setDisabled(disabled);
    }
}

void MainWindow::on_grid_button_clicked(int btnId)
{
    if (!started) {
        start = std::chrono::system_clock::now();
        started = true;
        timer->start(1000);
    }

    move_square(btnId);

    if (board->is_solved()) {
        namespace cr = std::chrono;
        auto end = cr::system_clock::now();
        auto time_taken_to_solve_puzzle = end - start;
        auto in_seconds = cr::duration_cast<cr::seconds>(time_taken_to_solve_puzzle);

        QMessageBox::information(
                    ui->centralwidget,
                    "Solved",
                    QStringLiteral("You've solved this puzzle in %1 moves and it took %2 seconds.")
                    .arg(board->moveCount())
                    .arg(in_seconds.count()));
        set_disable_buttons(true);
        timer->stop();
        started = false;
    }
}

void MainWindow::on_actionNew_triggered()
{
    new_game();
}
