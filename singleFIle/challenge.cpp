#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>


#define N 100
#define MAX 1000
#define seed chrono::system_clock::now().time_since_epoch().count()

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
       return index[index.size()/2];
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
    cout <<"pivot: " << vect[position] <<endl;
    newSwap(vect, position, end);
    int newPivot = vect[end];
    int i = start - 1;

    for (int j = start; j <= end - 1; ++j) 
    {
        if (vect[j] < newPivot)
        {
            i++;
            newSwap(vect, i, j);
        }
        else if (vect[j] == newPivot)
        {
            // Spostare solo l'elemento uguale al pivot al centro
            newSwap(vect, i + 1, j);
        }
    }
    newSwap(vect, i + 1, end);
    return i + 1;
}



int quickSelect(vectInt& vect, vectInt& index, int p, int q, int i)
{
    if (p >= q)
        return index[p];

    int pivot = median(vect, index);
    int r = pivPartition (pivot, vect, p, q);
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
    
    int m = 10;
    vectInt vect, index;
    for(int i=0; i<m; i++)
    {
        vect.push_back(i+1);
        index.push_back(i);
    }
    vect.at(1)=8;
    vect.at(2)=8;
    vect.at(3)=8;
    shuffle(vect.begin(), vect.end(), default_random_engine(seed));



    //cout << "med: " << vect.at(4) << endl;
    //int x = pivPartition(4, vect, 0, N-1);

    cout <<endl;
    printVec(vect);
    int x = pivPartition(1, vect, 0, m-1);
    cout << "x: " << x <<endl;
    printVec(vect);



    //int k = quickSelect(vect, index, 0, N-1, 80 );
    //cout <<"k: " <<k <<endl;

}