#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    solver = new SudokuSolver;

    connect(ui->solveButton, &QPushButton::clicked, this, &MainWindow::solveButtonClicked);
    connect(ui->clearButton, &QPushButton::clicked, this, &MainWindow::clearButtonClicked);
}

MainWindow::~MainWindow()
{
    delete solver;
    delete ui;
}

void MainWindow::clearButtonClicked()
{
    for (int row = 0; row < N; ++row) {
        for (int col = 0; col < N; ++col) {
            QString cellName = QString("cell_%1%2").arg(row).arg(col);
            QLineEdit *cell = findChild<QLineEdit*>(cellName);
            if (cell) {
                cell->clear();
                solver->setCell(row, col, 0, false);
                QPalette palette = cell->palette();
                palette.setColor(QPalette::Text, Qt::black);
                cell->setPalette(palette);
            }
        }
    }
    QMessageBox::information(this, "Message", "Grid has been cleared");
}

void MainWindow::solveButtonClicked()
{
    for (int row = 0; row < N; ++row) {
        for (int col = 0; col < N; ++col) {
            QString cellName = QString("cell_%1%2").arg(row).arg(col);
            QLineEdit *cell = findChild<QLineEdit*>(cellName);
            if (cell) {
                bool ok;
                int value = cell->text().toInt(&ok);
                if (ok) {
                    if (value >= 1 && value <= N) {
                        solver->setCell(row, col, value, true);
                    } else {
                        QMessageBox::critical(this, "Error", "Invalid input detected");
                        return;
                    }
                } else if (cell->text().isEmpty()) {
                    solver->setCell(row, col, 0, false);
                } else {
                    QMessageBox::critical(this, "Error", "Invalid input detected");
                    return;
                }
            }
        }
    }

    if (solver->solveSudoku(T)) {
        for (int row = 0; row < N; ++row) {
            for (int col = 0; col < N; ++col) {
                QString cellName = QString("cell_%1%2").arg(row).arg(col);
                QLineEdit *cell = findChild<QLineEdit*>(cellName);
                if (cell) {
                    int generatedValue = solver->getCell(row, col);
                    if (generatedValue != 0 && !solver->isUserInput(row, col)) {
                        QPalette palette = cell->palette();
                        palette.setColor(QPalette::Text, Qt::darkGreen);
                        cell->setPalette(palette);
                    }
                    cell->setText(QString::number(generatedValue));
                }
            }
        }
        QMessageBox::information(this, "Message", "Puzzle has been solved");
    } else {
        QMessageBox::critical(this, "Error", "Puzzle cannot be solved");
    }
}
