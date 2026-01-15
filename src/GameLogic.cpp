#include "GameLogic.h"

GameLogic::GameLogic(){
    resetBoard();
}

//-----Initialization-----

void GameLogic::resetBoard(){

    if(m_turn == PieceColor::Black)
        m_turn = PieceColor::White;

    for(auto& row : m_board){
        for(auto& square : row){
            square = {};
        }
    }
    
    auto setupBackRow = [&](int row , PieceColor color){

        m_board[row][0] = {PieceType::Rook, color};
        m_board[row][1] = {PieceType::Knight, color};
        m_board[row][2] = {PieceType::Bishop, color};
        m_board[row][3] = {PieceType::Queen, color};
        m_board[row][4] = {PieceType::King, color};
        m_board[row][5] = {PieceType::Bishop, color};
        m_board[row][6] = {PieceType::Knight, color};
        m_board[row][7] = {PieceType::Rook, color};
    };

    setupBackRow(0,PieceColor::Black);
    setupBackRow(7,PieceColor::White);

    for(int col{}; col<boardSize; col++){
        m_board[1][col] = {PieceType::Pawn, PieceColor::Black};
        m_board[6][col] = {PieceType::Pawn, PieceColor::White};
    }
}


//-----Board state-----

Piece GameLogic::getPiece(Pos& pos)const{
    if(!isVaild(pos))
        return {};

    return m_board[pos.row][pos.col];
}

//-----Logic-----

bool GameLogic::isLegalMove(Pos& from, Pos& to)const {

    if(!isVaild(from) || !isVaild(to))
        return false;

    if(from == to)
        return false;
    
        Piece piece {getPiece(from)};

    if(piece.color != m_turn || piece.isEmpty())
       return false;

    const Piece target {getPiece(to)};

    if(!target.isEmpty() && target.color == m_turn)
        return false;
    
    return true;
}

bool GameLogic::movePiece(Pos& from, Pos& to){
    
    if(!isLegalMove(from , to))
        return false;
    
    m_board[to.row][to.col] = m_board[from.row][from.col];
    m_board[from.row][from.col] = {};

    m_turn = currentTurn() == PieceColor::White 
            ? PieceColor::Black 
            : PieceColor::White;
            
    return true;
}