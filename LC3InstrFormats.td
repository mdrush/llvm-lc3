//===-- LC3InstrFormats.td - LC3 Instruction Formats ---*- tableGen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Instruction format superclass
//===----------------------------------------------------------------------===//
class InstLC3<bits<4> opcode, dag outs, dag ins, string asmstr, list<dag> pattern>
    : Instruction {
  field bits<16> Inst;

  let Namespace = "LC3";
  dag OutOperandList = outs;
  dag InOperandList = ins;
  let AsmString   = asmstr;
  let Pattern = pattern;
  let Size = 2;

  // Always execute - no condition flags for this example
  let Inst{15-12} = opcode;
}

// LC3 pseudo instructions format
class LC3PseudoInst<bits<4> opcode, dag outs, dag ins, string asmstr, list<dag> pattern>
    : InstLC3<opcode, outs, ins, asmstr, pattern> {
  let isPseudo = 1;
}

class ALUInst<bits<4> opcode, dag outs, dag ins, string asmstr, list<dag> pattern>
    : InstLC3<opcode, outs, ins, asmstr, pattern> {
}

//class MulInst<bits<7> opcode, dag outs, dag ins, string asmstr,
//              list<dag> pattern> : InstLC3<outs, ins, asmstr, pattern> {
//  let Inst{27-21} = opcode;
//  let Inst{20}    = 0;  // We never update flags
//  let Inst{7-4}   = 0b1001;
//}

class BranchInst<bits<4> opcode, dag outs, dag ins,
                 string asmstr, list<dag> pattern>
    : InstLC3<opcode, outs, ins, asmstr, pattern> {
}
