/**
 * @file k_nearest_neighbors.c
 * @brief K Nearest Neighbors Algorithm implemented
 * @details
 * This file has KNN algorithm implemented
 * It prints test output to console
 *
 * @author [Luis Ángel Meléndez] (https://github.com/LuisOfL)
 */

#include <float.h>   /* DBL_MAX */
#include <math.h>    /* sqrt */
#include <stdio.h>   /* printf */
#include <stdlib.h>  /* malloc, rand */
#include <time.h>    /* time */
#include <string.h>  /* memset */

/*!
 * @addtogroup machine_learning Machine Learning Algorithms
 * @{
 * @addtogroup knn K-Nearest Neighbors Algorithm
 * @{
 */

/*! @struct observation
 *  a class to store points in 2d plane
 *  x and y are coordinates, label is class
 */
typedef struct observation
{
    double x;      /**< x coordinate */
    double y;      /**< y coordinate */
    int label;     /**< class label */
} observation;

/*!
 * Calculate Euclidean distance between two points
 *
 * @param a  first observation
 * @param b  second observation
 *
 * @returns distance
 */
double euclideanDistance(observation* a, observation* b)
{
    return sqrt((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y));
}

/*!
 * Find the majority label among k nearest neighbors
 *
 * @param neighbors  array of nearest neighbors
 * @param k  number of neighbors
 *
 * @returns predicted label
 */
int majorityLabel(observation neighbors[], int k)
{
    int counts[100]; /* assuming max 100 classes */
    memset(counts, 0, sizeof(counts));

    for (int i = 0; i < k; i++)
    {
        counts[neighbors[i].label]++;
    }

    int maxCount = 0;
    int label = -1;
    for (int i = 0; i < 100; i++)
    {
        if (counts[i] > maxCount)
        {
            maxCount = counts[i];
            label = i;
        }
    }
    return label;
}

/*!
 * KNN algorithm
 *
 * @param train  training dataset
 * @param trainSize  number of training points
 * @param test  point to classify
 * @param k  number of neighbors
 *
 * @returns predicted label
 */
int kNearestNeighbors(observation train[], size_t trainSize, observation* test, int k)
{
    /* array to store distances and labels */
    observation* neighbors = malloc(sizeof(observation) * trainSize);

    for (size_t i = 0; i < trainSize; i++)
    {
        neighbors[i].x = euclideanDistance(&train[i], test);
        neighbors[i].label = train[i].label;
    }

    /* simple selection sort to find k smallest distances */
    for (int i = 0; i < k; i++)
    {
        int minIdx = i;
        for (int j = i + 1; j < trainSize; j++)
        {
            if (neighbors[j].x < neighbors[minIdx].x)
            {
                minIdx = j;
            }
        }
        if (minIdx != i)
        {
            observation tmp = neighbors[i];
            neighbors[i] = neighbors[minIdx];
            neighbors[minIdx] = tmp;
        }
    }

    /* take majority label among k nearest */
    int label = majorityLabel(neighbors, k);
    free(neighbors);
    return label;
}

/*!
 * Test the KNN function
 */
static void test()
{
    size_t size = 10;
    observation train[10];

    /* Generate random points with label 0 or 1 */
    for (size_t i = 0; i < size; i++)
    {
        train[i].x = ((double)rand() / RAND_MAX) * 10.0;
        train[i].y = ((double)rand() / RAND_MAX) * 10.0;
        train[i].label = i % 2; /* alternating labels 0 and 1 */
        printf("Train[%zu] = (%.2f, %.2f), label=%d\n", i, train[i].x, train[i].y, train[i].label);
    }

    observation testPoint;
    testPoint.x = 5.0;
    testPoint.y = 5.0;

    int k = 3;
    int predicted = kNearestNeighbors(train, size, &testPoint, k);
    printf("Test point (%.2f, %.2f) predicted label = %d\n", testPoint.x, testPoint.y, predicted);
}

/*!
 * Main function
 */
int main()
{
    srand(time(NULL));
    test();
    return 0;
}

/**
 * @}
 * @}
 */
