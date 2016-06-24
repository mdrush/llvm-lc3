void LC3InstPrinter::printOperand(const MCInst *MI, unsigned OpNo, raw_ostream &O) {
	const MCOperand &Op = MI->getOperand(OpNo);
	if (Op.isReg()) {
		printRegName(O, Op.getReg());
		return;
	}
	if (Op.isImm()) {
		O << "#" << Op.getImm();
			return;
	}
	assert(Op.isExpr() && "unknown operand kind in printOperand");
	printExpr(Op.getExpr(), O);
}

void TOYInstPrinter::printRegName(raw_ostream &OS, unsigned RegNo) const {
	OS << StringRef(getRegisterName(RegNo)).lower();
}

void TOYInstPrinter::printInst(const MCInst *MI, raw_ostream &O, StringRef Annot) {
	printInstruction(MI, O);
	printAnnotation(O, Annot);
}

