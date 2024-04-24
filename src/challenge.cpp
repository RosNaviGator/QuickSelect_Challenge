#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

#define seed 24024224524
#define N 100
#define MAX 1000

using namespace std;
using vectInt = vector<int>;
using llu = long long unsigned int;

void newSwap(vectInt& a, int i, int j)
{
    int t = a[i];
    a[i] = a[j];
    a[j] = t;
}

void printVec(vectInt& vect)
{
    for(llu i=0; i< vect.size(); i++)
    {
        cout << vect.at(i) <<" ";
    }
    cout << endl << "size is " << vect.size() <<endl;
}

int sort5(vector<int> vect, vector<int>& index, int i) 
{

    for( int j= i*5; j< 5*(i+1)-1; j++)
    {
        for(int z = i*5; z < 5*(i+1)-1; z++)
        {
            if (vect.at(z) > vect.at(z+1))
            {
                newSwap (vect, z, z+1);
                newSwap (index, z, z+1);
            }
        }
    }
    return (index.at(5*i+2));

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


int sortGroupsOf5(vectInt& vect, vectInt& index)
{
   if (index.size() < 5)
   {
       return index.at(index.size()/2);
   }
   int end = index.size();
   int blocks = index.size()/5;
   vectInt vect2;
   for(int i=0; i<blocks; i++)
   {
    vect2.push_back(newSort(vect, index, i));
   } 
   return sortGroupsOf5(vect, vect2);
    
}



int partition(vectInt& vect, int begin, int end)
{
    
    vectInt indexes;

    for(int i=0; i<vect.size(); i++)
        indexes.push_back(i);

    return sortGroupsOf5(vect, indexes);

}


int pivPartition(int index, vectInt& vect, int start, int end)
{   
    
    swap (vect.at(index), vect.at(end));
    int newPivot = vect.at(end);
    int i = start - 1;

    for (int j = start; j < end; ++j) // Changed end - 1 to end
    {
        if (vect.at(j) <= newPivot)
        {
            i++;
            swap (vect.at(i), vect.at(j));
        }
    }

    // Swap the pivot to its correct position
    swap (vect.at(i+1), vect.at(end));
    return i + 1;
}


int select(vectInt& vect, vectInt& index, int p, int q, int i)
{
    if (p >= q)
        return index[p];

    int pivot = sortGroupsOf5(vect, index);
    int r = pivPartition (pivot, vect, p, q);
    int k = r - p + 1;

    if (i == k)
        return index[r];
    else if (i < k)
        {   
            return select(vect, index, p, r - 1, i);
        } 
    else
        {
            return select(vect, index, r + 1, q, i - k);
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

    int k = select(vect, index, 0, N-1, 25 );
    cout <<endl <<"k: " <<k <<endl;

}