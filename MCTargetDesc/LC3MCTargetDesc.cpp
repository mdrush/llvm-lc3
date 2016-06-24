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

static MCRegisterInfo *createLC3MCRegisterInfo(StringRef TT) {
	MCRegisterInfo *X = new MCRegisterInfo();
	InitLC3MCRegisterInfo(X, LC3::LR);
	return X;
}

static MCSubtargetInfo *createLC3MCSubtargetInfo(StringRef TT, StringRef CPU,
	StringRef FS) {
	MCSubtargetInfo *X = new MCSubtargetInfo();
	InitLC3MCSubtargetInfo(X, TT, CPU, FS);
	return X;
}

static MCAsmInfo *createLC3MCAsmInfo(const MCRegisterInfo &MRI, StringRef TT) {
	MCAsmInfo *MAI = new LC3MCAsmInfo(TT);
	return MAI;
}

static MCCodeGenInfo *createLC3MCCodeGenInfo(StringRef TT, Reloc::Model RM,
	CodeModel::Model CM, CodeGenOpt::Level OL) {
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
	X->InitMCCodeGenInfo(RM, CM, OL);
	return X;
}

static MCInstPrinter *
createLC3MCInstPrinter(const Target &T, unsigned SyntaxVariant, 
	const MCAsmInfo &MAI, const MCInstrInfo &MII,
	const MCRegisterInfo &MRI, const MCSubtargetInfo &STI) {
	return new LC3InstPrinter(MAI, MII, MRI);
}

static MCStreamer *
createMCAsmStreamer(MCContext &Ctx, formatted_raw_ostream &OS,
	bool isVerboseAsm, bool useDwarfDirectory, MCInstPrinter *InstPrint,
	MCCodeEmitter *CE,MCAsmBackend *TAB, bool ShowInst) {
	return createAsmStreamer(Ctx, OS, isVerboseAsm, 
		useDwarfDirectory, InstPrint, CE, TAB, ShowInst);
}

static MCStreamer *createMCStreamer(const Target &T,
	StringRef TT, MCContext &Ctx, MCAsmBackend &MAB,
	raw_ostream &OS, MCCodeEmitter *Emitter, const MCSubtargetInfo &STI,
	bool RelaxAll, bool NoExecStack) {
	return createELFStreamer(Ctx, MAB, OS, Emitter, false, NoExecStack);
}

// Force static initialization.
extern "C" void LLVMInitializeLC3TargetMC() {

// Register the MC asm info.
RegisterMCAsmInfoFn X(TheLC3Target, createLC3MCAsmInfo);

// Register the MC codegen info.
TargetRegistry::RegisterMCCodeGenInfo(TheLC3Target,
createLC3MCCodeGenInfo);

// Register the MC instruction info.
TargetRegistry::RegisterMCInstrInfo(TheLC3Target,
createLC3MCInstrInfo);
// Register the MC register info.
TargetRegistry::RegisterMCRegInfo(TheLC3Target,
createLC3MCRegisterInfo);
// Register the MC subtarget info.
TargetRegistry::RegisterMCSubtargetInfo(TheLC3Target,
createLC3MCSubtargetInfo);
// Register the MCInstPrinter
TargetRegistry::RegisterMCInstPrinter(TheLC3Target,
createLC3MCInstPrinter);
// Register the ASM Backend.
TargetRegistry::RegisterMCAsmBackend(TheLC3Target,
createLC3AsmBackend);
// Register the assembly streamer.
TargetRegistry::RegisterAsmStreamer(TheLC3Target,
createMCAsmStreamer);
// Register the object streamer.
TargetRegistry::RegisterMCObjectStreamer(TheLC3Target,
createMCStreamer);
// Register the MCCodeEmitter
TargetRegistry::RegisterMCCodeEmitter(TheLC3Target,
createLC3MCCodeEmitter);
}
