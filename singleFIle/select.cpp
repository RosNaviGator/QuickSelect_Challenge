#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <fstream>




void swapElements(std::vector<int> &vect, int i, int j) // swap two elements in a vector
{
    int temp = vect[i];
    vect[i] = vect[j];
    vect[j] = temp;
}

void fillVector(int size, std::vector<int> &vect) // ordered vector of int
{
    for (int i = 0; i < size; ++i)
    {
        vect.push_back(i);
    }
}

void fillVectorWithDuplicates(int size, std::vector<int> &vect) // vector of int with duplicates
{
    for (int i = 0; i < size; ++i)
    {
        vect.push_back(i % 10);
    }
}

void sortVector(std::vector<int> &vect) // sort vector
{
    std::sort(vect.begin(), vect.end());
}

void fillVectorWithOnes(int size, std::vector<int> &vect) // vector of 1s
{
    for (int i = 0; i < size; ++i)
    {
        vect.push_back(1);
    }
}

void fillOppositeVector(int size, std::vector<int> &vect) // inverse-ordered vector of int
{
    for (int i = size; i > 0; --i)
    {
        vect.push_back(i);
    }
}

void printVector(std::vector<int> &vect) // print vector
{
    for (int i = 0; i < vect.size(); ++i)
    {
        std::cout << vect[i] << " ";
    }
    std::cout << std::endl;
}

void shuffleVector(std::vector<int> &vect, int seed) // shuffle vector elements
{
    std::shuffle(vect.begin(), vect.end(), std::default_random_engine(seed));
}

void moveElement(std::vector<int> &vect, int fromIndex, int toIndex) // move an element in a vector in medianFiveEntries function
{
    int valueToMove = vect[fromIndex]; // temporarily store the element to be moved
    if (fromIndex < toIndex)           // move elements to the right
    {
        for (int i = fromIndex; i < toIndex; ++i)
        {
            vect[i] = vect[i + 1];
        }
    }
    else // move elements to the left
    {
        for (int i = fromIndex; i > toIndex; --i)
        {
            vect[i] = vect[i - 1];
        }
    }

    vect[toIndex] = valueToMove; // place the element at the new position
}

int medianFiveEntries(std::vector<int> &vect, int i) // sort 5 entries vector from i to i+4 and return the median
{
    if (vect[i + 1] < vect[i])
    {
        swapElements(vect, i, i + 1);
    }
    if (vect[i + 3] < vect[i + 2])
    {
        swapElements(vect, i + 2, i + 3);
    }
    if (vect[i + 3] < vect[i + 1])
    {
        swapElements(vect, i, i + 2);
        swapElements(vect, i + 1, i + 3);
    }
    if (vect[i + 4] < vect[i + 1])
    {
        if (vect[i + 4] < vect[i])
        {
            moveElement(vect, i + 4, i);
            swapElements(vect, i + 4, i + 3);
        }
        else
        {
            moveElement(vect, i + 4, i + 1);
            swapElements(vect, i + 4, i + 3);
        }
    }
    else
    {
        if (vect[i + 4] < vect[i + 3])
        {
            moveElement(vect, i + 4, i + 2);
            swapElements(vect, i + 4, i + 3);
        }
        else
        {
            moveElement(vect, i + 4, i + 3);
            swapElements(vect, i + 4, i + 2);
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
    return vect[i + 2]; // return the median of the 5 entries
}

std::vector<int> mediansVector(std::vector<int> &vect, int p, int q) // return vector of medians of the 5 entries blocks
{
    if ((q - p + 1) < 5)
    {
        std::vector<int> medVect;
        medVect.push_back(vect[(p + q) / 2]);
        return medVect;
    }
    int blockNum = (q - p + 1) / 5;
    std::vector<int> medVect(blockNum);
    for (int i = 0; i < blockNum; ++i)
    {
        medVect[i] = medianFiveEntries(vect, p + i * 5);
    }
    return medVect;
}

void pivotPartition(std::vector<int> &vect, int pivot, int p, int q, int &lessNum, int &greatNum, int &pivNum) // partition the vector around the pivot
{
    int temp;
    for (int i = p; i <= q; ++i)
    {
        if (vect[i] > pivot)
        {
            greatNum++;
        }
        else if (vect[i] < pivot)
        {
            temp = vect[i];
            vect[i] = vect[p + lessNum + pivNum];
            vect[p + lessNum + pivNum] = vect[p + lessNum];
            vect[p + lessNum] = temp;
            lessNum++;
        }
        else // vect[j] == pivot
        {
            vect[i] = vect[p + lessNum + pivNum];
            vect[p + lessNum + pivNum] = pivot;
            pivNum++;
        }
    }
}

int select(std::vector<int> &vect, int p, int q, int i) // select the ith order statistic
{
    if (p == q)
        return vect[p];

    std::vector<int> medVector = mediansVector(vect, p, q);
    int pivot = select(medVector, 0, medVector.size() - 1, medVector.size() / 2);
    int lessNum = 0, greatNum = 0, pivNum = 0; // number of elements less than, greater than and equal to the pivot
    pivotPartition(vect, pivot, p, q, lessNum, greatNum, pivNum);
    int k = lessNum + 1;

    if (i == k)
        return pivot;
    else if (i < k)
        return select(vect, p, p + lessNum - 1, i);
    else
        return select(vect, p + lessNum + 1, q, i - k);
}

void tableResults(int M, int seed)
{
    // Remove any previous version of the CSV file
    std::remove("data.csv");

    // Open the CSV file for writing
    std::ofstream file("data.csv");

    // Check if the file opened successfully
    if (!file.is_open())
    {
        // File doesn't exist, create it
        std::cout << "File doesn't exist. Creating a new file." << std::endl;
        file.open("data.csv", std::ofstream::out | std::ofstream::trunc);
    }

    std::cout << "Generating data..." << std::endl;
    for (int N = 1; N < M; N += M/1000)
    {
        if(N % (M/10) == 1)
        {
            std::cout << "Progress: " << N / (M/10) * 10 << "%" << std::endl;
        }

        std::vector<int> vect;
        fillVector(N, vect);
        shuffleVector(vect, seed);

        auto start = std::chrono::high_resolution_clock::now();
        int x = select(vect, 0, N - 1, N/3);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

        file << N << "," << duration.count() << std::endl;
    }
    std::cout << "Progress: 100%" << std::endl << std::endl << "data.csv is ready!" << std::endl;
    file.close();
}




#define N 10000
#define i N / 4 * 3 + 1
#define M 1000000


int main()
{
    int seed = 280424;

    // Parameters
    // 1. ordered or not
    // 2. duplicates or not
    // 3. incomplete sequence

    // First we create a vector with integers from 0 to N-1 in order
    std::vector<int> vect;
    fillVector(N, vect);
    std::cout << "First vector: no duplicates" << std::endl;
    std::cout << "N = " << N << std::endl;
    std::cout << "i = " << i << std::endl
              << std::endl;

    // The i-th smallest element can be retrieved trivially by vect[i-1]
    std::cout << "The i-th smallest element can be retrieved trivially by vect[i-1] because it's generated in order" << std::endl;
    std::cout << "In this case the " << i << "th element is: " << vect[i - 1] << std::endl
              << std::endl;

    // Let's see if the select function can retrieve the correct i-th order statistic in a ordered vector with no duplicates
    std::cout << "Result using the 'select' function on the ordered vector:" << std::endl;

    auto startOrd = std::chrono::high_resolution_clock::now();
    int x = select(vect, 0, N - 1, i);
    auto endOrd = std::chrono::high_resolution_clock::now();
    auto durationOrd = std::chrono::duration_cast<std::chrono::nanoseconds>(endOrd - startOrd);

    std::cout << x << std::endl;
    std::cout << "Time taken: " << durationOrd.count() << " nanoseconds" << std::endl
              << std::endl;

    // Now we shuffle the vector
    shuffleVector(vect, seed);
    // Let's see if the result is the same
    std::cout << "Result using the 'select' function on the same vector shuffled:" << std::endl;

    auto startShuff = std::chrono::high_resolution_clock::now();
    int y = select(vect, 0, N - 1, i);
    auto endShuff = std::chrono::high_resolution_clock::now();
    auto durationShuff = std::chrono::duration_cast<std::chrono::nanoseconds>(endShuff - startShuff);

    std::cout << y << std::endl;
    std::cout << "Time taken: " << durationShuff.count() << " nanoseconds" << std::endl
              << std::endl
              << "--------------------------------------------------"
              << std::endl
              << std::endl;

    // Now we fill the vector with duplicates
    vect.clear();
    fillVectorWithDuplicates(N, vect);
    std::cout << "Second vector: generated with duplicates" << std::endl;
    std::cout << "N = " << N << std::endl;
    std::cout << "i = " << i << std::endl
              << std::endl;

    // The i-th smallest element can be retrieved trivially by vect[i-1] AFTER sorting the vector
    std::cout << "The i-th smallest element can be retrieved trivially by vect[i-1] after sorting it" << std::endl;
    sortVector(vect);
    std::cout << "The " << i << "th element is: " << vect[i - 1] << std::endl
              << std::endl;

    // Let's see if the select function can retrieve the correct i-th order statistic in a ordered vector with no duplicates
    std::cout << "Result using the 'select' function on the ordered vector:" << std::endl;

    auto startOrdDup = std::chrono::high_resolution_clock::now();
    int x1 = select(vect, 0, N - 1, i);
    auto endOrdDup = std::chrono::high_resolution_clock::now();
    auto durationOrdDup = std::chrono::duration_cast<std::chrono::nanoseconds>(endOrdDup - startOrdDup);

    std::cout << x1 << std::endl;
    std::cout << "Time taken: " << durationOrdDup.count() << " nanoseconds" << std::endl
              << std::endl;

    // Now we shuffle the vector
    shuffleVector(vect, seed);
    // Let's see if the result is the same
    std::cout << "Result using the 'select' function on the same vector shuffled:" << std::endl;

    auto startShuffDup = std::chrono::high_resolution_clock::now();
    int y1 = select(vect, 0, N - 1, i);
    auto endShuffDup = std::chrono::high_resolution_clock::now();
    auto durationShuffDup = std::chrono::duration_cast<std::chrono::nanoseconds>(endShuffDup - startShuffDup);

    std::cout << y1 << std::endl;
    std::cout << "Time taken: " << durationShuffDup.count() << " nanoseconds" << std::endl
              << std::endl
              << "--------------------------------------------------"
              << std::endl
              << std::endl;

    

    // Let's generate some data bitchez!
    tableResults(M, seed);
    
    return 0;
}
