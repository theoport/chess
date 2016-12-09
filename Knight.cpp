#include <iostream>
#include <string>
#include <cstdlib>
#include "ChessBoard.h"
#include "Chesspiece.h"
#include "Knight.h"

using namespace std;

Knight::Knight(string color, ChessBoard* chessboard):Chesspiece(color, "Knight",chessboard)
{
	
}
void Knight::submitMove(const string init,const  string dest){
	if (init==dest){
		cout<<"That is not a move."<<endl;
		return;
	}
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

bool Knight::can_move(const string init){
	string pos[SURROUNDING];
	for (int n=0;n<8;n++)
		pos[n]="A1";
	pos[0][0]=init[0]+2;
	pos[0][1]=init[1]+1;
	pos[1][0]=init[0]+1;
	pos[1][1]=init[1]+2;
	pos[2][0]=init[0]-2;
	pos[2][1]=init[1]-1;
	pos[3][0]=init[0]-1;
	pos[3][1]=init[1]-2;
	pos[4][0]=init[0]+2;
	pos[4][1]=init[1]-1;
	pos[5][0]=init[0]-1;
	pos[5][1]=init[1]+2;
	pos[6][0]=init[0]-2;
	pos[6][1]=init[1]+1;
	pos[7][0]=init[0]+1;
	pos[7][1]=init[1]-2;
	for (int n=0;n<SURROUNDING;n++){
		if (pos[n][0]<'A'||pos[n][0]>'H'||pos[n][1]<'1'||pos[n][1]>'8')
			pos[n]="NULL";
	}
	for (int n=0;n<SURROUNDING;n++){
		if ((pos[n]!="NULL")&&valid_move(init,pos[n])&&chessboard->EoD(pos[n],init)&&!chessboard->move_into_check(init,pos[n]))
			return true;
	}
	return false;
}
bool Knight::valid_move(const string init, const string dest){
	int diff_C, diff_R;
	diff_C=abs(init[0]-dest[0]);
	diff_R=abs(init[1]-dest[1]);
	return (((diff_C==2)&&(diff_R==1))||((diff_C==1)&&(diff_R==2)));	
}
