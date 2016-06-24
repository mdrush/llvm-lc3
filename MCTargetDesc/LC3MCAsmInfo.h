#ifndef LC3TARGETASMINFO_H
#define LC3TARGETASMINFO_H
#include "llvm/MC/MCAsmInfoELF.h"

namespace llvm {
	class StringRef;
	class Target;
	class LC3MCAsmInfo : public MCAsmInfoELF {
	virtual void anchor();
	public:
	 explicit LC3MCAsmInfo(StringRef TT);
	};
} // namespace llvm

#endif