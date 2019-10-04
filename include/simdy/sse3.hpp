#ifndef SIMDY_DETAIL_INCLUDE_GUARD_SSE3
#define SIMDY_DETAIL_INCLUDE_GUARD_SSE3

#include <simdy/detail/native_batch.hpp>

#include <boost/config.hpp>

namespace simdy::detail {
///////////////////////////////////////////////////////////////////////////////////////////////////

struct sse3;

namespace detail {
    template <>
    struct native_batch<sse3, float> {
        using type = __m128;
    };

    template <>
    struct native_batch<sse3, double> {
        using type = __m128d;
    };

    template <typename T>
    struct native_batch<sse3, T, std::enable_if_t<std::is_integral_v<T>>> {
        using type = __m128i;
    };
}

struct sse3 {
    template <typename T>
    using native_batch_t = detail::native_batch_t<sse3, T>;


    BOOST_FORCEINLINE static
    auto fill(float x0, float x1, float x2, float x3) {
        return _mm_setr_ps(x0, x1, x2, x3);
    }

    BOOST_FORCEINLINE static
    auto fill(double x0, double x1) {
        return _mm_setr_pd(x0, x1);
    }

    template <typename T, std::enable_if_t<std::is_integral_v<T> && sizeof(T) == 1>*...>
    BOOST_FORCEINLINE static
    auto fill(T x0, T x1, T x2, T x3, T x4, T x5, T x6, T x7,
              T x8, T x9, T xA, T xB, T xC, T xD, T xE, T xF) {
        return _mm_setr_epi8(static_cast<std::int8_t>(x0), static_cast<std::int8_t>(x1),
                             static_cast<std::int8_t>(x2), static_cast<std::int8_t>(x3),
                             static_cast<std::int8_t>(x4), static_cast<std::int8_t>(x5),
                             static_cast<std::int8_t>(x6), static_cast<std::int8_t>(x7),
                             static_cast<std::int8_t>(x8), static_cast<std::int8_t>(x9),
                             static_cast<std::int8_t>(xA), static_cast<std::int8_t>(xB),
                             static_cast<std::int8_t>(xC), static_cast<std::int8_t>(xD),
                             static_cast<std::int8_t>(xE), static_cast<std::int8_t>(xF));
    }

    template <typename T, std::enable_if_t<std::is_integral_v<T> && sizeof(T) == 2>*...>
    BOOST_FORCEINLINE static
    auto fill(T x0, T x1, T x2, T x3, T x4, T x5, T x6, T x7) {
        return _mm_setr_epi16(static_cast<std::int16_t>(x0), static_cast<std::int16_t>(x1),
                              static_cast<std::int16_t>(x2), static_cast<std::int16_t>(x3),
                              static_cast<std::int16_t>(x4), static_cast<std::int16_t>(x5),
                              static_cast<std::int16_t>(x6), static_cast<std::int16_t>(x7));
    }

    template <typename T, std::enable_if_t<std::is_integral_v<T> && sizeof(T) == 4>*...>
    BOOST_FORCEINLINE static
    auto fill(T x0, T x1, T x2, T x3) {
        return _mm_setr_epi32(static_cast<std::int32_t>(x0), static_cast<std::int32_t>(x1),
                              static_cast<std::int32_t>(x2), static_cast<std::int32_t>(x3));
    }

    template <typename T, std::enable_if_t<std::is_integral_v<T> && sizeof(T) == 8>*...>
    BOOST_FORCEINLINE static
    auto fill(T x0, T x1) {
        return _mm_set_epi64x(static_cast<std::int64_t>(x1), static_cast<std::int64_t>(x0));
    }


    BOOST_FORCEINLINE static
    auto broadcast(float x) {
        return _mm_set1_ps(x);
    }

    BOOST_FORCEINLINE static
    auto broadcast(double x) {
        return _mm_set1_pd(x);
    }

    template <typename T, std::enable_if_t<std::is_integral_v<T> && sizeof(T) == 1>*...>
    BOOST_FORCEINLINE static
    auto broadcast(T x) {
        return _mm_set1_epi8(static_cast<std::int8_t>(x));
    }

    template <typename T, std::enable_if_t<std::is_integral_v<T> && sizeof(T) == 2>*...>
    BOOST_FORCEINLINE static
    auto broadcast(T x) {
        return _mm_set1_epi16(static_cast<std::int16_t>(x));
    }

    template <typename T, std::enable_if_t<std::is_integral_v<T> && sizeof(T) == 4>*...>
    BOOST_FORCEINLINE static
    auto broadcast(T x) {
        return _mm_set1_epi32(static_cast<std::int32_t>(x));
    }

    template <typename T, std::enable_if_t<std::is_integral_v<T> && sizeof(T) == 8>*...>
    BOOST_FORCEINLINE static
    auto broadcast(T x) {
        return _mm_set1_epi64(static_cast<std::int64_t>(x));
    }


    template <typename T>
    BOOST_FORCEINLINE static
    auto add(auto a, auto b) {
        if constexpr (std::is_same_v<T, float>) { return _mm_add_ps(a, b); }
        if constexpr (std::is_same_v<T, double>) { return _mm_add_pd(a, b); }
        if constexpr (std::is_integral_v<T>) {
            if constexpr (sizeof(T) == 1) { return _mm_add_epi8 (a, b); }
            if constexpr (sizeof(T) == 2) { return _mm_add_epi16(a, b); }
            if constexpr (sizeof(T) == 4) { return _mm_add_epi32(a, b); }
            if constexpr (sizeof(T) == 8) { return _mm_add_epi64(a, b); }
        }
    }
};
    
///////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif
