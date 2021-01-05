#include <iostream>

#include <memory>


#include <time.h>

namespace details
{
// left part right part
// a is [left .. mid] [mid + 1 .. right]
template<typename T>
void merge(T* a, int left, int mid, int right)
{
    // Temp array
    // This algorithm can be improved to O(1) extra space
    std::unique_ptr<T[]> temp(new T[right - left + 1]);

    // Ends of parts in temp array
    const int left_end = mid - left, right_end = right - left;

    // Indices iterators in temp array
    int current_left = 0;
    int current_right = mid + 1 - left;

    // Where to place new element
    int current = left;

    // Copy values to temp array
    for (int i = left, j = 0; i <= right; i++, j++)
    {
        temp[j] = a[i];
    }

    // while not run out of elements in both parts
    while (current_left <= left_end || current_right <= right_end)
    {
        // insert elements
        while (current_left <= left_end
            && (current_right > right_end
            || temp[current_left] <= temp[current_right]))
        {
            a[current++] = temp[current_left++];
        }

        while (current_right <= right_end
            && (current_left > left_end
            || temp[current_right] <= temp[current_left]))
        {
            a[current++] = temp[current_right++];
        }
    }
}

template<typename T>
void sort(T* a, int left, int right)
{
    if (right - left >= 1)
    {
        int mid = (left + right) / 2;
        sort(a, left, mid);
        sort(a, mid + 1, right);
        merge<T>(a, left, mid, right);
    }
}

} // namespacve details

template<typename T>
void sort(T* a, int size)
{
    details::sort(a, 0, size - 1);
}


// for algorithm test

const int N = 10000000;
double a[N];

double rnd(double min, double max)
{
    double f = (double)rand() / RAND_MAX;
    return min + f * (max - min);
}

int main()
{
    for(double& v : a)
    {
        v = rnd(-1e10, 1e10);
    }

    sort<double>(a, sizeof(a)/sizeof(double));

    bool ok = true;

    for(int i = 0; i + 1 < N; i++)
    {
        if (a[i] > a[i + 1])
        {
            ok = false;
            std::cout << "Error: i = " << i << "\n"
                      << a[i] << " > " << a[i + 1] << std::endl;
            break;
        }
    }

    if (ok)
    {
        std::cout << "Sort algorithm is working" << std::endl;
    }

    return 0;
}


