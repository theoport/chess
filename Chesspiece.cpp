#include <iostream>
#include <string>
#include "ChessBoard.h"
#include "Chesspiece.h"

using namespace std;

Chesspiece::Chesspiece(std::string a, std::string b, ChessBoard* c):color(a),type(b),chessboard(c)
{
}
string Chesspiece::get_type(){
	return type;
}
string Chesspiece::get_color(){
	return color;
}
