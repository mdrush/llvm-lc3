//===-- LC3InstrFormats.td - LC3 Instruction Formats ---*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//


// class Format<bits<4> val> {
//   bits<4> Value = val;
// }

// def FrmA : Format<0>;
// def FrmL : Format<1>;


class InstLC3<dag outs, dag ins, string asmstr, list<dag> pattern> : Instruction {
  field bits<16> Inst;

  let Namespace = "LC3";
  dag OutOperandList = outs;
  dag InOperandList = ins;
  let AsmString = asmstr;
  let Pattern = pattern;
  let Size = 2; //???

  let Inst{15-12} = 0b0000;
}


class LC3PseudoInst<dag outs, dag ins, string asmstr, list<dag> pattern> : InstLC3<outs, ins, asmstr, pattern> {
  let isPseudo = 1;
}


class ALUInst<bits<4> opcode, dag outs, dag ins, string asmstr, list<dag> pattern> : InstLC3<outs, ins, asmstr, pattern> {
  let Inst{15-12} = opcode;
}



class BranchInst<bits<4> opcode, dag outs, dag ins, string asmstr, list<dag> pattern> : InstLC3<outs, ins, asmstr, pattern> {
  let Inst{15-12} = opcode;
}








// def immSExt5 : PatLeaf<(imm), [{ return isInt<5>(N->getSExtValue()); }]>;

// // Format A instruction class in LC3 : <|opcode|dr|sr1|0|00|sr2|>
// class FA<bits<4> op, dag outs, dag ins, string asmstr, list<dag> pattern, InstrItinClass itin> : LC3Inst<outs, ins, asmstr, pattern, itin, FrmA>
// {
//   bits<3> ra;
//   bits<3> rb;
//   bits<3> rc;

//   let Opcode = op;

//   let Inst{11-9} = ra; //DR
//   let Inst{8-6} = rb; //SR1
//   let Insr{2-0} = rc; //SR2

// }

// def Addii : ArithLogicI<0x1, "ADD", add, 

// // Format L instruction class in LC3 : <|opcode|dr|sr1|1|imm5|>
// class FL<bits<4> op, dag outs, dag ins, string asmstr, list<dag> pattern, InstrItinClass itin> : LC3Inst<outs, ins, asmstr, pattern, itin, FrmL>
// {
//   bits<3> dr;
//   bits<3> sr1;
//   bits<5> imm5;

//   let Opcode = op;

//   let Inst{11-9} = ra; //DR
//   let Inst{8-6} = rb; //SR1
//   let Insr{4-0} = imm5;
// }

// def ADDiu : ArithLogicI<0x1, "ADD", add, simm5, immSExt5, CPURegs>;

// def ANDiu : ArithLogicI<0x5, "AND", and, simm5, immSExt5, CPURegs>;

// // Arithmetic and logical instructions with 2 register operands
// class ArithLogicI<bits<4> op, string instr_asm, SDNode OpNode, Operand Od, PatLeaf imm_type, RegisterClass RC> :
//   FL<op, (outs GPROut:$ra), (ins RC:$rb, 0d:$imm5), !strconcat(instr_asm, "\t $ra, $rb, $imm5"),
//   [(set GPROut:$ra, (OpNode RC:$rb, imm_type:$imm5))], IIAlu> {
//     let isReMaterializable = 1;
//   }

// // Arithmetic and logical instructions with 3 register operands
// class ArithLogicI<bits<4> op, string instr_asm, SDNode OpNode, Operand Od, PatLeaf imm_type, RegisterClass RC> :
//   FA<op, (outs GPROut:$ra), (ins RC:$rb, 0d:$imm5), !strconcat(instr_asm, "\t $ra, $rb, $imm5"),
//   [(set GPROut:$ra, (OpNode RC:$rb, imm_type:$imm5))], IIAlu> {
//     let isReMaterializable = 1;
//   }





// class InstLC3<...> : Instruction {
//   field bits<32> Inst;
//   ...
// }