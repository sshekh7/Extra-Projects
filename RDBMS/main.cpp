/*main.cpp*/

//
// myDB project using AVL trees
//
// <<Shaan Shekhar>>
// U. of Illinois, Chicago
// CS 251: Fall 2019
// Project #04
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cassert>

#include "avl.h"
#include "util.h"

using namespace std;


//
// tokenize
//
// Given a string, breaks the string into individual tokens (words) based
// on spaces between the tokens.  Returns the tokens back in a vector.
//
// Example: "select * from students" would be tokenized into a vector
// containing 4 strings:  "select", "*", "from", "students".
//
vector<string> tokenize(string line)
{
  vector<string> tokens;
  stringstream  stream(line);
  string token;

  while (getline(stream, token, ' '))
  {
    tokens.push_back(token);
  }

  return tokens;
}

// checks if the column specified in the query is a valid column or not
bool isValidColumn(vector<string>allColumns, int numColumns, string column)
{
	for(int i = 0; i < numColumns; i++)
	{
		if(allColumns[i] == column)
			return true;
	}
	return false;
} // ends isValidColumn()

// checks if the query is valid or not
bool isValidQuery(vector<string>tokens, vector<string>allColumns, int numColumns, string tablename)
{
	if (tokens[0] != "select" && tokens[0] !="exit")  
		cout << "Unknown query, ignored..." << endl;
	else if (tokens[0] == "select" && tokens[1] != "*" && !isValidColumn(allColumns,numColumns,tokens[1]))
		cout << "Invalid select column, ignored..." << endl;
	else if (tokens.size() == 2 || tokens[2] != "from")
		cout << "Invalid select query, ignored..." << endl;
	else if (tokens.size() == 3 || tablename != tokens[3])
		cout << "Invalid table name, ignored..." << endl;
	else if (tokens.size() == 4 || tokens[4] != "where")
		cout << "Unknown query, ignored..." << endl;
	else if (tokens.size() == 5 || !isValidColumn(allColumns,numColumns,tokens[5]))
		cout << "Invalid where column, ignored..." << endl;
	else if (tokens.size() == 6 || tokens[6] != "=")
		cout << "Unknown query, ignored...";
	else if (tokens.size() != 8)
		cout << "Unknown query, ignored..." << endl;
	else
	{
		return true;
	}
	return false;
} // ends isValidQuery()

// checks the query and displays only the required information
void displayReqInfo(vector<string> allColumns, string token, vector<string> values)
{
	if(token == "*") // prints all information
	{
		for(size_t i = 0; i < values.size(); i++)
		{
			cout << allColumns[i] << ": " << values[i] << endl;
		}
	} 
	else // prints specific information
	{
		for(size_t i = 0; i < allColumns.size(); i++)
		{
			if(allColumns[i] == token)
			{
				cout << allColumns[i] << ": " << values[i] << endl;
			}
		}
	}
	
} // ends displayReqInfo()


int main()
{
  string tablename; // = "students";

  cout << "Welcome to myDB, please enter tablename> ";
  getline(cin, tablename);

  cout << "Reading meta-data..." << endl;
  string   filename = tablename + ".meta";
  ifstream data(filename, ios::in | ios::binary);

  if (!data.good())
  {
    cout << "**Error: couldn't open data file '" << filename << "'." << endl;
  }

  string value;                    // value of a column
  string name;                     // name of a column
  int RecordSize;                  // length of a line
  int numColumns;                  // number of columns
 
  vector<string> columns;          // will contain the columns where avl tree needs to be made
  vector<string> allColumns;       // contains all the column names.
  vector<int> indexes;             // will contain indexes of the columns needed to be made into avl trees
  vector<string> avlValues;        // stores all the data grabbed by the avl search
  vector<streamoff> lsValues;      // stores all data grabbed by the linear search
  int sizeOfColumns = 0;           // number of avl trees to be made
  data >> RecordSize;              // contains the size of the record.
  data >> numColumns;              // contains the number of columns.
 
  for (int i = 0; i < numColumns; ++i)         // read values, one per column:
  {
	 data >> name;                             // reads the name of the column
     data >> value;                            // reads the value of that column
	 allColumns.push_back(name);
      if(value == "1")
	  {
		columns.push_back(name);
		indexes.push_back(i);
		sizeOfColumns++;
	  }
     
   }
//   Testing:
//   
//   for(int i = 0; i < sizeOfColumns; i++)
//   {
// 	  cout << columns[i] << endl;
//   }
//   for(int i = 0; i < sizeOfColumns; i++)
//   {
// 	  cout << indexes[i] << endl;
//   }
  cout << "Building index tree(s)..." << endl;

  // Opening the data file and building index tree(s)
  
  string   filename_1 = tablename + ".data";
  ifstream data_1(filename_1, ios::in | ios::binary);
	
  data_1.seekg(0, data_1.end);  // move to the end to get length of file:
  streamoff length = data_1.tellg();             // gets the length of file
  streamoff pos = 0;                             // first record at offset 0:
  string avlKey;                                 
  
	  
	  
  if (!data_1.good())
  {
    cout << "**Error: couldn't open data file '" << filename << "'." << endl;
  }
	
  // A vector of avl tree can be made to store # of avl trees.
  vector<avltree<string, streamoff>> myTree (sizeOfColumns);
	
  for(int i = 0; i < sizeOfColumns; i++)
  {
	  pos = 0;                             // first record at offset 0:
	  while(pos < length)
	  {
		  data_1.seekg(pos, data_1.beg);   // seeks to the start of next line
		  for(int j = 0; j < numColumns; j++)
		  {
			  data_1 >> avlKey; 
			  if(j == indexes[i])
			  {
				  myTree[i].insert(avlKey,pos); // populates the tree with key, value
// Testing :	  cout << "The key is: " << avlKey << ". The pos is: " << pos << "." << endl;
				  break; // no need to check further
			  }
		  }
		  pos += RecordSize; // move to next line
	  }
  }
//  Testing:
//  
// 	for(int i = 0; i < sizeOfColumns; i++)
// 	{
// 		myTree[i].inorder();
// 	}
	
	
	for(int i = 0; i < sizeOfColumns; i++)
	{
		cout << "Index column: " << columns[i] << endl;
		cout << "  Tree size: " << myTree[i].size() << endl;
		cout << "  Tree height: " << myTree[i].height() << endl;
	}
	
  //
  // Main loop to input and execute queries from the user:
  //
  string query;
  
  cout << endl;
  cout << "Enter query> ";
  getline(cin, query);

  while (query != "exit")
  {
    vector<string> tokens = tokenize(query);
    
	if(isValidQuery(tokens,allColumns,numColumns,tablename)) // if the query is valid, else automatically asks for the next query
	{
		if(isValidColumn(columns,sizeOfColumns,tokens[5])) // AVL search
		{
			// get the index of search column in the vector
			for(int i = 0; i < sizeOfColumns; i++)
			{
				if(columns[i] == tokens[5])
				{
					// define a streamoff pointer to store pointer to value from avl search
					streamoff* getPos;
					getPos = myTree[i].search(tokens[7]);
                    // if not found in the tree
					if(getPos == nullptr)
					{
						cout << "Not found..." << endl;
					}
					else
						displayReqInfo(allColumns,tokens[1],GetRecord(tablename, *getPos, numColumns));
					break;
				} // ends if()
				
			} // ends for()
		}
		else // Linear search
		{
			// get the index of search column in the vector
			for(int i = 0; i < numColumns; i++)
			{
				if(allColumns[i] == tokens[5])
				{
					lsValues = LinearSearch(tablename,RecordSize,numColumns,tokens[7],(i+1));
					break;
				}
			}
			
			// get each streamoff value from the vector, call GetRecord function and then call displayReqInfo for each found value
			// if nothing found in linear search
			if(lsValues.size() == 0)
			{
				cout << "Not found..." << endl;
			}
			else
			{   // displays information for every pos found
				for(size_t i = 0; i < lsValues.size(); i++)
				{
					displayReqInfo(allColumns,tokens[1],GetRecord(tablename, lsValues[i], numColumns));
				}
			}
			
		}
	} 
	cout << endl;
    cout << "Enter query> ";
    getline(cin, query);
  }

  //
  // done:
  //
  return 0;
}	