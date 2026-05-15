#include "mainwindow.h"
#include "tetriswindow.h"
#include "ui_mainwindow.h"
#include "precompiled.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    TetrisWindow *window = new TetrisWindow;

    QHBoxLayout *layout = new QHBoxLayout;

    layout->addWidget(window);
    setCentralWidget(new QWidget);
    centralWidget()->setLayout(layout);
    setFixedSize(500, 670);
}

MainWindow::~MainWindow()
{
    delete ui;
}
