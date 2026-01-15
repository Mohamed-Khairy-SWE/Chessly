#include "MainWindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>


MainWindow::MainWindow(QWidget* parent)
    :QMainWindow{parent}
    {
        setWindowTitle("Chessly");
        resize(800, 600);

        auto* centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);

        auto* mainLayout = new QHBoxLayout(centralWidget);

        m_board = new ChessBoard(this);
        mainLayout->addWidget(m_board, 7);

        m_sidebar = new QWidget(this);
        m_sidebar->setFixedWidth(250);
        auto* sideLayout = new QVBoxLayout(m_sidebar);

        auto* statusLabel = new QLabel("Game status: Waitting", this);
        sideLayout->addWidget(statusLabel);

        auto* hostBtn = new QPushButton("Host game", this);
        auto* joinBtn = new QPushButton("Join game", this);
        sideLayout->addWidget(hostBtn);
        sideLayout->addWidget(joinBtn);
        sideLayout->addStretch();

        mainLayout->addWidget(m_sidebar, 3);

    }