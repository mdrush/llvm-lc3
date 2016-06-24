#include "LC3TargetMachine.h"
#include "LC3.h"
#include "LC3FrameLowering.h"
#include "LC3InstrInfo.h"
#include "LC3ISelLowering.h"
#include "LC3SelectionDAGInfo.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/IR/Module.h"
#include "llvm/PassManager.h"
#include "llvm/Support/TargetRegistry.h"


class LC3PassConfig : public TargetPassConfig {
 public:
	virtual bool addInstSelector();
};

bool LC3PassConfig::addInstSelector() {
	addPass(createLC3ISelDag(getLC3TargetMachine()));
	return false;
}

using namespace llvm;

LC3TargetMachine::LC3TargetMachine(const Target &T, StringRef TT,
	StringRef CPU, StringRef FS, const TargetOptions &Options,
	Reloc::Model RM, CodeModel::Model CM,
	CodeGenOpt::Level OL)
	: LLVMTargetMachine(T, TT, CPU, FS, Options, RM, CM, OL),
	Subtarget(TT, CPU, FS, *this) {
		initAsmInfo();
	}

namespace {
	class LC3PassConfig : public TargetPassConfig {
	 public:
		LC3PassConfig(LC3TargetMachine *TM, PassManagerBase &PM)
		: TargetPassConfig(TM, PM) {}
		LC3TargetMachine &getLC3TargetMachine() const {
			return getTM<LC3TargetMachine>();
		}
		virtual bool addPreISel();
		virtual bool addInstSelector();
		virtual bool addPreEmitPass();
		};
} // namespace

TargetPassConfig
*LC3TargetMachine::createPassConfig(PassManagerBase &PM) {
	return new LC3PassConfig(this, PM);
}

bool LC3PassConfig::addPreISel() { return false; }

bool LC3PassConfig::addInstSelector() {
	addPass(createLC3ISelDag(getLC3TargetMachine(),
	getOptLevel()));
	return false;
}

bool LC3PassConfig::addPreEmitPass() { return false; }

// Force static initialization.
extern "C" void LLVMInitializeLC3Target() {
	RegisterTargetMachine<LC3TargetMachine> X(TheLC3Target);
}

void LC3TargetMachine::addAnalysisPasses(PassManagerBase &PM) {}