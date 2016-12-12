#include <iostream>
#include <string>
#include <map>
#include "ChessBoard.h"
#include "Chesspiece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"


using namespace std;

ChessBoard::ChessBoard(){
	//Creates chesspieces dynamically and them to the appropriate pointers
	pw=new Pawn("White",this);
	pb=new Pawn("Black",this);
	rw=new Rook("White",this);
	rb=new Rook("Black",this);
	hw=new Knight("White",this);
	hb=new Knight("Black",this);
	bw=new Bishop("White",this);
	bb=new Bishop("Black",this);
	qw=new Queen("White",this);
	qb=new Queen("Black",this);
	kw=new King("White",this);
	kb=new King("Black",this);
	resetBoard();	
}
ChessBoard::~ChessBoard(){
	//deletes chesspieces
	delete pw;
	delete pb;
	delete rw;
	delete rb;
	delete hw;
	delete hb;
	delete bw;
	delete bb;
	delete qw;
	delete qb;
	delete kw;
	delete kb;
	//sets all pointers to NULL
	for (string a="A1";a[0]<'I';a[0]++){
		for (a[1]='1';a[1]<'9';a[1]++)
			board[a]=NULL;
	}
}
void ChessBoard::submitMove(const string a,const string b){
	//calls correct_input to check input
	if (correct_input(a,b))
		//calls submitMove function of chesspiece on field "init".
		board[a]->submitMove(a,b);
}
bool ChessBoard::empty(const string a){
	if (board[a]==NULL){
		return true;
	}
	else{
		return false;
	}
}
void ChessBoard::move(const string a,const string b){
	//outputs appropriate message
	cout<<board[a]->get_color()<<"'s "<<board[a]->get_type()<<" moves from "<<a;
	cout<<" to "<<b<<endl;
	//makes move
	board[b]=board[a];
	board[a]=NULL;
	//changes king position if piece is king
	if(board[b]->get_type()=="King"){
		if(white_turn)
			white_king=b;
		else
			black_king=b;
	}
	//changes whose turn it is
	white_turn=!white_turn;
	//checks if next player is in check, stalemate or checkmate
	check_status();
}
void ChessBoard::take(const string a, const string b){
	//ouputs appropriate message
	cout<<board[a]->get_color()<<"'s "<<board[a]->get_type()<<" moves from "<<a;
	cout<<" to "<<b<<" ";
	cout<<"taking "<<board[b]->get_color()<<"'s "<<board[b]->get_type()<<endl;
	//makes move
	board[b]=board[a];
	board[a]=NULL;	
	//changes king position if appropriate
	if(board[b]->get_type()=="King"){
		if(white_turn)
			white_king=b;
		else
			black_king=b;
	}
	//changes whose turn it is
	white_turn=!white_turn;
	//checks if next player is in check, stalemate, or checkmate
	check_status();
}
bool ChessBoard::EoD(const string a, const string b){
	if(empty(a))
		return true;
	else if(different_color(a,b))
		return true;
	else
		return false;
}
bool ChessBoard::different_color(const string a,const string b){
	if (board[a]->get_color()==board[b]->get_color())
		return false;
	else
		return true;
}
bool ChessBoard::is_white(const string a){
	if (board[a]->get_color()=="White")
		return true;
	else
		return false;
}

void ChessBoard::no_move(const string a, const string b){
	cout<<board[a]->get_color()<<"'s "<<board[a]->get_type()<<" cannot move from "<<a;
	cout<<" to "<<b<<endl;
}
bool ChessBoard::free_straight(const string a,const string b){
	string pos("A1");
	//loops through fields between "a" and "b" and returns false if one is occupied
	if (a[0]==b[0]){
		if (a[1]<b[1]){
			pos[0]=a[0];
			pos[1]=a[1]+1;
			for (string temp=pos;temp[1]<b[1];temp[1]++){
				if (!empty(temp))
					return false;
			}
		}
		else{
			pos[0]=a[0];
			pos[1]=a[1]-1;
			for (string temp=pos;temp[1]>b[1];temp[1]--){
				if(!empty(temp))
					return false;
			}
		}
	}
	else{
		if (a[0]<b[0]){
			pos[1]=a[1];
			pos[0]=a[0]+1;
			for (string temp=pos;temp[0]<b[0];temp[0]++){
				if (!empty(temp))
					return false;
			}
		}
		else{
			pos[1]=a[1];
			pos[0]=a[0]-1;
			for (string temp=pos;temp[0]>b[0];temp[0]--){
				if(!empty(temp))
					return false;
			}
		}
	}
	return true;
}
bool ChessBoard::free_diagonal(const string a,const string b){
	string pos="A1";
	//loops through fields between "a" and "b" and returns false if one is occupied
	if (a[0]>b[0]){
		if(a[1]>b[1]){
			for (int n=1;n<(a[0]-b[0]);n++){
				pos[0]=a[0]-n;
				pos[1]=a[1]-n;
				if (!empty(pos))
					return false;
			}
		}
		else{ 		
			for (int n=1;n<(a[0]-b[0]);n++){
				pos[0]=a[0]-n;
				pos[1]=a[1]+n;
				if (!empty(pos))
					return false;
			}
		}
	}
	else{ 
		if(a[1]>b[1]){
			for (int n=1;n<(b[0]-a[0]);n++){
				pos[0]=a[0]+n;
				pos[1]=a[1]-n;
				if (!empty(pos))
					return false;
			}
		}
		else{ 
			for (int n=1;n<(b[0]-a[0]);n++){
				pos[0]=a[0]+n;
				pos[1]=a[1]+n;
				if (!empty(pos))
					return false;
			}
		}
	}
	return true;
}
bool ChessBoard::move_into_check(const string a, const string b){
	//if piece is king, changes king position
	if (board[a]->get_type()=="King"){
		if (white_turn)
			white_king=b;
		else
			black_king=b;
	}	
	//makes move
	Chesspiece* temp;
	temp=board[b];
	board[b]=board[a];
	board[a]=NULL;
	//checks if player is in check after move
	if (in_check()){
		//undo move
		board[a]=board[b];
		board[b]=temp;
		//undo change in king position if piece is king
		if (board[a]->get_type()=="King"){
			if (white_turn)
				white_king=a;
			else
				black_king=a;
		}
		//return true if in check			
		return true;
	}
	//undo move
	board[a]=board[b];
	board[b]=temp;
	//undo change in king position if piece is king
	if (board[a]->get_type()=="King"){
		if (white_turn)
			white_king=a;
		else
			black_king=a;
	}			
	return false;
}
bool ChessBoard::in_check(){
	/*assigns either white's or black's king position to "x", depending 
	  on whose move it is*/
	string x= (white_turn)?white_king:black_king;
	/*loops through all fields and returns true if piece of opposite color
	  from the king on position "x" can attack king.*/
	for (string a="A1";a[0]<'I';a[0]++){
		for (a[1]='1';a[1]<'9';a[1]++){
			if (board[a]&&different_color(a,x)&&board[a]->valid_move(a,x))
				return true;
		}
	}
	return false;
}	
bool ChessBoard::stalemate(){
	/*loops through pieces of player whose turn it is and returns false 
		when one is found that can move.*/
	if (white_turn){
		for (string a="A1";a[0]<'I';a[0]++){
			for (a[1]='1';a[1]<'9';a[1]++){
				if (board[a]&&is_white(a)&&board[a]->can_move(a))
					return false;
			}
		}
		return true;
	}	
	else {
		for (string a="A1";a[0]<'I';a[0]++){
			for (a[1]='1';a[1]<'9';a[1]++){
				if (board[a]&&!is_white(a)&&board[a]->can_move(a))
					return false;
			}
		}
		return true;
	}
}
void ChessBoard::check_status(){
	//checks if player is in check, stalemate or checkmate
	string x=(white_turn)?"White":"Black";
	if (in_check()){
		if (stalemate())
			cout<<x<<" is in checkmate."<<endl;
		else
			cout<<x<<" is in check."<<endl;
	}
	else if (stalemate()){
		cout<<x<<" cannot move. It's a draw!"<<endl;
	}
}	
void ChessBoard::resetBoard(){
	cout<<"A new chess game is started!"<<endl;
	//assigns all pointers of empty fields to NULL
	for (string a="A3"; a[0]<'I';a[0]++){
		for (a[1]='3'; a[1]<'7';a[1]++)
			board[a]=NULL;
	}
	//assigns all pointers on row 2 to the white pawn object
	for (string a="A2";a[0]<'I';a[0]++)
		board[a]=pw;
	//assigns all pointers on row 7 to the black pawn object
	for (string a="A7";a[0]<'I';a[0]++)
		board[a]=pb;
	//assigns remaining fields to appropriate chesspiece objects
	board["A1"]=rw;
	board["B1"]=hw;
	board["C1"]=bw;
	board["D1"]=qw;
	board["E1"]=kw;
	board["F1"]=bw;
	board["G1"]=hw;
	board["H1"]=rw;
	board["A8"]=rb;
	board["B8"]=hb;
	board["C8"]=bb;
	board["D8"]=qb;
	board["E8"]=kb;
	board["F8"]=bb;
	board["G8"]=hb;
	board["H8"]=rb;
	//White always starts the game
	white_turn=true;
	//starting positions for both kings
	white_king="E1";
	black_king="E8";
}
bool ChessBoard::correct_input(const string init, const string dest){
	//checks if input strings have a different length than 2
	if (init.size()!=2||dest.size()!=2){
		if(init.size()!=2&&dest.size()!=2){ 
			cout<<"Field "<<init<<" and field "<<dest<<" have incorrect format.";
			cout<<" (Column has to be a letter between A and H ";
			cout<<"and row has to be a number between 1 and 8)."<<endl;
		}
		else if(init.size()!=2){
			cout<<"Field "<<init<<" has incorrect format."; 
			cout<<" (Column has to be a letter between A and H ";
			cout<<"and row has to be a number between 1 and 8)."<<endl;
		}
		else{
			cout<<"Field "<<dest<<" has incorrect format. "; 
			cout<<"(Column has to be a letter between A and H ";
			cout<<"and row has to be a number between 1 and 8)."<<endl;
		}	
		return false;
	}
	//checks if columns in input contatin correct letter but in lower case
	else if((init[0]<='h'&&init[0]>='a')||(dest[0]<='h'&&dest[0]>='a')){
		if ((init[0]<='h'&&init[0]>='a')&&(dest[0]<='h'&&dest[0]>='a')){
			cout<<"Column "<<init[0]<<" in starting field and column "<<dest[0];
			cout<<" in destination field have to be a capital letter."<<endl;
		}
		else if(init[0]<='h'&&init[0]>='a'){
			cout<<"Column "<<init[0]<<" in starting field has to";
			cout<<" be in capital letters."<<endl;
		}
		else{ 
			cout<<"Column "<<dest[0]<<" in destination field has to ";
			cout<<"be in capital letters."<<endl;
		}
		return false;
	}
	//checks if columns in input contain incorrect letter
	else if((init[0]>'H'||init[0]<'A')||(dest[0]>'H'||dest[0]<'A')){
		if ((init[0]>'H'||init[0]<'A')&&(dest[0]>'H'||dest[0]<'A')){
			cout<<"Column "<<init[0]<<" in starting field and column "<<dest[0];
			cout<<" in destination field do not exist."<<endl;
		}
		else if(init[0]>'H'||init[0]<'A')
			cout<<"Column "<<init[0]<<" in starting field does not exist."<<endl;
		else 
			cout<<"Column "<<dest[0]<<" in destination field does not exist."<<endl;
		return false;
	}
	//checks if rows in input contain incorrect number
	else if((init[1]>'8'||init[1]<'1')||(dest[1]>'8'||dest[1]<'1')){
		if ((init[1]>'8'||init[1]<'1')&&(dest[1]>'8'||dest[1]<'1')){
			cout<<"Row "<<init[1]<<" in starting field and row "<<dest[1];
			cout<<" in destination field do not exist."<<endl;
		}
		else if(init[1]>'8'||init[1]<'1')
			cout<<"Row "<<init[1]<<" in starting field does not exist."<<endl;
		else 
			cout<<"Row "<<dest[1]<<" in destination field does not exist."<<endl;
		return false;
	}
	//checks if starting field is empty
	else if (empty(init)){
		cout<<"There is no piece at position "<<init<<endl;
		return false;
	}
	//checks if it is the turn of player on starting field
	else if (((board[init]->get_color()=="White")&&(!white_turn))||((board[init]->get_color()=="Black")&&white_turn)){
		cout<<"It is not "<<board[init]->get_color()<<"'s turn."<<endl;
		return false;
	}
	return true;
}
