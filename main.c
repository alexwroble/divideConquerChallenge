/** 
 * Program Challenge: Divide and Conquer (see README)
 * Solution Author: Alexander Wroble
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    unsigned int p;
    unsigned int q;
} Pair;

//Merge function of mergeSort
void merge(Pair *myArr[], unsigned int a, unsigned int middle, unsigned int b)
{

    //number of elements on each side to be merged
    unsigned int firstSide = middle - a + 1;
    unsigned int secondSide = b - middle;

    //temp array with first side's elements
    Pair *S1[firstSide];
    for (unsigned int i = 0; i < firstSide; i++)
    {
        S1[i] = myArr[a + i];
    }

    //temp array with second side's elements
    Pair *S2[secondSide];
    for (unsigned int i = 0; i < secondSide; i++)
    {
        S2[i] = myArr[middle + i + 1];
    }

    unsigned int x = 0; //S1 index holder
    unsigned int y = 0; //S2 index holder
    unsigned int z = a; //index of finished array

    //re-adds pairs to myArr[] in sorted order
    while (x < firstSide && y < secondSide)
    {
        if (S1[x]->q <= S2[y]->q)
        {
            myArr[z] = S1[x];
            x++;
        }
        else
        {
            myArr[z] = S2[y];
            y++;
        }
        z++;
    }

    //Next two while loops fills remaining pairs (if any)
    while (x < firstSide)
    {
        myArr[z] = S1[x];
        x++;
        z++;
    }

    while (y < secondSide)
    {
        myArr[z] = S2[y];
        y++;
        z++;
    }
}

//MergeSort function (used with merge function above to instantiate the MergeSort method)
void mergeSort(Pair *myArr[], unsigned int a, unsigned int b)
{
    if (a < b)
    {
        unsigned int middle = (a + b) / 2;
        mergeSort(myArr, a, middle);     //recursive call for first half of array
        mergeSort(myArr, middle + 1, b); //...for second half of array
        merge(myArr, a, middle, b);      //call merge function to merge pairs back together
    }
}

//main method to execute challenge solution
int main(int argc, char *argv[])
{
    unsigned int answer = 0;
    unsigned int numInputs;
    scanf("%llu", &numInputs);

    //Empty array to be filled with 'pairs' (typedef above)
    Pair *myPairs[numInputs];

    //Read user input and add to "myPairs" array
    for (unsigned int i = 0; i < numInputs; i++)
    {
        Pair *newPair = malloc(sizeof(Pair));
        scanf("%llu", &(newPair->q));
        myPairs[i] = newPair;
    }
    for (unsigned int i = 0; i < numInputs; i++)
    {
        scanf("%llu", &(myPairs[i]->p));
    }

    //Use mergeSort algorithm to sort in O(nlogn) time
    mergeSort(myPairs, 0, numInputs - 1);

    //For testing purposes: prints all pairs collected from scanf
    // for(int i = 0; i < numInputs; i++){
    //         printf("You typed: (%d, %d)\n", myPairs[i]->q, myPairs[i]->p);
    // }

    //calculates number of intersecting lines, add to var "answer"
    for (unsigned int i = 0; i < numInputs - 1; i++)
    {
        unsigned int curr = myPairs[i]->p;
        for (unsigned int x = i + 1; x < numInputs; x++)
        {
            if (curr >= myPairs[x]->p)
            {
                answer++;
            }
        }
    }

    //print answer to terminal
    printf("%llu", answer);
}
