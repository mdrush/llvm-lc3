//===-- LC3FixupKinds.h - LC3-Specific Fixup Entries ------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LC3FIXUPKINDS_H
#define LLVM_LC3FIXUPKINDS_H

#include "llvm/MC/MCFixup.h"

namespace llvm {
namespace LC3 {
enum Fixups {
  fixup_lc3_mov_hi16_pcrel = FirstTargetFixupKind,
  fixup_lc3_mov_lo16_pcrel,

  // Marker
  LastTargetFixupKind,
  NumTargetFixupKinds = LastTargetFixupKind - FirstTargetFixupKind
};
}
}

#endif

