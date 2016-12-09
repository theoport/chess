// See Chesspiece.h for comments

#ifndef ROOK_H
#define ROOK_H
#include <string>
#include "ChessBoard.h"
#include "Chesspiece.h"

class Rook : public Chesspiece
{
private:
	static const int SURROUNDING=4;
public:
	Rook(std::string color,ChessBoard* chessboard);
	void submitMove(const std::string init, const std::string dest);
	bool valid_move(const std::string init, const std::string dest);
	bool can_move(const std::string pos);
};

#endif
