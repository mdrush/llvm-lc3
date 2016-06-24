set(LLVM_TARGET_DEFINITIONS LC3.td)

tablegen(LLVM LC3GenRegisterInfo.inc -gen-register-info)
tablegen(LLVM LC3GenInstrInfo.inc -gen-instr-info)
tablegen(LLVM LC3GenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM LC3GenDAGISel.inc -gen-dag-isel)
tablegen(LLVM LC3GenCallingConv.inc -gen-callingconv)
tablegen(LLVM LC3GenSubtargetInfo.inc -gen-subtarget)
tablegen(LLVM LC3GenMCCodeEmitter.inc -gen-emitter)
add_public_tablegen_target(LC3CommonTableGen)

add_llvm_target(LC3CodeGen
	LC3Subtarget.cpp
	LC3TargetMachine.cpp
	LC3FrameLowering.cpp
	LC3ISelDAGToDAG.cpp
	)

add_subdirectory(InstPrinter)
add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)
