#ifndef SIMDY_DETAIL_INCLUDE_GUARD_SSE
#define SIMDY_DETAIL_INCLUDE_GUARD_SSE

#include <simdy/detail/native_batch.hpp>

#include <boost/config.hpp>

namespace simdy::detail {
///////////////////////////////////////////////////////////////////////////////////////////////////

struct sse;

namespace detail {
    template <>
    struct native_batch<sse, float> {
        using type = __m128;
    };
}

struct sse {
    template <typename T>
    using native_batch_t = detail::native_batch_t<sse, T>;

    template <typename T, std::enable_if_t<std::is_same_v<T, float>>*...>
    BOOST_FORCEINLINE static
    auto add(auto a, auto b) {
        return _mm_add_ps(a, b);
    }

    template <typename T, std::enable_if_t<std::is_same_v<T, float>>*...>
    BOOST_FORCEINLINE static
    auto subtract(auto a, auto b) {
        return _mm_sub_ps(a, b);
    }

    template <typename T, std::enable_if_t<std::is_same_v<T, float>>*...>
    BOOST_FORCEINLINE static
    auto negate(auto x) {
        return _mm_xor_ps(_mm_set1_ps(-0.0f), x);
    }
};
    
///////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif
