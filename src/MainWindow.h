#pragma once

#include <QMainWindow>
#include "ChessBoard.h"

class MainWindow : public QMainWindow{
    Q_OBJECT
public:

    MainWindow(QWidget* parent = nullptr);

    ~MainWindow() override = default;

private:
    ChessBoard* m_board;
    QWidget* m_sidebar;
};