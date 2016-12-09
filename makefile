OBJ= Rook.o Knight.o Bishop.o King.o Queen.o Pawn.o Chesspiece.o ChessBoard.o ChessMain.o
EXE=chess
CXX=g++
CPPFLAGS= -Wall -g
HFILES=Rook.h Knight.h Bishop.h King.h Queen.h Pawn.h Chesspiece.h ChessBoard.h 
$(EXE): $(OBJ)
	$(CXX) $(CPPFLAGS) $(OBJ) -o $@ 

%.o: %.cpp 
	$(CXX) $(CPPFLAGS) -c $< 

Chessboard.o: Chesspiece.h ChessBoard.h

.PHONY:clean

clean:
	rm -f $(OBJ) $(EXE) 
