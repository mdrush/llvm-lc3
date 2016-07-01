//===-- LC3RegisterInfo.td - LC3 Register defs ---------*- tableGen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
//  Declarations that describe the LC3 register file 
//===----------------------------------------------------------------------===//

class LC3Reg<bits<16> Enc, string n> : Register<n> {
  let HWEncoding = Enc;
  let Namespace = "LC3";
}

// CPU registers
def R0  : LC3Reg< 0, "r0">;
def R1  : LC3Reg< 1, "r1">;
def R2  : LC3Reg< 2, "r2">;
def R3  : LC3Reg< 3, "r3">;
def R4  : LC3Reg< 4, "r4">;
def R5  : LC3Reg< 5, "r5">;
def R6  : LC3Reg< 6, "r6">;
def R7  : LC3Reg< 7, "r7">;
def R8  : LC3Reg< 8, "r8">;
def R9  : LC3Reg< 9, "r9">;

def SP  : LC3Reg<13, "sp">;
def LR  : LC3Reg<14, "lr">;

def CPSR  : LC3Reg<16, "cpsr">;

// Register classes.
//
def GRRegs : RegisterClass<"LC3", [i32], 32,
  // Return values and arguments
  (add R0, R1, R2, R3,
       R4, R5, R6, R7, R8, R9, SP)>;
