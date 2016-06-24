//===- LC3CallingConv.td - Calling Conventions for LC3 -*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
// This describes the calling conventions for LC3 architecture.
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// LC3 Return Value Calling Convention
//===----------------------------------------------------------------------===//
def RetCC_LC3 : CallingConv<[
  // i16 are returned in registers R0, R1, R2, R3
  CCIfType<[i16], CCAssignToReg<[R0, R1, R2, R3]>>,

  // Integer values get stored in stack slots that are 2 bytes in
  // size and 2-byte aligned.
  CCIfType<[i16], CCAssignToStack<2, 2>>
]>;

//===----------------------------------------------------------------------===//
// LC3 Argument Calling Conventions
//===----------------------------------------------------------------------===//
def CC_LC3 : CallingConv<[
  // Promote i8 arguments to i16.
  CCIfType<[i8], CCPromoteToType<i16>>,

  // The first 4 integer arguments are passed in integer registers.
  CCIfType<[i16], CCAssignToReg<[R0, R1, R2, R3]>>,

  // Integer values get stored in stack slots that are 2 bytes in
  // size and 2-byte aligned.
  CCIfType<[i16], CCAssignToStack<2, 2>>
]>;

def CC_Save : CalleeSavedRegs<(add R4, R5, R6, R7)>;
// Should there be only R7 here?
