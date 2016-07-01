//===-- LC3.h - Top-level interface for LC3 representation --*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the entry points for global functions defined in the LLVM
// LC3 back-end.
//
//===----------------------------------------------------------------------===//

#ifndef TARGET_LC3_H
#define TARGET_LC3_H

#include "MCTargetDesc/LC3MCTargetDesc.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {
class TargetMachine;
class LC3TargetMachine;

FunctionPass *createLC3ISelDag(LC3TargetMachine &TM,
                               CodeGenOpt::Level OptLevel);
} // end namespace llvm;

#endif
