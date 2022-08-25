                               //finding shortest path between two elements in a matrix
#include <iostream>
#include <fstream>
#include <conio.h>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
#include <random>
#include <time.h>
using namespace std;

//element is a member of matrix
struct Element
{

    int row = -1;
    int col = -1;
    int dist = 0; //dist = distance
    int value = 0;
    Element(int x = -1, int y = -1, int d = 0): row(x), col(y), dist(d)
    {
    }
};


//breadth-first search algorithm for finding shortest path (using queue)
int BFS(vector<vector <Element> >&mat, vector<vector <Element> >&prev, int row,int col, int Prow,int Pcol, int Drow,int Dcol)
{
    //marking blocked elements as visited
    bool visited[row][col];
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            int m_e = mat[i][j].value; //m_e = matrix element
            if (m_e == 2 || m_e == 6 || m_e == 7 || m_e == 9 || m_e == 10 || m_e == 14 || m_e == 15)
            {
                visited[i][j] = true;
            }
            else
            {
                visited[i][j] = false;
            }
        }
    }

    Element source;
    int srow = source.row = Prow;
    int scol = source.col = Pcol;
  
    queue<Element> q;
    q.push(source);
    visited[srow][scol] = true;

    int x = -1,y = -1,d = 0;
    while (!q.empty())
    {
        Element e = q.front();

        q.pop();

        x = e.row;
        y = e.col;
        d = e.dist;
        // moving up
        if (x - 1 >= 0 && visited[x - 1][y] == false)
        {
            q.push(Element(x - 1, y, d + 1));
            visited[x - 1][y] = true;
            prev[x - 1][y].row = x;
            prev[x - 1][y].col = y;

            if (mat[x - 1][y].value == 68) //68 = 'D' in ASCII code
            {
                return d + 1;
            }
        }

        // moving right
        if (y + 1 < col && visited[x][y + 1] == false)
        {
            q.push(Element(x, y + 1, d + 1));
            visited[x][y + 1] = true;
            prev[x][y + 1].row = x;
            prev[x][y + 1].col = y;

            if (mat[x][y + 1].value == 68) //68 = 'D' in ASCII code
            {
                return d + 1;
            }
        }

        // moving down
        if (x + 1 < row && visited[x + 1][y] == false)
        {
            q.push(Element(x + 1, y, d + 1));
            visited[x + 1][y] = true;
            prev[x + 1][y].row = x;
            prev[x + 1][y].col = y;

            if (mat[x + 1][y].value == 68) //68 = 'D' in ASCII code
            {
                return d + 1;
            }
        }

        // moving left
        if (y - 1 >= 0 && visited[x][y - 1] == false)
        {
            q.push(Element(x, y - 1, d + 1));
            visited[x][y - 1] = true;
            prev[x][y - 1].row = x;
            prev[x][y - 1].col = y;

            if (mat[x][y - 1].value == 68) //68 = 'D' in ASCII code
            {
                return d + 1;
            }
        }
    }
    return -1;
}


int calpoint (int playernum ,vector<vector <Element> > mat,vector< Element > path,int distance) //calpoint = calculate points
{
    int points = 0;
    for (int i = 0; i < distance; i++)
    {
        //vector path has cells of final path that gives us the row and column of each cell and we check the value of the similar cell in our matrix
        switch (mat[path[i].row][path[i].col].value)
        {
            case 5:
                if (playernum == 65) points += 1000; //65 = 'A' in ASCII code
                break;
            case 13:
                if (playernum == 66) points += 1000; //66 = 'B' in ASCII code
                break;
            case 8:
                if (playernum == 66) points -= 500;
                break;
            case 16:
                if (playernum == 65) points -= 500;
                break;
            case 11:
                if (playernum == 66) points -= 10;
                break;
            case 12:
                if (playernum == 65) points -= 10;
                break;

            default:
                break;
        }
    }
    return points;
}


vector<Element> pathfunc(vector<vector <Element> >prev,int distance ,int row, int col,int Drow, int Dcol)
{

    vector <Element> path (distance);
    //intialize the first cell of vector with destination row and column to start a backward path
    path[0].row = Drow;
    path[0].col = Dcol;

    int trow;
    int tcol;

    //before the 'for' starts we have destination row and column in 'path[0]' then at first in 'for' we have "path[i+1] = path[1]"
    //in 'path[1]' we put information of " 'path[0]' in prev " , 'path[0]' is destination it means we put information of destination in prev matrix
    //in 'path[1]' and the information of that is row and column of previous element in path
    for (int i = 0; i < distance-1; i++)
    {
        trow = path[i].row;
        tcol = path[i].col;
        path[i+1].row = prev[trow][tcol].row;
        path[i+1].col = prev[trow][tcol].col;
    }
    //reverse path from D to A,B  to  A,B to D
    reverse(path.begin(),path.end());
    return path;
}


int main()
{
    int row, col;
    cout << "Enter Number of Rows:" << endl;
    cin >> row;
    cout << "Enter Number of Column:" << endl;
    cin >> col;
    if (row < 1 || col < 1)
    {
        cerr << "!!  row and column can't be 0 or negetive  !!" << endl;
        abort();
    }
    //define a matrix using vector
    vector < vector <Element> > mat ( row, vector <Element> (col) );

    //define 2 matrix of elements , one for first player and one for second player
    //this matrix specifies previous element that each element has come from in BFS,it means each cell has the row and column of previous
    vector < vector <Element> > prev1 ( row, vector <Element> (col) ); //prev = previous
    vector < vector <Element> > prev2 ( row, vector <Element> (col) ); //prev = previous


    //reading the values of matrix elements from file
    ifstream myfile;
    myfile.open("map2.txt");
    if (myfile.is_open() == false)
    {
        cout << "!!Opening File Failed!!" << endl;
        abort();
        //cin.get();
    }
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            myfile >> mat[i][j].value;
        }
    }


    int Arow, Acol;
    cout << "Enter Row of Player A:" << endl;
    cin >> Arow;
    cout << "Enter Column of Player A:" << endl;
    cin >> Acol;

    int Brow, Bcol;
    cout << "Enter Row of Player B:" << endl;
    cin >> Brow;
    cout << "Enter Column of Player B:" << endl;
    cin >> Bcol;

    if (Arow == Brow && Acol == Bcol)
    {
        cout << "!!  Player A and Player B must not have same row and column  !!" << endl;
        getch();
        abort();
    }

    int Drow, Dcol;
    cout << "Enter Destination Row:" << endl;
    cin >> Drow;
    cout << "Enter Destination Column:" << endl;
    cin >> Dcol;

    if (Arow == Drow && Acol == Dcol)
    {
        cerr << "!! Player A and Destination must not have same row and column  !! \n ";
        getch();
        abort();
    }
    else if (Brow == Drow && Bcol == Dcol)
    {
        cerr << "!! Player B and Destination must not have same row and column  !! \n " ;
        getch();
        abort();
    }

    else if ( Arow < 1 || Brow < 1 || Drow < 1 || Acol < 1 || Bcol < 1 || Dcol < 1)
    {
        cerr << "!! row and column can't be 0 or negetive !! \n " ;
        getch();
        abort();
    }

    //because in arrays index starts with 0
    Arow -= 1;
    Acol -= 1;
    Brow -= 1;
    Bcol -= 1;
    Drow -= 1;
    Dcol -= 1;

    //specify sources and destination in matrix
    mat[Arow][Acol].value = 'A';
    mat[Brow][Bcol].value = 'B';
    mat[Drow][Dcol].value = 'D'; // D = destination , D = 4 (anbar mohemmat)

    cout << "---------------------------------" << endl;

    //print the original matrix
    cout << "// Matrix //" << endl;
    int m1value;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            m1value = mat[i][j].value;

            if (m1value == 65) // 65 = 'A'
            {
                cout << left << setw(3) << "A ";
            }
            else if (m1value == 66) // 66 = 'B'
            {
                cout << left << setw(3) << "B ";
            }
            else if (m1value == 68) // 68 = 'D'
            {
                cout << left << setw(3) << "D ";
            }
            else
            {
                cout << left << setw(2) << m1value << " ";
            }
        }
        cout << endl;
    }

    //print a understandable matrix
    cout << "## Matrix ##" << endl;
    vector < vector <Element> > tempmat ( row, vector <Element> (col) );
    tempmat = mat;
    int value;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            value = tempmat[i][j].value;
            if (value == 2 || value == 6 || value == 7 || value == 9 || value == 10 || value == 14 || value == 15)
            {
                cout << "#  ";
            }
            else if (value == 65) // 65 = 'A'
            {
                cout << "A  ";
            }
            else if (value == 66) // 66 = 'B'
            {
                cout << "B  ";
            }
            else if (value == 68) // 68 = 'D'
            {
                cout << "D  ";
            }
            else
            {
                cout << "-  ";
            }
        }
        cout << endl;
    }



    //call functions for Player A
    int distance1 = BFS(mat , prev1 , row , col , Arow , Acol , Drow , Dcol);
    vector <Element> path1 (distance1);
    path1 = pathfunc(prev1 , distance1 , row , col , Drow , Dcol);
    int Apoint = calpoint('A' , mat , path1 , distance1);

    //call functions for Player B
    int distance2 = BFS(mat , prev2 , row , col , Brow , Bcol , Drow , Dcol);
    vector <Element> path2 (distance2);
    path2 = pathfunc(prev2 , distance2 , row , col , Drow , Dcol);
    int Bpoint = calpoint('B' , mat , path2 , distance2);

    cout << "---------------------------------" << endl;

    //print informations for Player A
    cout << "Path A => {A -> ";
    for (int i = 0; i < distance1-1; i++)
    {
        cout << "(" << path1[i].row+1 << "," << path1[i].col+1 << ")" << " -> ";
    }
    cout << "D}" << " , Distance(Steps) = " << distance1 << endl;
    cout << "Points of Player A = " << Apoint << endl;

    //print informations for Player B
    cout << "Path B => {B -> ";
    for (int i = 0; i < distance2-1; i++)
    {
        cout << "(" << path2[i].row+1 << "," << path2[i].col+1 << ")" << " -> ";
    }
    cout << "D}" << " , Distance(Steps) = " << distance2 << endl;
    cout << "Points of Player B = " << Bpoint << endl;


    //who is the winner?
    if (distance1 < distance2)
    {
        if (distance1 != -1 )
        cout << "!!!!  Player A is the Winner   !!!!" << endl;
        else
        cout << "!!!!  Shortest Path doesn't exist for Player A  !!!!" << endl;

    }
    else if (distance1 > distance2)
    {
        if (distance2 != -1 )
        cout << "!!!!   Player B is the Winner   !!!!" << endl;
        else
        cout << "!!!!  Shortest Path doesn't exist for Player B  !!!!" << endl;
    }
    else if (distance1 == distance2)
    {
        if (Apoint > Bpoint)
        {
            cout << "!!!!   Player A with more points is the Winner   !!!!" << endl;
        }
        else if (Apoint < Bpoint)
        {
            cout << "!!!!   Player B with more points is the Winner   !!!!" << endl;
        }
        else if (Apoint == Bpoint)
        {
            cout << "!!!!   Player A and Player B are Equal   !!!!" << endl;
        }
    }

    myfile.close();

    getch();
    return 0;
}
