#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

extern void x86(size_t n, double* result, double* a, double* b);
extern void SIMDX(size_t n, double* result, double* a, double* b);
extern void SIMDY(size_t n, double* result, double* a, double* b);

void dotprod(size_t n, double* result, double* a, double* b) {
    *result = 0.0;
    for (size_t i = 0; i < n; i++) {
        *result += a[i] * b[i];
    }
}

void verify_output(double expected, double actual, const char* label) {
    if (expected != actual)
        printf("%s program is incorrect\n", label);
    else
        printf("%s program is correct\n", label);
    
    printf("Expected result: %f, Actual result: %f\n\n", expected, actual);
}

int main() {
    size_t sizes[] = { 1 << 20, 1 << 26, 1 << 28 };  // bagal na ng 29 sakin e
    for (int s = 0; s < 3; s++) {
        size_t n = sizes[s];
        size_t array_bytes = n * sizeof(double);
        double* a = (double*)malloc(array_bytes);
        double* b = (double*)malloc(array_bytes);
        double* c = (double*)malloc(array_bytes);
        double result, result_C, result_x86, result_SIMDX, result_SIMDY;
        int i;

        for (i = 0; i < n; i++) {
            a[i] = 1.0;
            b[i] = 2.0;
        }
        printf("\n---------------------------------------------\n", n);
        printf("\n----Test for vector size n = %zu\n", n);

        LARGE_INTEGER li;
        long long int start, end;
        double PCFreq, elapse;
        QueryPerformanceFrequency(&li);
        PCFreq = (double)(li.QuadPart);

        // ---- C ----
        QueryPerformanceCounter(&li);
        start = li.QuadPart;
        dotprod(n, &result_C, a, b);
        QueryPerformanceCounter(&li);
        end = li.QuadPart;
        elapse = ((double)(end - start)) * 1000.0 / PCFreq;
        printf("Time in C= %f ms\n", elapse);
        printf("C program is correct\n");
        for (i = 0; i < 10; i++) {
            printf("c[%d] = %f\n", i, result_C);
        }

        //  x86
        QueryPerformanceCounter(&li);
        start = li.QuadPart;
        x86(n, &result_x86, a, b);
        QueryPerformanceCounter(&li);
        end = li.QuadPart;
        elapse = ((double)(end - start)) * 1000.0 / PCFreq;
        printf("\nTime in x86 = %f ms\n", elapse);
        for (i = 0; i < 10; i++) {
            printf("c[%d] = %f\n", i, result_x86);
        }
        verify_output(result_C, result_x86, "x86-64");

        // xmm
     
        QueryPerformanceCounter(&li);
        start = li.QuadPart;
        SIMDX(n, &result_SIMDX, a, b);
        QueryPerformanceCounter(&li);
        end = li.QuadPart;
        elapse = ((double)(end - start)) * 1000.0 / PCFreq;
        printf("Time in SIMD XMM = %f ms\n", elapse);
        for (i = 0; i < 10; i++) {
            printf("c[%d] = %f\n", i, result_SIMDX);
        }
        verify_output(result_C, result_SIMDX, "SIMD XMM");

        // ymm
        QueryPerformanceCounter(&li);
        start = li.QuadPart;
        SIMDY(n, &result_SIMDY, a, b);
        QueryPerformanceCounter(&li);
        end = li.QuadPart;
        elapse = ((double)(end - start)) * 1000.0 / PCFreq;
        printf("Time in SIMD YMM = %f ms\n", elapse);
        for (i = 0; i < 10; i++) {
            printf("c[%d] = %f\n", i, result_SIMDY);
        }
        verify_output(result_C, result_SIMDY, "SIMD YMM");

        printf("--- Averge time for vector size n = %zu\n", n);

        // C
        double total_time = 0.0;
        for (i = 0; i < 30; i++) {
            QueryPerformanceCounter(&li);
            start = li.QuadPart;
            dotprod(n, &result, a, b);
            QueryPerformanceCounter(&li);
            end = li.QuadPart;
            elapse = ((double)(end - start)) * 1000.0 / PCFreq;
            total_time += elapse;
        }
        printf("Ave time in C = %f ms\n", total_time / 30.0);

        // x86
        total_time = 0.0;
        for (i = 0; i < n; i++) {
            c[i] = 0.0;
        }
        for (i = 0; i < 30; i++) {
            QueryPerformanceCounter(&li);
            start = li.QuadPart;
            x86(n, c, a, b);
            QueryPerformanceCounter(&li);
            end = li.QuadPart;
            elapse = ((double)(end - start)) * 1000.0 / PCFreq;
            total_time += elapse;
        }
        printf("Ave time in x86-64 = %f ms\n", total_time / 30.0);

        // xmm
        total_time = 0.0;
        for (i = 0; i < n; i++) {
            c[i] = 0.0;
        }
        for (i = 0; i < 30; i++) {
            QueryPerformanceCounter(&li);
            start = li.QuadPart;
            SIMDX(n, c, a, b);
            QueryPerformanceCounter(&li);
            end = li.QuadPart;
            elapse = ((double)(end - start)) * 1000.0 / PCFreq;
            total_time += elapse;
        }
        printf("Ave time in SIMD XMM = %f ms\n", total_time / 30.0);

        // ymm
        total_time = 0.0;
        for (i = 0; i < n; i++) {
            c[i] = 0.0;
        }
        for (i = 0; i < 30; i++) {
            QueryPerformanceCounter(&li);
            start = li.QuadPart;
            SIMDY(n, c, a, b);
            QueryPerformanceCounter(&li);
            end = li.QuadPart;
            elapse = ((double)(end - start)) * 1000.0 / PCFreq;
            total_time += elapse;
        }
        printf("Ave time in SIMD YMM = %f ms\n\n", total_time / 30.0);
    }

    return 0;
}
