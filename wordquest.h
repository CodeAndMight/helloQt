#ifndef WORDQUEST_H
#define WORDQUEST_H

#include <QVector>
#include <QChar>
#include <QString>

class WordQuest
{
public:
    void clearTableElements();
    void setTableElements(int rows, int columns, QString letterLine);
    void findWordInTable(QString word, QVector<int> &indices);

private:
    QVector<QChar> letters;
    QVector<bool> used;

    int rows;
    int columns;

    void resetUsed();
    bool isNeighbour(int row, int col, QChar nextLetter);
};

#endif // WORDQUEST_H
