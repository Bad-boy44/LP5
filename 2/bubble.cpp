#include <iostream>
#include <ctime>
#include <cstdlib>
#include <omp.h>

using namespace std;

void bubbleSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = 0; j < n - i - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void printArray(int arr[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main()
{
    int n;
    cout << "Enter the size of the array: ";
    cin >> n;

    int *arr = new int[n];
    srand(time(0));
    for (int i = 0; i < n; ++i)
    {
        arr[i] = rand() % 100;
    }

    cout << "Original array: ";
    printArray(arr, n);

    // Sequential Bubble Sort
    clock_t start = clock();
    bubbleSort(arr, n);
    clock_t end = clock();

    cout << "Sequential Bubble Sorted array: ";
    printArray(arr, n);

    double sequentialBubbleTime = double(end - start) / CLOCKS_PER_SEC;

    // Parallel Bubble Sort
    start = clock();
    #pragma omp parallel
    {
        bubbleSort(arr, n);
    }
    end = clock();

    cout << "Parallel Bubble Sorted array: ";
    printArray(arr, n);

    double parallelBubbleTime = double(end - start) / CLOCKS_PER_SEC;

    // Performance measurement
    cout << "Sequential Bubble Sort Time: " << sequentialBubbleTime << " seconds" << endl;
    cout << "Parallel Bubble Sort Time: " << parallelBubbleTime << " seconds" << endl;

    delete[] arr;

    return 0;
}
