; ModuleID = '/home/gexl/Desktop/test/RecoNIC/shell/compute/lookside/cl_box/solution1/.autopilot/db/a.g.ld.5.gdce.bc'
source_filename = "llvm-link"
target datalayout = "e-m:e-i64:64-i128:128-i256:256-i512:512-i1024:1024-i2048:2048-i4096:4096-n8:16:32:64-S128-v16:16-v24:32-v32:32-v48:64-v96:128-v192:256-v256:256-v512:512-v1024:1024"
target triple = "fpga64-xilinx-none"

%"class.hls::stream<unsigned int, 0>" = type { i32 }

; Function Attrs: inaccessiblememonly nounwind
declare void @llvm.sideeffect() #0

; Function Attrs: inaccessiblemem_or_argmemonly noinline
define void @apatb_cl_box_ir(%"class.hls::stream<unsigned int, 0>"* %ctl_cmd_stream, i32* %a_baseaddr, i32* %b_baseaddr, i32* %c_baseaddr, i32* %a_row, i32* %a_col, i32* %b_col, i32* %work_id) local_unnamed_addr #1 {
entry:
  %ctl_cmd_stream_copy = alloca i32, align 512
  call void @llvm.sideeffect() #0 [ "stream_interface"(i32* %ctl_cmd_stream_copy) ]
  %a_baseaddr_copy = alloca i32, align 512
  %b_baseaddr_copy = alloca i32, align 512
  %c_baseaddr_copy = alloca i32, align 512
  %a_row_copy = alloca i32, align 512
  %a_col_copy = alloca i32, align 512
  %b_col_copy = alloca i32, align 512
  %work_id_copy = alloca i32, align 512
  call fastcc void @copy_in(%"class.hls::stream<unsigned int, 0>"* %ctl_cmd_stream, i32* nonnull align 512 %ctl_cmd_stream_copy, i32* %a_baseaddr, i32* nonnull align 512 %a_baseaddr_copy, i32* %b_baseaddr, i32* nonnull align 512 %b_baseaddr_copy, i32* %c_baseaddr, i32* nonnull align 512 %c_baseaddr_copy, i32* %a_row, i32* nonnull align 512 %a_row_copy, i32* %a_col, i32* nonnull align 512 %a_col_copy, i32* %b_col, i32* nonnull align 512 %b_col_copy, i32* %work_id, i32* nonnull align 512 %work_id_copy)
  call void @apatb_cl_box_hw(i32* %ctl_cmd_stream_copy, i32* %a_baseaddr_copy, i32* %b_baseaddr_copy, i32* %c_baseaddr_copy, i32* %a_row_copy, i32* %a_col_copy, i32* %b_col_copy, i32* %work_id_copy)
  call fastcc void @copy_out(%"class.hls::stream<unsigned int, 0>"* %ctl_cmd_stream, i32* nonnull align 512 %ctl_cmd_stream_copy, i32* %a_baseaddr, i32* nonnull align 512 %a_baseaddr_copy, i32* %b_baseaddr, i32* nonnull align 512 %b_baseaddr_copy, i32* %c_baseaddr, i32* nonnull align 512 %c_baseaddr_copy, i32* %a_row, i32* nonnull align 512 %a_row_copy, i32* %a_col, i32* nonnull align 512 %a_col_copy, i32* %b_col, i32* nonnull align 512 %b_col_copy, i32* %work_id, i32* nonnull align 512 %work_id_copy)
  ret void
}

; Function Attrs: argmemonly noinline
define internal fastcc void @copy_in(%"class.hls::stream<unsigned int, 0>"*, i32* noalias align 512 "fpga.caller.interfaces"="layout_transformed", i32* readonly, i32* noalias align 512, i32* readonly, i32* noalias align 512, i32* readonly, i32* noalias align 512, i32* readonly, i32* noalias align 512, i32* readonly, i32* noalias align 512, i32* readonly, i32* noalias align 512, i32* readonly, i32* noalias align 512) unnamed_addr #2 {
entry:
  call fastcc void @"onebyonecpy_hls.p0class.hls::stream<unsigned int, 0>"(i32* align 512 %1, %"class.hls::stream<unsigned int, 0>"* %0)
  call fastcc void @onebyonecpy_hls.p0i32(i32* align 512 %3, i32* %2)
  call fastcc void @onebyonecpy_hls.p0i32(i32* align 512 %5, i32* %4)
  call fastcc void @onebyonecpy_hls.p0i32(i32* align 512 %7, i32* %6)
  call fastcc void @onebyonecpy_hls.p0i32(i32* align 512 %9, i32* %8)
  call fastcc void @onebyonecpy_hls.p0i32(i32* align 512 %11, i32* %10)
  call fastcc void @onebyonecpy_hls.p0i32(i32* align 512 %13, i32* %12)
  call fastcc void @onebyonecpy_hls.p0i32(i32* align 512 %15, i32* %14)
  ret void
}

; Function Attrs: argmemonly noinline
define internal fastcc void @"onebyonecpy_hls.p0class.hls::stream<unsigned int, 0>"(i32* noalias align 512 "fpga.caller.interfaces"="layout_transformed", %"class.hls::stream<unsigned int, 0>"* noalias "fpga.caller.interfaces"="layout_transformed") unnamed_addr #3 {
entry:
  %2 = icmp eq i32* %0, null
  %3 = icmp eq %"class.hls::stream<unsigned int, 0>"* %1, null
  %4 = or i1 %2, %3
  br i1 %4, label %ret, label %copy

copy:                                             ; preds = %entry
  call fastcc void @"streamcpy_hls.p0class.hls::stream<unsigned int, 0>"(i32* nonnull align 512 %0, %"class.hls::stream<unsigned int, 0>"* nonnull %1)
  br label %ret

ret:                                              ; preds = %copy, %entry
  ret void
}

; Function Attrs: argmemonly noinline
define internal fastcc void @"streamcpy_hls.p0class.hls::stream<unsigned int, 0>"(i32* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed", %"class.hls::stream<unsigned int, 0>"* noalias nocapture "fpga.caller.interfaces"="layout_transformed") unnamed_addr #4 {
entry:
  %2 = alloca %"class.hls::stream<unsigned int, 0>"
  %3 = alloca i32
  br label %empty

empty:                                            ; preds = %push, %entry
  %4 = bitcast %"class.hls::stream<unsigned int, 0>"* %1 to i8*
  %5 = call i1 @fpga_fifo_not_empty_4(i8* %4)
  br i1 %5, label %push, label %ret

push:                                             ; preds = %empty
  %6 = bitcast %"class.hls::stream<unsigned int, 0>"* %2 to i8*
  %7 = bitcast %"class.hls::stream<unsigned int, 0>"* %1 to i8*
  call void @fpga_fifo_pop_4(i8* %6, i8* %7)
  %8 = load volatile %"class.hls::stream<unsigned int, 0>", %"class.hls::stream<unsigned int, 0>"* %2
  %9 = call i32 @"_llvm.fpga.pack.bits.i32.s_class.hls::stream<unsigned int, 0>s"(%"class.hls::stream<unsigned int, 0>" %8)
  store i32 %9, i32* %3
  %10 = bitcast i32* %3 to i8*
  %11 = bitcast i32* %0 to i8*
  call void @fpga_fifo_push_4(i8* %10, i8* %11)
  br label %empty, !llvm.loop !5

ret:                                              ; preds = %empty
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @onebyonecpy_hls.p0i32(i32* noalias align 512, i32* noalias readonly) unnamed_addr #5 {
entry:
  %2 = icmp eq i32* %0, null
  %3 = icmp eq i32* %1, null
  %4 = or i1 %2, %3
  br i1 %4, label %ret, label %copy

copy:                                             ; preds = %entry
  %5 = load i32, i32* %1, align 4
  store i32 %5, i32* %0, align 512
  br label %ret

ret:                                              ; preds = %copy, %entry
  ret void
}

; Function Attrs: argmemonly noinline
define internal fastcc void @copy_out(%"class.hls::stream<unsigned int, 0>"*, i32* noalias align 512 "fpga.caller.interfaces"="layout_transformed", i32*, i32* noalias readonly align 512, i32*, i32* noalias readonly align 512, i32*, i32* noalias readonly align 512, i32*, i32* noalias readonly align 512, i32*, i32* noalias readonly align 512, i32*, i32* noalias readonly align 512, i32*, i32* noalias readonly align 512) unnamed_addr #6 {
entry:
  call fastcc void @"onebyonecpy_hls.p0class.hls::stream<unsigned int, 0>.4"(%"class.hls::stream<unsigned int, 0>"* %0, i32* align 512 %1)
  call fastcc void @onebyonecpy_hls.p0i32(i32* %2, i32* align 512 %3)
  call fastcc void @onebyonecpy_hls.p0i32(i32* %4, i32* align 512 %5)
  call fastcc void @onebyonecpy_hls.p0i32(i32* %6, i32* align 512 %7)
  call fastcc void @onebyonecpy_hls.p0i32(i32* %8, i32* align 512 %9)
  call fastcc void @onebyonecpy_hls.p0i32(i32* %10, i32* align 512 %11)
  call fastcc void @onebyonecpy_hls.p0i32(i32* %12, i32* align 512 %13)
  call fastcc void @onebyonecpy_hls.p0i32(i32* %14, i32* align 512 %15)
  ret void
}

; Function Attrs: argmemonly noinline
define internal fastcc void @"onebyonecpy_hls.p0class.hls::stream<unsigned int, 0>.4"(%"class.hls::stream<unsigned int, 0>"* noalias "fpga.caller.interfaces"="layout_transformed", i32* noalias align 512 "fpga.caller.interfaces"="layout_transformed") unnamed_addr #3 {
entry:
  %2 = icmp eq %"class.hls::stream<unsigned int, 0>"* %0, null
  %3 = icmp eq i32* %1, null
  %4 = or i1 %2, %3
  br i1 %4, label %ret, label %copy

copy:                                             ; preds = %entry
  call fastcc void @"streamcpy_hls.p0class.hls::stream<unsigned int, 0>.7"(%"class.hls::stream<unsigned int, 0>"* nonnull %0, i32* nonnull align 512 %1)
  br label %ret

ret:                                              ; preds = %copy, %entry
  ret void
}

; Function Attrs: argmemonly noinline
define internal fastcc void @"streamcpy_hls.p0class.hls::stream<unsigned int, 0>.7"(%"class.hls::stream<unsigned int, 0>"* noalias nocapture "fpga.caller.interfaces"="layout_transformed", i32* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed") unnamed_addr #4 {
entry:
  %2 = alloca i32
  %3 = alloca %"class.hls::stream<unsigned int, 0>"
  br label %empty

empty:                                            ; preds = %push, %entry
  %4 = bitcast i32* %1 to i8*
  %5 = call i1 @fpga_fifo_not_empty_4(i8* %4)
  br i1 %5, label %push, label %ret

push:                                             ; preds = %empty
  %6 = bitcast i32* %2 to i8*
  %7 = bitcast i32* %1 to i8*
  call void @fpga_fifo_pop_4(i8* %6, i8* %7)
  %8 = load volatile i32, i32* %2
  %oldret = insertvalue %"class.hls::stream<unsigned int, 0>" undef, i32 %8, 0
  store %"class.hls::stream<unsigned int, 0>" %oldret, %"class.hls::stream<unsigned int, 0>"* %3
  %9 = bitcast %"class.hls::stream<unsigned int, 0>"* %3 to i8*
  %10 = bitcast %"class.hls::stream<unsigned int, 0>"* %0 to i8*
  call void @fpga_fifo_push_4(i8* %9, i8* %10)
  br label %empty, !llvm.loop !5

ret:                                              ; preds = %empty
  ret void
}

; Function Attrs: alwaysinline nounwind readnone
define internal i32 @"_llvm.fpga.pack.bits.i32.s_class.hls::stream<unsigned int, 0>s"(%"class.hls::stream<unsigned int, 0>" %A) #7 {
  %A.0 = extractvalue %"class.hls::stream<unsigned int, 0>" %A, 0
  ret i32 %A.0
}

declare void @apatb_cl_box_hw(i32*, i32*, i32*, i32*, i32*, i32*, i32*, i32*)

define void @cl_box_hw_stub_wrapper(i32*, i32*, i32*, i32*, i32*, i32*, i32*, i32*) #8 {
entry:
  %8 = alloca %"class.hls::stream<unsigned int, 0>"
  call void @copy_out(%"class.hls::stream<unsigned int, 0>"* %8, i32* %0, i32* null, i32* %1, i32* null, i32* %2, i32* null, i32* %3, i32* null, i32* %4, i32* null, i32* %5, i32* null, i32* %6, i32* null, i32* %7)
  call void @cl_box_hw_stub(%"class.hls::stream<unsigned int, 0>"* %8, i32* %1, i32* %2, i32* %3, i32* %4, i32* %5, i32* %6, i32* %7)
  call void @copy_in(%"class.hls::stream<unsigned int, 0>"* %8, i32* %0, i32* null, i32* %1, i32* null, i32* %2, i32* null, i32* %3, i32* null, i32* %4, i32* null, i32* %5, i32* null, i32* %6, i32* null, i32* %7)
  ret void
}

declare void @cl_box_hw_stub(%"class.hls::stream<unsigned int, 0>"*, i32*, i32*, i32*, i32*, i32*, i32*, i32*)

declare i1 @fpga_fifo_not_empty_4(i8*)

declare void @fpga_fifo_pop_4(i8*, i8*)

declare void @fpga_fifo_push_4(i8*, i8*)

attributes #0 = { inaccessiblememonly nounwind }
attributes #1 = { inaccessiblemem_or_argmemonly noinline "fpga.wrapper.func"="wrapper" }
attributes #2 = { argmemonly noinline "fpga.wrapper.func"="copyin" }
attributes #3 = { argmemonly noinline "fpga.wrapper.func"="onebyonecpy_hls" }
attributes #4 = { argmemonly noinline "fpga.wrapper.func"="streamcpy_hls" }
attributes #5 = { argmemonly noinline norecurse "fpga.wrapper.func"="onebyonecpy_hls" }
attributes #6 = { argmemonly noinline "fpga.wrapper.func"="copyout" }
attributes #7 = { alwaysinline nounwind readnone }
attributes #8 = { "fpga.wrapper.func"="stub" }

!llvm.dbg.cu = !{}
!llvm.ident = !{!0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0}
!llvm.module.flags = !{!1, !2, !3}
!blackbox_cfg = !{!4}

!0 = !{!"clang version 7.0.0 "}
!1 = !{i32 2, !"Dwarf Version", i32 4}
!2 = !{i32 2, !"Debug Info Version", i32 3}
!3 = !{i32 1, !"wchar_size", i32 4}
!4 = !{}
!5 = distinct !{!5, !6}
!6 = !{!"llvm.loop.rotate.disable"}
