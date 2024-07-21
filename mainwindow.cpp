#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->Delaunay, &QPushButton::released, this, &MainWindow::onButtonDelaunay);
    connect(ui->Clown, &QPushButton::released, this, &MainWindow::onButtonClown);
    connect(ui->Knight, &QPushButton::released, this, &MainWindow::onButtonKnight);
    connect(ui->Castle, &QPushButton::released, this, &MainWindow::onButtonCastle);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::onButton()
{
    qDebug()<<"I'm Updating!";
    if(ui->widget->wire == false){
        ui->widget->wire = true;
    }
    else{
        ui->widget->wire = false;

    }

}

void MainWindow::onButtonDelaunay()
{
    qDebug()<<"I'm doing delaunay!";
    if(ui->widget->delaunay == false){
        ui->widget->delaunay = true;
    }
    else{
        ui->widget->delaunay = false;

    }

}

void MainWindow::onButtonClown()
{
    qDebug()<<"I'm changing mesh into Clown!";
    ui->widget->_geomWorld.change_file("C:/Users/dietf/OneDrive/Documents/geo_algo_maillage/GAM2022_Seance1/gam/data/clown.off");
}
void MainWindow::onButtonKnight()
{
    qDebug()<<"I'm changing mesh into Clown!";
    ui->widget->_geomWorld.change_file("C:/Users/dietf/OneDrive/Documents/geo_algo_maillage/GAM2022_Seance1/gam/data/knight.off");
}
void MainWindow::onButtonCastle()
{
    qDebug()<<"I'm changing mesh into Clown!";
    ui->widget->_geomWorld.change_file("C:/Users/dietf/OneDrive/Documents/geo_algo_maillage/GAM2022_Seance1/gam/data/castle.off");
}

