/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                         */
/*  \   \        Copyright (c) 2003-2020 Xilinx, Inc.                 */
/*  /   /        All Right Reserved.                                  */
/* /---/   /\                                                         */
/* \   \  /  \                                                        */
/*  \___\/\___\                                                       */
/**********************************************************************/

#if defined(_WIN32)
 #include "stdio.h"
 #define IKI_DLLESPEC __declspec(dllimport)
#else
 #define IKI_DLLESPEC
#endif
#include "iki.h"
#include <string.h>
#include <math.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
#include "svdpi.h"


#if (defined(_MSC_VER) || defined(__MINGW32__) || defined(__CYGWIN__))
#define DPI_DLLISPEC __declspec(dllimport)
#define DPI_DLLESPEC __declspec(dllexport)
#else
#define DPI_DLLISPEC
#define DPI_DLLESPEC
#endif


extern "C"
{
	DPI_DLLISPEC extern void  DPISetMode(int mode) ;
	DPI_DLLISPEC extern int   DPIGetMode() ; 
	DPI_DLLISPEC extern void  DPIAllocateExportedFunctions(int size) ;
	DPI_DLLISPEC extern void  DPIAddExportedFunction(int index, const char* value) ;
	DPI_DLLISPEC extern void  DPIAllocateSVCallerName(int index, const char* y) ;
	DPI_DLLISPEC extern void  DPISetCallerName(int index, const char* y) ;
	DPI_DLLISPEC extern void  DPISetCallerLine(int index, unsigned int y) ;
	DPI_DLLISPEC extern void  DPISetCallerOffset(int index, int y) ;
	DPI_DLLISPEC extern void  DPIAllocateDPIScopes(int size) ;
	DPI_DLLISPEC extern void  DPISetDPIScopeFunctionName(int index, const char* y) ;
	DPI_DLLISPEC extern void  DPISetDPIScopeHierarchy(int index, const char* y) ;
	DPI_DLLISPEC extern void  DPIRelocateDPIScopeIP(int index, char* IP) ;
	DPI_DLLISPEC extern void  DPIAddDPIScopeAccessibleFunction(int index, unsigned int y) ;
	DPI_DLLISPEC extern void  DPIFlushAll() ;
	DPI_DLLISPEC extern void  DPIVerifyScope() ;
	DPI_DLLISPEC extern char* DPISignalHandle(char* sigHandle, int length) ;
	DPI_DLLISPEC extern char* DPIMalloc(unsigned noOfBytes) ;
	DPI_DLLISPEC extern void  DPITransactionAuto(char* srcValue, unsigned int startIndex, unsigned int endIndex, char* net) ;
	DPI_DLLISPEC extern void  DPIScheduleTransactionBlocking(char* var, char* driver, char* src, unsigned setback, unsigned lenMinusOnne) ;
	DPI_DLLISPEC extern void  DPIMemsetSvToDpi(char* dst, char* src, int numCBytes, int is2state) ;
	DPI_DLLISPEC extern void  DPIMemsetDpiToSv(char* dst, char* src, int numCBytes, int is2state) ;
	DPI_DLLISPEC extern void  DPIMemsetSvLogic1ToDpi(char* dst, char* src) ;
	DPI_DLLISPEC extern void  DPIMemsetDpiToSvLogic1(char* dst, char* src) ;
	DPI_DLLISPEC extern void  DPIMemsetDpiToSvUnpackedLogic(char* dst, char* src, int* numRshift, int* shift) ;
	DPI_DLLISPEC extern void  DPIMemsetDpiToSvUnpackedLogicWithPackedDim(char* dst, char* src, int pckedSz, int* numRshift, int* shift) ;
	DPI_DLLISPEC extern void  DPIMemsetSvToDpiUnpackedLogic(char* dst, char* src, int* numRshift, int* shift) ;
	DPI_DLLISPEC extern void  DPIMemsetSvToDpiUnpackedLogicWithPackedDim(char* dst, char* src, int pckdSz, int* numRshift, int* shift) ;
	DPI_DLLISPEC extern void  DPIMemsetDpiToSvUnpackedBit(char* dst, char* src, int* numRshift, int* shift) ;
	DPI_DLLISPEC extern void  DPIMemsetDpiToSvUnpackedBitWithPackedDim(char* dst, char* src, int pckdSz, int* numRshift, int* shift) ;
	DPI_DLLISPEC extern void  DPIMemsetSvToDpiUnpackedBit(char* dst, char* src, int* numRshift, int* shift) ;
	DPI_DLLISPEC extern void  DPIMemsetSvToDpiUnpackedBitWithPackedDim(char* dst, char* src, int pckdSz, int* numRshift, int* shift) ;
	DPI_DLLISPEC extern void  DPISetFuncName(const char* funcName) ;
	DPI_DLLISPEC extern int   staticScopeCheck(const char* calledFunction) ;
	DPI_DLLISPEC extern void  DPIAllocateSVCallerInfo(int size) ;
	DPI_DLLISPEC extern void* DPICreateContext(int scopeId, char* IP, int callerIdx);
	DPI_DLLISPEC extern void* DPIGetCurrentContext();
	DPI_DLLISPEC extern void  DPISetCurrentContext(void*);
	DPI_DLLISPEC extern void  DPIRemoveContext(void*);
	DPI_DLLISPEC extern int   svGetScopeStaticId();
	DPI_DLLISPEC extern char* svGetScopeIP();
	DPI_DLLISPEC extern unsigned DPIGetUnpackedSizeFromSVOpenArray(svOpenArray*);
	DPI_DLLISPEC extern unsigned DPIGetConstraintSizeFromSVOpenArray(svOpenArray*, int);
	DPI_DLLISPEC extern int   topOffset() ;
	DPI_DLLISPEC extern char* DPIInitializeFunction(char* p, unsigned size, long long offset) ;
	DPI_DLLISPEC extern void  DPIInvokeFunction(char* processPtr, char* SP, void* func, char* IP) ;
	DPI_DLLISPEC extern void  DPIDeleteFunctionInvocation(char* SP) ;
	DPI_DLLISPEC extern void  DPISetTaskScopeId(int scopeId) ;
	DPI_DLLISPEC extern void  DPISetTaskCaller(int index) ;
	DPI_DLLISPEC extern int   DPIGetTaskCaller() ;
	DPI_DLLISPEC extern char* DPIInitializeTask(long long subprogInDPOffset, char* scopePropInIP, unsigned size, char* parentBlock) ;
	DPI_DLLISPEC extern void  DPIInvokeTask(long long subprogInDPOffset, char* SP, void* func, char* IP) ;
	DPI_DLLISPEC extern void  DPIDeleteTaskInvocation(char* SP) ;
	DPI_DLLISPEC extern void* DPICreateTaskContext(int (*wrapper)(char*, char*, char*), char* DP, char* IP, char* SP, size_t stackSz) ;
	DPI_DLLISPEC extern void  DPIRemoveTaskContext(void*) ;
	DPI_DLLISPEC extern void  DPICallCurrentContext() ;
	DPI_DLLISPEC extern void  DPIYieldCurrentContext() ;
	DPI_DLLISPEC extern void* DPIGetCurrentTaskContext() ;
	DPI_DLLISPEC extern int   DPIRunningInNewContext() ;
	DPI_DLLISPEC extern void  DPISetCurrentTaskContext(void* x) ;
}

namespace XILINX_DPI { 

	void dpiInitialize()
	{
		DPIAllocateSVCallerInfo(4) ;
		DPISetCallerName(0, "/home/gexl/Desktop/test2/RecoNIC/sim/src/rn_tb_2rdma_top.sv") ;
		DPISetCallerLine(0, 39) ;
		DPISetCallerOffset(0, 243736) ;
		DPISetCallerName(1, "/home/gexl/Desktop/test2/RecoNIC/sim/src/rn_tb_2rdma_top.sv") ;
		DPISetCallerLine(1, 40) ;
		DPISetCallerOffset(1, 243736) ;
		DPISetCallerName(2, "/home/gexl/Desktop/test2/RecoNIC/sim/src/rn_tb_2rdma_top.sv") ;
		DPISetCallerLine(2, 50) ;
		DPISetCallerOffset(2, 243864) ;
		DPISetCallerName(3, "/home/gexl/Desktop/test2/RecoNIC/sim/src/rn_tb_2rdma_top.sv") ;
		DPISetCallerLine(3, 53) ;
		DPISetCallerOffset(3, 243864) ;
		DPIAllocateDPIScopes(4) ;
		DPISetDPIScopeFunctionName(0, "set_init_mem_signals") ;
		DPISetDPIScopeHierarchy(0, "rn_tb_2rdma_top(SIMBRICKS_PCI_SOCKET=\"/workspaces/simbricks/experiments/out/reconic-qemu/1/dev.pci.server.rec_server\",SHM_PATH=\"/workspaces/simbricks/experiments/out/reconic-qemu/1/dev.shm.server.rec_server\")") ;
		DPIRelocateDPIScopeIP(0, (char*)(0x1624278)) ;
		DPISetDPIScopeFunctionName(1, "simbricks_init") ;
		DPISetDPIScopeHierarchy(1, "rn_tb_2rdma_top(SIMBRICKS_PCI_SOCKET=\"/workspaces/simbricks/experiments/out/reconic-qemu/1/dev.pci.server.rec_server\",SHM_PATH=\"/workspaces/simbricks/experiments/out/reconic-qemu/1/dev.shm.server.rec_server\")") ;
		DPIRelocateDPIScopeIP(1, (char*)(0x1624278)) ;
		DPISetDPIScopeFunctionName(2, "simbricks_is_exit") ;
		DPISetDPIScopeHierarchy(2, "rn_tb_2rdma_top(SIMBRICKS_PCI_SOCKET=\"/workspaces/simbricks/experiments/out/reconic-qemu/1/dev.pci.server.rec_server\",SHM_PATH=\"/workspaces/simbricks/experiments/out/reconic-qemu/1/dev.shm.server.rec_server\")") ;
		DPIRelocateDPIScopeIP(2, (char*)(0x1624278)) ;
		DPISetDPIScopeFunctionName(3, "init_shared_memory") ;
		DPISetDPIScopeHierarchy(3, "rn_tb_2rdma_top(SIMBRICKS_PCI_SOCKET=\"/workspaces/simbricks/experiments/out/reconic-qemu/1/dev.pci.server.rec_server\",SHM_PATH=\"/workspaces/simbricks/experiments/out/reconic-qemu/1/dev.shm.server.rec_server\")") ;
		DPIRelocateDPIScopeIP(3, (char*)(0x1624278)) ;
	}

}


extern "C" {
	void iki_initialize_dpi()
	{ XILINX_DPI::dpiInitialize() ; } 
}


extern "C" {

	extern void set_init_mem_signals(svLogic arg0, svLogic arg1) ;
	extern void simbricks_init(const char* arg0, const char* arg1, int64_t arg2, int64_t arg3) ;
	extern svBit simbricks_is_exit() ;
	extern void init_shared_memory() ;
}


extern "C" {
	void Dpi_wrapper_set_init_mem_signals(char *GlobalDP, char *IP, char *SP)
	{
DPISetMode(1) ; // Function chain mode : with or without context 

		    /******* Preserve Context Info *******/ 
		char *ptrToSP  = SP; 
		ptrToSP = ptrToSP + 168; 
		int scopeIdx = *((int*)ptrToSP);
		ptrToSP = (char*)((int*)ptrToSP + 1); 
		int callerIdx = *((int*)ptrToSP);
		void* funcContext = DPICreateContext(scopeIdx, IP, callerIdx);
		(*((void**)(SP + 168))) = funcContext;
		DPISetCurrentContext(*(void**)(SP + 168));
		ptrToSP = (char*)((int*)ptrToSP + 1); 

		    /******* Convert SV types to DPI-C Types *******/ 

		    /******* Create and populate DPI-C types for the arguments *******/ 

		ptrToSP = SP + 336 ; 
		svLogic cObj0;
		DPIMemsetSvLogic1ToDpi( (char*)(&cObj0), ptrToSP );
		ptrToSP = ptrToSP + 8; 

		ptrToSP = SP + 520 ; 
		svLogic cObj1;
		DPIMemsetSvLogic1ToDpi( (char*)(&cObj1), ptrToSP );
		ptrToSP = ptrToSP + 8; 

		    /******* Done Conversion of SV types to DPI-C Types *******/ 
		    /******* Call the DPI-C function *******/ 
		DPISetFuncName("set_init_mem_signals");
		DPIFlushAll();
		set_init_mem_signals(cObj0, cObj1);
		DPIRemoveContext(funcContext);
		DPIFlushAll();
		DPISetFuncName(0);
		/****** Subprogram Debug : Pop the Call Stack entry for this function invocation  ******/
		iki_vlog_function_callstack_update(SP); 
		return;
	}
	void Dpi_wrapper_simbricks_init(char *GlobalDP, char *IP, char *SP)
	{
DPISetMode(1) ; // Function chain mode : with or without context 

		    /******* Preserve Context Info *******/ 
		char *ptrToSP  = SP; 
		ptrToSP = ptrToSP + 168; 
		int scopeIdx = *((int*)ptrToSP);
		ptrToSP = (char*)((int*)ptrToSP + 1); 
		int callerIdx = *((int*)ptrToSP);
		void* funcContext = DPICreateContext(scopeIdx, IP, callerIdx);
		(*((void**)(SP + 168))) = funcContext;
		DPISetCurrentContext(*(void**)(SP + 168));
		ptrToSP = (char*)((int*)ptrToSP + 1); 

		    /******* Convert SV types to DPI-C Types *******/ 

		    /******* Create and populate DPI-C types for the arguments *******/ 

const char emptyStrLiteral = '\0';
		ptrToSP = SP + 336 ; 
		const char* cObj0;
		cObj0 = *(char**)ptrToSP == 0? &emptyStrLiteral : *(char**)ptrToSP;
		ptrToSP = ptrToSP + 8; 

		ptrToSP = SP + 520 ; 
		const char* cObj1;
		cObj1 = *(char**)ptrToSP == 0? &emptyStrLiteral : *(char**)ptrToSP;
		ptrToSP = ptrToSP + 8; 

		ptrToSP = SP + 704 ; 
		int64_t cObj2;
		DPIMemsetSvToDpi( (char*)(&cObj2), ptrToSP, 8, 1 );
		ptrToSP = ptrToSP + 16; 

		ptrToSP = SP + 896 ; 
		int64_t cObj3;
		DPIMemsetSvToDpi( (char*)(&cObj3), ptrToSP, 8, 1 );
		ptrToSP = ptrToSP + 16; 

		    /******* Done Conversion of SV types to DPI-C Types *******/ 
		    /******* Call the DPI-C function *******/ 
		DPISetFuncName("simbricks_init");
		DPIFlushAll();
		simbricks_init(cObj0, cObj1, cObj2, cObj3);
		DPIRemoveContext(funcContext);
		DPIFlushAll();
		DPISetFuncName(0);
		/****** Subprogram Debug : Pop the Call Stack entry for this function invocation  ******/
		iki_vlog_function_callstack_update(SP); 
		return;
	}
	svBit Dpi_wrapper_simbricks_is_exit(char *GlobalDP, char *IP, char *SP)
	{
DPISetMode(1) ; // Function chain mode : with or without context 

		    /******* Preserve Context Info *******/ 
		char *ptrToSP  = SP; 
		ptrToSP = ptrToSP + 168; 
		int scopeIdx = *((int*)ptrToSP);
		ptrToSP = (char*)((int*)ptrToSP + 1); 
		int callerIdx = *((int*)ptrToSP);
		void* funcContext = DPICreateContext(scopeIdx, IP, callerIdx);
		(*((void**)(SP + 168))) = funcContext;
		DPISetCurrentContext(*(void**)(SP + 168));
		ptrToSP = (char*)((int*)ptrToSP + 1); 

		    /******* Convert SV types to DPI-C Types *******/ 

		    /******* Create and populate DPI-C types for the arguments *******/ 

		    /******* Done Conversion of SV types to DPI-C Types *******/ 
		    /******* Call the DPI-C function *******/ 
		DPISetFuncName("simbricks_is_exit");
		DPIFlushAll();
		svBit result = 0 ;
		result = simbricks_is_exit();

		    /******* Write result value into the SP *******/ 
		ptrToSP = SP + 336 ; 
		DPIRemoveContext(funcContext);
		DPIFlushAll();
		DPISetFuncName(0);
		*((int*)ptrToSP) = result & 1; 
		*((int*)ptrToSP + 1) = 0; 
		/****** Subprogram Debug : Pop the Call Stack entry for this function invocation  ******/
		iki_vlog_function_callstack_update(SP); 
		return result ;
	}
	void Dpi_wrapper_init_shared_memory(char *GlobalDP, char *IP, char *SP)
	{
DPISetMode(1) ; // Function chain mode : with or without context 

		    /******* Preserve Context Info *******/ 
		char *ptrToSP  = SP; 
		ptrToSP = ptrToSP + 168; 
		int scopeIdx = *((int*)ptrToSP);
		ptrToSP = (char*)((int*)ptrToSP + 1); 
		int callerIdx = *((int*)ptrToSP);
		void* funcContext = DPICreateContext(scopeIdx, IP, callerIdx);
		(*((void**)(SP + 168))) = funcContext;
		DPISetCurrentContext(*(void**)(SP + 168));
		ptrToSP = (char*)((int*)ptrToSP + 1); 

		    /******* Convert SV types to DPI-C Types *******/ 

		    /******* Create and populate DPI-C types for the arguments *******/ 

		    /******* Done Conversion of SV types to DPI-C Types *******/ 
		    /******* Call the DPI-C function *******/ 
		DPISetFuncName("init_shared_memory");
		DPIFlushAll();
		init_shared_memory();
		DPIRemoveContext(funcContext);
		DPIFlushAll();
		DPISetFuncName(0);
		/****** Subprogram Debug : Pop the Call Stack entry for this function invocation  ******/
		iki_vlog_function_callstack_update(SP); 
		return;
	}
}


extern "C" {
}

