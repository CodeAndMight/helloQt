#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QVector>
#include <QTableWidgetItem>
#include <QString>

#include "wordquest.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_loadPushButton_clicked();

    void on_searchPushButton_clicked();

private:
    Ui::MainWindow *ui;

    QMessageBox errorMessageBox;

    QVector<QTableWidgetItem *> tableItems;
    WordQuest wordQuest;

    void removeWidgetCells();
    void deleteTableItems();
    void setTableWidgetSize(int rows, int columns);
    void putElementsToTableWidget(int rows, int columns, QString letterLine);

    void turnOffHighlightCell();
    void turnOnHighlightCellIfNeeded(QVector<int> &indices);
};

#endif // MAINWINDOW_H
