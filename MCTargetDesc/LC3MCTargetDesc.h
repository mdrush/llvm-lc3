//===-- LC3MCTargetDesc.h - LC3 Target Descriptions ---------*- C++ -*-===//
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

#ifndef LC3MCTARGETDESC_H
#define LC3MCTARGETDESC_H

#include "llvm/Support/DataTypes.h"

namespace llvm {
class Target;
class MCInstrInfo;
class MCRegisterInfo;
class MCSubtargetInfo;
class MCContext;
class MCCodeEmitter;
class MCAsmInfo;
class MCCodeGenInfo;
class MCInstPrinter;
class MCObjectWriter;
class MCAsmBackend;

class StringRef;
class raw_ostream;
class raw_pwrite_stream;
class Triple;

extern Target TheLC3Target;

MCCodeEmitter *createLC3MCCodeEmitter(const MCInstrInfo &MCII,
                                      const MCRegisterInfo &MRI,
                                      MCContext &Ctx);

MCAsmBackend *createLC3AsmBackend(const Target &T, const MCRegisterInfo &MRI,
                                  const Triple &TT, StringRef CPU);

MCObjectWriter *createLC3ELFObjectWriter(raw_pwrite_stream &OS, uint8_t OSABI);

} // End llvm namespace

// Defines symbolic names for LC3 registers.  This defines a mapping from
// register name to register number.
//
#define GET_REGINFO_ENUM
#include "LC3GenRegisterInfo.inc"

// Defines symbolic names for the LC3 instructions.
//
#define GET_INSTRINFO_ENUM
#include "LC3GenInstrInfo.inc"

#define GET_SUBTARGETINFO_ENUM
#include "LC3GenSubtargetInfo.inc"

#endif
