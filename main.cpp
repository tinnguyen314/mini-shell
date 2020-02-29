#include <iostream>
#include <stdlib.h>

int main(){
    

    std::cout << "hello tin!" << std::endl;
    const int SIZE = 20;
    /*
    int* p = new int[SIZE];
    // int* p = (int*)malloc(20*sizeof(int));
    
    for (int i = 0; i < SIZE; i++) {
        p[i] = i; 
    }
    std::cout << p[SIZE - 1] << std::endl;  //question???
    std::cout << p[7] << std::endl;
    delete[] p;
    */
    
    // Take forever to run

    /*
    int n;
    std::cout << ("enter size of an array: ");
    std::cin >> n;
    //int *a =(int*)malloc(n*sizeof(int));
    int *a = new int[n];
    for (int i = 0; i < n; i++)
    {
        a[i] = i + 1;
    }
    for (int i = 0; i < n; i++)
    {
        std::cout << a[i] << std::endl;
    }
    delete[] a;
    */


}