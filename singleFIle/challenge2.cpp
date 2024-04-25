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

int bubbleSort(vectInt& values, vectInt& index, int block) 
{
    for( int i = 0; i < 5-1; i++)
    {
        for(int j = 0; j < 5-i-1; j++)
        {
            if(values[index[j+5*block]] > values[index[j+1+ 5*block]])
            {
                swap(index[j+5*block], index[j+1+ 5*block]);
            }
        }
    }
    return index[2+5*block];
}


int sort5(vectInt& vect, vectInt& index, int i) 
{
    for (int j = i * 5; j < 5 * (i + 1) - 1; j++) 
    {
        for (int z = i * 5; z < 5 * (i + 1) - j - 1; z++) 
        {
            if (vect[index[z]] > vect[index[z + 1]]) 
            {
                swap(index[z], index[z + 1]);
            }
        }
    }

    cout <<"sorting ith block : " << i <<endl;
    for(int j=5*i; j< 5*(i+1); j++)
    {
        cout<< " " << index.at(j);
    }
    cout<<endl;
    return (index[5*i+2]);

}


void moveElement(std::vector<int>& vec, int fromIndex, int toIndex) {
        // Temporarily store the element to be moved
    int valueToMove = vec[fromIndex];

    // Move elements to the right
    if (fromIndex < toIndex) {
        for (int i = fromIndex; i < toIndex; ++i) {
            vec[i] = vec[i + 1];
        }
    }
    // Move elements to the left
    else {
        for (int i = fromIndex; i > toIndex; --i) {
            vec[i] = vec[i - 1];
        }
    }

    // Place the element at the new position
    vec[toIndex] = valueToMove;
}



int newSort(vector<int> &vect, vector<int> &index, int i)
{
    i = 5 * i;  

    if (vect[index[i + 1]] < vect[index[i]])
    {
        swap(index[i], index[i + 1]);
    }
    if (vect[index[i + 3]] < vect[index[i + 2]])
    {
        swap(index[i + 2], index[i + 3]);
    }

    if (vect[index[i + 3]] < vect[index[i + 1]])
    {
        swap(index[i], index[i + 2]);
        swap(index[i + 1], index[i + 3]);
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



    

int median(vectInt& vect, vectInt& index)
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
   vectInt vect2;
   for(int i=0; i<blocks; i++)
   {
    vect2.push_back(newSort(vect, index, i));
   } 
   //cout <<"vect2: ";
   //printVec(vect2);
   //printVec(vect2);
   return median(vect, vect2);
    
}


int pivPartition(vectInt& vect, vectInt& index, int start, int end, int pivotPos)
{   
    
    swap (vect.at(pivotPos), vect.at(end));
    int pivot = vect.at(end);
    int i = start - 1;

    for (int j = start; j < end; ++j) // Changed end - 1 to end
    {
        if (vect.at(j) <= pivot)
        {
            i++;
            swap (vect.at(i), vect.at(j));
            swap (index.at(i), index.at(j));


        }
    }

    // Swap the pivot to its correct position
    swap (vect.at(i+1), vect.at(end));
    swap (index.at(i+1), index.at(end));
    return i + 1;
}

int newPartition (vectInt& vect, vectInt& index, int start, int end, int pivotPos)
{
    int pivot_value = vect[pivotPos];
    newSwap(vect, pivotPos, start);
    newSwap(index, pivotPos, start);
    int i = start;

    for (int j = start + 1; j <= end; j++)
    {
        if (vect[j] < pivot_value)
        {
            i++;
            newSwap(vect, i, j);
            newSwap(index, i, j);
        }
    }

    newSwap(vect, start, i);
    newSwap(index, start, i);
    return i;
}


int quickSelect(vectInt& vect, vectInt& index, int p, int q, int i)
{
    if (p == q)
        return index[p];

    vectInt newVect;
    vectInt newIndex;
    for(int j=p,k=0; j<=q; ++j, ++k)
    {
        newVect.push_back(vect[j]);
        newIndex.push_back(k);
    }
    int pivPosition = median(newVect, newIndex);
    int pivot = newVect[pivPosition];
    cout <<"pivot: " << pivot <<endl;

    int r = newPartition(newVect,  newIndex, p, q, pivPosition);
    cout <<"r: " << r <<endl;
    
    printVec(newVect);

    int k = r - p + 1;

    if (i == k)
        return index[r];
    else if (i < k)
        {   
            return quickSelect(newVect, newIndex, p, r - 1, i);
        } 
    else
        {
            return quickSelect(newVect, newIndex, r + 1, q, i - k);
        }      
}

int main()
{
    
    // int m = 27;
    vectInt vect, index;
    vect = {1,3,5,4,2,8,7,6,5,1,9,1,1000,2,3,4,8,7,6,4,2,6,6,2,2,1,17,18,1000};
    int m = vect.size();
    for(int i=0; i<m; i++)
    {
        // vect.push_back(i+1);
        index.push_back(i);
    }
    //vect = {1,3,5,7,9,11,13,15,17,19,21,23,25,27,29,31,33,35,37,39,41,43};
    //printVec(vect);
    //printVec(index);
    //shuffle(vect.begin(), vect.end(), default_random_engine(seed));
    //printVec(vect);

    // int medianIndex = median(vect, index);
    // cout <<"The median index is " << medianIndex << endl;
    int ith = 4;
    int x = quickSelect(vect, index, 0, m-1, ith);
    cout <<"The " <<ith <<" smallest is " << x << endl;
    // int x = newPartition(vect, index, 0, m-1, medianIndex);
    // printVec(vect);
    // cout <<"x: " << x <<endl;
    // cout << "vector size: " << vect.size() <<endl;
    return 0;
}