#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

// Function to swap two elements in a vector
void newSwap(std::vector<int>& vect, int i, int j)
{
    int temp = vect[i];
    vect[i] = vect[j];
    vect[j] = temp;
}


// creat ordered vector of int
void fillArray(int size, std::vector<int> &array) {
    for (int i = 0; i < size; ++i) {
        array.push_back(i);
    }
}

// array print
void printArray(std::vector<int> &array) {
    for (int i = 0; i < array.size(); ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

// array shuffle
void shuffleArray(std::vector<int> &array, int seed) {
    std::shuffle(array.begin(), array.end(), std::default_random_engine(seed));
}

// select random pivot
int randomPivot(int p, int q) {
    return rand() % (q - p + 1) + p;
}

// Function to randomly partition the array
int rand_partition(std::vector<int> &a, int p, int q)
{
    // Select a random pivot element
    int r = randomPivot(p, q);
    newSwap(a, r, q);

    int x = a[q];
    int i = p - 1;

    // Partition the array around the pivot element
    for (int j = p; j < q; ++j)
    {
        if (a[j] <= x)
        {
            i++;
            newSwap(a, i, j);
        }
    }

    newSwap(a, i + 1, q);
    return i + 1;
}

// Function to find the i-th smallest element in the array with random pivot
int rand_select(std::vector<int> &a, int p, int q, int i)
{
    // Base case: If the array has only one element
    if (p == q)
        return a[p];

    // Partition the array and find the rank of the pivot element
    int r = rand_partition(a, p, q);
    int k = r - p + 1;

    // If the rank of the pivot element is equal to i, return the pivot element
    if (i == k)
        return a[r];
    // If the rank of the pivot element is greater than i, recursively find the i-th smallest element in the left subarray
    else if (i < k)
        return rand_select(a, p, r - 1, i);
    // If the rank of the pivot element is less than i, recursively find the (i-k)-th smallest element in the right subarray
    else
        return rand_select(a, r + 1, q, i - k);
}


void moveElement(std::vector<int>& vect, int fromIndex, int toIndex) {
        // Temporarily store the element to be moved
    int valueToMove = vect[fromIndex];

    // Move elements to the right
    if (fromIndex < toIndex)
    {
        for (int i = fromIndex; i < toIndex; ++i)
        {
            vect[i] = vect[i + 1];
        }
    }
    // Move elements to the left
    else
    {
        for (int i = fromIndex; i > toIndex; --i)
        {
            vect[i] = vect[i + 1];
        }
    }

    // Place the element at the new position
    vect[toIndex] = valueToMove;
}

// Sorting 5 entries vector (efficient in this case)
int newSort(std::vector<int> &vect, std::vector<int> &index, int i)
{
    i = 5 * i;  

    if (vect[index[i + 1]] < vect[index[i]])
    {
        std::swap(index[i], index[i + 1]);
    }
    if (vect[index[i + 3]] < vect[index[i + 2]])
    {
        std::swap(index[i + 2], index[i + 3]);
    }

    if (vect[index[i + 3]] < vect[index[i + 1]])
    {
        std::swap(index[i], index[i + 2]);
        std::swap(index[i + 1], index[i + 3]);
    }

    if (vect[index[i + 4]] < vect[index[i + 1]])
    {
        if (vect[index[i + 4]] < vect[index[i]])
        {
            moveElement(index, i + 4, i);
            newSwap(index, i + 4, i + 3);
        }
        else
        {
            moveElement(index, i + 4, i + 1);
            newSwap(index, i + 4, i + 3);
        }
    }
    else
    {
        if (vect[index[i + 4]] < vect[index[i + 3]])
        {
            moveElement(index, i + 4, i + 2);
            newSwap(index, i + 4, i + 3);
        }
        else
        {
            moveElement(index, i + 4, i + 3);
            newSwap(index, i + 4, i + 2);
        }
    }

    if (vect[index[i + 4]] < vect[index[i + 1]])
    {
        if (vect[index[i + 4]] < vect[index[i]])
        {
            moveElement(index, i + 4, i);
        }
        else
        {
            moveElement(index, i + 4, i + 1);
        }
    }
    else
    {
        if (vect[index[i + 4]] < vect[index[i + 2]])
        {
            moveElement(index, i + 4, i + 2);
        }
        else
        {
            moveElement(index, i + 4, i + 3);
        }
    }

    return index[i + 2];
}



int median(std::vector<int>& vect, std::vector<int>& index)
{
   if (index.size() < 5)
   {
       //cout <<"index size is less than 5" <<endl;
       int y = index.size()/2;
       //cout <<"y: " << y <<endl;
       //cout <<"index[y]: " << index[y] <<endl;
       return index[y];
   }
   int blocks = index.size()/5;
   std::vector<int> vect2;
   for(int i=0; i<blocks; ++i)
   {
    vect2.push_back(newSort(vect, index, i));
   } 
   //cout <<"vect2: ";
   //printVec(vect2);
   //printVec(vect2);
   return median(vect, vect2);

}


int newPartition (std::vector<int>& vect, int start, int end)
{
    std::vector<int> index;
    fillArray(end - start + 1, index);
    int r = median(vect, index) + start;
    int pivot_value = vect[r];
    newSwap(vect, start, r);
    int i = start;

    for (int j = start + 1; j <= end; ++j)
    {
        if (vect[j] < pivot_value)
        {
            i++;
            newSwap(vect, i, j);
        }
    }

    newSwap(vect, start, i);
    return i;
}



int quickSelect(std::vector<int>& vect, int p, int q, int i)
{
    if (p == q)
        return vect[p];


    int r = newPartition(vect, p, q);
    // std::cout <<"r: " << r << std::endl;
    

    int k = r - p + 1;

    if (i == k)
        return vect[r];
    else if (i < k)
        {   
            return quickSelect(vect, p, r - 1, i);
        } 
    else
        {
            return quickSelect(vect, r + 1, q, i - k);
        }      
}






#define N 1500000
#define seed 1049087
#define i (N - 1)

int main(int argc, char** argv)
{
    std::vector<int> array;
    fillArray(N, array);
    // printArray(array);
    std::cout << "The " << i << "th smallest element is " << array[i - 1] << std::endl;


    shuffleArray(array, seed);
    // printArray(array);
    std::vector<int> array2 = array;
    std::cout << "The " << i << "th smallest element is " << rand_select(array, 0, N - 1, i) << std::endl;

    std::cout << std::endl;
    // printArray(array2);
    std::cout << "The " << i << "th smallest element is " << quickSelect(array2, 0, N-1, i) << std::endl;



    return 0;    
}