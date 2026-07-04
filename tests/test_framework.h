#pragma once

#include <iostream>

inline int g_testsRun = 0;
inline int g_testsPassed = 0;
inline int g_testsFailed = 0;

#define REQUIRE(condition)                                    \
    do                                                        \
    {                                                         \
        g_testsRun++;                                         \
        if (condition)                                        \
        {                                                     \
            g_testsPassed++;                                  \
        }                                                     \
        else                                                  \
        {                                                     \
            g_testsFailed++;                                  \
            std::cout << "  [FAIL] " << #condition            \
                      << "  (" << __FILE__ << ":" << __LINE__ \
                      << ")\n";                               \
        }                                                     \
    } while (0)

inline void printTestSummary()
{
    std::cout << "\n===== TEST SUMMARY =====\n";
    std::cout << "Total: " << g_testsRun
              << " | Passed: " << g_testsPassed
              << " | Failed: " << g_testsFailed << "\n";

    if (g_testsFailed == 0)
    {
        std::cout << "ALL TESTS PASSED\n";
    }
    else
    {
        std::cout << "SOME TESTS FAILED\n";
    }
}