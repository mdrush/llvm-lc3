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
	extern Target TheLC3Target;
	MCCodeEmitter *createLC3MCCodeEmitter(const MCInstrInfo &MCII,
		const MCRegisterInfo &MRI, const MCSubtargetInfo &STI, MCContext &Ctx);
	MCAsmBackend *createLC3AsmBackend(const Target &T, const MCRegisterInfo &MRI,
		StringRef TT, StringRef CPU);
	MCObjectWriter *createLC3ELFObjectWriter(raw_ostream &OS, uint8_t OSABI);
} // End llvm namespace

#define GET_REGINFO_TARGET_DESC
#include "LC3GenRegisterInfo.inc"

#define GET_INSTRINFO_ENUM
#include "LC3GenInstrInfo.inc"

#define GET_SUBTARGETINFO_ENUM
#include "LC3GenSubtargetInfo.inc"

#endif