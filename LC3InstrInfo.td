//===-- LC3InstrInfo.td - Target Description for LC3 ---*- tableGen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file describes the LC3 instructions in TableGen format.
//
//===----------------------------------------------------------------------===//

include "LC3InstrFormats.td"
include "LC3Operators.td"

//===----------------------------------------------------------------------===//
// ALU Instructions
//===----------------------------------------------------------------------===//

multiclass BinOp<bits<4> opcode, string opstr, SDNode opnode> {
  def rr : ALUInst<opcode, (outs GRRegs:$dst),
                   (ins GRRegs:$src1, GRRegs:$src2),
                   !strconcat(opstr, " $dst, $src1, $src2"),
                   [(set i16:$dst, (opnode i16:$src1, i16:$src2))]> {
    bits<3> dst;
    bits<3> src1;
    bits<3> src2;
    let Inst{5} = 0;
    let Inst{11-9} = dst;
    let Inst{8-6} = src1;
    let Inst{4-3} = 0b00;
    let Inst{2-0} = src2;

  }
  def ri : ALUInst<opcode, (outs GRRegs:$dst),
                   (ins GRRegs:$src1, i16imm:$imm),
                   !strconcat(opstr, " $dst, $src1, $imm"),
                   [(set i16:$dst, (opnode i16:$src1, LC3imm5:$imm))]> {
    bits<3> dst;
    bits<3> src1;
    bits<5> imm;
    let Inst{5} = 1;
    let Inst{11-9} = dst;
    let Inst{8-6} = src1;
    let Inst{4-0}  = imm;
  }
}

defm ADD  : BinOp<0b0001, "add", add>;
defm AND  : BinOp<0b0101, "and", and>;

def SUBrr : InstLC3<0b1011, (outs GRRegs:$dst), (ins GRRegs:$src1, GRRegs:$src2), "",
                     [(set i16:$dst, (sub i16:$src1, i16:$src2))]> {
  let isPseudo = 1;
  //let Defs = [CPSR];
}

def SUBri : InstLC3<0b1011, (outs GRRegs:$dst), (ins GRRegs:$src1, i16imm:$imm), 
                     !strconcat("sub", " $dst, $src1, $imm"),
                     [(set i16:$dst, (sub i16:$src1, LC3imm5:$imm))]> {
  let isPseudo = 1;
}

def NOTrr : InstLC3<0b1001, (outs GRRegs:$dst), (ins GRRegs:$src1),
                     !strconcat("not", " $dst, $src1"),
                     [(set i16:$dst, (not i16:$src1))]> {
    bits<3> dst;
    bits<3> src1;
    let Inst{11-9} = dst;
    let Inst{8-6} = src1;
    let Inst{5-0} = 0b111111;
}


//multiclass ShiftOp<bits<4> opcoder, bits<3> opcodei, string opstr, SDNode opnode> {
//  def rr : ALUInst<0b1101, (outs GRRegs:$dst),
//                   (ins GRRegs:$src1, GRRegs:$src2),
//                   !strconcat(opstr, " $dst, $src1, $src2"),
//                   [(set i16:$dst, (opnode i16:$src1, i16:$src2))]> {
//    bits<4> dst;
//    bits<4> src1;
//   bits<4> src2;
//   let Inst{25}    = 0;
//   let Inst{20}    = 0;  // We never update flags
//    let Inst{19-16} = 0b0000;
//    let Inst{15-12} = dst;
//    let Inst{11-8}  = src2;
//    let Inst{7-4}   = opcoder;
//    let Inst{3-0}   = src1;
//  }
//  def ri : ALUInst<0b1101, (outs GRRegs:$dst),
//                   (ins GRRegs:$src1, i16imm:$imm),
//                   !strconcat(opstr, " $dst, $src1, $imm"),
//                   [(set i16:$dst, (sub i16:$src1, LC3imm8:$imm))]> {
//    bits<4> dst;
//    bits<4> src1;
//    bits<5> imm;
//    let Inst{25}    = 0;
//    let Inst{20}    = 0;  // We never update flags
//    let Inst{19-16} = 0b0000;
//    let Inst{15-12} = dst;
//    let Inst{11-7}  = imm;
//    let Inst{6-4}   = opcodei;
//    let Inst{3-0}   = src1;
//  }
//}

//defm EOR  : BinOp<0b0001, "eor", xor>;
//defm ORR  : BinOp<0b1100, "orr", or>;

//defm LSL  : ShiftOp<0b0001, 0b000, "lsl", shl>;
//defm LSR  : ShiftOp<0b0011, 0b010, "lsr", srl>;
//defm ASR  : ShiftOp<0b0101, 0b100, "asr", sra>;

//===----------------------------------------------------------------------===//
// Multiply Instructions
//===----------------------------------------------------------------------===//

//def MUL  : MulInst<0b0000000, (outs GRRegs:$dst),
//                   (ins GRRegs:$src1, GRRegs:$src2),
//                   "mul $dst, $src1, $src2",
//                   [(set i16:$dst, (mul i16:$src1, i16:$src2))]> {
//  bits<4> dst;
//  bits<4> src1;
//  bits<4> src2;
//  let Inst{19-16} = dst;
//  let Inst{15-12} = 0b0000;
//  let Inst{11-8}  = src2;
//  let Inst{3-0}   = src1;
//}

//def MLA  : MulInst<0b0000001, (outs GRRegs:$dst),
//                   (ins GRRegs:$src1, GRRegs:$src2, GRRegs:$src3),
//                   "mla $dst, $src1, $src2, $src3",
//                   [(set i16:$dst, (add (mul i16:$src1, i16:$src2),
//                                         i16:$src3))]> {
//  bits<4> dst;
//  bits<4> src1;
//  bits<4> src2;
//  bits<4> src3;
//  let Inst{19-16} = dst;
//  let Inst{15-12} = src3;
//  let Inst{11-8}  = src2;
//  let Inst{3-0}   = src1;
//}

//===----------------------------------------------------------------------===//
// Mov Instructions
//===----------------------------------------------------------------------===//
def MOVrr  : ALUInst<0b1011, (outs GRRegs:$dst), (ins GRRegs:$src),
                     "mov $dst, $src",
                     [/* No pattern */]> {
  let isPseudo = 1;
}

//===----------------------------------------------------------------------===//
// Mov Immediate Instructions
//===----------------------------------------------------------------------===//

class MOV<bits<1> t, string opstr, dag ins, list<dag>pattern>
    : ALUInst<0b1101, (outs GRRegs:$dst), ins,
              !strconcat(opstr, " $dst, $imm"), pattern> {
  bits<3> dst;
  bits<8> imm;
  let Inst{8} = t;
  let Inst{11-9} = dst;
  let Inst{7-0}  = imm;
}

def MOVLOi8 : MOV<0b0, "mov", (ins i16imm:$imm),
                  [(set i16:$dst, i16imm_lo:$imm)]>;
def MOVHIi8 : MOV<0b1, "movt", (ins GRRegs:$src1, i16imm:$imm),
                  [/* No Pattern */]>;

def MOVi16 : InstLC3<0b1011, (outs GRRegs:$dst), (ins i16imm:$src), "",
                     [(set i16:$dst, (movei16 imm:$src))]> {
  let isPseudo = 1;
}

//===----------------------------------------------------------------------===//
// Comparison Instructions
//===----------------------------------------------------------------------===//

def CMP : InstLC3<0b1011, (outs), (ins GRRegs:$lhs, GRRegs:$rhs),
                    "cmp $lhs, $rhs", []> {
  let isPseudo = 1;
  let Defs = [CPSR];
}

//===----------------------------------------------------------------------===//
// Load/Store Instructions
//===----------------------------------------------------------------------===//

def LDR  : InstLC3<0b0110, (outs GRRegs:$val), (ins memsrc:$addr),
                   "ldr $val, $addr",
                   [(set i16:$val, (load addr:$addr))]> {
  bits<3> val;
  bits<9> addr;

  let Inst{11-9} = val;
  let Inst{8-0} = addr;
  
}

def STR : InstLC3<0b0111, (outs), (ins GRRegs:$val, memsrc:$addr),
                  "str $val, $addr",
                  [(store i16:$val, addr:$addr)]> {
  bits<3> val;
  bits<9> addr;

  let Inst{11-9} = val;
  let Inst{8-0} = addr;
}

//===----------------------------------------------------------------------===//
// Return Instructions
//===----------------------------------------------------------------------===//

let isTerminator = 1, isReturn = 1, Uses = [LR] in {
  def RET : InstLC3<0b1100, (outs), (ins variable_ops),
                    "ret",  [(LC3RetFlag)]> {
    let Inst{11-0}  = 0b000111000000; //jmp r7
  }
}


//===----------------------------------------------------------------------===//
// Call Instructions
//===----------------------------------------------------------------------===//

let isCall = 1, Defs = [LR], Uses = [SP] in {
  def BL : BranchInst<0b0100, (outs), (ins GRRegs:$addr),
                      "jsrr $addr",
                      [(lc3_call i16:$addr)]> {
    bits<3> addr;
    let Inst{11-9} = 0b000;
    let Inst{8-6} = addr;
    let Inst{5-0} = 0b000000;
  }
}

def : Pattern<(i16 (load_sym tglobaladdr:$addr)),  [(MOVi16 $addr)]>;

//===----------------------------------------------------------------------===//
// Branch Instructions
//===----------------------------------------------------------------------===//

let isTerminator = 1, isBranch = 1, isBarrier = 1 in {
  def B : InstLC3<0b0000, (outs), (ins b_target:$dst),
                  "brnzp $dst", [(br bb:$dst)]> {
    bits<9> dst;
    let Inst{11-9} = 0b111;
    let Inst{8-0} = dst;
  }
}

let isTerminator = 1, isBranch = 1, Uses = [CPSR] in {
  def Bcc : InstLC3<0b0000, (outs), (ins cc_val:$cc, b_target:$dst),
                    "br$cc $dst",  []> {

  }
}

//===----------------------------------------------------------------------===//
// Pseudo Instructions
//===----------------------------------------------------------------------===//

let Defs = [SP], Uses = [SP] in {
def ADJCALLSTACKDOWN : LC3PseudoInst<0b1011, (outs), (ins i16imm:$amt),
                                    "# ADJCALLSTACKDOWN $amt",
                                    [(callseq_start timm:$amt)]>;
def ADJCALLSTACKUP   : LC3PseudoInst<0b1011, (outs), (ins i16imm:$amt1, i16imm:$amt2),
                                    "# ADJCALLSTACKUP $amt1",
                                    [(callseq_end timm:$amt1, timm:$amt2)]>;
}
