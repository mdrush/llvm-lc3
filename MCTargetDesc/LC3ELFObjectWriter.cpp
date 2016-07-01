//===-- LC3ELFObjectWriter.cpp - LC3 ELF Writer ---------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "MCTargetDesc/LC3MCTargetDesc.h"
#include "MCTargetDesc/LC3FixupKinds.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/ADT/StringSwitch.h"
#include "llvm/MC/MCELFObjectWriter.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCSectionELF.h"
#include "llvm/MC/MCValue.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {
  class LC3ELFObjectWriter : public MCELFObjectTargetWriter {
  public:
    LC3ELFObjectWriter(uint8_t OSABI);

    virtual ~LC3ELFObjectWriter();

    unsigned GetRelocType(const MCValue &Target, const MCFixup &Fixup,
                          bool IsPCRel) const override;
  };
}

unsigned LC3ELFObjectWriter::GetRelocType(const MCValue &Target,
                                          const MCFixup &Fixup,
                                          bool IsPCRel) const {
  if (!IsPCRel) {
    llvm_unreachable("Only dealying with PC-relative fixups for now");
  }

  unsigned Type = 0;
  switch ((unsigned)Fixup.getKind()) {
  default:
    llvm_unreachable("Unimplemented");
  case LC3::fixup_lc3_mov_hi16_pcrel:
    Type = ELF::R_ARM_MOVT_PREL;
    break;
  case LC3::fixup_lc3_mov_lo16_pcrel:
    Type = ELF::R_ARM_MOVW_PREL_NC;
    break;
  }
  return Type;
}

LC3ELFObjectWriter::LC3ELFObjectWriter(uint8_t OSABI)
    : MCELFObjectTargetWriter(/*Is64Bit*/ false, OSABI, /*ELF::EM_LC3*/ ELF::EM_ARM,
                              /*HasRelocationAddend*/ false) {}

LC3ELFObjectWriter::~LC3ELFObjectWriter() {}

MCObjectWriter *llvm::createLC3ELFObjectWriter(raw_pwrite_stream &OS, uint8_t OSABI) {
  MCELFObjectTargetWriter *MOTW = new LC3ELFObjectWriter(OSABI);
  return createELFObjectWriter(MOTW, OS, /*IsLittleEndian=*/true);
}
