//===-- LC3Subtarget.cpp - LC3 Subtarget Information ------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements the LC3 specific subclass of TargetSubtargetInfo.
//
//===----------------------------------------------------------------------===//

#include "LC3Subtarget.h"
#include "LC3.h"
#include "llvm/Support/TargetRegistry.h"

#define DEBUG_TYPE "lc3-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "LC3GenSubtargetInfo.inc"

using namespace llvm;

void LC3Subtarget::anchor() {}

LC3Subtarget::LC3Subtarget(const Triple &TT, StringRef CPU, StringRef FS,
                           LC3TargetMachine &TM)
    : LC3GenSubtargetInfo(TT, CPU, FS),
      DL("e-m:e-p:16:16-i1:16:16-i8:16:16-i16:16:16-i32:32:32-f64:32-a:0:16-n16"),
      InstrInfo(), TLInfo(TM), TSInfo(), FrameLowering() {}
