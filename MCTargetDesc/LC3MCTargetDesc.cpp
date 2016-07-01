//===-- LC3MCTargetDesc.cpp - LC3 Target Descriptions -----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file provides LC3 specific target descriptions.
//
//===----------------------------------------------------------------------===//

#include "LC3MCTargetDesc.h"
#include "InstPrinter/LC3InstPrinter.h"
#include "LC3MCAsmInfo.h"
#include "llvm/MC/MCCodeGenInfo.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/FormattedStream.h"
#include "llvm/Support/TargetRegistry.h"

#define GET_INSTRINFO_MC_DESC
#include "LC3GenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "LC3GenSubtargetInfo.inc"

#define GET_REGINFO_MC_DESC
#include "LC3GenRegisterInfo.inc"

using namespace llvm;

static MCInstrInfo *createLC3MCInstrInfo() {
  MCInstrInfo *X = new MCInstrInfo();
  InitLC3MCInstrInfo(X);
  return X;
}

static MCRegisterInfo *createLC3MCRegisterInfo(const Triple &TT) {
  MCRegisterInfo *X = new MCRegisterInfo();
  InitLC3MCRegisterInfo(X, LC3::LR);
  return X;
}

static MCSubtargetInfo *createLC3MCSubtargetInfo(const Triple &TT,
                                                 StringRef CPU,
                                                 StringRef FS) {
  return createLC3MCSubtargetInfoImpl(TT, CPU, FS);
}

static MCAsmInfo *createLC3MCAsmInfo(const MCRegisterInfo &MRI,
                                     const Triple &TT) {
  return new LC3MCAsmInfo(TT);
}

static MCCodeGenInfo *createLC3MCCodeGenInfo(const Triple &TT, Reloc::Model RM,
                                             CodeModel::Model CM,
                                             CodeGenOpt::Level OL) {
  MCCodeGenInfo *X = new MCCodeGenInfo();
  if (RM == Reloc::Default) {
    RM = Reloc::Static;
  }
  if (CM == CodeModel::Default) {
    CM = CodeModel::Small;
  }
  if (CM != CodeModel::Small && CM != CodeModel::Large) {
    report_fatal_error("Target only supports CodeModel Small or Large");
  }

  X->initMCCodeGenInfo(RM, CM, OL);
  return X;
}

static MCInstPrinter *
createLC3MCInstPrinter(const Triple &TT, unsigned SyntaxVariant,
                       const MCAsmInfo &MAI, const MCInstrInfo &MII,
                       const MCRegisterInfo &MRI) {
  return new LC3InstPrinter(MAI, MII, MRI);
}

// Force static initialization.
extern "C" void LLVMInitializeLC3TargetMC() {
  // Register the MC asm info.
  RegisterMCAsmInfoFn X(TheLC3Target, createLC3MCAsmInfo);

  // Register the MC codegen info.
  TargetRegistry::RegisterMCCodeGenInfo(TheLC3Target, createLC3MCCodeGenInfo);

  // Register the MC instruction info.
  TargetRegistry::RegisterMCInstrInfo(TheLC3Target, createLC3MCInstrInfo);

  // Register the MC register info.
  TargetRegistry::RegisterMCRegInfo(TheLC3Target, createLC3MCRegisterInfo);

  // Register the MC subtarget info.
  TargetRegistry::RegisterMCSubtargetInfo(TheLC3Target,
                                          createLC3MCSubtargetInfo);

  // Register the MCInstPrinter
  TargetRegistry::RegisterMCInstPrinter(TheLC3Target, createLC3MCInstPrinter);

  // Register the ASM Backend.
  TargetRegistry::RegisterMCAsmBackend(TheLC3Target, createLC3AsmBackend);

  // Register the MCCodeEmitter
  TargetRegistry::RegisterMCCodeEmitter(TheLC3Target, createLC3MCCodeEmitter);
}
