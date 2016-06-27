#include "LC3Subtarget.h"
#include "LC3.h"
#include "llvm/Support/TargetRegistry.h"

#define DEBUG_TYPE "lc3-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "LC3GenSubtargetInfo.inc"

using namespace llvm;

void LC3Subtarget::anchor() {}

LC3Subtarget::LC3Subtarget(const Triple &TT, StringRef CPU, StringRef FS,
                           LC3TargetMachine &TM)
    : LC3GenSubtargetInfo(TT, CPU, FS),
	DL("e-m:e-p:32:32-i1:8:32-i8:8:32-i16:16:32-i64:32-f64:32-a:0:32-n32"),
	InstrInfo(), TLInfo(TM), TSInfo(), FrameLowering()
	{}