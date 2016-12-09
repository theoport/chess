#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <map>
#include <string>
#include "Chesspiece.h"


class ChessBoard
{
private:
	bool white_turn;
	std::string white_king,black_king;
	typedef Chesspiece* piece_ptr;
	piece_ptr pw,pb,rw,rb,hw,hb,bw,bb,kw,kb,qw,qb;
	std::map<std::string, Chesspiece*> board;
public:
	ChessBoard();
	~ChessBoard();
	void submitMove(const std::string a,const std::string b);
	bool empty(const std::string a);
	void move(const std::string a, const std::string b);
	void take(const std::string a, const std::string b);
	bool different_color(const std::string a, const std::string b);
	bool is_white(const std::string a);
	bool EoD(const std::string a, const std::string b);
	void no_move(const std::string a, const std::string b);
	bool free_straight(const std::string a,const std::string b);
	bool free_diagonal(const std::string a,const std::string b);
	bool move_into_check(const std::string a,const std::string b);
	bool in_check();
	bool stalemate();
	void check_status();
	void resetBoard();
	bool correct_input(const std::string init, const std::string dest);
};
			
#endif

