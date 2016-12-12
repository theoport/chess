#include <iostream>
#include <string>
#include "ChessBoard.h"
#include "Chesspiece.h"
#include "Rook.h"

using namespace std;

Rook::Rook(string a, ChessBoard* chessboard):Chesspiece(a,"Rook",chessboard)
{
}
void Rook::submitMove(const string init,const string dest){
	//Checks if destination field is the same as starting field:
	if (init==dest){
		cout<<"That is not a move."<<endl;
		return;
	}
	//takes appropriate action if move from "init" to "dest" is legal:
	else if (valid_move(init,dest)&&(!chessboard->move_into_check(init,dest))){
		if (chessboard->empty(dest))
			chessboard->move(init,dest);
		else if (chessboard->different_color(init,dest))
			chessboard->take(init,dest);
		//move not legal:
		else
			chessboard->no_move(init,dest);
	}
	//move not legal:
	else
		chessboard->no_move(init,dest);
}
bool Rook::can_move(const string init){
	//loops through whole board to test if piece can move anywhere:
	for (string temp="A1";temp[0]<'I';temp[0]++){
		for (temp[1]=1;temp[1]<'9';temp[1]++){
			if ((temp!=init)&&valid_move(init,temp)&&chessboard->EoD(temp,init)
					&&!chessboard->move_into_check(init,temp))
				return true;
		}
	}
	return false;
}
bool Rook::valid_move(const string init,const string dest){
	/*returns true if "init" to "dest" is a valid move without testing for check, or 
		occupation of destination field, returns false otherwise.*/
	return ((init[0]==dest[0]||init[1]==dest[1])&&chessboard->free_straight(init,dest));
}	
