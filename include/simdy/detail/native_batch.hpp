#ifndef SIMDY_DETAIL_INCLUDE_GUARD_DETAIL_NATIVE_BATCH
#define SIMDY_DETAIL_INCLUDE_GUARD_DETAIL_NATIVE_BATCH

namespace simdy::detail {
///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename InstructionSet, typename T, typename = void>
struct native_batch;

template <typename InstructionSet, typename T>
using native_batch_t = typename native_batch<InstructionSet, T>::type;

///////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif
