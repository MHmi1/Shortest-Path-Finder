#include <fstream>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <random>
#include <time.h>
#include <conio.h>

#define row_size 25		// Number of matrix rows
#define col_size 25		//Number of matrix columns


using namespace std;

int
main ()
{
  FILE *f;
  fstream out;

  out.open ("map2.txt", ios::out | ios::ate);	//opening file to write data
  if (!out.is_open ())
    {
      cerr << " error in opening data file !!" << endl;
    }

  srand (time (0));
  random_device rd;
  default_random_engine dre (rd ());

  for (int k = 0; k < col_size; k++)
    {
      uniform_int_distribution < int >uid (1, 17);	// generate random num between 1 - 17 

      int arr[row_size];

      generate (arr, arr + sizeof (arr) / sizeof (int),[&]()  //lambda expression
		{
		return uid (dre);
		}
      );

      for (int z = 0; z < row_size; z++)	//map should not have 4 because destination input from the user
	{
	  if (arr[z] == 4)
	    arr[z] = 5;
	}

      for (int i = 0; i < row_size; i++)
	{
	  out << arr[i] << " ";
	}
      out << endl;
    }


  out.flush ();
  out.close ();
  getch ();
  return 0;

}
