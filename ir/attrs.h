#pragma once

// Copyright (c) 2018-present The Alive2 Authors.
// Distributed under the MIT license that can be found in the LICENSE file.

#include <ostream>

namespace IR {

class ParamAttrs final {
  unsigned bits;

public:
  enum Attribute { None = 0, NonNull = 1<<0, ByVal = 1<<1, NoCapture = 1<<2,
                   NoRead = 1<<3, NoWrite = 1<<4, Dereferenceable = 1<<5,
                   NoUndef = 1<<6, Align = 1<<7, Returned = 1<<8,
                   NoAlias = 1<<9 };

  ParamAttrs(unsigned bits = None) : bits(bits) {}

  uint64_t derefBytes; // Dereferenceable
  unsigned blockSize;  // exact block size for e.g. byval args
  unsigned align = 1;

  bool has(Attribute a) const { return (bits & a) != 0; }
  void set(Attribute a) { bits |= (unsigned)a; }

  // Returns true if it's UB for the argument to be poison / have a poison elem.
  bool poisonImpliesUB() const
  { return has(Dereferenceable) || has(NoUndef) || has(ByVal); }

   // Returns true if it is UB for the argument to be (partially) undef.
  bool undefImpliesUB() const;

  uint64_t getDerefBytes() const;

  friend std::ostream& operator<<(std::ostream &os, const ParamAttrs &attr);
};


class FnAttrs final {
  unsigned bits;

public:
  enum Attribute { None = 0, NoRead = 1 << 0, NoWrite = 1 << 1,
                   ArgMemOnly = 1 << 2, NNaN = 1 << 3, NoReturn = 1 << 4,
                   Dereferenceable = 1 << 5, NonNull = 1 << 6,
                   NoFree = 1 << 7, NoUndef = 1 << 8, Align = 1 << 9,
                   NoThrow = 1 << 10, NoAlias = 1 << 11, WillReturn = 1 << 12 };

  FnAttrs(unsigned bits = None) : bits(bits) {}

  bool has(Attribute a) const { return (bits & a) != 0; }
  void set(Attribute a) { bits |= (unsigned)a; }

  uint64_t derefBytes; // Dereferenceable
  unsigned align = 1;

  // Returns true if returning poison or an aggregate having a poison is UB
  bool poisonImpliesUB() const;

  // Returns true if returning (partially) undef is UB
  bool undefImpliesUB() const;

  friend std::ostream& operator<<(std::ostream &os, const FnAttrs &attr);
};

}
