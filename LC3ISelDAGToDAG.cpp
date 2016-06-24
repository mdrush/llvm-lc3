#include "LC3.h"
#include "LC3TargetMachine.h"
#include "llvm/CodeGen/SelectionDAGISel.h"
#include "llvm/Support/Compiler.h"
#include "llvm/Support/Debug.h"
#include "LC3InstrInfo.h"


class LC3DAGToDAGISel : public SelectionDAGISel {
	const TOYSubtarget &Subtarget;
 public:
	explicit LC3DAGToDAGISel(LC3TargetMachine &TM, CodeGenOpt::Level OptLevel) 
		: SelectionDAGISel(TM, OptLevel), Subtarget(*TM.getSubtargetImpl()) {}
	SDNode *Select(SDNode *N);
	bool SelectAddr(SDValue Addr, SDValue &Base, SDValue &Offset);
};



SDNode *LC3DAGToDAGISel::Select(SDNode *N) {
return SelectCode(N);
}


bool LC3DAGToDAGISel::SelectAddr(SDValue Addr, SDValue &Base, SDValue &Offset) {
	if (FrameIndexSDNode *FIN = dyn_cast<FrameIndexSDNode>(Addr)) {
		Base = CurDAG->getTargetFrameIndex(FIN->getIndex(), getTargetLowering()->getPointerTy());
		Offset = CurDAG->getTargetConstant(0, MVT::i32);
		return true;
	}
	if (Addr.getOpcode() == ISD::TargetExternalSymbol ||
		Addr.getOpcode() == ISD::TargetGlobalAddress ||
		Addr.getOpcode() == ISD::TargetGlobalTLSAddress) {
		return false; // direct calls.
	}
	Base = Addr;
	Offset = CurDAG->getTargetConstant(0, MVT::i32);
	return true;
}


FunctionPass *llvm::createLC3ISelDag(LC3TargetMachine &TM, CodeGenOpt::Level OptLevel) {
	return new LC3DAGToDAGISel(TM, OptLevel);
}
