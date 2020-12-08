
/*bsh.h*/

//
// Binary search tree
//

#pragma once

#include <iostream>
#include <algorithm>  // std::max

using namespace std;

template<typename TKey, typename TValue>
class binarysearchtree
{
private:
  struct NODE
  {
    TKey Key;
	TValue Value;
	NODE* Left;
	NODE* Right;;
  };

  NODE* Root;  // pointer to root node of tree (nullptr if empty)
  int   Size;  // # of nodes in the tree (0 if empty)
  
  // 
  // _inorder does the actual inorder traversal and output 
  // to console.  Eacah key is output to the console followed
  // by " ", including the last key.
  //
  void _inorder(NODE* cur)
  {
     if (cur == nullptr)
       return;
     else
     {
        _inorder(cur->Left);
        cout << cur->Key << " ";
        _inorder(cur->Right);
     }
  }
  
  int _height(NODE* cur) {
     
     int heightL = -1;
     int heightR = -1;
  if (cur == nullptr)
   return 0;
  else
  {
     heightL = _height(cur->Left); 
     heightR = _height(cur->Right);
     if (heightL > heightR)
     return (heightL + 1);
     else return (heightR + 1);
     }
   }
   
// copy constructor helper function 
  void _copy(const NODE *other)
  {
	  if(other != nullptr)
	  {
	  insert(other->Key,other->Value);
	  }
	  if(other->Left != NULL)
	  {
	  _copy(other->Left);
	  }
	  if(other->Right != NULL)
	  {
	  _copy(other->Right);
	  }
  }
  

public:
  //
  // default constructor:
  //
  // Creates an empty tree.
  //
  binarysearchtree()
  {
    Root = nullptr;
    Size = 0;
  }

  // copy constructor
  binarysearchtree( binarysearchtree& other)
  {
	  Root = nullptr;
	  Size = 0;
	  if(other.Root != nullptr)
	  {
	    _copy(other.Root);
	  }
  }
  

  // 
  // size:
  //
  // Returns the # of nodes in the tree, 0 if empty.
  //
  int size()
  {
    return Size;
  }

  //
  // height
  //
  // Computes and returns height of tree; height of an empty tree is
  // defined as -1.
  //
  int height()
  { 
    return (_height(Root)-1);
  }

  // 
  // search:
  //
  // Searches the tree for the given key, returning true if found
  // and false if not.
  //
  TValue* search(TKey key)
  {
    NODE* cur = Root;

    while (cur != nullptr)
    {
      if (key == cur->Key)  // already in tree
        return &(cur -> Value);

      if (key < cur->Key)  // search left:
      {
        cur = cur->Left;
      }
      else
      {
        cur = cur->Right;
      }
    }//while  
  
    // if get here, not found
    return nullptr;
  }

  //
  // insert
  //
  // Inserts the given key into the tree; if the key has already been insert then
  // the function returns without changing the tree.
  //
  void insert(TKey key, TValue value)
  {
    NODE* prev = nullptr;
    NODE* cur = Root;

    //
    // 1. Search to see if tree already contains key:
    //
    while (cur != nullptr)
    {
      if (key == cur->Key)  // already in tree
        return;

      if (key < cur->Key)  // search left:
      {
        prev = cur;
        cur = cur->Left;
      }
      else
      {
        prev = cur;
        cur = cur->Right;
      }
    }//while

    //
    // 2. if we get here, key is not in tree, so allocate
    // a new node to insert:
    // 
   NODE* toInsert = new NODE();
  
    toInsert -> Key = key;
    toInsert -> Left = nullptr;
    toInsert -> Right = nullptr;
	toInsert -> Value = value;

    //
    // 3. link in the new node:
    //
    // NOTE: cur is null, and prev denotes node where
    // we fell out of the tree.  if prev is null, then
    // the tree is empty and the Root pointer needs 
    // to be updated.
    //
      if(cur == nullptr && prev == nullptr)
      {
         Root = toInsert;
      }
      
      else if(key < prev -> Key)
      {
       prev -> Left = toInsert;  
      }
      else
      {
       prev -> Right = toInsert;  
      }
	  // 4. update size and we're done:
      Size++;
  }

  //
  // inorder:
  //
  // Performs an inorder traversal of the tree, outputting
  // the keys to the console.
  //
  void inorder()
  {
     cout << "Inorder: ";
     
     _inorder(Root);
     
     cout << endl;
  }

};

