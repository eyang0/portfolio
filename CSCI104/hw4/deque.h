#ifndef DEQUE_H
#define DEQUE_H
#include <stdexcept>

/**
 * Implements a templated, array-based, 
 * double-ended queue.
 *
 * The Deque should allow for amortized O(1) 
 * insertion and removal from either end. 
 * It should dynamically resize, when it becomes
 * full, but never needs to shrink.  
 *
 * It should use a circular buffer approach
 * by tracking the "front" and "back" location.
 *
 */


template <typename T>
class Deque
{
 public:
  /* START - DO NOT CHANGE ANY OF THESE LINES */
  /**
   *  Default constructor 
   *   Create an array of size 1 by default
   */
  Deque();

  /**
   *  Default constructor 
   *   Create an array of the given capacity.
   */
  Deque(size_t capacity);

  /**
   *  Destructor
   */
  ~Deque();

  /**
   *  Returns the number of elements in the Deque. 
   *   - Must run in O(1)
   */
  size_t size() const;

  /**
   *  returns true if the deque is empty
   *   - Must run in O(1)
   */
  bool empty() const;

  /**
   *  returns  the i-th element from the front
   *   - Must run in O(1)
   *   - Must throw std::range_error if i is
   *      an invalid location
   */
  T& operator[](size_t i);

  /**
   *  returns  the i-th element from the front
   *   - Must run in O(1)
   *   - Must throw std::range_error if i is
   *      an invalid location
   */
  T const & operator[](size_t i) const;

  /**
   *  Inserts a new item at the back of the
   *  Deque
   *   - Must run in amortized O(1)
   */
  void push_back(const T& item);

  /**
   *  Inserts a new item at the front of the
   *  Deque
   *   - Must run in amortized O(1)
   */
  void push_front(const T& item);

  /**
   *  Removes the back item from the Deque
   *   - Must run in amortized O(1)
   *   - Simply return if the deque is empty
   */
  void pop_back();

  /**
   *  Removes the front item from the Deque
   *   - Must run in amortized O(1)
   *   - Simply return if the deque is empty
   */
  void pop_front();
  /* END - DO NOT CHANGE ANY OF THESE LINES */
 private:
  /* Add data members and private helper 
   * functions below 
   */

  //capacity of circular buffer
  size_t max_size;
  size_t front;
  size_t back;

  //array of the data
  T* data;
  
};

/* Implement each Deque<T> member function below 
 * taking care to meet the runtime requirements
 */


//Default constructor. Creates an array of size 1 by default
template <typename T>
Deque<T>::Deque() :
  max_size(1), front(0), back(0)
{
  data = new T[1];

}

  
//Default constructor. Creates an array of the given capacity.
template <typename T>
Deque<T>::Deque(size_t capacity) :
  front(0), back(0)
{
  if(capacity == 0)
  {
    max_size = 1;
  }
  else
  {
    max_size = capacity;
  }
  data = new T[max_size];
}


//Destructor
template <typename T>
Deque<T>::~Deque()
{
  /*while(front != back)
  {

  */
  delete [] data;
}



//Returns the number of elements in the Deque. 
template <typename T>
size_t Deque<T>::size() const
{  
  if(front > back)
  {
    return (max_size-front)+back;
  }
  else if(front < back)
  {
    return back-front;
  }
  else //if front and back are same, it is empty
  {
    return 0;
  }

}


//returns true if the deque is empty
template <typename T>
bool Deque<T>::empty() const
{
  return (front == back);
}


//returns the i-th element from the front
template <typename T>
T& Deque<T>::operator[](size_t i)
{
  if(i < 0 || i >= this->size())
  {
    throw std::range_error("Index is invalid");
  }
  return data[(front+i)%max_size];
}


//returns  the i-th element from the front
template <typename T>
T const & Deque<T>::operator[](size_t i) const
{
  if(i < 0 || i >= this->size())
  {
    throw std::range_error("Index is invalid");
  }
  return data[(front+i)%max_size];
}



//Inserts a new item at the back of the Deque
template <typename T>
void Deque<T>::push_back(const T& item)
{

  //dynamically resizing if necessary 
  size_t current_size = this->size();
  if(current_size+1 == max_size)
  {
    max_size = 2*max_size;
    T* temp = data;
    data = new T[max_size];

    //copy over data
    for(size_t i = 0; i < current_size; i++)
    {
      data[i] = temp[(front+i)%current_size];
    }
    front = 0;
    back = current_size;

    //deallocate old data
    delete [] temp;
  }

  //insert the item at the back
  data[back] = item;
  back = (back + 1) % max_size;
}



//Inserts a new item at the front of the Deque
template <typename T>
void Deque<T>::push_front(const T& item)
{
  //dynamically resizing if necessary 
  size_t current_size = this->size();
  if(current_size+1 == max_size)
  {
    max_size = 2*max_size;
    T* temp = data;
    data = new T[max_size];

    //copy over data
    for(size_t i = 0; i < current_size; i++)
    {
      data[i] = temp[(front+i)%current_size];
    }
    front = 0;
    back = current_size;

    //deallocate old data
    delete [] temp;
  }

  //insert the item at the front
  front = (front-1) % max_size;
  data[front] = item;
}


//Removes the back item from the Deque
template <typename T>
void Deque<T>::pop_back()
{
  //if deque is empty, just return
  if(front == back)
  {
    return;
  }
  back = (back - 1) % max_size;

}


//Removes the front item from the Deque
template <typename T>
void Deque<T>::pop_front()
{
  //if deque is empty, just return
  if(front == back)
  {
    return;
  }
  front = (front + 1) % max_size;
}



#endif
