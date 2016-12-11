#include <iostream>
#include <string>
#include <cstdlib>
#include "ChessBoard.h"
#include "Chesspiece.h"
#include "Pawn.h"

using namespace std;


Pawn::Pawn(string color, ChessBoard* chessboard):Chesspiece(color, "Pawn",chessboard)
{
	
}
void Pawn::submitMove(const string init,const string dest){
	if (init==dest){
		cout<<init<<" to "<<dest<<" is not a move."<<endl;
		return;
	}
	if (color=="White"){
		if (dest[0]==init[0]){
			if ((dest[1]==init[1]+1)&&chessboard->empty(dest)&&!chessboard->move_into_check(init,dest))
				chessboard->move(init,dest);
			else if ((dest[1]==init[1]+2)&&(init[1]=='2')&&(chessboard->empty(dest))){
				string temp="A1";
				temp[0]=dest[0];
				temp[1]=dest[1]-1;
				if(!chessboard->move_into_check(init,dest)&&chessboard->empty(temp))
					chessboard->move(init,dest);
				else
					chessboard->no_move(init,dest);
			}
			else
				chessboard->no_move(init,dest);
		}
		else if(((dest[0]==init[0]+1)||(dest[0]==init[0]-1))&&(dest[1]==init[1]+1)){
			if(!chessboard->empty(dest)&&chessboard->different_color(init,dest)&&!chessboard->move_into_check(init,dest))
				chessboard->take(init,dest);
			else
				chessboard->no_move(init,dest);
		}
		else
			chessboard->no_move(init,dest);
	}
	else{
		if (dest[0]==init[0]){
			if ((dest[1]==init[1]-1)&&chessboard->empty(dest)&&!chessboard->move_into_check(init,dest))
				chessboard->move(init,dest);
			else if ((dest[1]==init[1]-2)&&(init[1]=='7')&&(chessboard->empty(dest))){
				string temp="A1";
				temp[0]=dest[0];
				temp[1]=dest[1]+1;
				if(!chessboard->move_into_check(init,dest)&&chessboard->empty(temp))
					chessboard->move(init,dest);
				else
					chessboard->no_move(init,dest);
			}
			else
				chessboard->no_move(init,dest);
		}
		else if(((dest[0]==init[0]+1)||(dest[0]==init[0]-1))&&(dest[1]==init[1]-1)){
			if(!chessboard->empty(dest)&&chessboard->different_color(init,dest)&&!chessboard->move_into_check(init,dest))
				chessboard->take(init,dest);
			else
				chessboard->no_move(init,dest);
		}
		else
			chessboard->no_move(init,dest);
	}
}
bool Pawn::can_move(const string init){
	if ((color=="Black"&&init[1]=='1')||(color=="White"&&init[1]=='8'))
		return false;
	string pos1("A1"),pos2("A1"),pos3("A1");
	if (color=="White"){
		pos1[0]=init[0];
		pos1[1]=init[1]+1;
		if (init[0]=='A'){
			pos2[0]=init[0]+1;
			pos2[1]=init[1]+1;
			pos3="NULL";
		}
		else if (init[0]=='H'){
			pos2[0]=init[0]-1;
			pos2[1]=init[0]+1;
			pos3="NULL";
		}
		else{
			pos2[0]=init[0]-1;
			pos2[1]=init[0]+1;
			pos3[0]=init[0]+1;
			pos3[1]=init[1]+1;
		}	
	}
	if (color=="Black"){
		pos1[0]=init[0];
		pos1[1]=init[1]-1;
		if (init[0]=='A'){
			pos2[0]=init[0]+1;
			pos2[1]=init[1]-1;
			pos3="NULL";
		}
		else if (init[0]=='H'){
			pos2[0]=init[0]-1;
			pos2[1]=init[0]-1;
			pos3="NULL";
		}
		else{
			pos2[0]=init[0]-1;
			pos2[1]=init[0]-1;
			pos3[0]=init[0]+1;
			pos3[1]=init[1]-1;
		}	
	}
	if (chessboard->empty(pos1)&&!chessboard->move_into_check(init,pos1))
		return true;
	else if (!chessboard->empty(pos2)&&chessboard->different_color(init,pos2)&&!chessboard->move_into_check(init,pos2))
		return true;
	else if ((pos3!="NULL")&&!chessboard->empty(pos3)&&chessboard->different_color(init,pos3)&&!chessboard->move_into_check(init,pos3))
		return true;	
	else
		return false;
}
bool Pawn::valid_move(const string init,const string dest){
	int diff_C, diff_R;
	diff_C=abs(dest[0]-init[0]);
	diff_R=dest[1]-init[1];
	if (color=="White"&&diff_R==1&&diff_C==1)
		return true;
	else if (color=="Black"&&diff_R==(-1)&&diff_C==1)
		return true;
	else
		return false;
}	
