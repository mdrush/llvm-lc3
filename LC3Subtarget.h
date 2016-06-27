#ifndef LC3SUBTARGET_H
#define LC3SUBTARGET_H

#include "LC3.h"
#include "LC3FrameLowering.h"
#include "LC3ISelLowering.h"
#include "LC3InstrInfo.h"
#include "LC3SelectionDAGInfo.h"
#include "LC3Subtarget.h"
#include <string>

#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetSubtargetInfo.h"

#define GET_SUBTARGETINFO_HEADER
#include "LC3GenSubtargetInfo.inc"

namespace llvm {
class StringRef;

class LC3Subtarget : public LC3GenSubtargetInfo {
virtual void anchor();
 private:
	const DataLayout DL;	// Calculates type size & alignment.
	LC3InstrInfo InstrInfo;
	LC3TargetLowering TLInfo;
	LC3SelectionDAGInfo TSInfo;
	LC3FrameLowering FrameLowering;
	InstrItineraryData InstrItins;
 public:
 	LC3Subtarget(const Triple &TT, StringRef CPU, StringRef FS, LC3TargetMachine &TM);

 	const InstrItineraryData *getInstrItineraryData() const override {
		return &InstrItins;
	}

	const LC3InstrInfo *getInstrInfo() const override { return &InstrInfo; }

	const LC3RegisterInfo *getRegisterInfo() const override {
		return &InstrInfo.getRegisterInfo();
	}

	const LC3TargetLowering *getTargetLowering() const override {
		return &TLInfo;
	}

	const LC3FrameLowering *getFrameLowering() const override {
		return &FrameLowering;
	}

	const LC3SelectionDAGInfo *getSelectionDAGInfo() const override {
		return &TSInfo;
	}

	const DataLayout *getDataLayout() const { return &DL; }

	void ParseSubtargetFeatures(StringRef CPU, StringRef FS);
};
}

#endif