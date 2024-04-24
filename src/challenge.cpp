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



int newSort(vectInt vect, vectInt &index, int i)
{
    i = 5 * i; 
    vector<int> a = {vect.at(index.at(i)), vect.at(index.at(i + 1)), vect.at(index.at(i + 2)), vect.at(index.at(i + 3)), vect.at(index.at(i + 4))};
    vector<int> indexa = {index[i], index[i + 1], index[i + 2], index[i + 3], index[i + 4]};
    // Sort first two pairs
    if (a[1] < a[0])
    {
        newSwap(a, 0, 1);
        newSwap(indexa, i + 0, i + 1);
    }
    if (a[3] < a[2])
    {
        newSwap(a, 2, 3);
        newSwap(indexa, i + 2, i + 3);
    }

    // Sort pairs by larger element
    if (a[3] < a[1])
    {
        a = {a[2], a[3], a[0], a[1], a[4]};
        indexa = { indexa[i + 2], indexa[i + 3], indexa[i + 0], indexa[i + 1], indexa[i + 4]};
    }

    // A = [a,b,c,d,e] with a < b < d and c < d

    // insert e into [a,b,d]
    vector<int> b;
    vector<int> indexb;
    if (a[4] < a[1])
    {                    // e < b
        if (a[4] < a[0]) // e < a
        {
            b = {a[4], a[0], a[1], a[3], a[2]}; // B = [e,a,b,d]
            indexb = {indexa[i + 4], indexa[i + 0], indexa[i + 1], indexa[i + 3], indexa[i + 2]};
        }
        else
        {
            b = {a[0], a[4], a[1], a[3], a[2]}; // B = [a,e,b,d]
            indexb = {indexa[i + 0], indexa[i + 4], indexa[i + 1], indexa[i + 3], indexa[i + 2]};
        }
    }
    else
    {                    // e > b
        if (a[4] < a[3]) // e < d
        {
            b = {a[0], a[1], a[4], a[3], a[2]}; // B = [a,b,e,d]
            indexb = {indexa[i + 0], indexa[i + 1], indexa[i + 4], indexa[i + 3], indexa[i + 2]};
        }
        else
        {
            b = {a[0], a[1], a[3], a[4], a[2]}; // B = [a,b,d,e]
            indexb = {indexa[i + 0], indexa[i + 1], indexa[i + 3], indexa[i + 4], indexa[i + 2]};
        }
    }

    // insert c into the first three elements of B
    vector<int> c;
    vector<int> indexc;
    if (a[2] < b[1])
    {
        if (a[2] < b[0])
        {
            c = {a[2], b[0], b[1], b[2], b[3]};
            indexc = {indexa[i + 2], indexb[i + 0], indexb[i + 1], indexb[i + 3], indexb[i + 4]};
        }
        else
        {
            c = {b[0], a[2], b[1], b[2], b[3]};
            indexc = {indexb[i + 0], indexa[i + 2], indexb[i + 1], indexb[i + 3], indexb[i + 4]};
        }
    }
    else
    {
        if (a[2] < b[2])
        {
            c = {b[0], b[1], a[2], b[2], b[3]};
            indexc = {indexb[i + 0], indexb[i + 1], indexa[i + 2], indexb[i + 3], indexb[i + 4]};
        }
        else
        {
            c = {b[0], b[1], b[2], a[2], b[3]};
            indexc = {indexb[i + 0], indexb[i + 1], indexb[i + 2], indexa[i + 3], indexb[i + 4]};
        }
    }
    for (int j = 0; j < 5; j++)
    {
        index.at(i + j) = indexc[j];
    }  

    return index[i + 2];
}

int sortGroupsOf5(vectInt vect, vectInt& index)
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


int select(vectInt& vect, int begin, int end, int i)
{
    if (begin == end)
        return vect.at(begin);  
    int pivot = partition(vect, begin, end);
    int k = pivot - begin +1;

    if (i==k) 
        return vect.at(pivot);
    else 
        if (i<k)
            return select(vect, begin, pivot-1, i);
        else 
            return select(vect, pivot+1, end, i-k);

}


int main()
{
    vectInt vector1, vector2, index;
    srand(time(NULL));

    llu counter5=0, newCounter=0;

    for(int j=0; j< MAX; j++)
        {
            vector1.clear();
            index.clear();
            for(int i=0; i<1000; i++)
            {
                vector1.push_back(i+1);
                index.push_back(i);
            }


            shuffle(vector1.begin(), vector1.end(), default_random_engine(seed+j));

            for(int i=0; i<5; i++)
            cout << " " <<vector1.at(i);

            cout <<endl;

            auto start = chrono::high_resolution_clock::now();
            int y = sort5(vector1, index, 0);
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::nanoseconds>(end-start);
            counter5 += duration.count();
            //cout << y <<endl;

            auto start2 = chrono::high_resolution_clock::now();
            int x = newSort(vector1, index, 0);
            auto end2 = chrono::high_resolution_clock::now();
            auto duration2 = chrono::duration_cast<chrono::nanoseconds>(end2-start2);
            newCounter += duration2.count();
            //cout << y <<endl;
            if(x!=y)
                cout <<"error!!!!!!!";
        }
        llu mean5 = counter5/static_cast<float>(MAX);
        llu newMean = newCounter/ static_cast<float>(MAX);

        cout <<endl <<"mean5: " <<mean5;
        cout <<endl <<"newMean: " <<newMean;


    // printVec(vector1);

        // int x = sortGroupsOf5(vector1, index);

        //cout << "Median position: " << x << endl;
        //cout << "Median: " << vector1.at(x) << endl;
    // printVec(vector1);
        
    //!!!!!!!!miss main select 
}