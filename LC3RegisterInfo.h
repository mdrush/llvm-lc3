//===-- LC3RegisterInfo.h - LC3 Register Information Impl ---*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the LC3 implementation of the MRegisterInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef LC3REGISTERINFO_H
#define LC3REGISTERINFO_H

#include "llvm/Target/TargetRegisterInfo.h"

#define GET_REGINFO_HEADER
#include "LC3GenRegisterInfo.inc"

namespace llvm {

class TargetInstrInfo;

struct LC3RegisterInfo : public LC3GenRegisterInfo {
public:
  LC3RegisterInfo();

  /// Code Generation virtual methods...
  const uint16_t *getCalleeSavedRegs(const MachineFunction *MF = 0) const
      override;

  const uint32_t *getCallPreservedMask(const MachineFunction &MF,
                                       CallingConv::ID) const override;

  BitVector getReservedRegs(const MachineFunction &MF) const override;

  bool requiresRegisterScavenging(const MachineFunction &MF) const override;

  bool trackLivenessAfterRegAlloc(const MachineFunction &MF) const override;

  bool useFPForScavengingIndex(const MachineFunction &MF) const override;

  void eliminateFrameIndex(MachineBasicBlock::iterator II, int SPAdj,
                           unsigned FIOperandNum, RegScavenger *RS = NULL) const
      override;

  // Debug information queries.
  unsigned getFrameRegister(const MachineFunction &MF) const;
};

} // end namespace llvm

#endif
