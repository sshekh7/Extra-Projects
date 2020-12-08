/*ILplates.cpp*/

//
// Hashing functions to store (license plate, amount) pairs
// using linear probing.
//
// << Shaan Shekhar >>
// U. of Illinois, Chicago
// CS 251: Fall 2019
// Project 05
//

#include <iostream>
#include <string>
#include <math.h>
#include "ILplates.h"

using namespace std;


//
// Hash:
//
// Given a specialized Illinois license plate, returns an index into
// the underyling hash table.  If the given plate does not follow the
// formatting rules given below, -1 is returned.
//
// Personalized:
//   letters and numbers, with a space between the letters 
//   and numbers.  Format: 1-5 letters plus 1..99 *OR* 
//   6 letters plus 1..9
//
//   Examples: A 1, B 99, ZZZZZ 1, ABCDEF 3
//
// Vanity:
//   Format: 1-3 numbers *OR* 1-7 letters
// 
//   Examples: 007, 1, 42, X, AAA, ZZZEFGH
//

// The function ckecks if a string is valid or not
bool isValid(string plate)
{
	if(isdigit(plate[0]) && plate.size() <= 3) // Vanity: all numbers
	{
		for(size_t i = 0; i < plate.length(); i++) // Checks for fully numeric
		{
			if(!isdigit(plate[i])) // if not fully numeric
				return false;
		}
		return true; // Valid string
	}
	
	else if(isalpha(plate[plate.length()-1]) && plate.length() <= 7) // Vanity: all letters
	{
		for(size_t i = 0; i < plate.length(); i++) // Checks for fully alphabetic
		{
			if(!isalpha(plate[i]) || islower(plate[i])) // if not full alphabetic
				return false;
		}
		return true; // Valid string
	}
	
	else if(isdigit(plate[plate.length()-1]) && isspace(plate[plate.length()-2])) // Personalized: 1-7 Letters 1-9 Numbers
	{
		if(plate.length() > 8) // Bad length
			return false;
		for(size_t i = 0; i < plate.length()-2; i++) // Checks for fully alphabetic
		{
			if(!isalpha(plate[i]) || islower(plate[i])) // if not fully alphabetic
				return false;
		}
		return true; // Valid string
	}
	
	else if(isdigit(plate[plate.length()-1]) && 
			isdigit(plate[plate.length()-2]) && 
			isspace(plate[plate.length()-3]) && 
			plate.length()<=8) // Personalized: 1-5 Letters 10-99 Numbers
	{
		for(size_t i = 0; i < plate.length()-3; i++) // Checks for fully alphabetic 
		{
			if(!isalpha(plate[i]) || islower(plate[i])) // if not fully alphabetic
				return false;
		}
		return true; // Valid string
	}
	return false; // Invalid string
	
} // ends isValid()

// Returns an index value to be used in the hash table
int ILplates::Hash(string plate)
{
  int index = -1;

	if(!isValid(plate)) // if invalid string
	{
		return -1;
	} // if the string is not valid, reject immediately
	else if(isdigit(plate[0])) // algorithm to calculate index of Vanity plates (all numeric)
	{
		int x = plate.size();
		for(size_t i = 0; i < plate.size(); i++)
		{
			index += i*(plate[i]) + x*stoi(plate) - x + 1020;
			if(plate.length() == 2)
			{
				index += x*i; 
			}
			if(plate.length() == 3)
			{
				index -= x*i + 50;
			}
			x--;
		}
	}
	else // algorithm to calculate index of Vanity & Personalized plates containing alphabets and numbers
	{
		int x = plate.size();
		for(size_t i = 0; i < plate.size(); i++)
		{
			index += x*(plate[i]*(40+i)) + (i)*plate[i] + 1200;
			if(isdigit(plate[plate.length()-2]))
			{
				index += x*i + 150;
			}
			else if(isdigit(plate[plate.length()-1]))
			{
				index += x*i + x*500;
			}
			x--;
		}
	}
	
	
	return index % HT.Size();
}
	
// searches the hashtable for a given plate value
int ILplates::Search(string plate)
{
  int index = Hash(plate); // gets index for the plate
  bool empty = true;       // stores empty status from .Get()
  string key;              // stores key from .Get()
  int value;               // stores value from .Get()
  HT.Get(index, empty, key, value); // probes the hashtable at index
  
// Checks until finds the first whitespace
  while(empty != true){
      if(key == plate){ // if finds the key
         return value;
      } 
      index = index + 1; // moves t the next index
      if(index == HT.Size()){
        index = 0; 
      }
	  HT.Get(index, empty, key, value); // probes the hashtable at the new index
  }
  return -1; // if finds a whitespace
}


//
// Insert
//
// Inserts the given (plate, newValue) into the hash table,
// overwriting an existing value if there.
//
void ILplates::Insert(string plate, int newValue)
{
  int index = Hash(plate);     // gets index for the plate
  bool empty = true;           // stores empty status from .Get()
  int value;                   // stores value from .Get()
  string key;                  // stores key from .Get()

  HT.Get(index, empty, key, value); // probes the hashtable at index
	
	while(true) // while the value is not set in the hashtable
	{
		if(empty == false)
		{
			if(key == plate) // if string exists already in the hashtable
			{
				HT.Set(index, plate, newValue); // probes the hashtable and overwrites the current value
				break;
			}
			else // if the space is occupied and string is not the key
			{
				index = index + 1; // moves to the next index
				HT.Get(index, empty, key, value); // probes the hashtable at the new index
			}	
		}
		else
		{
			HT.Set(index, plate, newValue); // if the space is empty at the given index, just sets the value
			break;
		}
	}
}
