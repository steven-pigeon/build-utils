#ifndef __MODULE_INSTRUCTIONS_ARITHMETIC__
#define __MODULE_INSTRUCTIONS_ARITHMETIC__

////////////////////////////////////////
class add: public instruction
 {
  public:

      constexpr static instruction_opcode opcode{instruction_opcode::add};
      void operator()(processor * cpu) const override {cpu->registers[r1]+=cpu->registers[r2]; }

  add(int r1_,int r2_, int) : instruction(r1_,r2_,0) {};
  ~add() override=default;
 };

////////////////////////////////////////
class sub: public instruction
 {
  public:

      constexpr static instruction_opcode opcode{instruction_opcode::sub};
      void operator()(processor * cpu) const override { cpu->registers[r1]-=cpu->registers[r2]; }

  sub(int r1_,int r2_, int) : instruction(r1_,r2_,0) {};
  ~sub() override=default;
 };

////////////////////////////////////////
class mul: public instruction
 {
  public:

      constexpr static instruction_opcode opcode{instruction_opcode::mul};
      void operator()(processor * cpu) const override { cpu->registers[r1]*=cpu->registers[r2]; }

  mul(int r1_,int r2_, int) : instruction(r1_,r2_,0) {};
  ~mul() override=default;
 };

////////////////////////////////////////
class divmod: public instruction
 {
  public:

      constexpr static instruction_opcode opcode{instruction_opcode::divmod};
      void operator()(processor * cpu) const override
       {
        processor::register_type a=cpu->registers[r1];
        processor::register_type b=cpu->registers[r2];

        if (b)
         {
          cpu->registers[r1]=a/b;
          cpu->registers[r2]=a%b;
         }
        else
         // overflow occurs
         cpu->registers[r1]=
          cpu->registers[r2]=
          std::numeric_limits<processor::register_type>::max();
       }

  divmod(int r1_,int r2_, int) : instruction(r1_,r2_,0) {};
  ~divmod() override=default;
 };

////////////////////////////////////////
class neg: public instruction
 {
  public:

      constexpr static instruction_opcode opcode{instruction_opcode::neg};
      void operator()(processor * cpu) const override { cpu->registers[r1]=-cpu->registers[r1]; }

  neg(int r1_,int r2_, int) : instruction(r1_,r2_,0) {};
  ~neg() override=default;
 };

////////////////////////////////////////
class sex: public instruction
 {
  public:

      constexpr static instruction_opcode opcode{instruction_opcode::sex};
      void operator()(processor * cpu) const override
       {
        cpu->registers[r2]=
         ~(((cpu->registers[r1] & processor::most_significant_bit) >> (processor::register_bits-1)) -1);
       }

  sex(int r1_,int r2_, int) : instruction(r1_,r2_,0) {};
  ~sex() override=default;
 };

////////////////////////////////////////
class dec: public instruction
 {
  public:

      constexpr static instruction_opcode opcode{instruction_opcode::dec};
      void operator()(processor * cpu) const override { cpu->registers[r1]--; }

  dec(int r1_,int r2_, int) : instruction(r1_,r2_,0) {};
  ~dec() override=default;
 };

////////////////////////////////////////
class inc: public instruction
 {
  public:

      constexpr static instruction_opcode opcode{instruction_opcode::inc};
      void operator()(processor * cpu) const override { cpu->registers[r1]++; }

  inc(int r1_,int r2_, int) : instruction(r1_,r2_,0) {};
  ~inc() override=default;
 };

#endif
     // __MODULE_INSTRUCTIONS_ARITHMETIC__
