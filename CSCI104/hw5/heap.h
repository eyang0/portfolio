#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
 public:
  /// Constructs an m-ary heap for any m >= 2
  Heap(int m, PComparator c = PComparator());

  /// Destructor as needed
  ~Heap();

  /// Adds an item
  void push(const T& item);

  /// returns the element at the top of the heap 
  ///  max (if max-heap) or min (if min-heap)
  T const & top() const;

  /// Removes the top element
  void pop();

  /// returns true if the heap is empty
  bool empty() const;

 private:
  /// Add whatever helper functions and data members you need below

  void heapify(size_t loc);
  void trickleUp(size_t loc);

  std::vector<T> _data; //vector to hold the data
  int m_ary; //to hold m
  PComparator comp; //to hold the comparator


};

// Add implementation of member functions here

//constructor
template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c)
  : m_ary(m), comp(c)
{

}

//destructor
template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap()
{
  
}

//trickeUp helper functions
template <typename T, typename PComparator>
void Heap<T,PComparator>::trickleUp(size_t loc)
{
  if(loc == 0) //if there is only one item in heap
  {
    return;
  }
  int parent = (loc-1)/m_ary;
  while(parent >= 0 && comp(_data[loc], _data[parent]))
  {
    T temp = _data[parent];
    _data[parent] = _data[loc];
    _data[loc] = temp;
    loc = parent; //change loc with the movement of the node
    if(loc == 0) //if we are now at the root node, we are done
    {
      break;
    }
    parent = (loc-1)/m_ary; //get the next parent
  }
}


template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item)
{
  //adds to bottom right
  _data.push_back(item);
  //trickleUp on the new item
  trickleUp(_data.size()-1);

}


//heapify() helper function
// loc - Location to start the heapify() process
template <typename T, typename PComparator>
void Heap<T,PComparator>::heapify(size_t loc)
{
  size_t size = _data.size();
  //if size is empty
  if(size == 0)
  {
    return;
  }
  //if it is a leaf node
  if(m_ary*loc+1 > size-1)
  {
    return;
  }
  int bestChild = m_ary*loc+1; //start with left-most child as best
  //getting the best child
  for(int i = 1; i < m_ary; i++)
  {
    if(!(m_ary*loc+1+i < size)) //if child one to the right doesn't exist
    {
      break;
    }
    else //if child one to the right exists
    {
      int nextChild = m_ary*loc+1+i;
      if(comp(_data[nextChild], _data[bestChild])) 
      {
        bestChild = nextChild;
      }
    }
  }
  //if the best child is better than current node
  if(comp(_data[bestChild], _data[loc]))
  {
    //swap them
    T temp = _data[loc];
    _data[loc] = _data[bestChild];
    _data[bestChild] = temp;
    heapify(bestChild);
  }
}


// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    throw std::logic_error("can't top an empty heap");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return _data[0];

}


template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    throw std::logic_error("can't pop an empty heap");
  }
  else if(_data.size() == 1)
  {
    _data.pop_back();
  }
  else
  {
    _data[0] = _data.back();
    _data.pop_back();
    heapify(0);
  }
}

template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const
{
  return _data.empty();
}



#endif

