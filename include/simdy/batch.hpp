#ifndef SIMDY_DETAIL_INCLUDE_GUARD_BATCH
#define SIMDY_DETAIL_INCLUDE_GUARD_BATCH

#include <simdy/detail/native_batch.hpp>

#include <boost/config.hpp>

namespace simdy {
///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename InstructionSet, typename T>
struct batch {
    using instruction_set = InstructionSet;
    using element_type = T;

    using native_type = native_batch_t<instruction_set, element_type>;

    native_type native;

    constexpr static
    auto const width = sizeof(native_type) / sizeof(element_type);

    BOOST_FORCEINLINE
    batch(element_type value)
    : native(instruction_set::broadcast(value))
    {}

    template <typename... U, std::void_t<
        decltype(instruction_set::fill(std::declval<U>()...))
    >*...>
    BOOST_FORCEINLINE
    batch(U x...)
    : native(instruction_set::fill(x...))
    {}

    BOOST_FORCEINLINE
    batch(native_type native_batch)
    : native(native_batch)
    {}

    batch() = default;

    BOOST_FORCEINLINE
    operator native_type()
    const
    { return native; }
};

///////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif
