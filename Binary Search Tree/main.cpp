//
// <<Shaan Shekhar>>
// U. of Illinois, Chicago
// CS 251: Fall 2019
//
// Project #02: inputs movies and reviews, allowing the user to search
// by movie ID, movie Name, or review ID.  Uses binary search trees for 
// fast search; no other data structures are allowed.
//

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#include "bst.h" //includes the bst file

// Object to store data inside the binary search tree
struct MovieData
  {
	string MovieName;
    int PubYear;         // stores the publication year of the movie
	int MovieID;         // stores the id of the movie in the text file  
	int Num5Stars = 0;   // stores 5 stars rating on the movie
	int Num4Stars = 0;   // stores 4 stars rating on the movie
	int Num3Stars = 0;   // stores 3 stars rating on the movie
	int Num2Stars = 0;   // stores 2 stars rating on the movie
	int Num1Stars = 0;   // stores 1 star rating on the movie
  };

//
// trim
//
// trims whitespace from beginning and end of string.
//
// Ref: https://stackoverflow.com/questions/25829143/trim-whitespace-from-a-string
// Modified: to handle empty strings, and strings of all blanks.
//
string trim(const string& str)
{
  size_t first = str.find_first_not_of(" \t\n\r");
  size_t last = str.find_last_not_of(" \t\n\r");

  if (first == string::npos && last == string::npos)  // empty, or all blanks:
    return "";
  else if (first == string::npos)  // no blanks at the start:
    first = 0;                     // 0-based
  else if (last == string::npos)   // no blanks trailing at end:
    last = str.length() - 1;       // 0-based

  return str.substr(first, (last - first + 1));
}


//
// InputMovies
//
// Inputs the data from the "movies" file, which contains N>0 lines, where
// each line contains: id pubYear name
//
int InputMovies(binarysearchtree<int,MovieData>&bstMoviesByID,binarysearchtree<string,MovieData>&bstMoviesByName,string moviesFilename)
{
  ifstream moviesFile(moviesFilename);
  int       id, pubYear, count = 0; // variables to store id, publication year and the number of inputs from the file
  string    name;                   // stores the movie name 
  MovieData chaseData;              // object to be added to the tree
  
  // check if the file is there or not
  if (!moviesFile.good())
  {
    cout << "**Error: unable to open movies file '" << moviesFilename << "', exiting" << endl;
    return -1;
  }

  moviesFile >> id;  // get first ID, or set EOF flag if file empty:
  

  while (!moviesFile.eof())
  {
    // we have more data, so input publication year and movie name:
    chaseData.MovieID = id; // stores the movie id to the id portion of the object
    moviesFile >> pubYear;  // reads the publication year of the movie 
	chaseData.PubYear = pubYear; // stores the publication year of the movie in the portion of the object
    getline(moviesFile, name);  // movie name fills rest of input line:

    // trim potential whitespace from both ends of movie name:
    name = trim(name); 
	chaseData.MovieName = name; // stores the movie name in the name portion of the object
	bstMoviesByID.insert(id, chaseData); // inserts the node in the main binary search tree
	bstMoviesByName.insert(name, chaseData); // inserts the node in the main binary search tree
	count++; 

    // debugging:
//     cout << id << "," << pubYear << "," << name << endl;

    moviesFile >> id;  // get next ID, or set EOF flag if no more data:
  }
	return count;
}


void intAverageValue(binarysearchtree<int,MovieData>&bstMoviesByID,int movieID)
{
	// stores the total sum of the ratings
	int reviewSum = (5*(bstMoviesByID.search(movieID)->Num5Stars) + 
					4*(bstMoviesByID.search(movieID)->Num4Stars) +
					3*(bstMoviesByID.search(movieID)->Num3Stars) +
					2*(bstMoviesByID.search(movieID)->Num2Stars) +
					1*(bstMoviesByID.search(movieID)->Num1Stars));
	// stores the total number of the reviews in the reviews text file
	int totalReviews =((bstMoviesByID.search(movieID)->Num5Stars) + 
					(bstMoviesByID.search(movieID)->Num4Stars) +
					(bstMoviesByID.search(movieID)->Num3Stars) +
					(bstMoviesByID.search(movieID)->Num2Stars) +
					(bstMoviesByID.search(movieID)->Num1Stars));
	if(totalReviews == 0)
	{
		cout << totalReviews << endl;
	}
	else
	{
		cout << (double)reviewSum / (double)totalReviews << endl; // prints double average value of the movie
	}

}

int InputReviews(binarysearchtree<int,MovieData>&bstMoviesByID,binarysearchtree<string,MovieData>&bstMoviesByName,string reviewsFilename)
{
  ifstream reviewsFile(reviewsFilename);
  int      reviewID, movieID, rating, count = 0; // variables store movie ID, review ID, movie rating and number of reviews in file
// check if the file is good
  if (!reviewsFile.good())
  {
    cout << "**Error: unable to open review file '" << reviewsFilename << "', exiting" << endl;
    return -1;
  }

  reviewsFile >> reviewID;  // get first ID, or set EOF flag if file empty:

  while (!reviewsFile.eof())
  {
	reviewsFile >> movieID; // reads the movie ID of the movie
	reviewsFile >> rating; // reads the rating of the movie
	switch(rating)
	{
	  case 1:
		 bstMoviesByID.search(movieID)->Num1Stars++; // increments number of 1 movie stars rating
		 bstMoviesByName.search(bstMoviesByID.search(movieID)->MovieName)->Num1Stars++; // similar update in the second tree
		 break;
	  case 2:
		 bstMoviesByID.search(movieID)->Num2Stars++; // increments number of 2 movie stars rating
		 bstMoviesByName.search(bstMoviesByID.search(movieID)->MovieName)->Num2Stars++; // similar update in the second tree
		 break;
	  case 3:
		 bstMoviesByID.search(movieID)->Num3Stars++; // increments number of 3 movie stars rating
		 bstMoviesByName.search(bstMoviesByID.search(movieID)->MovieName)->Num3Stars++; // similar update in the second tree
		 break;
	  case 4:
		 bstMoviesByID.search(movieID)->Num4Stars++; // increments number of 4 movie stars rating
		 bstMoviesByName.search(bstMoviesByID.search(movieID)->MovieName)->Num4Stars++; // similar update in the second tree
		 break;
	  case 5:
		 bstMoviesByID.search(movieID)->Num5Stars++; // increments number of 5 movie stars rating
		 bstMoviesByName.search(bstMoviesByID.search(movieID)->MovieName)->Num5Stars++; // similar update in the second tree
		 break;
	}
	count++;
    reviewsFile >> reviewID;  // get next ID, or set EOF flag if no more data:
  }
	return count;
}

// displays the movie name, movie id, movie star ratings for the required movie
void IntOutputContent(binarysearchtree<int,MovieData>&bstMoviesByID,int movieID)
{
// 	if movie is not found in the file
	if(bstMoviesByID.search(movieID) == nullptr)
	{
		cout << "not found..." << endl << endl;
	}
	else
	{
		cout << "Movie ID: "<<bstMoviesByID.search(movieID)->MovieID<<endl;     // prints the id of the movie
		cout << "Movie Name: "<<bstMoviesByID.search(movieID)->MovieName<<endl; // prints the movie name
		cout << "Avg rating: ";
		intAverageValue(bstMoviesByID,movieID);                                 // prints the average movie rating
		cout << "5 stars: "<<bstMoviesByID.search(movieID)->Num5Stars<<endl;    // prints number of 5 stars ratings
		cout << "4 stars: "<<bstMoviesByID.search(movieID)->Num4Stars<<endl;    // prints number of 4 stars ratings
		cout << "3 stars: "<<bstMoviesByID.search(movieID)->Num3Stars<<endl;    // prints number of 3 stars ratings
		cout << "2 stars: "<<bstMoviesByID.search(movieID)->Num2Stars<<endl;    // prints number of 2 stars ratings
		cout << "1 star: "<<bstMoviesByID.search(movieID)->Num1Stars<<endl<<endl; // prints number of 1 stars ratings
	}
}


//
// main
//
int main()
{
  binarysearchtree<int,MovieData>bstMoviesByID;       // binary search tree, stores movies with ID 
  binarysearchtree<string,MovieData>bstMoviesByName;  // binary search tree, stores movies with name
	
  string moviesFilename; // = "movies1.txt";
  string reviewsFilename; // = "reviews1.txt";
  int movieCount = 0;     // stores number of movies in the movie file
  int reviewCount = 0;    // stores number of reviews in the review file
  string movieName;       // stores the input of the user
  cout << "movies file?> ";
  cin >> moviesFilename;  // takes in the movie file name

  cout << "reviews file?> ";
  cin >> reviewsFilename; // takes in the review file name 

  string junk;
  getline(cin, junk);  // discard EOL following last input:

  movieCount = InputMovies(bstMoviesByID,bstMoviesByName,moviesFilename); // function call returns the number of movies in the file
  reviewCount = InputReviews(bstMoviesByID,bstMoviesByName,reviewsFilename); // function call returns the number of reviews in the review file
  // Basic infornmation display   
  cout << "Num movies: " << movieCount << endl;
  cout << "Num reviews: " << reviewCount << endl << endl;
  cout << "Tree by movie id: " << "size=" << bstMoviesByID.size() << ", height=" << bstMoviesByID.height() << endl;
  cout << "Tree by movie name: " << "size=" << bstMoviesByName.size() << ", height=" << bstMoviesByName.height() << endl << endl;
  // takes in user input for movie id or movie name
  cout << "Enter a movie id or name (or # to quit)> ";
  getline(cin,movieName); // takes in the whole string input indluding spaces between words
	
  int flag = 0; // helps in deciding when to call display function
	
  while(true)
  {
	if(movieName == "#")
	{
		break;
	}
	else
	{
		int i = 0;
		while(movieName[i] != '\0')
		{
			if(isalpha(movieName[i]))
			{
				if(bstMoviesByName.search(movieName)==nullptr) // if movie is not found in the file
				{
					cout << "not found..." << endl << endl;
				}
				else
				{
					int ID = bstMoviesByName.search(movieName)->MovieID; // takes in movie name and checks for movie id
					IntOutputContent(bstMoviesByID,ID); // function call to diaplay basic information about the movie
				}
				flag = 1; // so that the display function isn't called twice
				break;
			}
			i++;
		}

		if(flag == 0) // if the user input a movie id
		{
			IntOutputContent(bstMoviesByID,stoi(movieName)); // function call to diaplay basic information about the movie
		}
		cout << "Enter a movie id or name (or # to quit)> ";
		getline(cin,movieName); // takes in the whole string input indluding spaces between words
	}

	flag = 0; // reset the flag for next round of input
  }

  // done:
  return 0;
}
