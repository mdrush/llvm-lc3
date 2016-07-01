//===-- LC3FrameLowering.h - Frame info for LC3 Target ------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains LC3 frame information that doesn't fit anywhere else
// cleanly...
//
//===----------------------------------------------------------------------===//

#ifndef LC3FRAMEINFO_H
#define LC3FRAMEINFO_H

#include "llvm/Target/TargetFrameLowering.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {
class LC3Subtarget;

class LC3FrameLowering : public TargetFrameLowering {
public:
  LC3FrameLowering();

  /// emitProlog/emitEpilog - These methods insert prolog and epilog code into
  /// the function.
  void emitPrologue(MachineFunction &MF,
                    MachineBasicBlock &MBB) const override;
  void emitEpilogue(MachineFunction &MF, MachineBasicBlock &MBB) const override;

  void eliminateCallFramePseudoInstr(MachineFunction &MF,
                                     MachineBasicBlock &MBB,
                                     MachineBasicBlock::iterator I)
                                     const override;

  bool hasFP(const MachineFunction &MF) const;

  //! Stack slot size (4 bytes)
  static int stackSlotSize() { return 4; }

private:
  uint64_t computeStackSize(MachineFunction &MF) const;
};
}

#endif // LC3FRAMEINFO_H

