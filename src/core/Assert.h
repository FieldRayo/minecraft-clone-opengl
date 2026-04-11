#pragma once

namespace ACE { // Ayala Core Engine
    void AssertionFailed(const char* expr,
                         const char* msg,
                         const char* file,
                         int line);
}

#ifdef DEBUG

#define ACE_ASSERT(x, msg) \
    if (!(x)) ACE::AssertionFailed(#x, msg, __FILE__, __LINE__)

#else

#define ACE_ASSERT(x, msg)

#endif // DEBUG
