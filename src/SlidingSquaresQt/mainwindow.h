#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QToolButton>
#include <QLabel>
#include <QTimer>
#include <vector>
#include <memory>
#include "cgame.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Ui::MainWindow *ui;
    CGame the_game;
    std::vector<QToolButton*> buttons;
    QLabel *move_count_label;
    QLabel *timer_label;
    QTimer *timer;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();    
private slots:
    void on_actionNew_triggered();
private:
    void on_grid_button_clicked(int btnId);
    QToolButton *create_button(int btnIndex);
    void clear_buttons();
    void new_game();
    void update_buttons();
    void create_board(int size);
    void update_buttons(const std::vector<size_t> &buttonIdxs);
    void update_button(size_t i);
    void move_square(int btnId);
    void set_disable_buttons(bool disabled);
    void update_timer_label();
    void create_buttons(int size);
};
#endif // MAINWINDOW_H
