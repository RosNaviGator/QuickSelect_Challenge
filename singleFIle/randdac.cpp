#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <algorithm>
#include <random>

using namespace std;

// Function to randomly partition the array
int rand_partition(vector<int> &a, int p, int q)
{
    // Select a random pivot element
    int r = rand() % (q - p + 1) + p;
    swap(a[r], a[q]);

    int x = a[q];
    int i = p - 1;

    // Partition the array around the pivot element
    for (int j = p; j < q; j++)
    {
        if (a[j] <= x)
        {
            i++;
            swap(a[i], a[j]);
        }
    }

    swap(a[i + 1], a[q]);
    return i + 1;
}

// Function to find the i-th smallest element in the array
int rand_select(vector<int> &a, int p, int q, int i)
{
    // Base case: If the array has only one element
    if (p == q)
        return a[p];

    // Partition the array and find the rank of the pivot element
    int r = rand_partition(a, p, q);
    int k = r - p + 1;

    // If the rank of the pivot element is equal to i, return the pivot element
    if (i == k)
        return a[r];
    // If the rank of the pivot element is greater than i, recursively find the i-th smallest element in the left subarray
    else if (i < k)
        return rand_select(a, p, r - 1, i);
    // If the rank of the pivot element is less than i, recursively find the (i-k)-th smallest element in the right subarray
    else
        return rand_select(a, r + 1, q, i - k);
}

int main()
{
    for (int n = 10; n < 1e7; n *= 10)
    {
        vector<int> a(n);
          // Fill vector with numbers from 0 to n-1
        for (int i = 0; i < n; ++i)
        {
            a[i] = i;
        }

          // Shuffle the elements
        unsigned seed = 345;
        shuffle(a.begin(), a.end(), default_random_engine(seed));

        auto start    = chrono::high_resolution_clock::now();
        int  k        = rand_select(a, 0, n - 1, n / 5);
        auto end      = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

        cout << "n = " << n << ", k = " << k << ", time = " << duration.count() << " μs" << endl;
    }

    return 0;
}