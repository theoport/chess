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
	if (init==dest){
		cout<<"That is not a move."<<endl;
		return;
	}
	else if (valid_move(init,dest)&&(!chessboard->move_into_check(init,dest))){
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
bool Rook::can_move(const string init){
	string pos[SURROUNDING];
	for (int n=0;n<4;n++)
		pos[n]="A1";
	pos[0][0]=init[0];
	pos[0][1]=init[1]+1;
	pos[1][0]=init[0];
	pos[1][1]=init[1]-1;
	pos[2][0]=init[0]+1;
	pos[2][1]=init[1];
	pos[3][0]=init[0]-1;
	pos[3][1]=init[1];
	for (int n=0;n<SURROUNDING;n++){
		if (pos[n][0]<'A'||pos[n][0]>'H'||pos[n][1]<'1'||pos[n][1]>'8')
			pos[n]="NULL";
	}
	for (int n=0;n<SURROUNDING;n++){
		if ((pos[n]!="NULL")&&valid_move(init,pos[n])&&(chessboard->EoD(pos[n],init))&&!chessboard->move_into_check(init,pos[n]))
			return true;
	}	
	return false;
}
bool Rook::valid_move(const string init,const string dest){
	return ((init[0]==dest[0]||init[1]==dest[1])&&chessboard->free_straight(init,dest));
}	
