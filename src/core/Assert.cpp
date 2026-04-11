#include "Assert.h"

#include <iostream>

namespace ACE
{
    void AssertionFailed(const char* expr,
                      const char* msg,
                      const char* file,
                      int line)
    {
        std::cerr << "ACE::ASSERT_FAILED\n"
                  << "Expr: " << expr << "\n"
                  << "Msg: " << msg << "\n"
                  << "File: " << file << ":" << line << std::endl;

        std::abort();
    }
}
