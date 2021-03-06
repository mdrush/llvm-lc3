//===-- LC3Subtarget.h - Define Subtarget for the LC3 -------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares the LC3 specific subclass of TargetSubtargetInfo.
//
//===----------------------------------------------------------------------===//

#ifndef LC3SUBTARGET_H
#define LC3SUBTARGET_H

#include "LC3.h"
#include "LC3FrameLowering.h"
#include "LC3ISelLowering.h"
#include "LC3InstrInfo.h"
#include "LC3SelectionDAGInfo.h"
#include "LC3Subtarget.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetSubtargetInfo.h"
#include <string>

#define GET_SUBTARGETINFO_HEADER
#include "LC3GenSubtargetInfo.inc"

namespace llvm {
class StringRef;

class LC3Subtarget : public LC3GenSubtargetInfo {
  virtual void anchor();

private:
  const DataLayout DL;       // Calculates type size & alignment.
  LC3InstrInfo InstrInfo;
  LC3TargetLowering TLInfo;
  LC3SelectionDAGInfo TSInfo;
  LC3FrameLowering FrameLowering;
  InstrItineraryData InstrItins;

public:
  /// This constructor initializes the data members to match that
  /// of the specified triple.
  ///
  LC3Subtarget(const Triple &TT, StringRef CPU,
               StringRef FS, LC3TargetMachine &TM);

  /// getInstrItins - Return the instruction itineraries based on subtarget
  /// selection.
  const InstrItineraryData *getInstrItineraryData() const override {
    return &InstrItins;
  }
  const LC3InstrInfo *getInstrInfo() const override { return &InstrInfo; }
  const LC3RegisterInfo *getRegisterInfo() const override {
    return &InstrInfo.getRegisterInfo();
  }
  const LC3TargetLowering *getTargetLowering() const override {
    return &TLInfo;
  }
  const LC3FrameLowering *getFrameLowering() const override {
    return &FrameLowering;
  }
  const LC3SelectionDAGInfo *getSelectionDAGInfo() const override {
    return &TSInfo;
  }

  /// ParseSubtargetFeatures - Parses features string setting specified
  /// subtarget options.  Definition of function is auto generated by tblgen.
  void ParseSubtargetFeatures(StringRef CPU, StringRef FS);
};
} // End llvm namespace

#endif

