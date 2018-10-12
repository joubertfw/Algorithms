#include <iostream>
#include <fstream>

using namespace std;

void insertionSort(int *arr, int n)
{
   int i, key, j;
   for (i = 1; i < n; i++)
   {
       key = arr[i];
       j = i-1; 
       while (j >= 0 && arr[j] > key)
       {
           arr[j+1] = arr[j];
           j = j-1;
       }
       arr[j+1] = key;
   }
}

int main(int argc, char* argv[])
{
    int ord[VECTOR_SIZE] = {0};
    int i;
    int n;

    ifstream file;
    file.open(argv[1]);    

    while(fp >> n)
    {
        ord[i] = n;
    }

    for (i = 0; i < VECTOR_SIZE; i++)
    {
        cout << ord[i] << endl;
    }
    insertionSort(ord, VECTOR_SIZE);

    file.close()

    return 0;
}