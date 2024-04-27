#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>


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


#define N 100
#define i 50
#define seed 270424

int main()
{
    std::vector<int> vect;
    fillVector(N, vect);
    shuffleVector(vect, seed);

    auto start = std::chrono::high_resolution_clock::now();
    int x = select(vect, 0, N - 1, i);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    std::cout << "The " << i << "th order statistic is: " << x << std::endl;
    std::cout << "Time taken: " << duration.count() << " nanoseconds" << std::endl;
}
