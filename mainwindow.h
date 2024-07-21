#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QPushButton>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QPushButton *Delaunay;


private slots:
    void onButton();
    void onButtonDelaunay();
    void onButtonClown();
    void onButtonKnight();
    void onButtonCastle();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
