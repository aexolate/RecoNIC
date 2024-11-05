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
		DPIAllocateSVCallerInfo(16) ;
		DPISetCallerName(0, "/home/gexl/Desktop/test2/RecoNIC/sim/src/rn_tb_2rdma_top_remote.sv") ;
		DPISetCallerLine(0, 276) ;
		DPISetCallerOffset(0, 57064) ;
		DPISetCallerName(1, "/home/gexl/Desktop/test2/RecoNIC/sim/src/rn_tb_2rdma_top_remote.sv") ;
		DPISetCallerLine(1, 277) ;
		DPISetCallerOffset(1, 57064) ;
		DPISetCallerName(2, "/home/gexl/Desktop/test2/RecoNIC/sim/src/rn_tb_2rdma_top_remote.sv") ;
		DPISetCallerLine(2, 286) ;
		DPISetCallerOffset(2, 57192) ;
		DPISetCallerName(3, "/home/gexl/Desktop/test2/RecoNIC/sim/src/rn_tb_2rdma_top_remote.sv") ;
		DPISetCallerLine(3, 288) ;
		DPISetCallerOffset(3, 57192) ;
		DPISetCallerName(4, "/home/gexl/Desktop/test2/RecoNIC/sim/src/rn_tb_2rdma_top_remote.sv") ;
		DPISetCallerLine(4, 290) ;
		DPISetCallerOffset(4, 57192) ;
		DPISetCallerName(5, "/home/gexl/Desktop/test2/RecoNIC/sim/src/rn_tb_2rdma_top_remote.sv") ;
		DPISetCallerLine(5, 303) ;
		DPISetCallerOffset(5, 57464) ;
		DPISetCallerName(6, "/home/gexl/Desktop/test2/RecoNIC/sim/src/rn_tb_2rdma_top_remote.sv") ;
		DPISetCallerLine(6, 304) ;
		DPISetCallerOffset(6, 57464) ;
		DPISetCallerName(7, "/home/gexl/Desktop/test2/RecoNIC/sim/src/rn_tb_2rdma_top_remote.sv") ;
		DPISetCallerLine(7, 305) ;
		DPISetCallerOffset(7, 57464) ;
		DPISetCallerName(8, "/home/gexl/Desktop/test2/RecoNIC/sim/src/rn_tb_2rdma_top_remote.sv") ;
		DPISetCallerLine(8, 308) ;
		DPISetCallerOffset(8, 57464) ;
		DPISetCallerName(9, "/home/gexl/Desktop/test2/RecoNIC/sim/src/rn_tb_2rdma_top_remote.sv") ;
		DPISetCallerLine(9, 335) ;
		DPISetCallerOffset(9, 57464) ;
		DPISetCallerName(10, "/home/gexl/Desktop/test2/RecoNIC/sim/src/rn_tb_2rdma_top_remote.sv") ;
		DPISetCallerLine(10, 376) ;
		DPISetCallerOffset(10, 57464) ;
		DPISetCallerName(11, "/home/gexl/Desktop/test2/RecoNIC/sim/src/rn_tb_2rdma_top_remote.sv") ;
		DPISetCallerLine(11, 417) ;
		DPISetCallerOffset(11, 57464) ;
		DPISetCallerName(12, "/home/gexl/Desktop/test2/RecoNIC/sim/src/rn_tb_2rdma_top_remote.sv") ;
		DPISetCallerLine(12, 431) ;
		DPISetCallerOffset(12, 57464) ;
		DPISetCallerName(13, "/home/gexl/Desktop/test2/RecoNIC/sim/src/rn_tb_2rdma_top_remote.sv") ;
		DPISetCallerLine(13, 458) ;
		DPISetCallerOffset(13, 57464) ;
		DPISetCallerName(14, "/home/gexl/Desktop/test2/RecoNIC/sim/src/rn_tb_2rdma_top_remote.sv") ;
		DPISetCallerLine(14, 500) ;
		DPISetCallerOffset(14, 57464) ;
		DPISetCallerName(15, "/home/gexl/Desktop/test2/RecoNIC/sim/src/rn_tb_2rdma_top_remote.sv") ;
		DPISetCallerLine(15, 514) ;
		DPISetCallerOffset(15, 57464) ;
		DPIAllocateDPIScopes(16) ;
		DPISetDPIScopeFunctionName(0, "simbricks_init") ;
		DPISetDPIScopeHierarchy(0, "rn_tb_2rdma_top_remote(SIMBRICKS_PCI_SOCKET=\"/workspaces/simbricks/experiments/out/reconic-qemu/1/dev.pci.client.rec_client\",SHM_PATH=\"/workspaces/simbricks/experiments/out/reconic-qemu/1/dev.shm.client.rec_client\")") ;
		DPIRelocateDPIScopeIP(0, (char*)(0x568fd8)) ;
		DPISetDPIScopeFunctionName(1, "simbricks_is_exit") ;
		DPISetDPIScopeHierarchy(1, "rn_tb_2rdma_top_remote(SIMBRICKS_PCI_SOCKET=\"/workspaces/simbricks/experiments/out/reconic-qemu/1/dev.pci.client.rec_client\",SHM_PATH=\"/workspaces/simbricks/experiments/out/reconic-qemu/1/dev.shm.client.rec_client\")") ;
		DPIRelocateDPIScopeIP(1, (char*)(0x568fd8)) ;
		DPISetDPIScopeFunctionName(2, "init_shared_memory") ;
		DPISetDPIScopeHierarchy(2, "rn_tb_2rdma_top_remote(SIMBRICKS_PCI_SOCKET=\"/workspaces/simbricks/experiments/out/reconic-qemu/1/dev.pci.client.rec_client\",SHM_PATH=\"/workspaces/simbricks/experiments/out/reconic-qemu/1/dev.shm.client.rec_client\")") ;
		DPIRelocateDPIScopeIP(2, (char*)(0x568fd8)) ;
		DPISetDPIScopeFunctionName(3, "get_init_mem_signals") ;
		DPISetDPIScopeHierarchy(3, "rn_tb_2rdma_top_remote(SIMBRICKS_PCI_SOCKET=\"/workspaces/simbricks/experiments/out/reconic-qemu/1/dev.pci.client.rec_client\",SHM_PATH=\"/workspaces/simbricks/experiments/out/reconic-qemu/1/dev.shm.client.rec_client\")") ;
		DPIRelocateDPIScopeIP(3, (char*)(0x568fd8)) ;
		DPISetDPIScopeFunctionName(4, "set_finish_config_rdma2") ;
		DPISetDPIScopeHierarchy(4, "rn_tb_2rdma_top_remote(SIMBRICKS_PCI_SOCKET=\"/workspaces/simbricks/experiments/out/reconic-qemu/1/dev.pci.client.rec_client\",SHM_PATH=\"/workspaces/simbricks/experiments/out/reconic-qemu/1/dev.shm.client.rec_client\")") ;
		DPIRelocateDPIScopeIP(4, (char*)(0x568fd8)) ;
		DPISetDPIScopeFunctionName(5, "get_start_rdma2_stat") ;
		DPISetDPIScopeHierarchy(5, "rn_tb_2rdma_top_remote(SIMBRICKS_PCI_SOCKET=\"/workspaces/simbricks/experiments/out/reconic-qemu/1/dev.pci.client.rec_client\",SHM_PATH=\"/workspaces/simbricks/experiments/out/reconic-qemu/1/dev.shm.client.rec_client\")") ;
		DPIRelocateDPIScopeIP(5, (char*)(0x568fd8)) ;
		DPISetDPIScopeFunctionName(6, "set_rp_signals") ;
		DPISetDPIScopeHierarchy(6, "rn_tb_2rdma_top_remote(SIMBRICKS_PCI_SOCKET=\"/workspaces/simbricks/experiments/out/reconic-qemu/1/dev.pci.client.rec_client\",SHM_PATH=\"/workspaces/simbricks/experiments/out/reconic-qemu/1/dev.shm.client.rec_client\")") ;
		DPIRelocateDPIScopeIP(6, (char*)(0x568fd8)) ;
		DPISetDPIScopeFunctionName(7, "get_rp_signal_tready") ;
		DPISetDPIScopeHierarchy(7, "rn_tb_2rdma_top_remote(SIMBRICKS_PCI_SOCKET=\"/workspaces/simbricks/experiments/out/reconic-qemu/1/dev.pci.client.rec_client\",SHM_PATH=\"/workspaces/simbricks/experiments/out/reconic-qemu/1/dev.shm.client.rec_client\")") ;
		DPIRelocateDPIScopeIP(7, (char*)(0x568fd8)) ;
		DPISetDPIScopeFunctionName(8, "get_cmac_tx_signals") ;
		DPISetDPIScopeHierarchy(8, "rn_tb_2rdma_top_remote(SIMBRICKS_PCI_SOCKET=\"/workspaces/simbricks/experiments/out/reconic-qemu/1/dev.pci.client.rec_client\",SHM_PATH=\"/workspaces/simbricks/experiments/out/reconic-qemu/1/dev.shm.client.rec_client\")") ;
		DPIRelocateDPIScopeIP(8, (char*)(0x568fd8)) ;
		DPISetDPIScopeFunctionName(9, "set_axi_rdma2_send_write_payload_1") ;
		DPISetDPIScopeHierarchy(9, "rn_tb_2rdma_top_remote(SIMBRICKS_PCI_SOCKET=\"/workspaces/simbricks/experiments/out/reconic-qemu/1/dev.pci.client.rec_client\",SHM_PATH=\"/workspaces/simbricks/experiments/out/reconic-qemu/1/dev.shm.client.rec_client\")") ;
		DPIRelocateDPIScopeIP(9, (char*)(0x568fd8)) ;
		DPISetDPIScopeFunctionName(10, "get_axi_rdma2_send_write_payload_2") ;
		DPISetDPIScopeHierarchy(10, "rn_tb_2rdma_top_remote(SIMBRICKS_PCI_SOCKET=\"/workspaces/simbricks/experiments/out/reconic-qemu/1/dev.pci.client.rec_client\",SHM_PATH=\"/workspaces/simbricks/experiments/out/reconic-qemu/1/dev.shm.client.rec_client\")") ;
		DPIRelocateDPIScopeIP(10, (char*)(0x568fd8)) ;
		DPISetDPIScopeFunctionName(11, "get_axi_rdma_rsp_payload_2") ;
		DPISetDPIScopeHierarchy(11, "rn_tb_2rdma_top_remote(SIMBRICKS_PCI_SOCKET=\"/workspaces/simbricks/experiments/out/reconic-qemu/1/dev.pci.client.rec_client\",SHM_PATH=\"/workspaces/simbricks/experiments/out/reconic-qemu/1/dev.shm.client.rec_client\")") ;
		DPIRelocateDPIScopeIP(11, (char*)(0x568fd8)) ;
		DPISetDPIScopeFunctionName(12, "get_axi_rdma_get_wqe_2") ;
		DPISetDPIScopeHierarchy(12, "rn_tb_2rdma_top_remote(SIMBRICKS_PCI_SOCKET=\"/workspaces/simbricks/experiments/out/reconic-qemu/1/dev.pci.client.rec_client\",SHM_PATH=\"/workspaces/simbricks/experiments/out/reconic-qemu/1/dev.shm.client.rec_client\")") ;
		DPIRelocateDPIScopeIP(12, (char*)(0x568fd8)) ;
		DPISetDPIScopeFunctionName(13, "set_axi_rdma2_get_payload_1") ;
		DPISetDPIScopeHierarchy(13, "rn_tb_2rdma_top_remote(SIMBRICKS_PCI_SOCKET=\"/workspaces/simbricks/experiments/out/reconic-qemu/1/dev.pci.client.rec_client\",SHM_PATH=\"/workspaces/simbricks/experiments/out/reconic-qemu/1/dev.shm.client.rec_client\")") ;
		DPIRelocateDPIScopeIP(13, (char*)(0x568fd8)) ;
		DPISetDPIScopeFunctionName(14, "get_axi_rdma2_get_payload_2") ;
		DPISetDPIScopeHierarchy(14, "rn_tb_2rdma_top_remote(SIMBRICKS_PCI_SOCKET=\"/workspaces/simbricks/experiments/out/reconic-qemu/1/dev.pci.client.rec_client\",SHM_PATH=\"/workspaces/simbricks/experiments/out/reconic-qemu/1/dev.shm.client.rec_client\")") ;
		DPIRelocateDPIScopeIP(14, (char*)(0x568fd8)) ;
		DPISetDPIScopeFunctionName(15, "get_axi_rdma_completion_2") ;
		DPISetDPIScopeHierarchy(15, "rn_tb_2rdma_top_remote(SIMBRICKS_PCI_SOCKET=\"/workspaces/simbricks/experiments/out/reconic-qemu/1/dev.pci.client.rec_client\",SHM_PATH=\"/workspaces/simbricks/experiments/out/reconic-qemu/1/dev.shm.client.rec_client\")") ;
		DPIRelocateDPIScopeIP(15, (char*)(0x568fd8)) ;
	}

}


extern "C" {
	void iki_initialize_dpi()
	{ XILINX_DPI::dpiInitialize() ; } 
}


extern "C" {

	extern void simbricks_init(const char* arg0, const char* arg1, int64_t arg2, int64_t arg3) ;
	extern svBit simbricks_is_exit() ;
	extern void init_shared_memory() ;
	extern void get_init_mem_signals(int* arg0, int* arg1) ;
	extern void set_finish_config_rdma2(int arg0) ;
	extern void get_start_rdma2_stat(int* arg0) ;
	extern void set_rp_signals(const svBitVecVal arg0[SV_PACKED_DATA_NELEMS(512)], const svBitVecVal arg1[SV_PACKED_DATA_NELEMS(64)], int arg2, int arg3) ;
	extern void get_rp_signal_tready(int* arg0) ;
	extern void get_cmac_tx_signals(svBitVecVal arg0[SV_PACKED_DATA_NELEMS(512)], svBitVecVal arg1[SV_PACKED_DATA_NELEMS(64)], int* arg2, int* arg3, int* arg4) ;
	extern void set_axi_rdma2_send_write_payload_1(int arg0, const svBitVecVal arg1[SV_PACKED_DATA_NELEMS(64)], int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, const svBitVecVal arg9[SV_PACKED_DATA_NELEMS(512)], const svBitVecVal arg10[SV_PACKED_DATA_NELEMS(64)], int arg11, int arg12, int arg13, int arg14, const svBitVecVal arg15[SV_PACKED_DATA_NELEMS(64)], int arg16, int arg17, int arg18, int arg19, int arg20, int arg21, int arg22, int arg23) ;
	extern void get_axi_rdma2_send_write_payload_2(int* arg0, int* arg1, int* arg2, svBitVecVal arg3[SV_PACKED_DATA_NELEMS(2)], int* arg4, int* arg5, int* arg6, svBitVecVal arg7[SV_PACKED_DATA_NELEMS(512)], svBitVecVal arg8[SV_PACKED_DATA_NELEMS(2)], int* arg9, int* arg10) ;
	extern void get_axi_rdma_rsp_payload_2(int* arg0, int* arg1, int* arg2, svBitVecVal arg3[SV_PACKED_DATA_NELEMS(2)], int* arg4, int* arg5, int* arg6, svBitVecVal arg7[SV_PACKED_DATA_NELEMS(512)], svBitVecVal arg8[SV_PACKED_DATA_NELEMS(2)], int* arg9, int* arg10) ;
	extern void get_axi_rdma_get_wqe_2(int* arg0, int* arg1, int* arg2, svBitVecVal arg3[SV_PACKED_DATA_NELEMS(2)], int* arg4, int* arg5, int* arg6, svBitVecVal arg7[SV_PACKED_DATA_NELEMS(512)], svBitVecVal arg8[SV_PACKED_DATA_NELEMS(2)], int* arg9, int* arg10) ;
	extern void set_axi_rdma2_get_payload_1(int arg0, const svBitVecVal arg1[SV_PACKED_DATA_NELEMS(64)], int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, const svBitVecVal arg9[SV_PACKED_DATA_NELEMS(512)], const svBitVecVal arg10[SV_PACKED_DATA_NELEMS(64)], int arg11, int arg12, int arg13, int arg14, const svBitVecVal arg15[SV_PACKED_DATA_NELEMS(64)], int arg16, int arg17, int arg18, int arg19, int arg20, int arg21, int arg22, int arg23) ;
	extern void get_axi_rdma2_get_payload_2(int* arg0, int* arg1, int* arg2, svBitVecVal arg3[SV_PACKED_DATA_NELEMS(2)], int* arg4, int* arg5, int* arg6, svBitVecVal arg7[SV_PACKED_DATA_NELEMS(512)], svBitVecVal arg8[SV_PACKED_DATA_NELEMS(2)], int* arg9, int* arg10) ;
	extern void get_axi_rdma_completion_2(int* arg0, int* arg1, int* arg2, svBitVecVal arg3[SV_PACKED_DATA_NELEMS(2)], int* arg4, int* arg5, int* arg6, svBitVecVal arg7[SV_PACKED_DATA_NELEMS(512)], svBitVecVal arg8[SV_PACKED_DATA_NELEMS(2)], int* arg9, int* arg10) ;
}


extern "C" {
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
	void Dpi_wrapper_get_init_mem_signals(char *GlobalDP, char *IP, char *SP)
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
		int cObj0;
		DPIMemsetSvToDpi( (char*)(&cObj0), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		ptrToSP = SP + 520 ; 
		int cObj1;
		DPIMemsetSvToDpi( (char*)(&cObj1), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		    /******* Done Conversion of SV types to DPI-C Types *******/ 
		    /******* Call the DPI-C function *******/ 
		DPISetFuncName("get_init_mem_signals");
		DPIFlushAll();
		get_init_mem_signals(&cObj0, &cObj1);
		DPIRemoveContext(funcContext);
		DPIFlushAll();
		DPISetFuncName(0);



		    /******* Write OUTPUT/INOUT to the SP *******/ 
		ptrToSP = SP + 336 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)(&cObj0), 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 520 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)(&cObj1), 4, 1 );
		ptrToSP = ptrToSP + 8; 

		/****** Subprogram Debug : Pop the Call Stack entry for this function invocation  ******/
		iki_vlog_function_callstack_update(SP); 
		return;
	}
	void Dpi_wrapper_set_finish_config_rdma2(char *GlobalDP, char *IP, char *SP)
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
		int cObj0;
		DPIMemsetSvToDpi( (char*)(&cObj0), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		    /******* Done Conversion of SV types to DPI-C Types *******/ 
		    /******* Call the DPI-C function *******/ 
		DPISetFuncName("set_finish_config_rdma2");
		DPIFlushAll();
		set_finish_config_rdma2(cObj0);
		DPIRemoveContext(funcContext);
		DPIFlushAll();
		DPISetFuncName(0);
		/****** Subprogram Debug : Pop the Call Stack entry for this function invocation  ******/
		iki_vlog_function_callstack_update(SP); 
		return;
	}
	void Dpi_wrapper_get_start_rdma2_stat(char *GlobalDP, char *IP, char *SP)
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
		int cObj0;
		DPIMemsetSvToDpi( (char*)(&cObj0), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		    /******* Done Conversion of SV types to DPI-C Types *******/ 
		    /******* Call the DPI-C function *******/ 
		DPISetFuncName("get_start_rdma2_stat");
		DPIFlushAll();
		get_start_rdma2_stat(&cObj0);
		DPIRemoveContext(funcContext);
		DPIFlushAll();
		DPISetFuncName(0);



		    /******* Write OUTPUT/INOUT to the SP *******/ 
		ptrToSP = SP + 336 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)(&cObj0), 4, 1 );
		ptrToSP = ptrToSP + 8; 

		/****** Subprogram Debug : Pop the Call Stack entry for this function invocation  ******/
		iki_vlog_function_callstack_update(SP); 
		return;
	}
	void Dpi_wrapper_set_rp_signals(char *GlobalDP, char *IP, char *SP)
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
		svBitVecVal cObj0[SV_PACKED_DATA_NELEMS(512)];
		DPIMemsetSvToDpi( (char*)cObj0, ptrToSP, 64, 1 );
		ptrToSP = ptrToSP + 128; 

		ptrToSP = SP + 640 ; 
		svBitVecVal cObj1[SV_PACKED_DATA_NELEMS(64)];
		DPIMemsetSvToDpi( (char*)cObj1, ptrToSP, 8, 1 );
		ptrToSP = ptrToSP + 16; 

		ptrToSP = SP + 832 ; 
		int cObj2;
		DPIMemsetSvToDpi( (char*)(&cObj2), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		ptrToSP = SP + 1016 ; 
		int cObj3;
		DPIMemsetSvToDpi( (char*)(&cObj3), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		    /******* Done Conversion of SV types to DPI-C Types *******/ 
		    /******* Call the DPI-C function *******/ 
		DPISetFuncName("set_rp_signals");
		DPIFlushAll();
		set_rp_signals(cObj0, cObj1, cObj2, cObj3);
		DPIRemoveContext(funcContext);
		DPIFlushAll();
		DPISetFuncName(0);
		/****** Subprogram Debug : Pop the Call Stack entry for this function invocation  ******/
		iki_vlog_function_callstack_update(SP); 
		return;
	}
	void Dpi_wrapper_get_rp_signal_tready(char *GlobalDP, char *IP, char *SP)
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
		int cObj0;
		DPIMemsetSvToDpi( (char*)(&cObj0), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		    /******* Done Conversion of SV types to DPI-C Types *******/ 
		    /******* Call the DPI-C function *******/ 
		DPISetFuncName("get_rp_signal_tready");
		DPIFlushAll();
		get_rp_signal_tready(&cObj0);
		DPIRemoveContext(funcContext);
		DPIFlushAll();
		DPISetFuncName(0);



		    /******* Write OUTPUT/INOUT to the SP *******/ 
		ptrToSP = SP + 336 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)(&cObj0), 4, 1 );
		ptrToSP = ptrToSP + 8; 

		/****** Subprogram Debug : Pop the Call Stack entry for this function invocation  ******/
		iki_vlog_function_callstack_update(SP); 
		return;
	}
	void Dpi_wrapper_get_cmac_tx_signals(char *GlobalDP, char *IP, char *SP)
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
		svBitVecVal cObj0[SV_PACKED_DATA_NELEMS(512)];
		DPIMemsetSvToDpi( (char*)cObj0, ptrToSP, 64, 1 );
		ptrToSP = ptrToSP + 128; 

		ptrToSP = SP + 640 ; 
		svBitVecVal cObj1[SV_PACKED_DATA_NELEMS(64)];
		DPIMemsetSvToDpi( (char*)cObj1, ptrToSP, 8, 1 );
		ptrToSP = ptrToSP + 16; 

		ptrToSP = SP + 832 ; 
		int cObj2;
		DPIMemsetSvToDpi( (char*)(&cObj2), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		ptrToSP = SP + 1016 ; 
		int cObj3;
		DPIMemsetSvToDpi( (char*)(&cObj3), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		ptrToSP = SP + 1200 ; 
		int cObj4;
		DPIMemsetSvToDpi( (char*)(&cObj4), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		    /******* Done Conversion of SV types to DPI-C Types *******/ 
		    /******* Call the DPI-C function *******/ 
		DPISetFuncName("get_cmac_tx_signals");
		DPIFlushAll();
		get_cmac_tx_signals(cObj0, cObj1, &cObj2, &cObj3, &cObj4);
		DPIRemoveContext(funcContext);
		DPIFlushAll();
		DPISetFuncName(0);



		    /******* Write OUTPUT/INOUT to the SP *******/ 
		ptrToSP = SP + 336 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)cObj0, 64, 1 );
		ptrToSP = ptrToSP + 128; 
		ptrToSP = SP + 640 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)cObj1, 8, 1 );
		ptrToSP = ptrToSP + 16; 
		ptrToSP = SP + 832 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)(&cObj2), 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 1016 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)(&cObj3), 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 1200 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)(&cObj4), 4, 1 );
		ptrToSP = ptrToSP + 8; 

		/****** Subprogram Debug : Pop the Call Stack entry for this function invocation  ******/
		iki_vlog_function_callstack_update(SP); 
		return;
	}
	void Dpi_wrapper_set_axi_rdma2_send_write_payload_1(char *GlobalDP, char *IP, char *SP)
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
		int cObj0;
		DPIMemsetSvToDpi( (char*)(&cObj0), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		ptrToSP = SP + 520 ; 
		svBitVecVal cObj1[SV_PACKED_DATA_NELEMS(64)];
		DPIMemsetSvToDpi( (char*)cObj1, ptrToSP, 8, 1 );
		ptrToSP = ptrToSP + 16; 

		ptrToSP = SP + 712 ; 
		int cObj2;
		DPIMemsetSvToDpi( (char*)(&cObj2), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 896 ; 
		int cObj3;
		DPIMemsetSvToDpi( (char*)(&cObj3), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 1080 ; 
		int cObj4;
		DPIMemsetSvToDpi( (char*)(&cObj4), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 1264 ; 
		int cObj5;
		DPIMemsetSvToDpi( (char*)(&cObj5), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 1448 ; 
		int cObj6;
		DPIMemsetSvToDpi( (char*)(&cObj6), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 1632 ; 
		int cObj7;
		DPIMemsetSvToDpi( (char*)(&cObj7), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 1816 ; 
		int cObj8;
		DPIMemsetSvToDpi( (char*)(&cObj8), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		ptrToSP = SP + 2000 ; 
		svBitVecVal cObj9[SV_PACKED_DATA_NELEMS(512)];
		DPIMemsetSvToDpi( (char*)cObj9, ptrToSP, 64, 1 );
		ptrToSP = ptrToSP + 128; 

		ptrToSP = SP + 2304 ; 
		svBitVecVal cObj10[SV_PACKED_DATA_NELEMS(64)];
		DPIMemsetSvToDpi( (char*)cObj10, ptrToSP, 8, 1 );
		ptrToSP = ptrToSP + 16; 

		ptrToSP = SP + 2496 ; 
		int cObj11;
		DPIMemsetSvToDpi( (char*)(&cObj11), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 2680 ; 
		int cObj12;
		DPIMemsetSvToDpi( (char*)(&cObj12), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 2864 ; 
		int cObj13;
		DPIMemsetSvToDpi( (char*)(&cObj13), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		ptrToSP = SP + 3048 ; 
		int cObj14;
		DPIMemsetSvToDpi( (char*)(&cObj14), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		ptrToSP = SP + 3232 ; 
		svBitVecVal cObj15[SV_PACKED_DATA_NELEMS(64)];
		DPIMemsetSvToDpi( (char*)cObj15, ptrToSP, 8, 1 );
		ptrToSP = ptrToSP + 16; 

		ptrToSP = SP + 3424 ; 
		int cObj16;
		DPIMemsetSvToDpi( (char*)(&cObj16), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 3608 ; 
		int cObj17;
		DPIMemsetSvToDpi( (char*)(&cObj17), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 3792 ; 
		int cObj18;
		DPIMemsetSvToDpi( (char*)(&cObj18), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 3976 ; 
		int cObj19;
		DPIMemsetSvToDpi( (char*)(&cObj19), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 4160 ; 
		int cObj20;
		DPIMemsetSvToDpi( (char*)(&cObj20), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 4344 ; 
		int cObj21;
		DPIMemsetSvToDpi( (char*)(&cObj21), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 4528 ; 
		int cObj22;
		DPIMemsetSvToDpi( (char*)(&cObj22), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 4712 ; 
		int cObj23;
		DPIMemsetSvToDpi( (char*)(&cObj23), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		    /******* Done Conversion of SV types to DPI-C Types *******/ 
		    /******* Call the DPI-C function *******/ 
		DPISetFuncName("set_axi_rdma2_send_write_payload_1");
		DPIFlushAll();
		set_axi_rdma2_send_write_payload_1(cObj0, cObj1, cObj2, cObj3, cObj4, cObj5, cObj6, cObj7, cObj8, cObj9, cObj10, cObj11, cObj12, cObj13, cObj14, cObj15, cObj16, cObj17, cObj18, cObj19, cObj20, cObj21, cObj22, cObj23);
		DPIRemoveContext(funcContext);
		DPIFlushAll();
		DPISetFuncName(0);
		/****** Subprogram Debug : Pop the Call Stack entry for this function invocation  ******/
		iki_vlog_function_callstack_update(SP); 
		return;
	}
	void Dpi_wrapper_get_axi_rdma2_send_write_payload_2(char *GlobalDP, char *IP, char *SP)
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
		int cObj0;
		DPIMemsetSvToDpi( (char*)(&cObj0), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 520 ; 
		int cObj1;
		DPIMemsetSvToDpi( (char*)(&cObj1), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		ptrToSP = SP + 704 ; 
		int cObj2;
		DPIMemsetSvToDpi( (char*)(&cObj2), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		ptrToSP = SP + 888 ; 
		svBitVecVal cObj3[SV_PACKED_DATA_NELEMS(2)];
		DPIMemsetSvToDpi( (char*)cObj3, ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		ptrToSP = SP + 1072 ; 
		int cObj4;
		DPIMemsetSvToDpi( (char*)(&cObj4), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		ptrToSP = SP + 1256 ; 
		int cObj5;
		DPIMemsetSvToDpi( (char*)(&cObj5), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		ptrToSP = SP + 1440 ; 
		int cObj6;
		DPIMemsetSvToDpi( (char*)(&cObj6), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		ptrToSP = SP + 1624 ; 
		svBitVecVal cObj7[SV_PACKED_DATA_NELEMS(512)];
		DPIMemsetSvToDpi( (char*)cObj7, ptrToSP, 64, 1 );
		ptrToSP = ptrToSP + 128; 

		ptrToSP = SP + 1928 ; 
		svBitVecVal cObj8[SV_PACKED_DATA_NELEMS(2)];
		DPIMemsetSvToDpi( (char*)cObj8, ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		ptrToSP = SP + 2112 ; 
		int cObj9;
		DPIMemsetSvToDpi( (char*)(&cObj9), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 2296 ; 
		int cObj10;
		DPIMemsetSvToDpi( (char*)(&cObj10), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		    /******* Done Conversion of SV types to DPI-C Types *******/ 
		    /******* Call the DPI-C function *******/ 
		DPISetFuncName("get_axi_rdma2_send_write_payload_2");
		DPIFlushAll();
		get_axi_rdma2_send_write_payload_2(&cObj0, &cObj1, &cObj2, cObj3, &cObj4, &cObj5, &cObj6, cObj7, cObj8, &cObj9, &cObj10);
		DPIRemoveContext(funcContext);
		DPIFlushAll();
		DPISetFuncName(0);



		    /******* Write OUTPUT/INOUT to the SP *******/ 
		ptrToSP = SP + 336 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)(&cObj0), 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 520 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)(&cObj1), 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 704 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)(&cObj2), 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 888 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)cObj3, 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 1072 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)(&cObj4), 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 1256 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)(&cObj5), 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 1440 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)(&cObj6), 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 1624 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)cObj7, 64, 1 );
		ptrToSP = ptrToSP + 128; 
		ptrToSP = SP + 1928 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)cObj8, 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 2112 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)(&cObj9), 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 2296 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)(&cObj10), 4, 1 );
		ptrToSP = ptrToSP + 8; 

		/****** Subprogram Debug : Pop the Call Stack entry for this function invocation  ******/
		iki_vlog_function_callstack_update(SP); 
		return;
	}
	void Dpi_wrapper_get_axi_rdma_rsp_payload_2(char *GlobalDP, char *IP, char *SP)
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
		int cObj0;
		DPIMemsetSvToDpi( (char*)(&cObj0), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 520 ; 
		int cObj1;
		DPIMemsetSvToDpi( (char*)(&cObj1), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		ptrToSP = SP + 704 ; 
		int cObj2;
		DPIMemsetSvToDpi( (char*)(&cObj2), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		ptrToSP = SP + 888 ; 
		svBitVecVal cObj3[SV_PACKED_DATA_NELEMS(2)];
		DPIMemsetSvToDpi( (char*)cObj3, ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		ptrToSP = SP + 1072 ; 
		int cObj4;
		DPIMemsetSvToDpi( (char*)(&cObj4), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		ptrToSP = SP + 1256 ; 
		int cObj5;
		DPIMemsetSvToDpi( (char*)(&cObj5), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		ptrToSP = SP + 1440 ; 
		int cObj6;
		DPIMemsetSvToDpi( (char*)(&cObj6), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		ptrToSP = SP + 1624 ; 
		svBitVecVal cObj7[SV_PACKED_DATA_NELEMS(512)];
		DPIMemsetSvToDpi( (char*)cObj7, ptrToSP, 64, 1 );
		ptrToSP = ptrToSP + 128; 

		ptrToSP = SP + 1928 ; 
		svBitVecVal cObj8[SV_PACKED_DATA_NELEMS(2)];
		DPIMemsetSvToDpi( (char*)cObj8, ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		ptrToSP = SP + 2112 ; 
		int cObj9;
		DPIMemsetSvToDpi( (char*)(&cObj9), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 2296 ; 
		int cObj10;
		DPIMemsetSvToDpi( (char*)(&cObj10), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		    /******* Done Conversion of SV types to DPI-C Types *******/ 
		    /******* Call the DPI-C function *******/ 
		DPISetFuncName("get_axi_rdma_rsp_payload_2");
		DPIFlushAll();
		get_axi_rdma_rsp_payload_2(&cObj0, &cObj1, &cObj2, cObj3, &cObj4, &cObj5, &cObj6, cObj7, cObj8, &cObj9, &cObj10);
		DPIRemoveContext(funcContext);
		DPIFlushAll();
		DPISetFuncName(0);



		    /******* Write OUTPUT/INOUT to the SP *******/ 
		ptrToSP = SP + 336 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)(&cObj0), 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 520 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)(&cObj1), 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 704 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)(&cObj2), 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 888 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)cObj3, 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 1072 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)(&cObj4), 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 1256 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)(&cObj5), 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 1440 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)(&cObj6), 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 1624 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)cObj7, 64, 1 );
		ptrToSP = ptrToSP + 128; 
		ptrToSP = SP + 1928 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)cObj8, 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 2112 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)(&cObj9), 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 2296 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)(&cObj10), 4, 1 );
		ptrToSP = ptrToSP + 8; 

		/****** Subprogram Debug : Pop the Call Stack entry for this function invocation  ******/
		iki_vlog_function_callstack_update(SP); 
		return;
	}
	void Dpi_wrapper_get_axi_rdma_get_wqe_2(char *GlobalDP, char *IP, char *SP)
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
		int cObj0;
		DPIMemsetSvToDpi( (char*)(&cObj0), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 520 ; 
		int cObj1;
		DPIMemsetSvToDpi( (char*)(&cObj1), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		ptrToSP = SP + 704 ; 
		int cObj2;
		DPIMemsetSvToDpi( (char*)(&cObj2), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		ptrToSP = SP + 888 ; 
		svBitVecVal cObj3[SV_PACKED_DATA_NELEMS(2)];
		DPIMemsetSvToDpi( (char*)cObj3, ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		ptrToSP = SP + 1072 ; 
		int cObj4;
		DPIMemsetSvToDpi( (char*)(&cObj4), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		ptrToSP = SP + 1256 ; 
		int cObj5;
		DPIMemsetSvToDpi( (char*)(&cObj5), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		ptrToSP = SP + 1440 ; 
		int cObj6;
		DPIMemsetSvToDpi( (char*)(&cObj6), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		ptrToSP = SP + 1624 ; 
		svBitVecVal cObj7[SV_PACKED_DATA_NELEMS(512)];
		DPIMemsetSvToDpi( (char*)cObj7, ptrToSP, 64, 1 );
		ptrToSP = ptrToSP + 128; 

		ptrToSP = SP + 1928 ; 
		svBitVecVal cObj8[SV_PACKED_DATA_NELEMS(2)];
		DPIMemsetSvToDpi( (char*)cObj8, ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		ptrToSP = SP + 2112 ; 
		int cObj9;
		DPIMemsetSvToDpi( (char*)(&cObj9), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 2296 ; 
		int cObj10;
		DPIMemsetSvToDpi( (char*)(&cObj10), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		    /******* Done Conversion of SV types to DPI-C Types *******/ 
		    /******* Call the DPI-C function *******/ 
		DPISetFuncName("get_axi_rdma_get_wqe_2");
		DPIFlushAll();
		get_axi_rdma_get_wqe_2(&cObj0, &cObj1, &cObj2, cObj3, &cObj4, &cObj5, &cObj6, cObj7, cObj8, &cObj9, &cObj10);
		DPIRemoveContext(funcContext);
		DPIFlushAll();
		DPISetFuncName(0);



		    /******* Write OUTPUT/INOUT to the SP *******/ 
		ptrToSP = SP + 336 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)(&cObj0), 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 520 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)(&cObj1), 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 704 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)(&cObj2), 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 888 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)cObj3, 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 1072 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)(&cObj4), 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 1256 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)(&cObj5), 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 1440 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)(&cObj6), 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 1624 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)cObj7, 64, 1 );
		ptrToSP = ptrToSP + 128; 
		ptrToSP = SP + 1928 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)cObj8, 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 2112 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)(&cObj9), 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 2296 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)(&cObj10), 4, 1 );
		ptrToSP = ptrToSP + 8; 

		/****** Subprogram Debug : Pop the Call Stack entry for this function invocation  ******/
		iki_vlog_function_callstack_update(SP); 
		return;
	}
	void Dpi_wrapper_set_axi_rdma2_get_payload_1(char *GlobalDP, char *IP, char *SP)
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
		int cObj0;
		DPIMemsetSvToDpi( (char*)(&cObj0), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		ptrToSP = SP + 520 ; 
		svBitVecVal cObj1[SV_PACKED_DATA_NELEMS(64)];
		DPIMemsetSvToDpi( (char*)cObj1, ptrToSP, 8, 1 );
		ptrToSP = ptrToSP + 16; 

		ptrToSP = SP + 712 ; 
		int cObj2;
		DPIMemsetSvToDpi( (char*)(&cObj2), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 896 ; 
		int cObj3;
		DPIMemsetSvToDpi( (char*)(&cObj3), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 1080 ; 
		int cObj4;
		DPIMemsetSvToDpi( (char*)(&cObj4), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 1264 ; 
		int cObj5;
		DPIMemsetSvToDpi( (char*)(&cObj5), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 1448 ; 
		int cObj6;
		DPIMemsetSvToDpi( (char*)(&cObj6), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 1632 ; 
		int cObj7;
		DPIMemsetSvToDpi( (char*)(&cObj7), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 1816 ; 
		int cObj8;
		DPIMemsetSvToDpi( (char*)(&cObj8), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		ptrToSP = SP + 2000 ; 
		svBitVecVal cObj9[SV_PACKED_DATA_NELEMS(512)];
		DPIMemsetSvToDpi( (char*)cObj9, ptrToSP, 64, 1 );
		ptrToSP = ptrToSP + 128; 

		ptrToSP = SP + 2304 ; 
		svBitVecVal cObj10[SV_PACKED_DATA_NELEMS(64)];
		DPIMemsetSvToDpi( (char*)cObj10, ptrToSP, 8, 1 );
		ptrToSP = ptrToSP + 16; 

		ptrToSP = SP + 2496 ; 
		int cObj11;
		DPIMemsetSvToDpi( (char*)(&cObj11), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 2680 ; 
		int cObj12;
		DPIMemsetSvToDpi( (char*)(&cObj12), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 2864 ; 
		int cObj13;
		DPIMemsetSvToDpi( (char*)(&cObj13), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		ptrToSP = SP + 3048 ; 
		int cObj14;
		DPIMemsetSvToDpi( (char*)(&cObj14), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		ptrToSP = SP + 3232 ; 
		svBitVecVal cObj15[SV_PACKED_DATA_NELEMS(64)];
		DPIMemsetSvToDpi( (char*)cObj15, ptrToSP, 8, 1 );
		ptrToSP = ptrToSP + 16; 

		ptrToSP = SP + 3424 ; 
		int cObj16;
		DPIMemsetSvToDpi( (char*)(&cObj16), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 3608 ; 
		int cObj17;
		DPIMemsetSvToDpi( (char*)(&cObj17), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 3792 ; 
		int cObj18;
		DPIMemsetSvToDpi( (char*)(&cObj18), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 3976 ; 
		int cObj19;
		DPIMemsetSvToDpi( (char*)(&cObj19), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 4160 ; 
		int cObj20;
		DPIMemsetSvToDpi( (char*)(&cObj20), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 4344 ; 
		int cObj21;
		DPIMemsetSvToDpi( (char*)(&cObj21), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 4528 ; 
		int cObj22;
		DPIMemsetSvToDpi( (char*)(&cObj22), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 4712 ; 
		int cObj23;
		DPIMemsetSvToDpi( (char*)(&cObj23), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		    /******* Done Conversion of SV types to DPI-C Types *******/ 
		    /******* Call the DPI-C function *******/ 
		DPISetFuncName("set_axi_rdma2_get_payload_1");
		DPIFlushAll();
		set_axi_rdma2_get_payload_1(cObj0, cObj1, cObj2, cObj3, cObj4, cObj5, cObj6, cObj7, cObj8, cObj9, cObj10, cObj11, cObj12, cObj13, cObj14, cObj15, cObj16, cObj17, cObj18, cObj19, cObj20, cObj21, cObj22, cObj23);
		DPIRemoveContext(funcContext);
		DPIFlushAll();
		DPISetFuncName(0);
		/****** Subprogram Debug : Pop the Call Stack entry for this function invocation  ******/
		iki_vlog_function_callstack_update(SP); 
		return;
	}
	void Dpi_wrapper_get_axi_rdma2_get_payload_2(char *GlobalDP, char *IP, char *SP)
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
		int cObj0;
		DPIMemsetSvToDpi( (char*)(&cObj0), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 520 ; 
		int cObj1;
		DPIMemsetSvToDpi( (char*)(&cObj1), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		ptrToSP = SP + 704 ; 
		int cObj2;
		DPIMemsetSvToDpi( (char*)(&cObj2), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		ptrToSP = SP + 888 ; 
		svBitVecVal cObj3[SV_PACKED_DATA_NELEMS(2)];
		DPIMemsetSvToDpi( (char*)cObj3, ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		ptrToSP = SP + 1072 ; 
		int cObj4;
		DPIMemsetSvToDpi( (char*)(&cObj4), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		ptrToSP = SP + 1256 ; 
		int cObj5;
		DPIMemsetSvToDpi( (char*)(&cObj5), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		ptrToSP = SP + 1440 ; 
		int cObj6;
		DPIMemsetSvToDpi( (char*)(&cObj6), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		ptrToSP = SP + 1624 ; 
		svBitVecVal cObj7[SV_PACKED_DATA_NELEMS(512)];
		DPIMemsetSvToDpi( (char*)cObj7, ptrToSP, 64, 1 );
		ptrToSP = ptrToSP + 128; 

		ptrToSP = SP + 1928 ; 
		svBitVecVal cObj8[SV_PACKED_DATA_NELEMS(2)];
		DPIMemsetSvToDpi( (char*)cObj8, ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		ptrToSP = SP + 2112 ; 
		int cObj9;
		DPIMemsetSvToDpi( (char*)(&cObj9), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 2296 ; 
		int cObj10;
		DPIMemsetSvToDpi( (char*)(&cObj10), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		    /******* Done Conversion of SV types to DPI-C Types *******/ 
		    /******* Call the DPI-C function *******/ 
		DPISetFuncName("get_axi_rdma2_get_payload_2");
		DPIFlushAll();
		get_axi_rdma2_get_payload_2(&cObj0, &cObj1, &cObj2, cObj3, &cObj4, &cObj5, &cObj6, cObj7, cObj8, &cObj9, &cObj10);
		DPIRemoveContext(funcContext);
		DPIFlushAll();
		DPISetFuncName(0);



		    /******* Write OUTPUT/INOUT to the SP *******/ 
		ptrToSP = SP + 336 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)(&cObj0), 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 520 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)(&cObj1), 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 704 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)(&cObj2), 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 888 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)cObj3, 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 1072 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)(&cObj4), 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 1256 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)(&cObj5), 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 1440 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)(&cObj6), 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 1624 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)cObj7, 64, 1 );
		ptrToSP = ptrToSP + 128; 
		ptrToSP = SP + 1928 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)cObj8, 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 2112 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)(&cObj9), 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 2296 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)(&cObj10), 4, 1 );
		ptrToSP = ptrToSP + 8; 

		/****** Subprogram Debug : Pop the Call Stack entry for this function invocation  ******/
		iki_vlog_function_callstack_update(SP); 
		return;
	}
	void Dpi_wrapper_get_axi_rdma_completion_2(char *GlobalDP, char *IP, char *SP)
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
		int cObj0;
		DPIMemsetSvToDpi( (char*)(&cObj0), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 520 ; 
		int cObj1;
		DPIMemsetSvToDpi( (char*)(&cObj1), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		ptrToSP = SP + 704 ; 
		int cObj2;
		DPIMemsetSvToDpi( (char*)(&cObj2), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		ptrToSP = SP + 888 ; 
		svBitVecVal cObj3[SV_PACKED_DATA_NELEMS(2)];
		DPIMemsetSvToDpi( (char*)cObj3, ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		ptrToSP = SP + 1072 ; 
		int cObj4;
		DPIMemsetSvToDpi( (char*)(&cObj4), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		ptrToSP = SP + 1256 ; 
		int cObj5;
		DPIMemsetSvToDpi( (char*)(&cObj5), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		ptrToSP = SP + 1440 ; 
		int cObj6;
		DPIMemsetSvToDpi( (char*)(&cObj6), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		ptrToSP = SP + 1624 ; 
		svBitVecVal cObj7[SV_PACKED_DATA_NELEMS(512)];
		DPIMemsetSvToDpi( (char*)cObj7, ptrToSP, 64, 1 );
		ptrToSP = ptrToSP + 128; 

		ptrToSP = SP + 1928 ; 
		svBitVecVal cObj8[SV_PACKED_DATA_NELEMS(2)];
		DPIMemsetSvToDpi( (char*)cObj8, ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		ptrToSP = SP + 2112 ; 
		int cObj9;
		DPIMemsetSvToDpi( (char*)(&cObj9), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 2296 ; 
		int cObj10;
		DPIMemsetSvToDpi( (char*)(&cObj10), ptrToSP, 4, 1 );
		ptrToSP = ptrToSP + 8; 

		    /******* Done Conversion of SV types to DPI-C Types *******/ 
		    /******* Call the DPI-C function *******/ 
		DPISetFuncName("get_axi_rdma_completion_2");
		DPIFlushAll();
		get_axi_rdma_completion_2(&cObj0, &cObj1, &cObj2, cObj3, &cObj4, &cObj5, &cObj6, cObj7, cObj8, &cObj9, &cObj10);
		DPIRemoveContext(funcContext);
		DPIFlushAll();
		DPISetFuncName(0);



		    /******* Write OUTPUT/INOUT to the SP *******/ 
		ptrToSP = SP + 336 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)(&cObj0), 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 520 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)(&cObj1), 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 704 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)(&cObj2), 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 888 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)cObj3, 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 1072 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)(&cObj4), 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 1256 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)(&cObj5), 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 1440 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)(&cObj6), 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 1624 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)cObj7, 64, 1 );
		ptrToSP = ptrToSP + 128; 
		ptrToSP = SP + 1928 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)cObj8, 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 2112 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)(&cObj9), 4, 1 );
		ptrToSP = ptrToSP + 8; 
		ptrToSP = SP + 2296 ; 
		DPIMemsetDpiToSv( ptrToSP, (char*)(&cObj10), 4, 1 );
		ptrToSP = ptrToSP + 8; 

		/****** Subprogram Debug : Pop the Call Stack entry for this function invocation  ******/
		iki_vlog_function_callstack_update(SP); 
		return;
	}
}


extern "C" {
}

