//===-- LC3SelectionDAGInfo.h - LC3 SelectionDAG Info -------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines the LC3 subclass for TargetSelectionDAGInfo.
//
//===----------------------------------------------------------------------===//

#ifndef LC3SELECTIONDAGINFO_H
#define LC3SELECTIONDAGINFO_H

#include "llvm/Target/TargetSelectionDAGInfo.h"

namespace llvm {

class LC3SelectionDAGInfo : public TargetSelectionDAGInfo {
public:
  ~LC3SelectionDAGInfo();
};
}

#endif
