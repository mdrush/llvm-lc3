#ifndef TARGET_LC3_H
#define TARGET_LC3_H
#include "MCTargetDesc/LC3MCTargetDesc.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {
	class TargetMachine;
	class LC3TargetMachine;
	FunctionPass *createLC3ISelDag(LC3TargetMachine &TM, CodeGenOpt::Level OptLevel);
} // end namespace llvm;

#endif