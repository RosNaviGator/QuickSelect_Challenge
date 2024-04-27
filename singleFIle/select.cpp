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
