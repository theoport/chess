#include <iostream>
#include <string>
#include <cstdlib>
#include "ChessBoard.h"
#include "Chesspiece.h"
#include "Queen.h"

using namespace std;

Queen::Queen(string color, ChessBoard* chessboard):Chesspiece(color, "Queen",chessboard)
{
	
}
void Queen::submitMove(const string init, const string dest){
	//Checks if destination field is the same as starting field:
	if (init==dest){
		cout<<"That is not a move."<<endl;
		return;
	}
	//takes appropriate action if move from "init" to "dest" is legal:
	else if (valid_move(init,dest)&&!chessboard->move_into_check(init,dest)){
		if (chessboard->empty(dest))
			chessboard->move(init,dest);
		else if (chessboard->different_color(init,dest))
			chessboard->take(init,dest);
		else
			chessboard->no_move(init,dest);
	}	
	else
		chessboard->no_move(init,dest);
}
bool Queen::can_move(const string init){
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

bool Queen::valid_move(const string init,const string dest){
	/*returns true if "init" to "dest" is a valid move without testing for check, or 
		occupation of destination field, returns false if otherwise.*/
	int diff_C, diff_R;
	diff_C=abs(init[0]-dest[0]);
	diff_R=abs(init[1]-dest[1]);
	if ((diff_C==diff_R)&&chessboard->free_diagonal(init,dest))
		return true;
	else if ((init[0]==dest[0]||init[1]==dest[1])
					&&chessboard->free_straight(init,dest))
		return true;
	else
		return false;
}

