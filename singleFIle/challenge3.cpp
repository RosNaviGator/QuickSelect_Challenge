#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>
#include <omp.h>



void newSwap(std::vector<int> &vect, int i, int j) // swap two elements in a vector
{
    int temp = vect[i];
    vect[i] = vect[j];
    vect[j] = temp;
}

void fillArray(int size, std::vector<int> &array) // fill ordered vector of int
{
    for (int i = 0; i < size; ++i)
    {
        array.push_back(i);
    }
}

void fillArrayWithDuplicates(int size, std::vector<int> &array)
{
    for (int i = 0; i < size; ++i)
    {
        array.push_back(i % 10);
    }
}

void fillArrayWithOnes(int size, std::vector<int> &array) // creat ordered vector of int
{
    for (int i = 0; i < size; ++i)
    {
        array.push_back(1);
    }
}

void fillOppositeArray(int size, std::vector<int> &array) // creat ordered vector of int
{
    for (int i = size; i > 0; --i)
    {
        array.push_back(i);
    }
}

void printArray(std::vector<int> &array) // array print
{
    for (int i = 0; i < array.size(); ++i)
    {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

void shuffleArray(std::vector<int> &array, int seed) // array shuffle
{
    std::shuffle(array.begin(), array.end(), std::default_random_engine(seed));
}

int randomPivot(int p, int q) // select random pivot
{
    return rand() % (q - p + 1) + p;
}

int rand_partition(std::vector<int> &a, int p, int q) // randomly partition the array
{
    int r = randomPivot(p, q); // Select a random pivot element
    newSwap(a, r, q);
    int x = a[q];
    int i = p - 1;

    for (int j = p; j < q; ++j) // Partition the array around the pivot element
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

int rand_select(std::vector<int> &a, int p, int q,
                int i) // Function to find the i-th smallest element in the array with random pivot
{
    if (p == q) // Base case: If the array has only one element
        return a[p];

    int r = rand_partition(a, p, q); // Partition the array and find the rank of the pivot element
    int k = r - p + 1;

    if (i == k) // If the rank of the pivot element is equal to i, return the pivot element
        return a[r];

    else if (i < k) // If the rank of the pivot element is greater than i, recursively find the i-th smallest element in
                    // the left subarray
        return rand_select(a, p, r - 1, i);

    else // If the rank of the pivot element is less than i, recursively find the (i-k)-th smallest element in the right
         // subarray
        return rand_select(a, r + 1, q, i - k);
}

void moveElement(std::vector<int> &vect, int fromIndex, int toIndex)
{
    int valueToMove = vect[fromIndex]; // Temporarily store the element to be moved
    if (fromIndex < toIndex)           // Move elements to the right
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

int bubbleSort(std::vector<int> &values, std::vector<int> &index, int block) // Bubble sort for 5 elements
{
    for (int i = 0; i < 5 - 1; i++)
    {
        for (int j = 0; j < 5 - i - 1; j++)
        {
            if (values[index[j + 5 * block]] > values[index[j + 1 + 5 * block]])
            {
                std::swap(index[j + 5 * block], index[j + 1 + 5 * block]);
            }
        }
    }
    return index[2 + 5 * block];
}


int newSort(std::vector<int> &vect, int i) // Sorting 5 entries vector (efficient in this case)
{

    if (vect[i + 1] < vect[i])
    {
        newSwap(vect, i, i + 1);
    }
    if (vect[i + 3] < vect[i + 2])
    {
        newSwap(vect, i + 2, i + 3);
    }
    if (vect[i + 3] < vect[i + 1])
    {
        newSwap(vect, i, i + 2);
        newSwap(vect, i + 1, i + 3);
    }
    if (vect[i + 4] < vect[i + 1])
    {
        if (vect[i + 4] < vect[i])
        {
            moveElement(vect, i + 4, i);
            newSwap(vect, i + 4, i + 3);
        }
        else
        {
            moveElement(vect, i + 4, i + 1);
            newSwap(vect, i + 4, i + 3);
        }
    }
    else
    {
        if (vect[i + 4] < vect[i + 3])
        {
            moveElement(vect, i + 4, i + 2);
            newSwap(vect, i + 4, i + 3);
        }
        else
        {
            moveElement(vect, i + 4, i + 3);
            newSwap(vect, i + 4, i + 2);
        }
    }
    if (vect[i + 4] < vect[i + 1])
    {
        if (vect[i + 4] < vect[i])
        {
            moveElement(vect, i + 4, i);
        }
        else
        {
            moveElement(vect, i + 4, i + 1);
        }
    }
    else
    {
        if (vect[i + 4] < vect[i + 2])
        {
            moveElement(vect, i + 4, i + 2);
        }
        else
        {
            moveElement(vect, i + 4, i + 3);
        }
    }
    return vect[i + 2];
}

int median(std::vector<int> &vect, std::vector<int> &index) // finding index of median of medians
{
    if (index.size() < 5)
    {
        // cout <<"index size is less than 5" <<endl;
        int y = index.size() / 2;
        // cout <<"y: " << y <<endl;
        // cout <<"index[y]: " << index[y] <<endl;
        return index[y];
    }
    int blocks = index.size() / 5;
    std::vector<int> vect2;
    for (int i = 0; i < blocks; ++i)
    {
        vect2.push_back(newSort(vect, i));
    }
    // cout <<"vect2: ";
    // printVec(vect2);
    // printVec(vect2);
    return median(vect, vect2);
}

int newPartition(std::vector<int> &vect, int start, int end)
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

int randPartition(std::vector<int>& vect, int start, int end)
{   

    srand(time(NULL));
    // Genera un numero casuale nell'intervallo [start, end - 1]
    int rP = start -1 + std::rand() % (end - start);

    newSwap (vect, rP, end);
    int pivot = vect.at(end);
    int i = start - 1;

    for (int j = start; j < end; ++j) // Changed end - 1 to end
    {
        if (vect.at(j) <= pivot)
        {
            i++;
            newSwap (vect, i, j);
        }
    }

    // Swap the pivot to its correct position
    newSwap (vect, i+1, end);
    return i + 1;
}




int partition(std::vector<int>& vect, int start, int end) {
    int pivot = vect[end];
    int i = start - 1;
    
    for (int j = start; j < end; j++) {
        if (vect[j] < pivot) {
            i++;
            newSwap(vect, i, j);
        }
    }
    newSwap(vect, i + 1, end);
    return i + 1;
}

void quickSort(std::vector<int>& vect, int start, int end) {
    if (start < end) {
        int pivotIndex = partition(vect, start, end);
        quickSort(vect, start, pivotIndex - 1);
        quickSort(vect, pivotIndex + 1, end);
    }
}


int medianOf5(std::vector<int> &vect, int start)
{
    quickSort(vect, start, start + 5); //! TO CHANGE WITH OUR SORT FUNCTION
    //std::sort(vect.begin() + start, vect.begin() + start + 5);
    return vect[start + 2];
}

std::vector<int> mediansVector(std::vector<int> &vect, int p, int q)
{
    if ((q - p + 1) < 5)
    {
        std::vector<int> output;
        output.push_back(vect[(p + q) / 2]);
        return output;
    }
    
    int blockNum = (q - p + 1) / 5;
    std::vector<int> output(blockNum);

    #pragma omp parallel
    {
        #pragma omp for 
        for (int i = 0; i < blockNum; ++i)
        {
            output[i] = (newSort(vect, p + i * 5));
        }

    }

    return output;
}

void partition(std::vector<int> &vect, int pivot, int p, int q, int &lessNum, int &greatNum, int &pivNum)
{
    int temp;
    for(int i=p; i<= q; ++i )
    {
        if (vect[i] > pivot) 
        {
            greatNum++;
        }
        else if (vect[i] < pivot)
        {
            temp = vect[i];
            vect[i] = vect[p +lessNum + pivNum];
            vect[p + lessNum + pivNum] = vect[p +lessNum];
            vect[p + lessNum] = temp;
            lessNum++;
        }
        else //vect[j] == pivot
        {
            vect[i] = vect[p + lessNum + pivNum];
            vect[p +lessNum + pivNum] = pivot;
            pivNum++;
        }

    }
}







int select(std::vector<int> &vect, int p, int q, int i)
{
    if (p == q)
        return vect[p];

    std::vector<int> medVector = mediansVector(vect, p, q);

    /*
    std::cout<<"medVector: ";
    printArray(medVector);
    */

    int pivot = select(medVector, 0, medVector.size() - 1, medVector.size() / 2);

    //std::cout<<"pivot: " << pivot <<std::endl;

    int lessNum = 0, greatNum = 0, pivNum = 0;
    /*
    std::cout<< std::endl << "vect:  ";
    printArray(vect);

    std::cout<<"pivot= "<<pivot;
    std::cout<<"p = "<<p << "    ";
    std::cout<<"q = "<<q << "    ";
    */

    partition(vect, pivot, p, q, lessNum, greatNum, pivNum);

    /*
    std::cout<<"lessNum: " << lessNum << "    ";
    std::cout<<"greatNum: " << greatNum << "    ";


    std::cout<<"vect after partitioning: ";
    printArray(vect);
    std::cout<<" ; ";
    */

    int k = lessNum + 1; 

    //std::cout<<"k: " << k <<std::endl;

    if (i == k)
        return pivot;

    else if (i < k)
        return select(vect, p, p + lessNum -1, i);

    else
        return select(vect, p + lessNum +1, q, i - k);
}


#define N 250000
#define seed 2704

int main()
{

    std::srand(std::time(nullptr));

    std::vector<int> vect, index;
    fillArray(N, vect);
    fillArray(N, index);
    //fillArrayWithDuplicates(N, vect);
    shuffleArray(vect, seed);

    //add chrono
    auto start1 = std::chrono::high_resolution_clock::now();
    int x = select(vect, 0, N-1, 252);
    auto end1 = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::nanoseconds>(end1 - start1);

    //add chrono
    auto start2 = std::chrono::high_resolution_clock::now();
    int y = rand_select(vect, 0 , N-1, 252);
    auto end2 = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - start2);

    std::cout << "select duration: " << duration1.count() << std::endl;
    std::cout << "rand_select duration: " << duration2.count() << std::endl;


    std::cout << "x = " << x <<std::endl;
    std::cout << "y = " << y <<std::endl;





}










/*
#define N 1000
#define seed 17049


int main(int argc, char **argv)
{
    int z = 0;

    for (int M = N - 1; M < N; M++)
    {
        std::cout << "M: " << M << "/" << N << std::endl;
        for (int i = M / 3; i <= M; i++)
        {
            // std:: cout << "M: " << M << " i: " << i << std::endl;
            std::vector<int> array;
            fillArray(M, array);
            // fillOppositeArray(M, array);
            //  array.push_back(100);

            // std::sort(array.begin(), array.end());
            // printArray(array);
            // std::cout << "The " << i << "th smallest element is " << array[i - 1] << std::endl;

            shuffleArray(array, seed);
            // printArray(array);
            std::vector<int> array2 = array;

            // add chrono
            auto start1 = std::chrono::high_resolution_clock::now();
            int x = rand_select(array, 0, M - 1, i);
            // std::cout << "randSelect: The " << i << "the smallest element is " << x << std::endl;
            auto end1 = std::chrono::high_resolution_clock::now();
            auto duration1 = std::chrono::duration_cast<std::chrono::nanoseconds>(end1 - start1);
            std::cout << std::endl << "rand_select duration: " << duration1.count() << std::endl;

            // std::cout << std::endl;
            // printArray(array2);

            auto start2 = std::chrono::high_resolution_clock::now();
            int y = quickSelect(array2, 0, M - 1, i);
            // std::cout << "quickSelect: The " << i << "th smallest element is " <<y << std::endl;
            auto end2 = std::chrono::high_resolution_clock::now();
            auto duration2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - start2);
            std::cout << "quickSelect duration: " << duration2.count() << std::endl;

            if (x != y)
            {
                std::cout << -1;
                std::cout << "    M: " << M << " i: " << i << std::endl;
                std::cout << std::endl;
            }
        }
    }
}

*/