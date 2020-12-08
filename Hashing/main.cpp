/*main.cpp*/

//
// Hashing program for specialized Illinois license plates,
// which processes an input file of license plates and fines.
// The output is the total fines per license plate, in 
// sorted order.
//
// Original author: Prof. Joe Hummel
// Modified by:     << YOUR NAME >>
//
// U. of Illinois, Chicago
// CS 251: Fall 2019
// Project 05
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <cassert>

#include "ILplates.h"

using namespace std;


//
// hashInput:
//
void hashInput(string basename, ILplates& hashplates)
{
  string infilename = basename + ".txt";
  ifstream infile(infilename);

  if (!infile.good())
  {
    cout << endl;
    cout << "**Error: unable to open input file '" << infilename << "', exiting." << endl;
    cout << endl;
    exit(-1);
  }

  //
  // input the plates and fines:
  //
  cout << "Reading '" << infilename << "'..." << endl;

  string fine;
  string plate;

  getline(infile, fine);

  //
  // for each pair (fine, license plate), hash and store/update fine:
  //
  while (!infile.eof())
  {
    getline(infile, plate);

    //cout << fine << endl;
    //cout << plate << endl;

    // 
    // is plate valid?  Only process valid plates:
    //
    if (hashplates.Hash(plate) >= 0)  // yes:
    {
      int amount = hashplates.Search(plate);

      if (amount < 0)  // not found:
      {
        hashplates.Insert(plate, stoi(fine));
      }
      else  // we found it, so update total in hash table:
      {
        amount += stoi(fine);
        hashplates.Insert(plate, amount);
      }

    }//valid

    getline(infile, fine);
  }
}

// Compares two strings index by index
// 
// if the strings require switching, the function returns 1.
int strcmp(string left, string right)
{
	int i = 0;           // goes index by index
    while (true)
    {
        if (left[i] > right[i])
            return 1;
        else if (left[i] < right[i])
            return -1;
        if (left[i] == '\0')
            break;
        i++;
    }
    return 0;
}

// simple bubble sort algorithm to sort the plates and amounts vector
void sortForOutput(vector<string>& plates, vector<int>& amounts)
{
	string temp;    // for switching strings in the vector
	int tempAmount; // for switching amounts in the vector
	for (size_t j=0; j<plates.size()-1; j++) 
    { 
        for (size_t i=j+1; i<plates.size(); i++) 
        { 
            if (strcmp(plates[j], plates[i]) > 0) // if needs switching
            { 
                temp = plates[j];        // stores in temp string
                plates[j] = plates[i];   // switching
                plates[i] = temp;        // switching
				
				// similar change in the amounts vector
				tempAmount = amounts[j];
				amounts[j] = amounts[i];
				amounts[i] = tempAmount;
            } 
        } 
    }
}


int main()
{
  int    N;        // = 10000;
  string basename; // = "tickets1";

  cout << "Enter hashtable size> ";
  cin >> N;

  hashtable<string, int>  ht(N);
  ILplates                hashplates(ht);

  cout << "Enter base filename> ";
  cin >> basename;
  cout << endl;

  //
  // process input file of fines and license plates:
  //
  hashInput(basename, hashplates);
//   vector<string> plates = ht.Keys(); // stores all the keys in the hashtable
//   vector<int> amounts = ht.Values(); // stores all the values in the hashtable
  cout << "Sorting...\n";
//   sortForOutput(plates, amounts); // sorts plates and amounts
  cout << "Writing '" << basename << "-output.txt'...\n";
	
//   ofstream myFile(basename+"-output.txt"); // ofstream to write the output file
// 	  if(myFile.is_open())
// 	  {
// // 		  for(size_t i = 0; i < plates.size(); i++)
// // 		  {
// // 			  myFile << "\"" << plates[i] << "\" " << "$" << amounts[i] << "\n";   // writes the file line by line
// // 		  }

// 		for(int i = 0; i < ht.Size(); i++)
// 	  {
// 	  bool empty = true;           // stores empty status from .Get()
// 	  int value;                   // stores value from .Get()
// 	  string key;                  // stores key from .Get()

// 		  ht.Get(i,empty,key,value);
// 		  myFile << "Index: " << i << " String: " << key << endl;
// 	  }
// 	  }
	  
  return 0;
}