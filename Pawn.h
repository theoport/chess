// See Chesspiece.h for comments

#ifndef PAWN_H
#define PAWN_H
#include <string>
#include "Chesspiece.h"
#include "ChessBoard.h"

class Pawn:public Chesspiece
{
public:
	Pawn(std::string color,ChessBoard* chessboard);
	void submitMove(const std::string init, const std::string dest);
	bool valid_move(const std::string init, const std::string dest);
	bool can_move(const std::string init);
};

#endif

