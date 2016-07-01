//===-- LC3MachineFuctionInfo.h - LC3 machine function info -*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares LC3-specific per-machine-function information.
//
//===----------------------------------------------------------------------===//

#ifndef LC3MACHINEFUNCTIONINFO_H
#define LC3MACHINEFUNCTIONINFO_H

#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"

namespace llvm {

// Forward declarations
class Function;

/// LC3FunctionInfo - This class is derived from MachineFunction private
/// LC3 target-specific information for each MachineFunction.
class LC3FunctionInfo : public MachineFunctionInfo {
public:
  LC3FunctionInfo() {}

  ~LC3FunctionInfo() {}
};
} // End llvm namespace

#endif // LC3MACHINEFUNCTIONINFO_H

