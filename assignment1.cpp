#include <iostream>
#include <fstream>
using namespace std;

//Struct that holds all points size center row and column and type of the sign
struct point{
	int size;
	int centerrow;
	int centercol;
	char sign;
};
//Adds Plus sign to the specified position of the grid
void addPlus(int row, int col, point* grid, int rownum, int colnum, int size, char a, int &conflict_error, int &border_error){
	if(colnum < col+size || col-size<=0 || row+size > rownum || row-size <= 0){
		border_error = 1;
		return;
	} else {
		//First I assign the center of the sign
		if(((grid+(colnum*(row-1)+(col-1)))->sign != '.' && a == '.' )|| ((grid+(colnum*(row-1)+(col-1)))->sign == '.' && a != '.')){
			(grid+(colnum*(row-1)+(col-1)))->sign = a;
		} else {
			conflict_error = 1;
			return;
			
		}
		
		for(int i=1; i<=size; i++){
			//then assigning the other parts
			if(((grid+(colnum*(row-1-i)+(col-1)))->sign != '.' && a == '.') || ((grid+(colnum*(row-1-i)+(col-1)))->sign == '.' && a != '.')){
				(grid+(colnum*(row-1-i)+(col-1)))->sign = a;
			} else {
				if(a=='+') (grid+(colnum*(row-1)+(col-1)))->sign = '.';
				conflict_error = 1;
				return;
				 
			}
			
			if(((grid+(colnum*(row-1+i)+(col-1)))->sign != '.' && a == '.') || ((grid+(colnum*(row-1+i)+(col-1)))->sign == '.' && a != '.')){
				(grid+(colnum*(row-1+i)+(col-1)))->sign = a;
			} else {
				if(a=='+') {(grid+(colnum*(row-1-i)+(col-1)))->sign = '.'; (grid+(colnum*(row-1)+(col-1)))->sign = '.';}
				conflict_error = 1;
				return;
				
			}	
				
			
			if(((grid+(colnum*(row-1)+(col-1-i)))->sign != '.' && a == '.') || ((grid+(colnum*(row-1)+(col-1-i)))->sign == '.' && a != '.')){
				(grid+(colnum*(row-1)+(col-1-i)))->sign = a;
			} else {
				if(a=='+') {(grid+(colnum*(row-1-i)+(col-1)))->sign = '.'; (grid+(colnum*(row-1)+(col-1)))->sign = '.'; (grid+(colnum*(row-1+i)+(col-1)))->sign = '.';}
				conflict_error = 1;
				return;
				
			}	
			
			if(((grid+(colnum*(row-1)+(col-1+i)))->sign != '.' && a == '.') || ((grid+(colnum*(row-1)+(col-1+i)))->sign == '.' && a != '.')){
				(grid+(colnum*(row-1)+(col-1+i)))->sign = a;
			} else {
				if(a=='+') {(grid+(colnum*(row-1-i)+(col-1)))->sign = '.'; (grid+(colnum*(row-1)+(col-1)))->sign = '.'; (grid+(colnum*(row-1+i)+(col-1)))->sign = '.'; (grid+(colnum*(row-1)+(col-1+i)))->sign = '.';}
				conflict_error = 1;
				return;
			}
			(grid+(colnum*(row-1)+(col-1)))->size = size;
			
			(grid+(colnum*(row-1-i)+(col-1)))->centerrow = row; 
			(grid+(colnum*(row-1+i)+(col-1)))->centerrow = row;
			(grid+(colnum*(row-1)+(col-1)))->centerrow = row;
			(grid+(colnum*(row-1)+(col-1-i)))->centerrow = row;
			(grid+(colnum*(row-1)+(col-1+i)))->centerrow = row;
			
			(grid+(colnum*(row-1-i)+(col-1)))->centercol = col; 
			(grid+(colnum*(row-1+i)+(col-1)))->centercol = col;
			(grid+(colnum*(row-1)+(col-1)))->centercol = col;
			(grid+(colnum*(row-1)+(col-1-i)))->centercol = col;
			(grid+(colnum*(row-1)+(col-1+i)))->centercol = col;
			
					
		}
		border_error = 0;
		conflict_error = 0;
	}
}
//adds Minus sign to the grid
void addMinus(int row, int col, point* grid, int rownum, int colnum, int size, char a, int &conflict_error, int &border_error){
	conflict_error = 0; border_error = 0;
	if(col-size<=0 || row-size <= 0 || row < 0 || row > rownum || col+size > colnum){
		border_error = 1;
		return;
	} else {
		//First I assign the center of the sign
		if(((grid+(colnum*(row-1)+(col-1)))->sign != '.' && a == '.' )|| ((grid+(colnum*(row-1)+(col-1)))->sign == '.' && a != '.')){
			(grid+(colnum*(row-1)+(col-1)))->sign = a;
		} else {
			conflict_error = 1;
			return;
		}
		for(int i=1; i<=size; i++){
			//then assigning the other parts
			if(((grid+(colnum*(row-1)+(col-1-i)))->sign != '.' && a == '.' )|| ((grid+(colnum*(row-1)+(col-1-i)))->sign == '.' && a != '.')){
				(grid+(colnum*(row-1)+(col-1-i)))->sign = a;
			} else {
				if(a=='-') (grid+(colnum*(row-1)+(col-1)))->sign = '.';
				conflict_error = 1;
				return;
			}
			if(((grid+(colnum*(row-1)+(col-1+i)))->sign != '.' && a == '.' ) || ((grid+(colnum*(row-1)+(col-1+i)))->sign == '.' && a != '.')){
				(grid+(colnum*(row-1)+(col-1+i)))->sign = a;
			} else {
				if(a=='-') {(grid+(colnum*(row-1)+(col-1)))->sign = '.'; (grid+(colnum*(row-1)+(col-1-i)))->sign = '.';}
				conflict_error = 1;
				return;
				
			}
				
			(grid+(colnum*(row-1)+(col-1)))->size = size;
			
			(grid+(colnum*(row-1)+(col-1)))->centerrow = row;
			(grid+(colnum*(row-1)+(col-1-i)))->centerrow = row;
			(grid+(colnum*(row-1)+(col-1+i)))->centerrow = row;
			
			(grid+(colnum*(row-1)+(col-1)))->centercol = col;
			(grid+(colnum*(row-1)+(col-1-i)))->centercol = col;
			(grid+(colnum*(row-1)+(col-1+i)))->centercol = col;
			
		}
	}
}
//adds Cross sign to the grid
void addCross(int row, int col, point* grid, int rownum, int colnum, int size, char a, int &conflict_error, int &border_error){
	if(colnum < col+size || col-size<=0 || row+size > rownum || row-size <= 0){
		border_error = 1;
		return;
	} else {
		//First I assign the center of the sign
		if(((grid+(colnum*(row-1)+(col-1)))->sign != '.' && a == '.' )|| ((grid+(colnum*(row-1)+(col-1)))->sign == '.' && a != '.')){
			(grid+(colnum*(row-1)+(col-1)))->sign = a;
		} else {
			conflict_error = 1;
			return;
		}
		for(int i=1; i<=size; i++){
			//then assigning the other parts
			if(((grid+(colnum*(row-1-i)+(col-1-i)))->sign != '.' && a == '.' ) || ((grid+(colnum*(row-1-i)+(col-1-i)))->sign == '.' && a != '.')){
				(grid+(colnum*(row-1-i)+(col-1-i)))->sign = a;
			} else {
				conflict_error = 1;
				if(a=='x') (grid+(colnum*(row-1)+(col-1)))->sign = '.';
				return;
			}
			
			if(((grid+(colnum*(row-1+i)+(col-1+i)))->sign != '.' && a == '.' )|| ((grid+(colnum*(row-1+i)+(col-1+i)))->sign == '.' && a != '.')){
				(grid+(colnum*(row-1+i)+(col-1+i)))->sign = a;
			} else {
				if(a=='x'){(grid+(colnum*(row-1)+(col-1)))->sign = '.'; (grid+(colnum*(row-1-i)+(col-1-i)))->sign = '.';}
				conflict_error = 1;
				return;
			}
			
			if(((grid+(colnum*(row-1+i)+(col-1-i)))->sign != '.' && a == '.' )|| ((grid+(colnum*(row-1+i)+(col-1-i)))->sign == '.' && a != '.')){
				(grid+(colnum*(row-1+i)+(col-1-i)))->sign = a;
			} else {
				if(a=='x'){(grid+(colnum*(row-1)+(col-1)))->sign = '.'; (grid+(colnum*(row-1-i)+(col-1-i)))->sign = '.'; (grid+(colnum*(row-1+i)+(col-1+i)))->sign = '.';}
				conflict_error = 1;
				return;
			}
			
			if(((grid+(colnum*(row-1-i)+(col-1+i)))->sign != '.' && a == '.' )|| ((grid+(colnum*(row-1-i)+(col-1+i)))->sign == '.' && a != '.')){
				(grid+(colnum*(row-1-i)+(col-1+i)))->sign = a;
			} else {
				if(a=='x'){(grid+(colnum*(row-1)+(col-1)))->sign = '.'; (grid+(colnum*(row-1-i)+(col-1-i)))->sign = '.'; (grid+(colnum*(row-1+i)+(col-1+i)))->sign = '.';(grid+(colnum*(row-1+i)+(col-1-i)))->sign = '.';}
				conflict_error = 1;
				return;
			}
			
			(grid+(colnum*(row-1)+(col-1)))->size = size;
			
			(grid+(colnum*(row-1-i)+(col-1-i)))->centerrow = row; 
			(grid+(colnum*(row-1+i)+(col-1+i)))->centerrow = row;
			(grid+(colnum*(row-1)+(col-1)))->centerrow = row;
			(grid+(colnum*(row-1+i)+(col-1-i)))->centerrow = row;
			(grid+(colnum*(row-1-i)+(col-1+i)))->centerrow = row;
			
			(grid+(colnum*(row-1-i)+(col-1-i)))->centercol = col; 
			(grid+(colnum*(row-1+i)+(col-1+i)))->centercol = col;
			(grid+(colnum*(row-1)+(col-1)))->centercol = col;
			(grid+(colnum*(row-1+i)+(col-1-i)))->centercol = col;
			(grid+(colnum*(row-1-i)+(col-1+i)))->centercol = col;
			
		}
		border_error = 0;
		conflict_error = 0;
	}
}
//adds slash symbol to the grid
void addSlash(int row, int col, point* grid, int rownum, int colnum, int size, char a, int &conflict_error, int &border_error){
	
	if(colnum < col+size || col-size<=0 || row+size > rownum || row-size <= 0){
		border_error = 1;
		return;
	} else {
		//First I assign the center of the sign
		if(((grid+(colnum*(row-1)+(col-1)))->sign != '.' && a == '.' )|| ((grid+(colnum*(row-1)+(col-1)))->sign == '.' && a != '.')){
			(grid+(colnum*(row-1)+(col-1)))->sign = a;
		} else {
			conflict_error = 1;
			return;
		}
		for(int i=1; i<=size; i++){
			//then assigning the other parts
			if(((grid+(colnum*(row-1+i)+(col-1-i)))->sign != '.' && a == '.' )|| ((grid+(colnum*(row-1+i)+(col-1-i)))->sign == '.' && a != '.')){
				(grid+(colnum*(row-1+i)+(col-1-i)))->sign = a;
			} else {
				if(a=='/') (grid+(colnum*(row-1)+(col-1)))->sign = '.';
				conflict_error = 1;
				return;
			}
			
			if(((grid+(colnum*(row-1-i)+(col-1+i)))->sign != '.' && a == '.' )|| ((grid+(colnum*(row-1-i)+(col-1+i)))->sign == '.' && a != '.')){
				(grid+(colnum*(row-1-i)+(col-1+i)))->sign = a;
			} else {
				if(a=='/') {(grid+(colnum*(row-1)+(col-1)))->sign = '.'; (grid+(colnum*(row-1+i)+(col-1-i)))->sign = '.';}
				conflict_error = 1;
				return;
				
			}
			
			(grid+(colnum*(row-1)+(col-1)))->size = size;
			
			(grid+(colnum*(row-1)+(col-1)))->centerrow = row;
			(grid+(colnum*(row-1+i)+(col-1-i)))->centerrow = row;
			(grid+(colnum*(row-1-i)+(col-1+i)))->centerrow = row;
			
			(grid+(colnum*(row-1)+(col-1)))->centercol = col;
			(grid+(colnum*(row-1+i)+(col-1-i)))->centercol = col;
			(grid+(colnum*(row-1-i)+(col-1+i)))->centercol = col;
			
		}
		border_error = 0;
		conflict_error = 0;
	}
}
//Moves the sign right
void moveRight(int recrow, int reccol, point* grid, int colnum, int rownum, int move, int &conflict_error, int &border_error){
	//Taking all values from the grid
	int center_row = (grid+(colnum*(recrow-1)+(reccol-1)))->centerrow;
	int center_col = (grid+(colnum*(recrow-1)+(reccol-1)))->centercol;
	int size = (grid+(colnum*(center_row-1)+(center_col-1)))->size;
	char sign = (grid+(colnum*(center_row-1)+(center_col-1)))->sign;
	//move the center
	int new_center_col = center_col + move;
	switch(sign){
		case '+':
			//Deleting the current position of the sign
			addPlus(center_row, center_col, grid, rownum, colnum, size, '.', conflict_error, border_error);.
			//Placing to the new position of the sign
			addPlus(center_row, new_center_col, grid, rownum, colnum, size, '+', conflict_error, border_error);
			if(border_error == 1){
				cout << "BORDER ERROR: " << sign << " can not be moved from (" << center_row << "," << center_col << ") to (" << center_row << "," << new_center_col << ")." << endl;
			}
			if(conflict_error == 1){
				//if there is a conflict error Placing the sign back to its place
				addPlus(center_row, center_col, grid, rownum, colnum, size, '+', conflict_error, border_error);
				cout << "CONFLICT ERROR: " << sign << " can not be moved from (" << center_row << "," << center_col << ") to (" << center_row << "," << new_center_col << ")." << endl;
			}
			if(conflict_error != 1 && border_error != 1){
				cout << "SUCCESS: " << sign << " moved from (" << center_row << "," << center_col << ") to (" << center_row << "," << new_center_col << ")." << endl;
			}
			break;
		case '-':
			//Deleting the current position of the sign
			addMinus(center_row, center_col, grid, rownum, colnum, size, '.', conflict_error, border_error);
			//Placing to the new position of the sign
			addMinus(center_row, new_center_col, grid, rownum, colnum, size, '-', conflict_error, border_error);
			if(border_error == 1){
				cout << "BORDER ERROR: " << sign << " can not be moved from (" << center_row << "," << center_col << ") to (" << center_row << "," << new_center_col << ")." << endl;
			}
			if(conflict_error == 1){
				addMinus(center_row, center_col, grid, rownum, colnum, size, '-', conflict_error, border_error);
				cout << "CONFLICT ERROR: " << sign << " can not be moved from (" << center_row << "," << center_col << ") to (" << center_row << "," << new_center_col << ")." << endl;
			}
			if(conflict_error != 1 && border_error != 1){
				cout << "SUCCESS: " << sign << " moved from (" << center_row << "," << center_col << ") to (" << center_row << "," << new_center_col << ")." << endl;
			}
			break;
		case 'x':
			//Deleting the current position of the sign
			addCross(center_row, center_col, grid, rownum, colnum, size, '.', conflict_error, border_error);
			//Placing to the new position of the sign
			addCross(center_row, new_center_col, grid, rownum, colnum, size, 'x', conflict_error, border_error);
			if(border_error == 1){
				cout << "BORDER ERROR: " << sign << " can not be moved from (" << center_row << "," << center_col << ") to (" << center_row << "," << new_center_col << ")." << endl;
			}
			if(conflict_error == 1){
				addCross(center_row, center_col, grid, rownum, colnum, size, 'x', conflict_error, border_error);
				cout << "CONFLICT ERROR: " << sign << " can not be moved from (" << center_row << "," << center_col << ") to (" << center_row << "," << new_center_col << ")." << endl;
			}
			if(conflict_error != 1 && border_error != 1){
				cout << "SUCCESS: " << sign << " moved from (" << center_row << "," << center_col << ") to (" << center_row << "," << new_center_col << ")." << endl;
			}
			break;
		case '/':
			//Deleting the current position of the sign
			addSlash(center_row, center_col, grid, rownum, colnum, size, '.', conflict_error, border_error);
			//Placing to the new position of the sign
			addSlash(center_row, new_center_col, grid, rownum, colnum, size, '/', conflict_error, border_error);
			if(border_error == 1){
				cout << "BORDER ERROR: " << sign << " can not be moved from (" << center_row << "," << center_col << ") to (" << center_row << "," << new_center_col << ")." << endl;
			}
			if(conflict_error == 1){
				addSlash(center_row, center_col, grid, rownum, colnum, size, '/', conflict_error, border_error);
				cout << "CONFLICT ERROR: " << sign << " can not be moved from (" << center_row << "," << center_col << ") to (" << center_row << "," << new_center_col << ")." << endl;
			}
			if(conflict_error != 1 && border_error != 1){
				cout << "SUCCESS: " << sign << " moved from (" << center_row << "," << center_col << ") to (" << center_row << "," << new_center_col << ")." << endl;
			}
			break;
	}			
}
//Moves the sign to left
void moveLeft(int recrow, int reccol, point* grid, int colnum, int rownum, int move, int &conflict_error, int &border_error){
	//Taking all values from the grid
	int center_row = (grid+(colnum*(recrow-1)+(reccol-1)))->centerrow;
	int center_col = (grid+(colnum*(recrow-1)+(reccol-1)))->centercol;
	int size = (grid+(colnum*(center_row-1)+(center_col-1)))->size;
	char sign = (grid+(colnum*(center_row-1)+(center_col-1)))->sign;
	//move the center
	int new_center_col = center_col - move;
	switch(sign){
		case '+':
			//Deleting the current position of the sign
			addPlus(center_row, center_col, grid, rownum, colnum, size, '.', conflict_error, border_error);
			//Placing to the new position of the sign
			addPlus(center_row, new_center_col, grid, rownum, colnum, size, '+', conflict_error, border_error);
			if(border_error == 1){
				cout << "BORDER ERROR: " << sign << " can not be moved from (" << center_row << "," << center_col << ") to (" << center_row << "," << new_center_col << ")." << endl;
			}
			if(conflict_error == 1){
			addPlus(center_row, center_col, grid, rownum, colnum, size, '+', conflict_error, border_error);
				cout << "CONFLICT ERROR: " << sign << " can not be moved from (" << center_row << "," << center_col << ") to (" << center_row << "," << new_center_col << ")." << endl;
			}
			if(conflict_error != 1 && border_error != 1){
				cout << "SUCCESS: " << sign << " moved from (" << center_row << "," << center_col << ") to (" << center_row << "," << new_center_col << ")." << endl;
			}
			break;
		case '-':
			//Deleting the current position of the sign
			addMinus(center_row, center_col, grid, rownum, colnum, size, '.', conflict_error, border_error);
			//Placing to the new position of the sign
			addMinus(center_row, new_center_col, grid, rownum, colnum, size, '-', conflict_error, border_error);
			if(border_error == 1){
				cout << "BORDER ERROR: " << sign << " can not be moved from (" << center_row << "," << center_col << ") to (" << center_row << "," << new_center_col << ")." << endl;
			}
			if(conflict_error == 1){
				addMinus(center_row, center_col, grid, rownum, colnum, size, '-', conflict_error, border_error);
				cout << "CONFLICT ERROR: " << sign << " can not be moved from (" << center_row << "," << center_col << ") to (" << center_row << "," << new_center_col << ")." << endl;
			}
			if(conflict_error != 1 && border_error != 1){
				cout << "SUCCESS: " << sign << " moved from (" << center_row << "," << center_col << ") to (" << center_row << "," << new_center_col << ")." << endl;
			}
			break;
		case 'x':
			//Deleting the current position of the sign
			addCross(center_row, center_col, grid, rownum, colnum, size, '.', conflict_error, border_error);
			//Placing to the new position of the sign
			addCross(center_row, new_center_col, grid, rownum, colnum, size, 'x', conflict_error, border_error);
			if(border_error == 1){
				cout << "BORDER ERROR: " << sign << " can not be moved from (" << center_row << "," << center_col << ") to (" << center_row << "," << new_center_col << ")." << endl;
			}
			if(conflict_error == 1){
				addCross(center_row, center_col, grid, rownum, colnum, size, 'x', conflict_error, border_error);
				cout << "CONFLICT ERROR: " << sign << " can not be moved from (" << center_row << "," << center_col << ") to (" << center_row << "," << new_center_col << ")." << endl;
			}
			if(conflict_error != 1 && border_error != 1){
				cout << "SUCCESS: " << sign << " moved from (" << center_row << "," << center_col << ") to (" << center_row << "," << new_center_col << ")." << endl;
			}
			break;
		case '/':
			//Deleting the current position of the sign
			addSlash(center_row, center_col, grid, rownum, colnum, size, '.', conflict_error, border_error);
			//Placing to the new position of the sign
			addSlash(center_row, new_center_col, grid, rownum, colnum, size, '/', conflict_error, border_error);
			if(border_error == 1){
				cout << "BORDER ERROR: " << sign << " can not be moved from (" << center_row << "," << center_col << ") to (" << center_row << "," << new_center_col << ")." << endl;
			}
			if(conflict_error == 1){
				addSlash(center_row, center_col, grid, rownum, colnum, size, '/', conflict_error, border_error);
				cout << "CONFLICT ERROR: " << sign << " can not be moved from (" << center_row << "," << center_col << ") to (" << center_row << "," << new_center_col << ")." << endl;
			}
			if(conflict_error != 1 && border_error != 1){
				cout << "SUCCESS: " << sign << " moved from (" << center_row << "," << center_col << ") to (" << center_row << "," << new_center_col << ")." << endl;
			}
			break;
	}
			
}
//Moves the sign up
void moveDown(int recrow, int reccol, point* grid, int colnum, int rownum, int move, int &conflict_error, int &border_error){
	//Taking all values from the grid
	int center_row = (grid+(colnum*(recrow-1)+(reccol-1)))->centerrow;
	int center_col = (grid+(colnum*(recrow-1)+(reccol-1)))->centercol;
	int size = (grid+(colnum*(center_row-1)+(center_col-1)))->size;
	char sign = (grid+(colnum*(center_row-1)+(center_col-1)))->sign;
	//move the center
	int new_center_row = center_row + move;
	switch(sign){
		case '+':
			//Deleting the current position of the sign
			addPlus(center_row, center_col, grid, rownum, colnum, size, '.', conflict_error, border_error);
			//Placing to the new position of the sign
			addPlus(new_center_row, center_col, grid, rownum, colnum, size, '+', conflict_error, border_error);
			if(border_error == 1){
				cout << "BORDER ERROR: " << sign << " can not be moved from (" << center_row << "," << center_col << ") to (" << new_center_row << "," << center_col << ")." << endl;
			}
			if(conflict_error == 1){
				addPlus(center_row, center_col, grid, rownum, colnum, size, '+', conflict_error, border_error);
				cout << "CONFLICT ERROR: " << sign << " can not be moved from (" << center_row << "," << center_col << ") to (" << new_center_row << "," << center_col << ")." << endl;
			}
			if(conflict_error != 1 && border_error != 1){
				cout << "SUCCESS: " << sign << " moved from (" << center_row << "," << center_col << ") to (" << new_center_row << "," << center_col << ")." << endl;
			}
			break;
		case '-':
			//Deleting the current position of the sign
			addMinus(center_row, center_col, grid, rownum, colnum, size, '.', conflict_error, border_error);
			//Placing to the new position of the sign
			addMinus(new_center_row, center_col, grid, rownum, colnum, size, '-', conflict_error, border_error);
			if(border_error == 1){
				cout << "BORDER ERROR: " << sign << " can not be moved from (" << center_row << "," << center_col << ") to (" << new_center_row << "," << center_col << ")." << endl;
			}
			if(conflict_error == 1){
				addMinus(center_row, center_col, grid, rownum, colnum, size, '-', conflict_error, border_error);
				cout << "CONFLICT ERROR: " << sign << " can not be moved from (" << center_row << "," << center_col << ") to (" << new_center_row << "," << center_col << ")." << endl;
			}
			if(conflict_error != 1 && border_error != 1){
				cout << "SUCCESS: " << sign << " moved from (" << center_row << "," << center_col << ") to (" << new_center_row << "," << center_col << ")." << endl;
			}
			break;
		case 'x':
			//Deleting the current position of the sign
			addCross(center_row, center_col, grid, rownum, colnum, size, '.', conflict_error, border_error);
			//Placing to the new position of the sign
			addCross(new_center_row, center_col, grid, rownum, colnum, size, 'x', conflict_error, border_error);
			if(border_error == 1){
				cout << "BORDER ERROR: " << sign << " can not be moved from (" << center_row << "," << center_col << ") to (" << new_center_row << "," << center_col << ")." << endl;
			}
			if(conflict_error == 1){
				addCross(center_row, center_col, grid, rownum, colnum, size, 'x', conflict_error, border_error);
				cout << "CONFLICT ERROR: " << sign << " can not be moved from (" << center_row << "," << center_col << ") to (" << new_center_row << "," << center_col << ")." << endl;
			}
			if(conflict_error != 1 && border_error != 1){
				cout << "SUCCESS: " << sign << " moved from (" << center_row << "," << center_col << ") to (" << new_center_row << "," << center_col << ")." << endl;
			}
			break;
		case '/':
			//Deleting the current position of the sign
			addSlash(center_row, center_col, grid, rownum, colnum, size, '.', conflict_error, border_error);
			//Placing to the new position of the sign
			addSlash(new_center_row, center_col, grid, rownum, colnum, size, '/', conflict_error, border_error);
			if(border_error == 1){
				cout << "BORDER ERROR: " << sign << " can not be moved from (" << center_row << "," << center_col << ") to (" << new_center_row << "," << center_col << ")." << endl;
			}
			if(conflict_error == 1){
				addSlash(center_row, center_col, grid, rownum, colnum, size, '/', conflict_error, border_error);
				cout << "CONFLICT ERROR: " << sign << " can not be moved from (" << center_row << "," << center_col << ") to (" << new_center_row << "," << center_col << ")." << endl;
			}
			if(conflict_error != 1 && border_error != 1){
				cout << "SUCCESS: " << sign << " moved from (" << center_row << "," << center_col << ") to (" << new_center_row << "," << center_col << ")." << endl;
			}
			break;
	}
			
}
//Moves the sign down
void moveUp(int recrow, int reccol, point* grid, int colnum, int rownum, int move, int &conflict_error, int &border_error){
	//Taking all values from the grid
	int center_row = (grid+(colnum*(recrow-1)+(reccol-1)))->centerrow;
	int center_col = (grid+(colnum*(recrow-1)+(reccol-1)))->centercol;
	int size = (grid+(colnum*(center_row-1)+(center_col-1)))->size;
	char sign = (grid+(colnum*(center_row-1)+(center_col-1)))->sign;
	//move the center
	int new_center_row = center_row - move;
	switch(sign){
		case '+':
			//Deleting the current position of the sign
			addPlus(center_row, center_col, grid, rownum, colnum, size, '.', conflict_error, border_error);
			//Placing to the new position of the sign
			addPlus(new_center_row, center_col, grid, rownum, colnum, size, '+', conflict_error, border_error);
			if(border_error == 1){
				cout << "BORDER ERROR: " << sign << " can not be moved from (" << center_row << "," << center_col << ") to (" << new_center_row << "," << center_col << ")." << endl;
			}
			if(conflict_error == 1){
				addPlus(center_row, center_col, grid, rownum, colnum, size, '+', conflict_error, border_error);
				cout << "CONFLICT ERROR: " << sign << " can not be moved from (" << center_row << "," << center_col << ") to (" << new_center_row << "," << center_col << ")." << endl;
			}
			if(conflict_error != 1 && border_error != 1){
				cout << "SUCCESS: " << sign << " moved from (" << center_row << "," << center_col << ") to (" << new_center_row << "," << center_col << ")." << endl;
			}
			break;
		case '-':
			//Deleting the current position of the sign
			addMinus(center_row, center_col, grid, rownum, colnum, size, '.', conflict_error, border_error);
			//Placing to the new position of the sign
			addMinus(new_center_row, center_col, grid, rownum, colnum, size, '-', conflict_error, border_error);
			if(border_error == 1){
				cout << "BORDER ERROR: " << sign << " can not be moved from (" << center_row << "," << center_col << ") to (" << new_center_row << "," << center_col << ")." << endl;
			}
			if(conflict_error == 1){
				addMinus(center_row, center_col, grid, rownum, colnum, size, '-', conflict_error, border_error);
				cout << "CONFLICT ERROR: " << sign << " can not be moved from (" << center_row << "," << center_col << ") to (" << new_center_row << "," << center_col << ")." << endl;
			}
			if(conflict_error != 1 && border_error != 1){
				cout << "SUCCESS: " << sign << " moved from (" << center_row << "," << center_col << ") to (" << new_center_row << "," << center_col << ")." << endl;
			}
			break;
		case 'x':
			//Deleting the current position of the sign
			addCross(center_row, center_col, grid, rownum, colnum, size, '.', conflict_error, border_error);
			//Placing to the new position of the sign
			addCross(new_center_row, center_col, grid, rownum, colnum, size, 'x', conflict_error, border_error);
			if(border_error == 1){
				cout << "BORDER ERROR: " << sign << " can not be moved from (" << center_row << "," << center_col << ") to (" << new_center_row << "," << center_col << ")." << endl;
			}
			if(conflict_error == 1){
				addCross(center_row, center_col, grid, rownum, colnum, size, 'x', conflict_error, border_error);
				cout << "CONFLICT ERROR: " << sign << " can not be moved from (" << center_row << "," << center_col << ") to (" << new_center_row << "," << center_col << ")." << endl;
			}
			if(conflict_error != 1 && border_error != 1){
				cout << "SUCCESS: " << sign << " moved from (" << center_row << "," << center_col << ") to (" << new_center_row << "," << center_col << ")." << endl;
			}
			break;
		case '/':
			//Deleting the current position of the sign
			addSlash(center_row, center_col, grid, rownum, colnum, size, '.', conflict_error, border_error);
			//Placing to the new position of the sign
			addSlash(new_center_row, center_col, grid, rownum, colnum, size, '/', conflict_error, border_error);
			if(border_error == 1){
				cout << "BORDER ERROR: " << sign << " can not be moved from (" << center_row << "," << center_col << ") to (" << new_center_row << "," << center_col << ")." << endl;
			}
			if(conflict_error == 1){
				addSlash(center_row, center_col, grid, rownum, colnum, size, '/', conflict_error, border_error);
				cout << "CONFLICT ERROR: " << sign << " can not be moved from (" << center_row << "," << center_col << ") to (" << new_center_row << "," << center_col << ")." << endl;
			}
			if(conflict_error != 1 && border_error != 1){
				cout << "SUCCESS: " << sign << " moved from (" << center_row << "," << center_col << ") to (" << new_center_row << "," << center_col << ")." << endl;
			}
			break;
	}
			
}

int main(int argc, char* argv[]){
	int row, column;
	//opening the grid file
	ifstream grid1(argv[1]);
	//creating a grid and initializing by the values from grid file
	grid1 >> row;
	grid1 >> column;
	point arr[row][column];

	cout << "A grid is created: " << row << " " << column << endl;
	
	point *grid = arr[0];
	
	//assigning the initial values to grid arr
	for(int i=0;i<row;i++){
		for(int j=0;j<column; j++){
			arr[i][j].size = -1;
			arr[i][j].centerrow = -1;
			arr[i][j].centercol = -1;
			arr[i][j].sign = '.';
		}
	}
	
	char sign;
	int centerrow, centercol, size;
	int border_error = 0, conflict_error = 0;
	while(!grid1.eof()){
		//Taking the information from the file
		conflict_error = 0;
		border_error = 0;
		grid1 >> sign;
		grid1 >> centerrow;
		grid1 >> centercol;
		grid1 >> size;
		if( grid1.eof() ) break; 
		switch(sign){
			case '+':
				conflict_error = 0;
				border_error = 0;
				addPlus(centerrow, centercol, grid, row, column, size, '+', conflict_error, border_error);
				if(border_error == 1){
					cout << "BORDER ERROR: Operator " << sign << " with size " << size << " can not be placed on (" << centerrow << "," << centercol << ")." << endl;
					continue;
				}
				if(conflict_error == 1){
					cout << "CONFLICT ERROR: Operator " << sign << " with size " << size << " can not be placed on (" << centerrow << "," << centercol << ")." << endl;
					continue;
				}
				cout << "SUCCESS: Operator " << sign << " with size " << size << " is placed on (" << centerrow << "," << centercol << ")." << endl; 
				break;
			case '-':
				conflict_error = 0;
				border_error = 0;
				addMinus(centerrow, centercol, grid, row, column, size, '-', conflict_error, border_error);
				if(border_error == 1){
					cout << "BORDER ERROR: Operator " << sign << " with size " << size << " can not be placed on (" << centerrow << "," << centercol << ")." << endl;
					continue;
				}
				if(conflict_error == 1){
					cout << "CONFLICT ERROR: Operator " << sign << " with size " << size << " can not be placed on (" << centerrow << "," << centercol << ")." << endl;
					continue;
				}
				cout << "SUCCESS: Operator " << sign << " with size " << size << " is placed on (" << centerrow << "," << centercol << ")." << endl; 
				break;
			case 'x':
				conflict_error = 0;
				border_error = 0;
				addCross(centerrow, centercol, grid, row, column, size, 'x', conflict_error, border_error);
				if(border_error == 1){
					cout << "BORDER ERROR: Operator " << sign << " with size " << size << " can not be placed on (" << centerrow << "," << centercol << ")." << endl;
					continue;
				}
				if(conflict_error == 1){
					cout << "CONFLICT ERROR: Operator " << sign << " with size " << size << " can not be placed on (" << centerrow << "," << centercol << ")." << endl;
					continue;
				}
				cout << "SUCCESS: Operator " << sign << " with size " << size << " is placed on (" << centerrow << "," << centercol << ")." << endl; 
				break;
			case '/':
				conflict_error = 0;
				border_error = 0;
				addSlash(centerrow, centercol, grid, row, column, size, '/', conflict_error, border_error);
				if(border_error == 1){
					cout << "BORDER ERROR: Operator " << sign << " with size " << size << " can not be placed on (" << centerrow << "," << centercol << ")." << endl;
					continue;
				}
				if(conflict_error == 1){
					cout << "CONFLICT ERROR: Operator " << sign << " with size " << size << " can not be placed on (" << centerrow << "," << centercol << ")." << endl;
					continue;
				}
				cout << "SUCCESS: Operator " << sign << " with size " << size << " is placed on (" << centerrow << "," << centercol << ")." << endl; 
				break;	
		}
	}
	//closing the grid file
	grid1.close();
	//end of grid placements
	
	//opening the instructions file
	ifstream instructions(argv[2]);
	
	char operation[3];
	int pointrow, pointcol, move_by;
	while(!instructions.eof()){
		//reading the inputs line by line
		conflict_error = 0;
		border_error = 0;
		instructions >> operation;
		instructions >> pointrow;
		instructions >> pointcol;
		instructions >> move_by;
		if( instructions.eof() ) break;
		switch(operation[2]){
			case 'R':
				moveRight(pointrow, pointcol, grid, column, row, move_by, conflict_error, border_error);
				if(conflict_error == 1 || border_error == 1){
					continue;
				}
				break;
			case 'L':
				moveLeft(pointrow, pointcol, grid, column, row, move_by, conflict_error, border_error);
				if(conflict_error == 1 || border_error == 1){
					continue;
				}
				break;
			case 'D':
				moveDown(pointrow, pointcol, grid, column, row, move_by, conflict_error, border_error);
				if(conflict_error == 1 || border_error == 1){
					continue;
				}
				break;
			case 'U':
				moveUp(pointrow, pointcol, grid, column, row, move_by, conflict_error, border_error);
				if(conflict_error == 1 || border_error == 1){
					continue;
				}
				break;	
		}
		
		for(int i=0; i<row; i++){
			for(int j = 0; j<column; j++){
				cout << arr[i][j].sign;
			}
			cout << endl;
		}
	}
	//closing the instructions file
	instructions.close();
	//end of movements
	return 0;
}
