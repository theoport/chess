// See Chesspiece.h for comments

#ifndef QUEEN_H
#define QUEEN_H
#include <string>
#include "Chesspiece.h"
#include "ChessBoard.h"

class Queen:public Chesspiece 
{
private:
	static const int SURROUNDING=8;
public:
	Queen(std::string color,ChessBoard* chessboard);
	void submitMove(const std::string init,const std::string dest);
	bool valid_move(const std::string init, const std::string dest);
	bool can_move(const std::string init);
};

#endif
