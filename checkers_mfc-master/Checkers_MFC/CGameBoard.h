#pragma once
#include <list>
#include <utility>

using namespace std;
class CGameBoard
{
public:
    /* Statuses
       -999: Out of array bounds
       -2: Available for move
       -1: Empty white cell
       0: Empty black cell
       1: Black cell with Player 1's piece (white)
       2: Black cell with Player 2's piece (black)
       3: Black cell with Player 1's king (white)
       4: Black cell with Player 2's king (black)
    */
    enum class Status {
        out_matrix = -999,
        available_cell = -2,
        white_empty = -1,
        black_empty = 0,
        white_cell = 1,
        black_cell = 2,
        white_queen = 3,
        black_queen = 4
    };

    /* Default constructor */
    CGameBoard();

    /* Destructor */
    ~CGameBoard();

    /* Initial setup */
    void SetupBoard();

    /* Get the state of a specific cell */
    Status GetState(int row, int col);

    /* Getters for the game board parameters */
    int GetColumns() const { return m_nColumns; }
    int GetRows() const { return m_nRows; }
    int GetHeight() const { return m_nHeight; }
    int GetWidth() const { return m_nWidth; }

    /* Game result */
    int GetResult() const { return m_nResult; }

    /* Coordinates of the active piece */
    int GetCurrRow() const { return m_nCurrentRow; }
    int GetCurrCol() const { return m_nCurrentCol; }

    /* Get the turn order */
    bool GetMove() const { return m_nMove; }

    /* Update status */
    bool SetStatus(int row, int col, Status st);

    /* Set the active piece */
    void SetCurrRow(int row);
    void SetCurrCol(int col);

    /* Check if the game is over and save the result if the game has ended */
    bool IsGameOver();

    /* Delete the game board and free memory */
    void DeleteBoard();

    /* Reset available cells */
    void ResetAvailable();

    /* Change turn */
    void ChangeMove();

    /* Remove captured pieces */
    void BitMiddle(int row_before, int col_before, int row_after, int col_after);

    /* Get the list of available cells */
    list<pair<int, int>> getAvailableCellsList(int row, int col);
private:
    /* Pointer to the two-dimensional array */
    int** m_arrBoard;

    /* Board size */
    int m_nColumns;
    int m_nRows;
    int m_nHeight;
    int m_nWidth;

    /* Game result */
    /* Results:
       1 - White wins
       0 - Draw
       -1 - Black wins */
    int m_nResult;

    /*
      Turn order:
      true - White
      false - Black
    */
    bool m_nMove;

    /* Coordinates of the active piece */
    int m_nCurrentRow, m_nCurrentCol;

    /* Create the board */
    void CreateBoard();

    /* Get the list of available moves by offset */
    list<pair<int, int>> getAvailableCellsOffset(int row, int col, int row_offset, int col_offset, bool is_white);
};






if (!m_isSelected) {
    Pawn pawn = m_board.GetPawnAt(row, col);
    if (pawn.GetType() != PawnType::EMPTY) {
        m_isSelected = true;
        m_selectedRow = row;
        m_selectedCol = col;
        m_validMoves = m_board.GetValidMoves(row, col);
    }
}
else {
    Move move(m_selectedRow, m_selectedCol, row, col);
    if (std::find_if(m_validMoves.begin(), m_validMoves.end(), [&move](const Move& m) { 
        return m.GetStartRow() == move.GetStartRow() && m.GetStartCol() == move.GetStartCol()
            && m.GetEndRow() == move.GetEndRow() && m.GetEndCol() == move.GetEndCol(); }) != m_validMoves.end()
            && m_board.ApplyMove(move)) {
        m_isSelected = false;

        // Toggle the turn to the other player
        m_isBlackTurn = !m_isBlackTurn;
    }
    else {
        m_isSelected = false;
    }
}

Invalidate();