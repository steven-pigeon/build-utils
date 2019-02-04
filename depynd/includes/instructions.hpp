#ifndef __MODULE_INSTRUCTION__
#define __MODULE_INSTRUCTION__

#include <limits>
#include <type_traits>
#include <processor.hpp>

////////////////////////////////////////
class instruction
 {
  protected:

  // rather than implementing a complete instruction
  // encoding, 
      int r1,r2;
      processor::register_type c;

  public:

      // instructions do not affect flags
      // as there are no flags anyway.
      enum instruction_opcode
       {
        // basic arithmetic
        //
        add,   // ri += rj
        sub,   // ri -= rj
        mul,   // ri *= rj
        divmod, // (ri,rj) = (ri/rj,ri%rj)
        neg,    // ri = -ri
        sex,    // ri = sign-extend rj
        inc,    // ri++
        dec,    // ri--

        // unsightly underscores because most of
        // them are reserved keywords (c++98, §2.5)
        //
        and_,   // ri &= rj
        or_,    // ri |= rj
        xor_,   // ri ^= rj
        not_,   // ri = ~ri
        shr,    // ri >>= c (as unsigned)
        ashr,   // ri >>= c (as signed)
        shl,    // ri <<= c
        nand_,  // ri &= ~rj
        nor_,   // ri |= ~rj
        nxor_,  // ri ^= ~rj

        // misc
        //
        xchg,   // (ri,rj) = (rj,ri)
        clr,    // ri = 0
        bswap,  // change endian of ri

        // "fancy" instructions
        //
        gray,   // transforms to gray, ri ^= (r1>>1) (as unsigned)
        shuffle, // perfect shuffle of ri
        shrz,    // while ((ri & 1==0) && (ri)) ri >>= 1
        shlz,    // while ((ri & most_significant_bit==0) && (ri)) ri <<= 1
       };

      // instruction affects processor state,
      // not instruction state
      virtual void operator()(processor *) const=0;

  instruction(int r1_, int r2_, processor::register_type c_=0)
   : r1(r1_),r2(r2_),c(c_)
  {}

  virtual ~instruction()=default;
 };

#include <instructions-arithmetic.hpp>


#endif
     // __MODULE_INSTRUCTION__
