#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

#define seed 24042024
#define N 100
#define MAX 1000

using namespace std;
using vectInt = vector<int>;
using llu = long long unsigned int;


void newSwap(vectInt& vect, int i, int j)
{
    int temp = vect[i];
    vect[i] = vect[j];
    vect[j] = temp;
}

void printVec(vectInt& vect)
{
    for(llu i=0; i< vect.size(); i++)
    {
        cout << vect[i] <<" ";
    }
    cout << endl << "size is " << vect.size() <<endl;
    return;
}

int sort5(vectInt vect, vectInt& index, int i) 
{

    for( int j= i*5; j< 5*(i+1)-1; j++)
    {
        for(int z = i*5; z < 5*(i+1)-1; z++)
        {
            if (vect[z] > vect[z+1])
            {
                newSwap(vect, z, z+1);
                newSwap(index, z, z+1);
            }
        }
    }
    return (index[5*i+2]);

}



int newSort(vectInt& vect, vectInt& index, int i) 
{
    i = 5 * i; 

    // Sort first two pairs
    if (vect[index[i + 1]] < vect[index[i]]) 
    {
        newSwap(index, i, i+1);
    }
    if (vect[index[i + 3]] < vect[index[i + 2]]) 
    {
        newSwap(index, i+2, i+3);
    }

    // Sort pairs by larger element
    if (vect[index[i + 3]] < vect[index[i + 1]]) 
    {
        newSwap(index, i , i+2);
        newSwap(index, i , i+3);
    }

    // Insert e into [a,b,d]
    int eIndex = index[i + 4];
    int aIndex = index[i];
    int bIndex = index[i + 1];
    int dIndex = index[i + 3];
    if (vect[eIndex] < vect[index[i + 1]]) 
    {
        if (vect[eIndex] < vect[index[i]]) 
        {
            newSwap(index, i, i+4);
        } 
        else 
        {
            newSwap(index, i, i+4);
        }
    } 
    else 
    {
        if (vect[eIndex] < vect[index[i + 3]]) 
        {
            newSwap(index, i+3, i+4);
        }
    }

    // Insert c into the first three elements of B
    int cIndex = index[i + 2]; 
    int b0Index = index[i];
    int b1Index = index[i + 1];
    int b2Index = index[i + 3];
    if (vect[cIndex] < vect[index[i + 1]]) 
    {
        if (vect[cIndex] < vect[index[i]]) 
        {
            newSwap(index, i, i+2);
        } 
        else 
        {
            newSwap(index, i+1, i+2);
        }
    } 
    else 
    {
        if (vect[cIndex] < vect[index[i + 3]]) 
        {
            newSwap(index, i+3, i+2);
        }
    }
    
    // Return the index of the median element
    return index[i + 3];
}



int median(vectInt& vect, vectInt& index)
{
   if (index.size() < 5)
   {
       return index[index.size()];
   }
   int end = index.size();
   int blocks = index.size()/5;
   vectInt vect2;
   for(int i=0; i<blocks; i++)
   {
    vect2.push_back(newSort(vect, index, i));
   } 
   return median(vect, vect2);
    
}


int pivPartition(int position, vectInt& vect, int start, int end)
{   
    
    newSwap (vect, position, end);
    int newPivot = vect[end];
    int i = start - 1;

    for (int j = start; j < end; ++j) 
    {
        if (vect[j] <= newPivot)
        {
            i++;
            newSwap (vect, i, j);
        }
    }

    // Swap the pivot to its correct position
    newSwap (vect, i+1, end);
    return i + 1;
}

int partition(vectInt& arr, int low, int high, int pivot) {
    int left = low;
    int right = high;

    while (left <= right) {
        while (arr[left] < pivot) {
            left++;
        }
        while (arr[right] > pivot) {
            right--;
        }
        if (left <= right) {
            swap(arr[left], arr[right]);
            left++;
            right--;
        }
    }
    return left;
}


int quickSelect(vectInt& vect, vectInt& index, int p, int q, int i)
{
    if (p >= q)
        return index[p];

    int pivot = median(vect, index);
    int r = pivPartition (vect[pivot], vect, p, q);
    int k = r - p + 1;

    if (i == k)
        return index[r];
    else if (i < k)
        {   
            return quickSelect(vect, index, p, r - 1, i);
        } 
    else
        {
            return quickSelect(vect, index, r + 1, q, i - k);
        }      
}

int main()
{
    vectInt vect, index;
    for(int i=0; i<N; i++)
    {
        vect.push_back(i+1);
        index.push_back(i);
    }


    //cout << "med: " << vect.at(4) << endl;
    //int x = pivPartition(4, vect, 0, N-1);

    cout <<endl;

    int k = quickSelect(vect, index, 0, N-1, 25 );
    cout <<"k: " <<k <<endl;

}