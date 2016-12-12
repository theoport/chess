#ifndef CHESSBOARD_H
#define CHESSBOARD_H

/*
submitMove: 			Pre-Condition: Chessboard exists.
									Post-Condition: Checks if stings "a" and "b"
									are in the right format, i.e. in the form of
									an existing field on the chessboard. Also 
									checks if field "a" is empty and if not, whether
									it is the turn of the player on field "a".
empty:						Pre-Condition: string "a" is an existing 
									field on a chessboard.
									Post-Condition: returns true if chess field
									is empty, otherwise returns false.
move:							Pre-Condition: strings "a" and "b" are existing
									fields on a chessboard,"a" is occupied, the move
									from field "a" to field "b" is legal and "b" is empty.
									Post-Condition: moves chesspiece from "a" to "b"
									and outputs message.
take:							Pre-Condition: strings "a" and "b" are existing fields
									on a chessboard, move from field "a" to field "b" is 
									legal and "a" and "b" are occupied by chesspieces of 
									opposite colors.
									Post-Condition: moves chesspiece on field "a" to 
									field "b" and removes chesspiece on field "b" from
									chessboard. Outputs appropriate message
different_color:	Pre-Condition: Field "a" and "b" are both existing,
									occupied fields on the chessboard.
									Post-Condition: Returns true if chesspieces on "a" 
									and "b" have different colors. Returns false if otherwise.
is_white:					Pre-Condition: Field "a" is an existing, occupied 
									field on the chessboard. Post-Condition:	Returns true 
									if piece on "a" is white. Returns false if otherwise.
EoD								Pre-Condition:	Fields "a" and "b" are existing fields 
									on	chessboard and "a" is occupied.
									Post-Condition:	Returns true if either field "b" is 
									empty or pieces on "a" and "b" have different color. 
									Returns false if otherwise.
no_move						Pre-Condition: Fields "a" and "b" are existing fields 
									on a chessboard, field "a" is occupied and move from 
									"a" to "b" is illegal.
									Post-Condition: Outputs message that move from "a" 
									to "b" is illegal.
free_straight			Pre-Condition: Fields "a" and "b" are existing fields 
									on a chessboard and both fields lie in either the 
									same row or the same column.
									Post-Condition:	Returns true if all fields on the 
									straight between "a" and "b" are unoccupied. Returns 
									false if otherwise.
free_diagonal			Pre-Condition:	Fields "a" and "b" are existing fields 
									on a chessboard and both fields lie on the same diagonal.
									Post-Condition:	Returns true if all fields lying on the 
									diagonal between "a" and "b" are unoccupied. Returns 
									false if otherwise.
move_into_check		Pre-Condition: Fields "a" and "b" are existing fields 
									on a chessboard and "a" is occupied. The move from 
									"a" to "b" is a legal move.
									Post-Condition:	Returns true if the move from "a" to 
									"b" leaves player whose turn it, is in check. Returns 
									false if otherwise.
in_check					Pre-Condition: Chessboard is not empty.
									Post_Condition:	Returns true if player whose turn 
									it is, is in check.
stalemate					Pre-Condition: Chessboard is not empty.
									Post-Condition:	Returns true if player whose turn 
									it is, cannot move.
check_status			Checks if player whose turn it is is either in check, 
									stalemate or checkmate (if both check and stalemate).
resetBoard 				Pre-Condition: Chessboard with fields pointing to 
									NULL exists.
									Post-Condition:	Resets board to standard starting position.
correct_input			Helps submitMove by checking input validity.
*/


#include <map>
#include <string>
#include "Chesspiece.h"


class ChessBoard
{
private:
	bool white_turn;		//bool keeping track of whose turn it is
	std::string white_king,black_king; //strings keeping track of both kings
	typedef Chesspiece* piece_ptr;
	piece_ptr pw,pb,rw,rb,hw,hb,bw,bb,kw,kb,qw,qb; 	//Pointers to each type of chesspiece.
	std::map<std::string, Chesspiece*> board;		//Map fields as key and chesspiece 
																							//pointer as value.
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

