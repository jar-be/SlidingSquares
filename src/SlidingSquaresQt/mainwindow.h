#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QToolButton>
#include <vector>
#include <memory>
#include <cboard.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Ui::MainWindow *ui;
    std::unique_ptr<CBoard> board;
    std::vector<QToolButton*> buttons;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();    
private slots:
    void on_actionNew_triggered();
private:
    void onGridButtonClicked(int btnId);
    QToolButton *createButton(int btnIndex);
    void clearButtons();
    void newGame();
    void updateButtons();
    void createButtons();
};
#endif // MAINWINDOW_H
