#include "wordquest.h"

#include <QChar>

void WordQuest::clearTableElements()
{
    letters.clear();
    used.clear();
}

void WordQuest::setTableElements(int rows, int columns, QString letterLine)
{
    this->rows = rows;
    this->columns = columns;

    for (int i = 0; i < rows * columns; i++) {
        this->letters.push_back(letterLine.at(i));
        this->used.push_back(true);
    }
}

void WordQuest::findWordInTable(QString word, QVector<int> &indices)
{
    if (word.length() == 0) {
        return;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            // Извлечение и проверка первой буквы
            QChar firstLetter = word.at(0);
            int index = i * columns + j;

            if (firstLetter != letters.at(index)) {
                continue;
            }

            // Отметить используемую букву
            resetUsed();
            used[index] = false;
            indices.push_back(index);

            int row = i;
            int col = j;

            // Проверка соседних букв на соответствие
            for (int k = 1; k < word.length(); k++) {
                QChar nextLetter = word.at(k);

                if (isNeighbour(row + 1, col, nextLetter)) {          // Нижняя буква
                    used[columns * (row + 1) + col] = false;
                    indices.push_back(columns * (row + 1) + col);
                    row = row + 1;
                } else if (isNeighbour(row - 1, col, nextLetter)) { // Верхняя буква
                    used[columns * (row - 1) + col] = false;
                    indices.push_back(columns * (row - 1) + col);
                    row = row - 1;
                } else if (isNeighbour(row, col + 1, nextLetter)) { // Правая буква
                    used[columns * row + col + 1] = false;
                    indices.push_back(columns * row + col + 1);
                    col = col + 1;
                } else if (isNeighbour(row, col - 1, nextLetter)) { // Левая буква
                    used[columns * row + col - 1] = false;
                    indices.push_back(columns * row + col - 1);
                    col = col - 1;
                }
            }

            // Найдя слово, закончить работу
            if (indices.length() == word.length()) {
                return;
            } else {
                indices.clear();
            }
        }
    }
}

bool WordQuest::isNeighbour(int row, int col, QChar nextLetter)
{
    return row < rows
            && row >= 0
            && col < columns
            && col >= 0
            && used.at(columns * row + col)
            && nextLetter == letters.at(columns * row + col);
}

void WordQuest::resetUsed()
{
    for (int i = 0; i < used.length(); i++) {
        used[i] = true;
    }
}
