#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <stdexcept>
#include <QMessageBox>
#include <QToolButton>
#include <QTimer>
#include <QInputDialog>
#include "cgame.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
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
    auto duration_in_seconds = the_game.get_game_stats().get_duration().get_formatted_duration();
    timer_label->setText(QString("Taken: %1").arg(duration_in_seconds.c_str()));
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

void MainWindow::create_board(int size)
{
    the_game.new_game(size);
    the_game.shuffle(CGame::random);

    create_buttons(size);
}

void MainWindow::create_buttons(int size)
{
    int buttonsCount = size * size;
    for (int i = 0; i < buttonsCount; ++i) {
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
    timer->stop();

    bool ok = false;
    auto boardSize = QInputDialog::getInt(
                this,
                "New game",
                "Board size: ",
                3,
                3,
                20,
                1,
                &ok);

    if (!ok) {
        return;
    }

    clear_buttons();

    create_board(boardSize);

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
    auto display_name = the_game.get_display_name(i);

    if (display_name.empty()) {
        button->setText("");
        button->hide();
    } else {
        button->setText(display_name.c_str());
        button->show();
    }

    const QString styleBase = "font-size: 15px; font-weight: bold; background-color: %1;";
    if (the_game.is_at_correct_place(i)) {
        button->setStyleSheet(styleBase.arg("lightgreen"));
    } else {
        button->setStyleSheet(styleBase.arg("orange"));
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
        auto newSquarePosition = the_game.move(btnId);
        update_buttons({ newSquarePosition, (size_t)btnId });
        move_count_label->setText(QString("Moves: %1").arg(the_game.get_game_stats().get_move_count()));
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
    if (!timer->isActive()) {
        timer->start(500);
    }

    move_square(btnId);

    if (the_game.is_solved()) {
        set_disable_buttons(true);
        timer->stop();
        auto duration = the_game.get_game_stats().get_duration().get_formatted_duration();

        QMessageBox::information(
                    ui->centralwidget,
                    "Solved",
                    QStringLiteral("You've solved this puzzle in %1 moves and it took you %2.")
                    .arg(the_game.get_game_stats().get_move_count())
                    .arg(duration.c_str()));
    }
}

void MainWindow::on_actionNew_triggered()
{
    new_game();
}
