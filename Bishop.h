// See Chesspiece.h for comments

#ifndef BISHOP_H
#define BISHOP_H
#include <string>
#include "Chesspiece.h"
#include "ChessBoard.h"

class Bishop:public Chesspiece
{
public:
	Bishop(std::string color,ChessBoard* chessboard);
	void submitMove(const std::string init,const std::string dest);
	bool valid_move(const std::string init, const std::string dest);
	bool can_move(const std::string init);
};

#endif
