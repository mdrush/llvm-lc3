//===-- LC3MCAsmInfo.h - LC3 asm properties --------------------*- C++ -*--===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the declaration of the LC3MCAsmInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef LC3TARGETASMINFO_H
#define LC3TARGETASMINFO_H

#include "llvm/MC/MCAsmInfoELF.h"

namespace llvm {
class StringRef;
class Target;
class Triple;

class LC3MCAsmInfo : public MCAsmInfoELF {
  virtual void anchor();

public:
  explicit LC3MCAsmInfo(const Triple &TT);
};

} // namespace llvm

#endif
