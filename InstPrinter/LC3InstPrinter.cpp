//===-- LC3InstPrinter.cpp - Convert LC3 MCInst to assembly syntax ----===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This class prints an LC3 MCInst to a .s file.
//
//===----------------------------------------------------------------------===//

#define DEBUG_TYPE "asm-printer"
#include "LC3InstPrinter.h"
#include "llvm/ADT/StringExtras.h"
#include "llvm/CodeGen/ISDOpcodes.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"
using namespace llvm;

#include "LC3GenAsmWriter.inc"

void LC3InstPrinter::printRegName(raw_ostream &OS, unsigned RegNo) const {
  OS << StringRef(getRegisterName(RegNo)).lower();
}

void LC3InstPrinter::printInst(const MCInst *MI, raw_ostream &O,
                               StringRef Annot, const MCSubtargetInfo &STI) {
  printInstruction(MI, O);
  printAnnotation(O, Annot);
}

static void printExpr(const MCExpr *Expr, raw_ostream &OS) {
  int Offset = 0;
  const MCSymbolRefExpr *SRE;

  if (const MCBinaryExpr *BE = dyn_cast<MCBinaryExpr>(Expr)) {
    SRE = dyn_cast<MCSymbolRefExpr>(BE->getLHS());
    const MCConstantExpr *CE = dyn_cast<MCConstantExpr>(BE->getRHS());
    assert(SRE && CE && "Binary expression must be sym+const.");
    Offset = CE->getValue();
  } else {
    SRE = dyn_cast<MCSymbolRefExpr>(Expr);
    assert(SRE && "Unexpected MCExpr type.");
  }
  const MCSymbolRefExpr::VariantKind Kind = SRE->getKind();
  assert(Kind == MCSymbolRefExpr::VK_None ||
         Kind == MCSymbolRefExpr::VK_LC3_LO ||
         Kind == MCSymbolRefExpr::VK_LC3_HI);

  OS << SRE->getSymbol();

  if (Offset) {
    if (Offset > 0) {
      OS << '+';
    }
    OS << Offset;
  }
}

const char * condCodeToString(ISD::CondCode CC) {
  switch (CC) {
  default:
  case ISD::SETCC_INVALID:
  case ISD::SETFALSE:      //    0 0 0 0       Always false (always folded)
  case ISD::SETFALSE2:     //  1 X 0 0 0       Always false (always folded)
  case ISD::SETOEQ:        //    0 0 0 1       True if ordered and equal
  case ISD::SETOGT:        //    0 0 1 0       True if ordered and greater than
  case ISD::SETOGE:        //    0 0 1 1       True if ordered and greater than or equal
  case ISD::SETOLT:        //    0 1 0 0       True if ordered and less than
  case ISD::SETOLE:        //    0 1 0 1       True if ordered and less than or equal
  case ISD::SETONE:        //    0 1 1 0       True if ordered and operands are unequal
  case ISD::SETO:          //    0 1 1 1       True if ordered (no nans)
  case ISD::SETUO:         //    1 0 0 0       True if unordered: isnan(X) | isnan(Y)
  case ISD::SETUEQ:        //    1 0 0 1       True if unordered or equal
  case ISD::SETUGT:        //    1 0 1 0       True if unordered or greater than
  case ISD::SETUGE:        //    1 0 1 1       True if unordered, greater than, or equal
  case ISD::SETULT:        //    1 1 0 0       True if unordered or less than
  case ISD::SETULE:        //    1 1 0 1       True if unordered, less than, or equal
  case ISD::SETUNE:        //    1 1 1 0       True if unordered or not equal
    llvm_unreachable("Invalid or unsupported condition code");
    return nullptr;
    
  case ISD::SETTRUE:       //    1 1 1 1       Always true (always folded)
  case ISD::SETTRUE2:      //  1 X 1 1 1       Always true (always folded)
    return "";
  
  // Don't care operations: undefined if the input is a nan.
  case ISD::SETEQ:         //  1 X 0 0 1       True if equal
    return "z";
  case ISD::SETGT:         //  1 X 0 1 0       True if greater than
    return "p";
  case ISD::SETGE:         //  1 X 0 1 1       True if greater than or equal
    return "zp";
  case ISD::SETLT:         //  1 X 1 0 0       True if less than
    return "n";
  case ISD::SETLE:         //  1 X 1 0 1       True if less than or equal
    return "nz";
  case ISD::SETNE:         //  1 X 1 1 0       True if not equal
    return "np";
  }
}

// Print a condition code (e.g. for predication).
void LC3InstPrinter::printCondCode(const MCInst *MI, unsigned OpNum,
                                   raw_ostream &O) {
  const MCOperand &Op = MI->getOperand(OpNum);
  ISD::CondCode CC = (ISD::CondCode)Op.getImm();
  const char *Str = condCodeToString(CC);
  O << Str;
}

// Print a 'memsrc' operand which is a (Register, Offset) pair.
void LC3InstPrinter::printAddrModeMemSrc(const MCInst *MI, unsigned OpNum,
                                         raw_ostream &O) {
  const MCOperand &Op1 = MI->getOperand(OpNum);
  const MCOperand &Op2 = MI->getOperand(OpNum + 1);
  //O << "[";
  printRegName(O, Op1.getReg());

  unsigned Offset = Op2.getImm();
  //if (Offset) {
    O << ", #" << (Offset / 2);
  //}
  //O << "]";
}

void LC3InstPrinter::printOperand(const MCInst *MI, unsigned OpNo,
                                  raw_ostream &O) {
  const MCOperand &Op = MI->getOperand(OpNo);
  if (Op.isReg()) {
    printRegName(O, Op.getReg());
    return;
  }

  if (Op.isImm()) {
    if (getOpcodeName(MI->getOpcode()) == "MOVLOi8" || 
        getOpcodeName(MI->getOpcode()) == "MOVHIi8")
      O << "=" << MCInstPrinter::formatHex(Op.getImm());
    else
      O << "#" << Op.getImm();
    return;
  }

  assert(Op.isExpr() && "unknown operand kind in printOperand");
  printExpr(Op.getExpr(), O);
}
