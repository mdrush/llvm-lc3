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