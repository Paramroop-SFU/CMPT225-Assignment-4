// a4_sort_implementations.h

/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : <Paramroop Parmar>
// St.# : <301555338>
// Email: <psp10@sfu.ca>
//
//
// Statement of Originality
// ------------------------
//
// All the code and comments below are my own original work. For any non-
// original work, I have provided citations in the comments with enough
// detail so that someone can see the exact source and extent of the
// borrowed work.
//
// In addition, I have not shared this work with anyone else, and I have
// not seen solutions from other students, tutors, websites, books,
// etc.
//
/*
// Cite: under each function

*/
/////////////////////////////////////////////////////////////////////////

#pragma once

#include "a4_base.h"
//
// Do NOT add any other #includes to this file!
//

using namespace std;



// Cite: Given in assignment page 110
template <typename T>
Sort_stats bubble_sort(vector<T> &v)
{
    ulong num_comps = 0; // <--- num_comps is initialized to 0 here
    clock_t start = clock();

    for (int i = 0; i < v.size(); i++)
    {
        for (int j = 0; j < v.size() - 1; j++)
        {
            num_comps++; // <--- num_comps is incremented here
            if (v[j] > v[j + 1])
            {
                T temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }

    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;
    return Sort_stats{"Bubble sort",
                      v.size(),
                      num_comps,
                      elapsed_cpu_time_sec};
}



// Cite: From the 225 textbook
template <typename T>
Sort_stats insertion_sort(vector<T> &v)
{
    ulong num_comps = 0; // Initialize the number of comparisons to 0
    clock_t start = clock();

    for (int i = 1; i < v.size(); i++)
    {
        T pos = v[i];
        int j = i - 1;

        while (j >= 0 && v[j] > pos)
        {

            v[j + 1] = v[j];
            j--;
            num_comps++;
        }
        v[j + 1] = pos;
    }

    clock_t end = clock();
    double elapsed_cpu_time_sec = static_cast<double>(end - start) / CLOCKS_PER_SEC;

    return Sort_stats{"insertion_sort",
                      v.size(),
                      num_comps,
                      elapsed_cpu_time_sec};
}



// Cite: https://www.geeksforgeeks.org/selection-sort/
template <typename T>
Sort_stats selection_sort(vector<T> &v)
{
    ulong num_comps = 0; // <--- num_comps is initialized to 0 here
    clock_t start = clock();
    for (int i = 0; i < v.size(); i++)
    {
        T pos = v[i];
        int j = i;

        for (int p = i; p < v.size(); p++)
        {
            num_comps++;
            if (pos > v[p])
            {
                pos = v[p];
                j = p;
            }
        }
        v[j] = v[i];
        v[i] = pos;
    }
    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;
    return Sort_stats{"Selection_sort",
                      v.size(),
                      num_comps,
                      elapsed_cpu_time_sec};
}




// Cite: https://www.geeksforgeeks.org/shellsort/
template <typename T>
Sort_stats shell_sort(vector<T> &v)
{
    ulong num_comps = 0; // <--- num_comps is initialized to 0 here
    clock_t start = clock();
    int n = v.size();

    // Start with a large gap and reduce it over iterations
    for (int gap = n / 2; gap > 0; gap = gap / 2)
    {
        // Pesudo insertion sort
        for (int i = gap; i < v.size(); i++)
        {
            T temp = v[i];
            int j;
            for (j = i; j >= gap && v[j - gap] > temp; j -= gap)
            {
                num_comps++;
                v[j] = v[j - gap];
            }
            v[j] = temp;
        }
    }
    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;
    return Sort_stats{"Shell_sort",
                      v.size(),
                      num_comps,
                      elapsed_cpu_time_sec};
}






// helper function for merge sort
template <typename T>
vector<T> merge(const vector<T> &v1, const vector<T> &v2, ulong &num)
{
    vector<T> v;
    int i = 0;
    int j = 0;
    while (i < v1.size() && j < v2.size())
    {
        num++;
        if (v1[i] < v2[j])
        {
            v.push_back(v1[i]);
            i++;
        }
        else
        {
            v.push_back(v2[j]);
            j++;
        }
    }
    while (i < v1.size())
    {

        v.push_back(v1[i]);
        i++;
    }
    while (j < v2.size())
    {

        v.push_back(v2[j]);
        j++;
    }
    return v;
}

// helper function for merge sort
template <typename T> 
void merge_sort_helper(vector<T> &v, ulong &num)
{

    if (v.size() <= 1)
    {
        return;
    }
    int mid = v.size() / 2;
    vector<T> v1(v.begin(), v.begin() + mid);
    vector<T> v2(v.begin() + mid, v.end());
    merge_sort_helper(v1, num);
    merge_sort_helper(v2, num);
    v = merge(v1, v2, num);
}

// cite: Prof's notes week 9 sorting.cpp
template <typename T>
Sort_stats merge_sort(vector<T> &v)
{
    ulong num_comps = 0;     // Initialize the number of comparisons to 0
    clock_t start = clock(); // Record the start time

    merge_sort_helper(v, num_comps);

    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;
    return Sort_stats{"Merge_sort",
                      v.size(),
                      num_comps,
                      elapsed_cpu_time_sec};
}




// helper function for iquick sort and quick sort
template <typename T>
int partition(vector<T> &v, int low, int high, ulong &num_comps)
{
    T pivot = v[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        num_comps++; // Increment the comparison count
        if (v[j] <= pivot)
        {
            i++;
            swap(v[i], v[j]);
        }
    }

    swap(v[i + 1], v[high]);
    return i + 1;
}


// helper function for quick sort
template <typename T>
void quick(vector<T> &v, int low, int high, ulong &num_comps)
{
    if (low < high)
    {
        int pi = partition(v, low, high, num_comps);
        quick(v, low, pi - 1, num_comps);
        quick(v, pi + 1, high, num_comps);
    }
}


// Cite: week 9 sorting.cpp
template <typename T>
Sort_stats quick_sort(vector<T> &v)
{
    ulong num_comps = 0;     // Initialize the number of comparisons to 0
    clock_t start = clock(); // Record the start time

    int low = 0;
    int high = v.size() - 1;

    quick(v, low, high, num_comps);

    clock_t end = clock(); // Record the end time
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;

    return Sort_stats{"Quick sort",
                      v.size(),
                      num_comps,
                      elapsed_cpu_time_sec};
}








// helper function for iquicksort
template <typename T>
void insert(vector<T> &v, int low, int high, ulong &num_comparisons)
{
    for (int i = low + 1; i <= high; i++)
    {
        T key = v[i];
        int j = i - 1;
        num_comparisons++;
        while (j >= low && v[j] > key)
        {
            num_comparisons++;
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = key;
    }
}

//helper for quick sort
template <typename T>
void iquick(vector<T> &v, int low, int high, ulong &num_comps, int threshold)
{
    if (low < high)
    {
        if (high - low + 1 < threshold)
        {
            insert(v, low, high, num_comps);
            return;
        }
        int pi = partition(v, low, high, num_comps);
        iquick(v, low, pi - 1, num_comps, threshold);
        iquick(v, pi + 1, high, num_comps, threshold);
    }
}

// cite: https://www.geeksforgeeks.org/advanced-quick-sort-hybrid-algorithm/
template <typename T>
Sort_stats iquick_sort(vector<T> &v)
{
    ulong num_comps = 0;     // Initialize the number of comparisons to 0
    clock_t start = clock(); // Record the start time

    const int threshold = 10; // You can adjust this threshold as needed
    int low = 0;
    int high = v.size() - 1;

    iquick(v, low, high, num_comps, threshold);

    clock_t end = clock(); // Record the end time
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;

    return Sort_stats{"iquick sort",
                      v.size(),
                      num_comps,
                      elapsed_cpu_time_sec};
}




// class for pqueue
template <typename T>
class Pqueue
{
private:
    vector<T> v;
    int num_comp = 0;

public:
    int size() const
    {
        return v.size();
    }

    bool empty() const
    {
        return size() == 0;
    }

    void insert(const T &x)
    {
        v.push_back(x);
        int i = size() - 1;
        while (i > 0 && v[i] < v[(i - 1) / 2])
        {
            num_comp++;
            swap(v[i], v[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    const T &min() const
    {
        // assert(!empty());
        return v[0];
    }

    //
    void remove_min()
    {
        // assert(!empty());
        //  replace root with last element
        v[0] = v.back();
        v.pop_back();

        int i = 0;
        while (2 * i + 1 < size())
        {
            num_comp++;
            int j = 2 * i + 1;
            if (j + 1 < size() && v[j + 1] < v[j])
            {
                j++;
            }
            num_comp++;
            if (v[i] <= v[j])
            {
                break;
            }
            swap(v[i], v[j]);
            i = j;
        }
    }

    ulong compare() { return num_comp; }
};


//cite: From notes, week7_priority_queues.pptx
template <typename T>
Sort_stats priority_queue_sort(vector<T> &v)
{
    clock_t start = clock();
    Pqueue<T> pq;

    while (!v.empty())
    {
        pq.insert(v.back());
        v.pop_back();
    }
    while (!pq.empty())
    {
        v.push_back(pq.min());
        pq.remove_min();
    }

    clock_t end = clock();
    double elapsed_cpu_time_sec = static_cast<double>(end - start) / CLOCKS_PER_SEC;

    return Sort_stats{"Priority Queue sort", v.size(), pq.compare(), elapsed_cpu_time_sec};
}




vector<int> rand_vec(int size, int min, int max)
{
    vector<int> v;

    for (int i = 0; i < size; i++)
    {
        int temp = min + rand() % (max - min + 1);
        v.push_back(temp);
    }
    return v;
}



// cite: week 7 notes
template <typename T>
bool is_sorted(vector<T> &v)
{
    if (v.empty())
    {
        return true;
    }

    for (int i = 1; i < v.size(); i++)
    {
        if (v[i] < v[i - 1])
        {
            return false;
        }
    }

    return true;
}