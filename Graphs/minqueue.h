/*minqueue.h*/

//
// Min queue that stores (key, value) pairs using a min-heap 
// implementation.  When pop is called, the key from the 
// (key, value) pair with the smallest value is returned; if 
// two pairs have the same value, the smaller key is returned.
// Push and pop have O(lgN) time complexity.
//
// << Shaan Shekhar >>
//
// Original author: Prof. Joe Hummel
// U. of Illinois, Chicago
// CS 251: Fall 2019
// Project #07
//

#pragma once

#include <iostream>
#include <vector>
#include <exception>
#include <stdexcept>
#include <map>
using namespace std;


template<typename TKey, typename TValue>

class minqueue
{
private:
  struct NODE
  {
    TKey    Key;
    TValue  Value;
  };

 NODE* treeArray;
 int Capacity;
 int currentUse;
 map<TKey,int> keyIndex;
public:

  //
  // default constructor:
  //
  // Queue has a max capacity for efficient implementation.
  // This max capacity must be specified at queue creation.
  //
  minqueue(int capacity)
  {
    //
    // TODO:
    //
    treeArray = new NODE[capacity];
	Capacity = capacity;
	currentUse = 0;
  }
  
  //
  // fill constructor:
  //
  // This allows for the efficient O(N) construction of
  // a queue with an initial set of keys, all with the same
  // initial value.  The max capacity of the queue is 
  // set to the # of keys provided for initialization;
  // it is assumed the keys are in ascending order.
  //
  minqueue(vector<TKey> keys, TValue initialValue)
  {
    //
    // TODO:
    //
    Capacity = keys.size();
    for(size_t i = 0; i < keys.size(); i++)
	{
		treeArray[i].Key = keys[i];
		treeArray[i].Value = initialValue;
		keyIndex[keys[i]] = i;
	}
	currentUse = keys.size();
	
	

  }
  
  
  //
  // destructor:
  //
  virtual ~minqueue()
  {
    //
    // TODO:
    //
    delete[] treeArray;
  }
  
  void swap(int parentIndex, int nodeIndex)
  {
    keyIndex.find(treeArray[parentIndex].Key)->second = nodeIndex; // gets the indexes of the reqiured 
    keyIndex.find(treeArray[nodeIndex].Key)->second = parentIndex; // gets the indexes of the reqiured 
   
	auto temp = treeArray[parentIndex];
    treeArray[parentIndex] = treeArray[nodeIndex];
    treeArray[nodeIndex] = temp;
  }
  //
  // empty:
  //
  // Returns true if empty, false if not.
  //
  bool empty()
  {
	  if(currentUse == 0)
		  return true;
	  return false;
  }

	
  void siftUp(int nodeIndex)
  {
	  int parentIndex = (nodeIndex-1)/2;

	  
	  if(parentIndex < 0) // if parent does not exists
		  return;
	  if(nodeIndex != 0)
	  {

		  if((treeArray[parentIndex].Value > treeArray[nodeIndex].Value)||
			 (treeArray[parentIndex].Key > treeArray[nodeIndex].Key && treeArray[parentIndex].Value == treeArray[nodeIndex].Value))
		  {
			  swap(parentIndex, nodeIndex);
			  siftUp(parentIndex);
		  }
	  }
  }


void doDelete(TKey key, TValue value){
		
		int p = keyIndex.find(key)->second; // get the index of the current : Step 1

		

		int lastPosition = currentUse-1;
		
		
		if(p==lastPosition){
		 currentUse--;
		 return;
		}

		
		swap(p, lastPosition);   // swap with the last index : Step 2

		
		currentUse--;           // Step 3

		int minIndex;
		int leftChild = 2*p+1;
		int rightChild = 2*p+2;
		int parentIndex = (p-1)/2;
		if(p > 0)               // siftUp and down conditions : remaining steps
		{
			
			if(treeArray[parentIndex].Value >= treeArray[p].Value){
				siftUp(p);
			}
		}

		if(rightChild >= currentUse) 
		{
			if(leftChild >= currentUse)
				return;
		else
			minIndex = leftChild;

	}
	
	else {
		if(treeArray[leftChild].Value < treeArray[rightChild].Value)
			minIndex = leftChild;
			
		else if(treeArray[leftChild].Value == treeArray[rightChild].Value)
		{
			if(treeArray[leftChild].Key > treeArray[rightChild].Key)
			{
				minIndex = rightChild;
			}
			else
			{
				minIndex = leftChild;
			}
		}
		else
			minIndex = rightChild;

	}
	

			if (treeArray[p].Value > treeArray[minIndex].Value)
			{
				siftDown(p);
			}
			else if (treeArray[p].Value == treeArray[minIndex].Value && treeArray[p].Key > treeArray[minIndex].Key)
			{
				siftDown(p);
			}

		return;
   
  }
 
// void getMinIndex(int leftChildIndex,int rightChildIndex, int &minIndex, bool &changed){
	
// }






  //
  // push:
  //
  // Inserts the given (key, value) pair into the queue such that 
  // pop always returns the pair with the minimum value.  If the 
  // key is *already* in the queue, it's value is updated to the
  // given value and the queue reordered.  If the key is not in
  // the queue, the (key, value) pairs is added and the queue
  // reordered.
  //
  // NOTE: if two keys have the same value, i.e. (key1, value) and
  // (key2, value), then those pairs are ordered into ascending value
  // by their key.
  //
  void pushinorder(TKey key, TValue value)
  {
	
		
// 		Approach 2
    
	if(keyIndex.find(key) != keyIndex.end())
	{
		doDelete(key,value);
		keyIndex.erase(key);
		pushinorder(key, value);
	}
    else if (Capacity == currentUse)
    {
     throw runtime_error("minqueue::pushinorder: queue full");
    }
	else
	{
		currentUse++;
		treeArray[currentUse-1].Key = key;
		treeArray[currentUse-1].Value = value;
		keyIndex[key] = currentUse-1;
		siftUp(currentUse-1);
	}
	

    
  }


  //
  // front:
  //
  // Returns the key at the front of the queue; does *not* pop the 
  // (key, value) pair.  Throws a logic_error exception if the queue
  // is empty.
  //
  TKey minfront()
  {
    if (empty())
    {
      throw logic_error("minqueue::minfront: queue empty");
    }
    
    //
    // TODO:
    //
    return treeArray[0].Key;
  }


  void siftDown(int nodeIndex)
  {
	  int leftChild = 2*nodeIndex + 1;
	  int rightChild = 2*nodeIndex + 2;
	  int minIndex;
// 	  auto tmp;
// 	  TKey TempKey;
// 	  TValue TempValue;
	  
// 	  if(leftChild > currentUse || rightChild > currentUse)
// 		  return;
// 	  check if there is any left or right index. //--TODO--//
	  
	  if(rightChild >= currentUse)
	  {
		  if(leftChild >= currentUse)
			  return;
		  else
			  minIndex = leftChild;
	  }
	  else 
	  {
		  if((treeArray[leftChild].Value < treeArray[rightChild].Value) ||
			  (treeArray[leftChild].Value == treeArray[rightChild].Value && treeArray[leftChild].Key < treeArray[rightChild].Key))
			  minIndex = leftChild;
		  else if(treeArray[leftChild].Value > treeArray[rightChild].Value)
			  minIndex = rightChild;
		  else
			  minIndex = rightChild;
	   }
	   

	   
	   if((treeArray[nodeIndex].Value > treeArray[minIndex].Value) ||
		   (treeArray[nodeIndex].Key > treeArray[minIndex].Key && treeArray[nodeIndex].Value == treeArray[nodeIndex].Value))
	   {
// 		   TempKey = treeArray[minIndex].Key;
// 		   TempValue = treeArray[minIndex].Value;
// 		   treeArray[minIndex].Key = treeArray[nodeIndex].Key;
// 		   treeArray[minIndex].Value = treeArray[nodeIndex].Value;
// 		   treeArray[nodeIndex].Key = TempKey;
// 		   treeArray[nodeIndex].Value = TempValue;
// // 		   update the tree with new (key, value) pair
// 		   keyIndex[treeArray[nodeIndex].Key] = nodeIndex;
// 		   keyIndex[treeArray[minIndex].Key] = minIndex;
		   swap(nodeIndex, minIndex);
// 		   recursive call to itself
// 		   cout << "minIndex value: " << minIndex << endl;
		   siftDown(minIndex);
	   }
	  
  }

  //
  // pop:
  //
  // Pops and discards the (key, value) pair at the front of the queue.
  // Throws a logic_error exception if the queue is empty.
  //
  void minpop()
  {
    if (empty())
    {
      throw logic_error("minqueue::minpop: queue empty");
    }
    else
	{
		treeArray[0] = treeArray[currentUse-1];
		keyIndex[treeArray[0].Key] = 0;
		currentUse--;
		if(currentUse > 0)
			siftDown(0);
	}
    //
    // TODO:
    //
    
  }

};