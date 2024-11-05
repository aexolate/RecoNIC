# This script segment is generated automatically by AutoPilot

# clear list
if {${::AESL::PGuard_autoexp_gen}} {
    cg_default_interface_gen_dc_begin
    cg_default_interface_gen_bundle_begin
    AESL_LIB_XILADAPTER::native_axis_begin
}

# XIL_BRAM:
if {${::AESL::PGuard_autoexp_gen}} {
if {[info proc ::AESL_LIB_XILADAPTER::xil_bram_gen] == "::AESL_LIB_XILADAPTER::xil_bram_gen"} {
eval "::AESL_LIB_XILADAPTER::xil_bram_gen { \
    id 3 \
    name localA \
    reset_level 1 \
    sync_rst true \
    dir O \
    corename localA \
    op interface \
    ports { localA_address0 { O 4 vector } localA_ce0 { O 1 bit } localA_we0 { O 1 bit } localA_d0 { O 32 vector } } \
} "
} else {
puts "@W \[IMPL-110\] Cannot find bus interface model in the library. Ignored generation of bus interface for 'localA'"
}
}


# XIL_BRAM:
if {${::AESL::PGuard_autoexp_gen}} {
if {[info proc ::AESL_LIB_XILADAPTER::xil_bram_gen] == "::AESL_LIB_XILADAPTER::xil_bram_gen"} {
eval "::AESL_LIB_XILADAPTER::xil_bram_gen { \
    id 4 \
    name localA_1 \
    reset_level 1 \
    sync_rst true \
    dir O \
    corename localA_1 \
    op interface \
    ports { localA_1_address0 { O 4 vector } localA_1_ce0 { O 1 bit } localA_1_we0 { O 1 bit } localA_1_d0 { O 32 vector } } \
} "
} else {
puts "@W \[IMPL-110\] Cannot find bus interface model in the library. Ignored generation of bus interface for 'localA_1'"
}
}


# XIL_BRAM:
if {${::AESL::PGuard_autoexp_gen}} {
if {[info proc ::AESL_LIB_XILADAPTER::xil_bram_gen] == "::AESL_LIB_XILADAPTER::xil_bram_gen"} {
eval "::AESL_LIB_XILADAPTER::xil_bram_gen { \
    id 5 \
    name localA_2 \
    reset_level 1 \
    sync_rst true \
    dir O \
    corename localA_2 \
    op interface \
    ports { localA_2_address0 { O 4 vector } localA_2_ce0 { O 1 bit } localA_2_we0 { O 1 bit } localA_2_d0 { O 32 vector } } \
} "
} else {
puts "@W \[IMPL-110\] Cannot find bus interface model in the library. Ignored generation of bus interface for 'localA_2'"
}
}


# XIL_BRAM:
if {${::AESL::PGuard_autoexp_gen}} {
if {[info proc ::AESL_LIB_XILADAPTER::xil_bram_gen] == "::AESL_LIB_XILADAPTER::xil_bram_gen"} {
eval "::AESL_LIB_XILADAPTER::xil_bram_gen { \
    id 6 \
    name localA_3 \
    reset_level 1 \
    sync_rst true \
    dir O \
    corename localA_3 \
    op interface \
    ports { localA_3_address0 { O 4 vector } localA_3_ce0 { O 1 bit } localA_3_we0 { O 1 bit } localA_3_d0 { O 32 vector } } \
} "
} else {
puts "@W \[IMPL-110\] Cannot find bus interface model in the library. Ignored generation of bus interface for 'localA_3'"
}
}


# XIL_BRAM:
if {${::AESL::PGuard_autoexp_gen}} {
if {[info proc ::AESL_LIB_XILADAPTER::xil_bram_gen] == "::AESL_LIB_XILADAPTER::xil_bram_gen"} {
eval "::AESL_LIB_XILADAPTER::xil_bram_gen { \
    id 7 \
    name localA_4 \
    reset_level 1 \
    sync_rst true \
    dir O \
    corename localA_4 \
    op interface \
    ports { localA_4_address0 { O 4 vector } localA_4_ce0 { O 1 bit } localA_4_we0 { O 1 bit } localA_4_d0 { O 32 vector } } \
} "
} else {
puts "@W \[IMPL-110\] Cannot find bus interface model in the library. Ignored generation of bus interface for 'localA_4'"
}
}


# XIL_BRAM:
if {${::AESL::PGuard_autoexp_gen}} {
if {[info proc ::AESL_LIB_XILADAPTER::xil_bram_gen] == "::AESL_LIB_XILADAPTER::xil_bram_gen"} {
eval "::AESL_LIB_XILADAPTER::xil_bram_gen { \
    id 8 \
    name localA_5 \
    reset_level 1 \
    sync_rst true \
    dir O \
    corename localA_5 \
    op interface \
    ports { localA_5_address0 { O 4 vector } localA_5_ce0 { O 1 bit } localA_5_we0 { O 1 bit } localA_5_d0 { O 32 vector } } \
} "
} else {
puts "@W \[IMPL-110\] Cannot find bus interface model in the library. Ignored generation of bus interface for 'localA_5'"
}
}


# XIL_BRAM:
if {${::AESL::PGuard_autoexp_gen}} {
if {[info proc ::AESL_LIB_XILADAPTER::xil_bram_gen] == "::AESL_LIB_XILADAPTER::xil_bram_gen"} {
eval "::AESL_LIB_XILADAPTER::xil_bram_gen { \
    id 9 \
    name localA_6 \
    reset_level 1 \
    sync_rst true \
    dir O \
    corename localA_6 \
    op interface \
    ports { localA_6_address0 { O 4 vector } localA_6_ce0 { O 1 bit } localA_6_we0 { O 1 bit } localA_6_d0 { O 32 vector } } \
} "
} else {
puts "@W \[IMPL-110\] Cannot find bus interface model in the library. Ignored generation of bus interface for 'localA_6'"
}
}


# XIL_BRAM:
if {${::AESL::PGuard_autoexp_gen}} {
if {[info proc ::AESL_LIB_XILADAPTER::xil_bram_gen] == "::AESL_LIB_XILADAPTER::xil_bram_gen"} {
eval "::AESL_LIB_XILADAPTER::xil_bram_gen { \
    id 10 \
    name localA_7 \
    reset_level 1 \
    sync_rst true \
    dir O \
    corename localA_7 \
    op interface \
    ports { localA_7_address0 { O 4 vector } localA_7_ce0 { O 1 bit } localA_7_we0 { O 1 bit } localA_7_d0 { O 32 vector } } \
} "
} else {
puts "@W \[IMPL-110\] Cannot find bus interface model in the library. Ignored generation of bus interface for 'localA_7'"
}
}


# XIL_BRAM:
if {${::AESL::PGuard_autoexp_gen}} {
if {[info proc ::AESL_LIB_XILADAPTER::xil_bram_gen] == "::AESL_LIB_XILADAPTER::xil_bram_gen"} {
eval "::AESL_LIB_XILADAPTER::xil_bram_gen { \
    id 11 \
    name localA_8 \
    reset_level 1 \
    sync_rst true \
    dir O \
    corename localA_8 \
    op interface \
    ports { localA_8_address0 { O 4 vector } localA_8_ce0 { O 1 bit } localA_8_we0 { O 1 bit } localA_8_d0 { O 32 vector } } \
} "
} else {
puts "@W \[IMPL-110\] Cannot find bus interface model in the library. Ignored generation of bus interface for 'localA_8'"
}
}


# XIL_BRAM:
if {${::AESL::PGuard_autoexp_gen}} {
if {[info proc ::AESL_LIB_XILADAPTER::xil_bram_gen] == "::AESL_LIB_XILADAPTER::xil_bram_gen"} {
eval "::AESL_LIB_XILADAPTER::xil_bram_gen { \
    id 12 \
    name localA_9 \
    reset_level 1 \
    sync_rst true \
    dir O \
    corename localA_9 \
    op interface \
    ports { localA_9_address0 { O 4 vector } localA_9_ce0 { O 1 bit } localA_9_we0 { O 1 bit } localA_9_d0 { O 32 vector } } \
} "
} else {
puts "@W \[IMPL-110\] Cannot find bus interface model in the library. Ignored generation of bus interface for 'localA_9'"
}
}


# XIL_BRAM:
if {${::AESL::PGuard_autoexp_gen}} {
if {[info proc ::AESL_LIB_XILADAPTER::xil_bram_gen] == "::AESL_LIB_XILADAPTER::xil_bram_gen"} {
eval "::AESL_LIB_XILADAPTER::xil_bram_gen { \
    id 13 \
    name localA_10 \
    reset_level 1 \
    sync_rst true \
    dir O \
    corename localA_10 \
    op interface \
    ports { localA_10_address0 { O 4 vector } localA_10_ce0 { O 1 bit } localA_10_we0 { O 1 bit } localA_10_d0 { O 32 vector } } \
} "
} else {
puts "@W \[IMPL-110\] Cannot find bus interface model in the library. Ignored generation of bus interface for 'localA_10'"
}
}


# XIL_BRAM:
if {${::AESL::PGuard_autoexp_gen}} {
if {[info proc ::AESL_LIB_XILADAPTER::xil_bram_gen] == "::AESL_LIB_XILADAPTER::xil_bram_gen"} {
eval "::AESL_LIB_XILADAPTER::xil_bram_gen { \
    id 14 \
    name localA_11 \
    reset_level 1 \
    sync_rst true \
    dir O \
    corename localA_11 \
    op interface \
    ports { localA_11_address0 { O 4 vector } localA_11_ce0 { O 1 bit } localA_11_we0 { O 1 bit } localA_11_d0 { O 32 vector } } \
} "
} else {
puts "@W \[IMPL-110\] Cannot find bus interface model in the library. Ignored generation of bus interface for 'localA_11'"
}
}


# XIL_BRAM:
if {${::AESL::PGuard_autoexp_gen}} {
if {[info proc ::AESL_LIB_XILADAPTER::xil_bram_gen] == "::AESL_LIB_XILADAPTER::xil_bram_gen"} {
eval "::AESL_LIB_XILADAPTER::xil_bram_gen { \
    id 15 \
    name localA_12 \
    reset_level 1 \
    sync_rst true \
    dir O \
    corename localA_12 \
    op interface \
    ports { localA_12_address0 { O 4 vector } localA_12_ce0 { O 1 bit } localA_12_we0 { O 1 bit } localA_12_d0 { O 32 vector } } \
} "
} else {
puts "@W \[IMPL-110\] Cannot find bus interface model in the library. Ignored generation of bus interface for 'localA_12'"
}
}


# XIL_BRAM:
if {${::AESL::PGuard_autoexp_gen}} {
if {[info proc ::AESL_LIB_XILADAPTER::xil_bram_gen] == "::AESL_LIB_XILADAPTER::xil_bram_gen"} {
eval "::AESL_LIB_XILADAPTER::xil_bram_gen { \
    id 16 \
    name localA_13 \
    reset_level 1 \
    sync_rst true \
    dir O \
    corename localA_13 \
    op interface \
    ports { localA_13_address0 { O 4 vector } localA_13_ce0 { O 1 bit } localA_13_we0 { O 1 bit } localA_13_d0 { O 32 vector } } \
} "
} else {
puts "@W \[IMPL-110\] Cannot find bus interface model in the library. Ignored generation of bus interface for 'localA_13'"
}
}


# XIL_BRAM:
if {${::AESL::PGuard_autoexp_gen}} {
if {[info proc ::AESL_LIB_XILADAPTER::xil_bram_gen] == "::AESL_LIB_XILADAPTER::xil_bram_gen"} {
eval "::AESL_LIB_XILADAPTER::xil_bram_gen { \
    id 17 \
    name localA_14 \
    reset_level 1 \
    sync_rst true \
    dir O \
    corename localA_14 \
    op interface \
    ports { localA_14_address0 { O 4 vector } localA_14_ce0 { O 1 bit } localA_14_we0 { O 1 bit } localA_14_d0 { O 32 vector } } \
} "
} else {
puts "@W \[IMPL-110\] Cannot find bus interface model in the library. Ignored generation of bus interface for 'localA_14'"
}
}


# XIL_BRAM:
if {${::AESL::PGuard_autoexp_gen}} {
if {[info proc ::AESL_LIB_XILADAPTER::xil_bram_gen] == "::AESL_LIB_XILADAPTER::xil_bram_gen"} {
eval "::AESL_LIB_XILADAPTER::xil_bram_gen { \
    id 18 \
    name localA_15 \
    reset_level 1 \
    sync_rst true \
    dir O \
    corename localA_15 \
    op interface \
    ports { localA_15_address0 { O 4 vector } localA_15_ce0 { O 1 bit } localA_15_we0 { O 1 bit } localA_15_d0 { O 32 vector } } \
} "
} else {
puts "@W \[IMPL-110\] Cannot find bus interface model in the library. Ignored generation of bus interface for 'localA_15'"
}
}


# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 1 \
    name systolic \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_systolic \
    op interface \
    ports { m_axi_systolic_AWVALID { O 1 bit } m_axi_systolic_AWREADY { I 1 bit } m_axi_systolic_AWADDR { O 64 vector } m_axi_systolic_AWID { O 1 vector } m_axi_systolic_AWLEN { O 32 vector } m_axi_systolic_AWSIZE { O 3 vector } m_axi_systolic_AWBURST { O 2 vector } m_axi_systolic_AWLOCK { O 2 vector } m_axi_systolic_AWCACHE { O 4 vector } m_axi_systolic_AWPROT { O 3 vector } m_axi_systolic_AWQOS { O 4 vector } m_axi_systolic_AWREGION { O 4 vector } m_axi_systolic_AWUSER { O 1 vector } m_axi_systolic_WVALID { O 1 bit } m_axi_systolic_WREADY { I 1 bit } m_axi_systolic_WDATA { O 512 vector } m_axi_systolic_WSTRB { O 64 vector } m_axi_systolic_WLAST { O 1 bit } m_axi_systolic_WID { O 1 vector } m_axi_systolic_WUSER { O 1 vector } m_axi_systolic_ARVALID { O 1 bit } m_axi_systolic_ARREADY { I 1 bit } m_axi_systolic_ARADDR { O 64 vector } m_axi_systolic_ARID { O 1 vector } m_axi_systolic_ARLEN { O 32 vector } m_axi_systolic_ARSIZE { O 3 vector } m_axi_systolic_ARBURST { O 2 vector } m_axi_systolic_ARLOCK { O 2 vector } m_axi_systolic_ARCACHE { O 4 vector } m_axi_systolic_ARPROT { O 3 vector } m_axi_systolic_ARQOS { O 4 vector } m_axi_systolic_ARREGION { O 4 vector } m_axi_systolic_ARUSER { O 1 vector } m_axi_systolic_RVALID { I 1 bit } m_axi_systolic_RREADY { O 1 bit } m_axi_systolic_RDATA { I 512 vector } m_axi_systolic_RLAST { I 1 bit } m_axi_systolic_RID { I 1 vector } m_axi_systolic_RFIFONUM { I 9 vector } m_axi_systolic_RUSER { I 1 vector } m_axi_systolic_RRESP { I 2 vector } m_axi_systolic_BVALID { I 1 bit } m_axi_systolic_BREADY { O 1 bit } m_axi_systolic_BRESP { I 2 vector } m_axi_systolic_BID { I 1 vector } m_axi_systolic_BUSER { I 1 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 2 \
    name sext_ln104 \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_sext_ln104 \
    op interface \
    ports { sext_ln104 { I 58 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id -1 \
    name ap_ctrl \
    type ap_ctrl \
    reset_level 1 \
    sync_rst true \
    corename ap_ctrl \
    op interface \
    ports { ap_start { I 1 bit } ap_ready { O 1 bit } ap_done { O 1 bit } ap_idle { O 1 bit } } \
} "
}


# Adapter definition:
set PortName ap_clk
set DataWd 1 
if {${::AESL::PGuard_autoexp_gen}} {
if {[info proc cg_default_interface_gen_clock] == "cg_default_interface_gen_clock"} {
eval "cg_default_interface_gen_clock { \
    id -2 \
    name ${PortName} \
    reset_level 1 \
    sync_rst true \
    corename apif_ap_clk \
    data_wd ${DataWd} \
    op interface \
}"
} else {
puts "@W \[IMPL-113\] Cannot find bus interface model in the library. Ignored generation of bus interface for '${PortName}'"
}
}


# Adapter definition:
set PortName ap_rst
set DataWd 1 
if {${::AESL::PGuard_autoexp_gen}} {
if {[info proc cg_default_interface_gen_reset] == "cg_default_interface_gen_reset"} {
eval "cg_default_interface_gen_reset { \
    id -3 \
    name ${PortName} \
    reset_level 1 \
    sync_rst true \
    corename apif_ap_rst \
    data_wd ${DataWd} \
    op interface \
}"
} else {
puts "@W \[IMPL-114\] Cannot find bus interface model in the library. Ignored generation of bus interface for '${PortName}'"
}
}



# merge
if {${::AESL::PGuard_autoexp_gen}} {
    cg_default_interface_gen_dc_end
    cg_default_interface_gen_bundle_end
    AESL_LIB_XILADAPTER::native_axis_end
}


# flow_control definition:
set InstName mmult_flow_control_loop_pipe_sequential_init_U
set CompName mmult_flow_control_loop_pipe_sequential_init
set name flow_control_loop_pipe_sequential_init
if {${::AESL::PGuard_autocg_gen} && ${::AESL::PGuard_autocg_ipmgen}} {
if {[info proc ::AESL_LIB_VIRTEX::xil_gen_UPC_flow_control] == "::AESL_LIB_VIRTEX::xil_gen_UPC_flow_control"} {
eval "::AESL_LIB_VIRTEX::xil_gen_UPC_flow_control { \
    name ${name} \
    prefix mmult_ \
}"
} else {
puts "@W \[IMPL-107\] Cannot find ::AESL_LIB_VIRTEX::xil_gen_UPC_flow_control, check your platform lib"
}
}


if {${::AESL::PGuard_rtl_comp_handler}} {
	::AP::rtl_comp_handler $CompName BINDTYPE interface TYPE internal_upc_flow_control INSTNAME $InstName
}


