#include <vector>

//heapify() helper function
// loc - Location to start the heapify() process
// effsize - Effective size (number of items in the vector that
//           are part of the heap). Useful for performing heap-sort in place.
template <typename T, typename Comparator>
void heapify(std::vector<T>& data, size_t loc, size_t effsize, Comparator& c)
{
	//if effecive size is empty
	if(effsize == 0)
	{
		return;
	}
	//if it is a leaf node
	if(2*loc+1 > effsize-1)
	{
		return;
	}
	int betterChild = 2*loc+1; //start with left child as best
	if(2*loc+2 < effsize) //if right child exists
	{
		int rChild = betterChild+1;
		if(c(data[rChild], data[betterChild]))
		{
			betterChild = rChild;
		}
	}
	//if the best child is better than current node
	if(c(data[betterChild], data[loc]))
	{
		//swap them
		T temp = data[loc];
		data[loc] = data[betterChild];
		data[betterChild] = temp;
		heapify(data, betterChild, effsize, c);
	}
}



template <typename T, typename Comparator>
void hsort(std::vector<T>& data, Comparator c = Comparator())
{
	size_t full_size = data.size();
	
	//if vector is empty or size of 1, already sorted so return
	if(full_size == 0 || full_size == 1)
	{
		return;
	}

	//starting at last node's parent, converting array to valid heap in theta(n)
	for(int i = (full_size-2)/2; i >= 0; i--)
	{
		heapify(data, i, full_size, c);
	}

	//sorting (reversed) in nlogn
	for(unsigned int j = 0; j < full_size-1; j++)
	{
		T to_pop = data[0];
		data[0] = data[full_size-1-j]; //bring last from heap to front
		data[full_size-1-j] = to_pop; //add 'popped' to sorted area
		heapify(data, 0, full_size-1-j, c); //heapify top of the remaining heap
	}

	//now reverse the array in linear time to get proper order
	int front = 0;
	int back = full_size-1;
	while(front < back)
	{
		T temp = data[front];
		data[front] = data[back];
		data[back] = temp;
		front++;
		back--;
	}

}

