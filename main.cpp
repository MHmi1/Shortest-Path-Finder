#include <iostream>
#include <fstream>
#include <conio.h>
#include <iomanip>
using namespace std;

int main() {


  int row=0, col=0;

  cout<<"enter number of row : " <<endl;
  cin>>row;

    cout<<"enter number of column : " <<endl;
  cin>>col;

  ifstream myfile;
  myfile.open ("matrix.txt");
  char mat[row][col][col*2];

  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      myfile >> mat[i][j];
    }
  }
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      cout <<setw(2) <<left<<mat[i][j] <<" ";
    }
    cout << endl;
  }
  getch();
  return 0;
}
