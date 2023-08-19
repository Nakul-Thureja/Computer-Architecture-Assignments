#include "base/trace.hh"
#include "base/logging.hh"
#include "debug/ADDRESULT.hh"
#include "debug/DOTRESULT.hh"
#include "debug/NORMALIZE.hh"
#include "debug/VECTOR.hh"
#include "A2/vector_op.hh"
#include <iostream>
#include <math.h>
#include <cstdlib>

using namespace std;
namespace gem5
{
    float *A;
    float *B;
    int size;
    int i;
    int tick1, tick2, tick3;

    VectorOperations::VectorOperations(const VectorOperationsParams &params) : SimObject(params), event1([this]
                                                                                                         { processEvent1(); },
                                                                                                         name()),
                                                                               event2([this]
                                                                                      { processEvent2(); },
                                                                                      name()),
                                                                               event3([this]
                                                                                      { processEvent3(); },
                                                                                      name()),
                                                                               vectors(params.parameter)
    {

        cout << "\nDEBUG FLAGS\n";
        cout << "VECTOR: display the vectors\n";
        cout << "ADDRESULT: display the resultant vector from VectorAddition\n";
        cout << "DOTRESULT: display the resultant value from VectorDotProduct\n";
        cout << "NORMALIZ: display the resultant vectors from NormalizeVector\n\n";

        int index = 0;
        int curr = 0;
        while (vectors[index] != ' ')
        {
            curr = curr * 10 + (vectors[index] - '0');
            index++;
        }
        index++;
        A = (float *)calloc(curr, sizeof(int));
        B = (float *)calloc(curr, sizeof(int));
        size = curr;
        for (int i = 0; i < size; i++)
        {
            curr = 0;
            while (vectors[index] != ' ')
            {
                curr = curr * 10 + (vectors[index] - '0');
                index++;
            }
            index++;
            A[i] = curr;
        }

        for (int i = 0; i < size; i++)
        {
            curr = 0;
            while (vectors[index] != ' ')
            {
                curr = curr * 10 + (vectors[index] - '0');
                index++;
            }
            index++;
            B[i] = curr;
        }
        DPRINTF(VECTOR, "created Vectors\n");
        DPRINTF(VECTOR, "Vector 1:\n");
        for (int i = 0; i < size; i++)
        {
            DPRINTF(VECTOR, "%f ", A[i]);
        }
        DPRINTF(VECTOR, "\n");
        DPRINTF(VECTOR, "Vector 2:\n");
        for (int i = 0; i < size; i++)
        {
            DPRINTF(VECTOR, "%f ", B[i]);
        }
        DPRINTF(VECTOR, "\n");
        DPRINTF(VECTOR, "Ticks: \n");
        curr = 0;
        while (vectors[index] != ' ')
        {
            curr = curr * 10 + (vectors[index] - '0');
            index++;
        }
        tick1 = curr;
        DPRINTF(VECTOR, "%d ", tick1);
        index++;

        curr = 0;
        while (vectors[index] != ' ')
        {
            curr = curr * 10 + (vectors[index] - '0');
            index++;
        }
        tick2 = curr;
        DPRINTF(VECTOR, "%d ", tick2);
        index++;

        curr = 0;
        while (vectors[index] != ' ')
        {
            curr = curr * 10 + (vectors[index] - '0');
            index++;
        }
        tick3 = curr;
        DPRINTF(VECTOR, "%d \n\n", tick3);
        index++;
    }

    void VectorOperations::processEvent1()
    {

        float sum[size];
        cout << "\nResultant Addition Vector: ";
        for (i = 0; i < size; i++)
        {
            sum[i] = A[i] + B[i];
            cout << sum[i] << " ";
        }
        cout << "\n\n";

        DPRINTF(ADDRESULT, "Addition Vector:");
        for (i = 0; i < size; i++)
        {
            DPRINTF(ADDRESULT, "%f ", sum[i]);
        }
        DPRINTF(ADDRESULT, "\n");
    }

    void VectorOperations::processEvent2()
    {

        float dot = 0;
        for (i = 0; i < size; i++)
            dot = dot + A[i] * B[i];

        cout << "\nDot Product: " << dot << endl
             << endl;
        DPRINTF(DOTRESULT, "Dot Product: %f \n", dot);
    }

    void VectorOperations::processEvent3()
    {

        float sum1 = 0;
        float sum2 = 0;

        for (i = 0; i < size; i++)
        {
            sum1 += A[i] * A[i];
            sum2 += B[i] * B[i];
        }
        sum1 = sqrt(sum1);
        sum2 = sqrt(sum2);

        for (i = 0; i < size; i++)
        {
            A[i] = A[i] / sum1;
            B[i] = B[i] / sum2;
        }

        cout << "\nResultant Normal Vector 1: \n";
        for (i = 0; i < size; i++)
        {
            cout << A[i] << " ";
        }
        cout << "\n";

        cout << "Resultant Normal Vector 2: \n";
        for (i = 0; i < size; i++)
        {
            cout << B[i] << " ";
        }
        cout << "\n\n";

        DPRINTF(NORMALIZE, "Normal Vector 1: \n");

        for (i = 0; i < size; i++)
        {
            DPRINTF(NORMALIZE, "%f ", A[i]);
        }
        DPRINTF(NORMALIZE, "\n");

        DPRINTF(NORMALIZE, "Normal Vector 2: \n");
        for (i = 0; i < size; i++)
        {
            DPRINTF(NORMALIZE, "%f ", B[i]);
        }
        DPRINTF(NORMALIZE, "\n");
    }

    void
    VectorOperations::startup()
    {
        schedule(event1, tick1);
        schedule(event2, tick2);
        schedule(event3, tick3);
    }
}
