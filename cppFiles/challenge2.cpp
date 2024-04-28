#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>


void newSwap(std::vector<int>& vect, int i, int j) //swap two elements in a vector
{
    int temp = vect[i];
    vect[i] = vect[j];
    vect[j] = temp;
}


void fillArray(int size, std::vector<int> &array) //fill ordered vector of int
{
    for (int i = 0; i < size; ++i) {
        array.push_back(i);
    }
}


void fillArrayWithDuplicates(int size, std::vector<int> &array) 
{
    for (int i = 0; i < size; ++i) {
        array.push_back(i % 10);
    }
}


void fillArrayWithOnes(int size, std::vector<int> &array) //creat ordered vector of int
{
    for (int i = 0; i < size; ++i) {
        array.push_back(1);
    }
}

void fillOppositeArray(int size, std::vector<int> &array) //creat ordered vector of int
{
    for (int i = size; i > 0; --i) {
        array.push_back(i);
    }
}


void printArray(std::vector<int> &array) //array print
{
    for (int i = 0; i < array.size(); ++i) 
    {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}


void shuffleArray(std::vector<int> &array, int seed) //array shuffle
{
    std::shuffle(array.begin(), array.end(), std::default_random_engine(seed));
}


int randomPivot(int p, int q) //select random pivot
{
    return rand() % (q - p + 1) + p;
}


int rand_partition(std::vector<int> &a, int p, int q) //randomly partition the array
{
    int r = randomPivot(p, q); //Select a random pivot element
    newSwap(a, r, q);
    int x = a[q];
    int i = p - 1;

    for (int j = p; j < q; ++j) //Partition the array around the pivot element
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


int rand_select(std::vector<int> &a, int p, int q, int i) //Function to find the i-th smallest element in the array with random pivot
{
    if (p == q) // Base case: If the array has only one element
        return a[p];

    int r = rand_partition(a, p, q); //Partition the array and find the rank of the pivot element
    int k = r - p + 1;

    if (i == k) // If the rank of the pivot element is equal to i, return the pivot element
        return a[r];

    else if (i < k) // If the rank of the pivot element is greater than i, recursively find the i-th smallest element in the left subarray
        return rand_select(a, p, r - 1, i);

    else // If the rank of the pivot element is less than i, recursively find the (i-k)-th smallest element in the right subarray
        return rand_select(a, r + 1, q, i - k);
}


void moveElement(std::vector<int>& vect, int fromIndex, int toIndex) 
{
    int valueToMove = vect[fromIndex]; // Temporarily store the element to be moved
    if (fromIndex < toIndex) // Move elements to the right
    {
        for (int i = fromIndex; i < toIndex; ++i)
        {
            vect[i] = vect[i + 1];
        }
    }  
    else // Move elements to the left
    {
        for (int i = fromIndex; i > toIndex; --i)
        {
            vect[i] = vect[i - 1];
        }
    }

    vect[toIndex] = valueToMove; // Place the element at the new position
}


int bubbleSort(std::vector<int>& values, std::vector<int>& index, int block) //Bubble sort for 5 elements
{
    for( int i = 0; i < 5-1; i++)
    {
        for(int j = 0; j < 5-i-1; j++)
        {
            if(values[index[j+5*block]] > values[index[j+1+ 5*block]])
            {
                std::swap(index[j+5*block], index[j+1+ 5*block]);
            }
        }
    }
    return index[2+5*block];
}


int newSort(std::vector<int> &vect, std::vector<int> &index, int i) //Sorting 5 entries vector (efficient in this case)
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


int median(std::vector<int>& vect, std::vector<int>& index) //finding index of median of medians
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
    /*std::cout <<"r: " << r << std::endl;
    std::cout << "p: " << p << std::endl;
    std::cout << "q: " << q << std::endl;
    std::cout << "i - k: " << i - (r - p + 1) << std::endl;
    
    std::cout <<"k: " << (r - p + 1) << std::endl;
    std::cout << std::endl;*/

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






#define N 1000
#define seed 17049


int main(int argc, char** argv)
{
    int z = 0;
    
    for ( int M = N-1; M < N; M++)
    {
        std::cout << "M: " << M <<"/" <<N <<std::endl;
        for(int i = M/3; i <= M; i++)
        {
            //std:: cout << "M: " << M << " i: " << i << std::endl;
            std::vector<int> array;
            fillArray(M, array);
            //fillOppositeArray(M, array);
            // array.push_back(100);

            // std::sort(array.begin(), array.end());
            // printArray(array);
            // std::cout << "The " << i << "th smallest element is " << array[i - 1] << std::endl;


            shuffleArray(array, seed);
            //printArray(array);
            std::vector<int> array2 = array;


            //add chrono
            auto start1 = std::chrono::high_resolution_clock::now();
            int x = rand_select(array, 0, M - 1, i);
            //std::cout << "randSelect: The " << i << "the smallest element is " << x << std::endl;
            auto end1 = std::chrono::high_resolution_clock::now();
            auto duration1 = std::chrono::duration_cast<std::chrono::nanoseconds>(end1 - start1);
            std::cout <<std::endl << "rand_select duration: " << duration1.count() << std::endl;

            //std::cout << std::endl;
            //printArray(array2);

            auto start2 = std::chrono::high_resolution_clock::now();
            int y = quickSelect(array2, 0, M-1, i);
            //std::cout << "quickSelect: The " << i << "th smallest element is " <<y << std::endl;
            auto end2 = std::chrono::high_resolution_clock::now();
            auto duration2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - start2);
            std::cout << "quickSelect duration: " << duration2.count() << std::endl;
            
            if (x!= y)
            {
               std::cout << -1;
               std:: cout << "    M: " << M << " i: " << i << std::endl;
               std::cout<<std::endl;
            }
        }
      
    }
}