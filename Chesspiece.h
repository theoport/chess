/*
submitMove:	Pre-Condition: strings "init" and "dest" are existing fields
						on a chessboard. Field "init" is occupied by a chesspiece.
						Post-Condition: Attempts to move chesspiece from position 
						"init" to position "dest". Checks whether destination field
						is free or whether the chesspiece can attack opponents 
						piece on destination field. Checks if piece leaves player in
						 check. Checks all fields between start and destination field
						are unoccupied. Checks if move is permitted by characteristics of the 
						chesspiece that occupies starting field.  
valid_move:	Helps submitMove
can_move:		Pre-Condition: strings "init" and "dest" are existing fields
						on a chessboard. Field "init" is occupied by a chesspiece.
						Post-Condition:Checks if there exists a legal move for piece
						on field "init".
get_color:	Returns color of chesspiece.
get_type:		Returns type of chesspiecel
*/


#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <string>
#include "ChessBoard.h"

class ChessBoard;

class Chesspiece
{
protected:
	std::string color, type;
	ChessBoard* chessboard;
public:
	Chesspiece (std::string a, std::string b, ChessBoard* c);
	virtual ~Chesspiece(){}
	virtual void submitMove(const std::string init, const std::string dest)=0;
	virtual bool valid_move(const std::string init, const std::string dest)=0;
	virtual bool can_move(const std::string init)=0;
	std::string get_color();
	std::string get_type();	
};

#endif
