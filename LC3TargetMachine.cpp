//===-- LC3TargetMachine.cpp - Define TargetMachine for LC3 -----------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
//
//===----------------------------------------------------------------------===//

#include "LC3TargetMachine.h"
#include "LC3.h"
#include "LC3FrameLowering.h"
#include "LC3InstrInfo.h"
#include "LC3ISelLowering.h"
#include "LC3SelectionDAGInfo.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

static std::string computeDataLayout(const Triple &TT, StringRef CPU,
                                     const TargetOptions &Options) {
  // XXX Build the triple from the arguments.
  // This is hard-coded for now for this example target.
  return "e-m:e-p:32:32-i1:8:32-i8:8:32-i16:16:32-i64:32-f64:32-a:0:32-n32";
}

LC3TargetMachine::LC3TargetMachine(const Target &T, const Triple &TT,
                                   StringRef CPU, StringRef FS,
                                   const TargetOptions &Options,
                                   Reloc::Model RM, CodeModel::Model CM,
                                   CodeGenOpt::Level OL)
    : LLVMTargetMachine(T, computeDataLayout(TT, CPU, Options), TT, CPU, FS,
                        Options, RM, CM, OL),
      Subtarget(TT, CPU, FS, *this),
      TLOF(make_unique<TargetLoweringObjectFileELF>()) {
  initAsmInfo();
}

namespace {
/// LC3 Code Generator Pass Configuration Options.
class LC3PassConfig : public TargetPassConfig {
public:
  LC3PassConfig(LC3TargetMachine *TM, PassManagerBase &PM)
      : TargetPassConfig(TM, PM) {}

  LC3TargetMachine &getLC3TargetMachine() const {
    return getTM<LC3TargetMachine>();
  }

  virtual bool addPreISel() override;
  virtual bool addInstSelector() override;
  virtual void addPreEmitPass() override;
};
} // namespace

TargetPassConfig *LC3TargetMachine::createPassConfig(PassManagerBase &PM) {
  return new LC3PassConfig(this, PM);
}

bool LC3PassConfig::addPreISel() { return false; }

bool LC3PassConfig::addInstSelector() {
  addPass(createLC3ISelDag(getLC3TargetMachine(), getOptLevel()));
  return false;
}

void LC3PassConfig::addPreEmitPass() {}

// Force static initialization.
extern "C" void LLVMInitializeLC3Target() {
  RegisterTargetMachine<LC3TargetMachine> X(TheLC3Target);
}