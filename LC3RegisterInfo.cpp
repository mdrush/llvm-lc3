//===-- LC3RegisterInfo.cpp - LC3 Register Information ----------------===//
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

#include "LC3RegisterInfo.h"
#include "LC3.h"
#include "LC3FrameLowering.h"
#include "LC3InstrInfo.h"
#include "LC3MachineFunctionInfo.h"
#include "llvm/ADT/BitVector.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/RegisterScavenging.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Type.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/MathExtras.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Target/TargetFrameLowering.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"

#define GET_REGINFO_TARGET_DESC
#include "LC3GenRegisterInfo.inc"

using namespace llvm;

LC3RegisterInfo::LC3RegisterInfo() : LC3GenRegisterInfo(LC3::LR) {}

const uint16_t *
LC3RegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
  static const uint16_t CalleeSavedRegs[] = { LC3::R4, LC3::R5, LC3::R6,
                                              LC3::R7, LC3::R8, LC3::R9,
                                              0 };
  return CalleeSavedRegs;
}

BitVector LC3RegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  BitVector Reserved(getNumRegs());

  Reserved.set(LC3::SP);
  Reserved.set(LC3::LR);
  return Reserved;
}

const uint32_t *LC3RegisterInfo::getCallPreservedMask(const MachineFunction &MF,
                                                      CallingConv::ID) const {
  return CC_Save_RegMask;
}

bool
LC3RegisterInfo::requiresRegisterScavenging(const MachineFunction &MF) const {
  return true;
}

bool
LC3RegisterInfo::trackLivenessAfterRegAlloc(const MachineFunction &MF) const {
  return true;
}

bool LC3RegisterInfo::useFPForScavengingIndex(const MachineFunction &MF) const {
  return false;
}

void LC3RegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
                                          int SPAdj, unsigned FIOperandNum,
                                          RegScavenger *RS) const {
  MachineInstr &MI = *II;
  const MachineFunction &MF = *MI.getParent()->getParent();
  const MachineFrameInfo *MFI = MF.getFrameInfo();
  MachineOperand &FIOp = MI.getOperand(FIOperandNum);
  unsigned FI = FIOp.getIndex();

  // Determine if we can eliminate the index from this kind of instruction.
  unsigned ImmOpIdx = 0;
  switch (MI.getOpcode()) {
  default:
    // Not supported yet.
    return;
  case LC3::LDR:
  case LC3::STR:
    ImmOpIdx = FIOperandNum + 1;
    break;
  }

  // FIXME: check the size of offset.
  MachineOperand &ImmOp = MI.getOperand(ImmOpIdx);
  int Offset = MFI->getObjectOffset(FI) + MFI->getStackSize() + ImmOp.getImm();
  FIOp.ChangeToRegister(LC3::SP, false);
  ImmOp.setImm(Offset);
}

unsigned LC3RegisterInfo::getFrameRegister(const MachineFunction &MF) const {
  return LC3::SP;
}
