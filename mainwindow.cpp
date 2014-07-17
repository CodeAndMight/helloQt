#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>
#include <QFileDialog>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), errorMessageBox(this)
{
    ui->setupUi(this);
    errorMessageBox.setText("Файл не соответствует формату!");
    errorMessageBox.setIcon(QMessageBox::Warning);
}

MainWindow::~MainWindow()
{
    deleteTableItems();

    delete ui;
}

void MainWindow::on_loadPushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    QFile file(fileName);

    if (!file.exists()) {
        return;
    }

    file.open(QIODevice::ReadOnly);

    QString sizeLine = file.readLine();
    QString letterLine = file.readLine();
    QStringList size = sizeLine.split(" ");

    file.close();

    if (size.length() < 2) {
        errorMessageBox.exec();
        return;
    }

    bool successRows, successColumns;
    int rows = size.at(0).toInt(&successRows);
    int columns = size.at(1).toInt(&successColumns);

    if (successRows && successColumns && letterLine.length() >= rows * columns) {
        wordQuest.clearTableElements();
        wordQuest.setTableElements(rows, columns, letterLine);
        removeWidgetCells();
        deleteTableItems();
        setTableWidgetSize(rows, columns);
        putElementsToTableWidget(rows, columns, letterLine);
    } else {
        errorMessageBox.exec();
    }
}

void MainWindow::on_searchPushButton_clicked()
{
    QVector<int> indices;
    QString word = ui->wordLineEdit->text();

    turnOffHighlightCell();
    wordQuest.findWordInTable(word, indices);
    turnOnHighlightCellIfNeeded(indices);
}

void MainWindow::turnOnHighlightCellIfNeeded(QVector<int> &indices)
{
    for (int i = 0; i < indices.length(); i++) {
        QTableWidgetItem *item = tableItems.at(indices.at(i));
        QColor color(Qt::red);

        item->setForeground(color);
    }
}

void MainWindow::turnOffHighlightCell()
{
    for (int i = 0; i < tableItems.length(); i++) {
        QTableWidgetItem *item = tableItems.at(i);
        QColor color(Qt::black);

        item->setForeground(color);
    }
}

void MainWindow::putElementsToTableWidget(int rows, int columns, QString letterLine)
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            int index = columns * i + j;

            QString element(letterLine.at(index));
            QTableWidgetItem *item = new QTableWidgetItem(element);

            ui->letterTableWidget->setItem(i, j, item);
            tableItems.push_back(item);
        }
    }
}

void MainWindow::setTableWidgetSize(int rows, int columns)
{
    ui->letterTableWidget->setRowCount(rows);
    ui->letterTableWidget->setColumnCount(columns);
}

void MainWindow::deleteTableItems()
{
    if (tableItems.empty()) {
        return;
    }

    for (int i = 0; i < tableItems.length(); i++) {
        QTableWidgetItem *item = tableItems.at(i);

        delete item;
    }

    tableItems.clear();
}

void MainWindow::removeWidgetCells()
{
    QTableWidget *tableWidget = ui->letterTableWidget;

    for (int i = 0; i < tableWidget->rowCount(); i++) {
        for (int j = 0; j < tableWidget->columnCount(); j++) {
            tableWidget->removeCellWidget(i, j);
        }
    }
}
