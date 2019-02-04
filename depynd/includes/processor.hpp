#ifndef __MODULE_PROCESSOR__
#define __MODULE_PROCESSOR__

#include <cstdint>
#include <cstddef>
#include <type_traits>
#include <limits>

////////////////////////////////////////
//
// emulates a very simple CPUette
//
// A "real" CPU would have state flags
// (like carry, zero, parity, etc.) but
// we won't be needing them for now. It
// would also have complex registers
// (with parts and sub-parts) but we won't
// need that either.
//
class processor
 {
  public:

      // lots o'stuff for type safety
      constexpr static size_t nb_registers{2}; // no storage!
      using register_type=uint64_t;
      constexpr static size_t register_bits=
       std::numeric_limits<std::make_unsigned<register_type>::type>::digits;
      constexpr static register_type most_significant_bit=
       register_type{1} << (register_bits-1);

      register_type registers[nb_registers];

      void reset()
       {
        registers[1]=registers[0]=0;
       }

  processor()
   : registers{0} // zeroes all
  {}

  ~processor()=default;
 };

#endif
    // __MODULE_PROCESSOR__
