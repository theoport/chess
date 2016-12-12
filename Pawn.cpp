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
	//checks if destination field is same as starting field
	if (init==dest){
		cout<<init<<" to "<<dest<<" is not a move."<<endl;
		return;
	}
	if (color=="White"){
		if (dest[0]==init[0]){
			if ((dest[1]==init[1]+1)&&chessboard->empty(dest)
					&&!chessboard->move_into_check(init,dest))
				/*make move if Pawn is white, moves one field ahead, doesnt leave white in check, 
					and if destination field is empty*/
				chessboard->move(init,dest);
			else if ((dest[1]==init[1]+2)&&(init[1]=='2')&&(chessboard->empty(dest))){
				string temp="A1";
				temp[0]=dest[0];
				temp[1]=dest[1]-1;
				if(!chessboard->move_into_check(init,dest)&&chessboard->empty(temp))
					/*make move if Pawn is white and on row 2, if it tries to move two fields
						ahead, if destination field and field in between is empty, and if
						move doesn't leave white in check.*/
					chessboard->move(init,dest);
				else
					//move is illegal:
					chessboard->no_move(init,dest);
			}
			else
				//move is illegal:
				chessboard->no_move(init,dest);
		}
		else if(((dest[0]==init[0]+1)||(dest[0]==init[0]-1))
							&&(dest[1]==init[1]+1)){
			if(!chessboard->empty(dest)&&chessboard->different_color(init,dest)
					&&!chessboard->move_into_check(init,dest))
				/*move white Pawn and take piece on destination field, if piece on
					destination field is black, if destination field lies diagonally 
					ahead and if move doesnt leave white in check.*/
				chessboard->take(init,dest);
			else
				//move is illegal
				chessboard->no_move(init,dest);
		}
		else
			//move is illegal
			chessboard->no_move(init,dest);
	}
	else{
		if (dest[0]==init[0]){
			if ((dest[1]==init[1]-1)&&chessboard->empty(dest)
					&&!chessboard->move_into_check(init,dest))
				/*make move if Pawn is black, moves one field ahead, doesnt leave black in check, 
					and if destination field is empty*/
				chessboard->move(init,dest);
			else if ((dest[1]==init[1]-2)&&(init[1]=='7')&&(chessboard->empty(dest))){
				string temp="A1";
				temp[0]=dest[0];
				temp[1]=dest[1]+1;
				if(!chessboard->move_into_check(init,dest)&&chessboard->empty(temp))
					/*make move if Pawn is black and on row 7, if it tries to move two fields
						ahead, if destination field and field in between is empty, and if
						move doesn't leave black in check.*/
					chessboard->move(init,dest);
				else
					//move is illegal
					chessboard->no_move(init,dest);
			}
			else	
				//move is illegal
				chessboard->no_move(init,dest);
		}
		else if(((dest[0]==init[0]+1)||(dest[0]==init[0]-1))&&(dest[1]==init[1]-1)){
			if(!chessboard->empty(dest)&&chessboard->different_color(init,dest)
					&&!chessboard->move_into_check(init,dest))
				/*move Pawn and take piece on destination field, if piece on destination 
					field is white, if destination field lies diagonally ahead and 
					if move doesnt leave black in check.*/
				chessboard->take(init,dest);
			else
				//move is illegal
				chessboard->no_move(init,dest);
		}
		else
			//move is illegal
			chessboard->no_move(init,dest);
	}
}
bool Pawn::can_move(const string init){
	if ((color=="Black"&&init[1]=='1')||(color=="White"&&init[1]=='8'))
		return false;
	string pos[4];
	for (int n=0;n<4;n++)
		pos[n]="A1";
		//creates 4 possible positions where pawn	could move
	if (color=="White"){
		pos[0][0]=init[0];
		pos[0][1]=init[1]+1;
		pos[1][0]=init[0];
		pos[1][1]=init[1]+2;
		pos[2][0]=init[0]+1;
		pos[2][1]=init[1]+1;
		pos[3][0]=init[0]-1;
		pos[3][1]=init[1]+1;
	}
	if (color=="Black"){
		pos[0][0]=init[0];
		pos[0][1]=init[1]-1;
		pos[1][0]=init[0];
		pos[1][1]=init[1]-2;
		pos[2][0]=init[0]+1;
		pos[2][1]=init[1]-1;
		pos[3][0]=init[0]-1;
		pos[3][1]=init[1]-1;
	}
	//sets position to "NULL", if position is out of the bounds of the chessboard:
	for (int n=0;n<4;n++){
		if (pos[n][0]<'A'||pos[n][0]>'H'||pos[n][1]<'1'||pos[n][1]>'8')
			pos[n]="NULL";
	}
	//Returns true if pawn can move to different positions, otherwise returns false
	if ((pos[0]!="NULL")&&chessboard->empty(pos[0])
			&&!chessboard->move_into_check(init,pos[0]))
		return true;
	else if (pos[1]!="NULL"&&chessboard->empty(pos[0])
						&&chessboard->empty(pos[1])
						&&!chessboard->move_into_check(init,pos[1]))
		return true;
	else if ((pos[2]!="NULL")&&!chessboard->empty(pos[2])
						&&chessboard->different_color(init,pos[2])
						&&!chessboard->move_into_check(init,pos[2]))
		return true;
	else if ((pos[3]!="NULL")&&!chessboard->empty(pos[3])
						&&chessboard->different_color(init,pos[3])
						&&!chessboard->move_into_check(init,pos[3]))
		return true;	
	else
		return false;
}
bool Pawn::valid_move(const string init,const string dest){
	//returns true if "init" to "dest" is a valid ATTACKING move, otherwise returns false.
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
