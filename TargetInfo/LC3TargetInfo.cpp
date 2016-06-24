#include "LC3.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

Target llvm::TheLC3Target;
extern "C" void LLVMInitializeLC3TargetInfo() {
	RegisterTarget<Triple::lc3> X(TheLC3Target, "lc3", "LC3");
}