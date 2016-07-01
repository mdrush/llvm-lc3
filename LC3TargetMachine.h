//===-- LC3TargetMachine.h - Define TargetMachine for LC3 ---*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares the LC3 specific subclass of TargetMachine.
//
//===----------------------------------------------------------------------===//

#ifndef LC3TARGETMACHINE_H
#define LC3TARGETMACHINE_H

#include "LC3.h"
#include "LC3FrameLowering.h"
#include "LC3ISelLowering.h"
#include "LC3InstrInfo.h"
#include "LC3SelectionDAGInfo.h"
#include "LC3Subtarget.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {

class LC3TargetMachine : public LLVMTargetMachine {
  LC3Subtarget Subtarget;
  std::unique_ptr<TargetLoweringObjectFile> TLOF;

public:
  LC3TargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                   StringRef FS, const TargetOptions &Options, Reloc::Model RM,
                   CodeModel::Model CM, CodeGenOpt::Level OL);
  
  const LC3Subtarget * getSubtargetImpl() const {
    return &Subtarget;
  }
  
  virtual const TargetSubtargetInfo *
  getSubtargetImpl(const Function &) const override {
    return &Subtarget;
  }

  // Pass Pipeline Configuration
  virtual TargetPassConfig *createPassConfig(PassManagerBase &PM) override;
  
  TargetLoweringObjectFile *getObjFileLowering() const override {
    return TLOF.get();
  }
};

} // end namespace llvm

#endif
