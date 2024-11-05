//==============================================================================
// Copyright (C) 2023, Advanced Micro Devices, Inc. All rights reserved.
// SPDX-License-Identifier: MIT
//
//==============================================================================
`timescale 1ns/1ps

import rn_tb_pkg::*;

module rn_tb_2rdma_top_remote #(
    // Define parameters with default values
    parameter string SIMBRICKS_PCI_SOCKET = "/path/to/socket",
    parameter string SHM_PATH = "/path/to/shm",
    parameter int SYNC_PERIOD = 500,
    parameter int PCI_LATENCY = 500
) (

);

// ====== SimBricks Adapter Code ======
import "DPI-C" function void simbricks_init(
    input string pci_socket,
    input string shm_path,
    input longint sync_period,
    input longint pci_latency
);

import "DPI-C" function bit simbricks_is_exit();
import "DPI-C" function void init_shared_memory();
import "DPI-C" function void get_init_mem_signals(output int sys_done, output int dev_done);

import "DPI-C" function void set_finish_config_rdma2( input int finish_config_rdma2 );
import "DPI-C" function void get_start_rdma2_stat( output int start_rdma2_stat );

import "DPI-C" function void set_rp_signals(input bit [511:0] tdata, 
                                           input bit [63:0] tkeep, 
                                           input int tvalid, 
                                           input int tlast);
import "DPI-C" function void set_rp_signal_tready(input int tready);
import "DPI-C" function void get_rp_signals(output bit [511:0] tdata, 
                                           output bit [63:0] tkeep, 
                                           output int tvalid, 
                                           output int tlast);
import "DPI-C" function void get_rp_signal_tready(output int tready);

import "DPI-C" function void set_cmac_tx_signals(
    input bit [511:0] tdata, 
    input bit [63:0] tkeep, 
    input int tvalid, 
    input int tlast, 
    input int tuser_size
);
import "DPI-C" function void set_cmac_tx_signal_tready(input int tready);

import "DPI-C" function void get_cmac_tx_signals(
    output bit [511:0] tdata, 
    output bit [63:0] tkeep, 
    output int tvalid, 
    output int tlast, 
    output int tuser_size
);
import "DPI-C" function void get_cmac_tx_signal_tready(output int tready);

import "DPI-C" function void get_axi_rdma2_send_write_payload_1(
    output int awid,
    output bit [63:0] awaddr,
    output int awqos, awlen, awsize, awburst, awcache, awprot, awvalid,
    output bit [511:0] wdata,
    output bit [63:0] wstrb,
    output int wlast, wvalid, awlock,
    output int arid,
    output bit [63:0] araddr,
    output int arlen, arsize, arburst, arcache, arprot, arvalid, arlock, arqos
);

import "DPI-C" function void set_axi_rdma2_send_write_payload_1(
    input int awid,
    input bit [63:0] awaddr,
    input int awqos, awlen, awsize, awburst, awcache, awprot, awvalid,
    input bit [511:0] wdata,
    input bit [63:0] wstrb,
    input int wlast, wvalid, awlock,
    input int arid,
    input bit [63:0] araddr,
    input int arlen, arsize, arburst, arcache, arprot, arvalid, arlock, arqos
);

import "DPI-C" function void set_axi_rdma2_send_write_payload_2(
    input int awready, wready,
    input int bid, input bit [1:0] bresp, input int bvalid,
    input int arready, input int rid,
    input bit [511:0] rdata, input bit [1:0] rresp,
    input int rlast, rvalid
);

import "DPI-C" function void get_axi_rdma2_send_write_payload_2(
    output int awready, wready,
    output int bid, output bit [1:0] bresp, output int bvalid,
    output int arready, output int rid,
    output bit [511:0] rdata, output bit [1:0] rresp,
    output int rlast, rvalid
);

// axi_rdma_rsp
import "DPI-C" function void get_axi_rdma_rsp_payload_1(
    output int awid,
    output bit [63:0] awaddr,
    output int awqos, awlen, awsize, awburst, awcache, awprot, awvalid,
    output bit [511:0] wdata,
    output bit [63:0] wstrb,
    output int wlast, wvalid, awlock,
    output int arid,
    output bit [63:0] araddr,
    output int arlen, arsize, arburst, arcache, arprot, arvalid, arlock, arqos
);

import "DPI-C" function void set_axi_rdma_rsp_payload_1(
    input int awid,
    input bit [63:0] awaddr,
    input int awqos, awlen, awsize, awburst, awcache, awprot, awvalid,
    input bit [511:0] wdata,
    input bit [63:0] wstrb,
    input int wlast, wvalid, awlock,
    input int arid,
    input bit [63:0] araddr,
    input int arlen, arsize, arburst, arcache, arprot, arvalid, arlock, arqos
);

import "DPI-C" function void set_axi_rdma_rsp_payload_2(
    input int awready, wready,
    input int bid, input bit [1:0] bresp, input int bvalid,
    input int arready, input int rid,
    input bit [511:0] rdata, input bit [1:0] rresp,
    input int rlast, rvalid
);

import "DPI-C" function void get_axi_rdma_rsp_payload_2(
    output int awready, wready,
    output int bid, output bit [1:0] bresp, output int bvalid,
    output int arready, output int rid,
    output bit [511:0] rdata, output bit [1:0] rresp,
    output int rlast, rvalid
);


// axi_rdma_get_wqe
import "DPI-C" function void get_axi_rdma_get_wqe_1(
    output int awid,
    output bit [63:0] awaddr,
    output int awqos, awlen, awsize, awburst, awcache, awprot, awvalid,
    output bit [511:0] wdata,
    output bit [63:0] wstrb,
    output int wlast, wvalid, awlock,
    output int arid,
    output bit [63:0] araddr,
    output int arlen, arsize, arburst, arcache, arprot, arvalid, arlock, arqos
);

import "DPI-C" function void set_axi_rdma_get_wqe_1(
    input int awid,
    input bit [63:0] awaddr,
    input int awqos, awlen, awsize, awburst, awcache, awprot, awvalid,
    input bit [511:0] wdata,
    input bit [63:0] wstrb,
    input int wlast, wvalid, awlock,
    input int arid,
    input bit [63:0] araddr,
    input int arlen, arsize, arburst, arcache, arprot, arvalid, arlock, arqos
);

import "DPI-C" function void set_axi_rdma_get_wqe_2(
    input int awready, wready,
    input int bid, input bit [1:0] bresp, input int bvalid,
    input int arready, input int rid,
    input bit [511:0] rdata, input bit [1:0] rresp,
    input int rlast, rvalid
);

import "DPI-C" function void get_axi_rdma_get_wqe_2(
    output int awready, wready,
    output int bid, output bit [1:0] bresp, output int bvalid,
    output int arready, output int rid,
    output bit [511:0] rdata, output bit [1:0] rresp,
    output int rlast, rvalid
);


// axi_rdma2_get_payload
import "DPI-C" function void get_axi_rdma2_get_payload_1(
    output int awid,
    output bit [63:0] awaddr,
    output int awqos, awlen, awsize, awburst, awcache, awprot, awvalid,
    output bit [511:0] wdata,
    output bit [63:0] wstrb,
    output int wlast, wvalid, awlock,
    output int arid,
    output bit [63:0] araddr,
    output int arlen, arsize, arburst, arcache, arprot, arvalid, arlock, arqos
);

import "DPI-C" function void set_axi_rdma2_get_payload_1(
    input int awid,
    input bit [63:0] awaddr,
    input int awqos, awlen, awsize, awburst, awcache, awprot, awvalid,
    input bit [511:0] wdata,
    input bit [63:0] wstrb,
    input int wlast, wvalid, awlock,
    input int arid,
    input bit [63:0] araddr,
    input int arlen, arsize, arburst, arcache, arprot, arvalid, arlock, arqos
);

import "DPI-C" function void set_axi_rdma2_get_payload_2(
    input int awready, wready,
    input int bid, input bit [1:0] bresp, input int bvalid,
    input int arready, input int rid,
    input bit [511:0] rdata, input bit [1:0] rresp,
    input int rlast, rvalid
);

import "DPI-C" function void get_axi_rdma2_get_payload_2(
    output int awready, wready,
    output int bid, output bit [1:0] bresp, output int bvalid,
    output int arready, output int rid,
    output bit [511:0] rdata, output bit [1:0] rresp,
    output int rlast, rvalid
);


// axi_rdma_completion
import "DPI-C" function void get_axi_rdma_completion_1(
    output int awid,
    output bit [63:0] awaddr,
    output int awqos, awlen, awsize, awburst, awcache, awprot, awvalid,
    output bit [511:0] wdata,
    output bit [63:0] wstrb,
    output int wlast, wvalid, awlock,
    output int arid,
    output bit [63:0] araddr,
    output int arlen, arsize, arburst, arcache, arprot, arvalid, arlock, arqos
);

import "DPI-C" function void set_axi_rdma_completion_1(
    input int awid,
    input bit [63:0] awaddr,
    input int awqos, awlen, awsize, awburst, awcache, awprot, awvalid,
    input bit [511:0] wdata,
    input bit [63:0] wstrb,
    input int wlast, wvalid, awlock,
    input int arid,
    input bit [63:0] araddr,
    input int arlen, arsize, arburst, arcache, arprot, arvalid, arlock, arqos
);

import "DPI-C" function void set_axi_rdma_completion_2(
    input int awready, wready,
    input int bid, input bit [1:0] bresp, input int bvalid,
    input int arready, input int rid,
    input bit [511:0] rdata, input bit [1:0] rresp,
    input int rlast, rvalid
);

import "DPI-C" function void get_axi_rdma_completion_2(
    output int awready, wready,
    output int bid, output bit [1:0] bresp, output int bvalid,
    output int arready, output int rid,
    output bit [511:0] rdata, output bit [1:0] rresp,
    output int rlast, rvalid
);



initial begin
  $display("Running [rn_tb_2rdma_top_remote]");
  $display("Initializing SimBricks Adapter");
  init_shared_memory();
  simbricks_init(
      SIMBRICKS_PCI_SOCKET,
      SHM_PATH,
      SYNC_PERIOD,
      PCI_LATENCY
  );
end

always @(posedge axis_clk) begin
    set_rp_signals(rp_rdma2lp_rdma_axis_tdata, rp_rdma2lp_rdma_axis_tkeep, 
      rp_rdma2lp_rdma_axis_tvalid, rp_rdma2lp_rdma_axis_tlast);
    get_rp_signal_tready(rp_rdma2lp_rdma_axis_tready);

    get_cmac_tx_signals(m_axis_cmac_tx_tdata, m_axis_cmac_tx_tkeep, m_axis_cmac_tx_tvalid, m_axis_cmac_tx_tlast, m_axis_cmac_tx_tuser_size);
    //set_cmac_tx_signal_tready(m_axis_cmac_tx_tready);
end

// for analysis
always_comb begin
  if (m_axis_cmac_tx_tvalid && m_axis_cmac_tx_tready) begin
    $display("INFO: [rn_tb_2rdma_top_remote] packet_data=%x %x %x", m_axis_cmac_tx_tdata, m_axis_cmac_tx_tkeep, m_axis_cmac_tx_tlast);
  end
end

always @(posedge axil_clk) begin

    get_init_mem_signals(init_sys_mem_done, init_dev_mem_done);
    set_finish_config_rdma2(finish_config_rdma2);
    get_start_rdma2_stat(start_rdma2_stat);


    set_axi_rdma2_send_write_payload_1(
        axi_rdma2_send_write_payload_awid,
        axi_rdma2_send_write_payload_awaddr,
        dummy,  //replace awqos
        axi_rdma2_send_write_payload_awlen,
        axi_rdma2_send_write_payload_awsize,
        axi_rdma2_send_write_payload_awburst,
        axi_rdma2_send_write_payload_awcache,
        axi_rdma2_send_write_payload_awprot,
        axi_rdma2_send_write_payload_awvalid,
        axi_rdma2_send_write_payload_wdata,
        axi_rdma2_send_write_payload_wstrb,
        axi_rdma2_send_write_payload_wlast,
        axi_rdma2_send_write_payload_wvalid,
        axi_rdma2_send_write_payload_awlock,
        axi_rdma2_send_write_payload_arid,
        axi_rdma2_send_write_payload_araddr,
        axi_rdma2_send_write_payload_arlen,
        axi_rdma2_send_write_payload_arsize,
        axi_rdma2_send_write_payload_arburst,
        axi_rdma2_send_write_payload_arcache,
        axi_rdma2_send_write_payload_arprot,
        axi_rdma2_send_write_payload_arvalid,
        axi_rdma2_send_write_payload_arlock,
        dummy    //replace arqos
    );

    get_axi_rdma2_send_write_payload_2(
        axi_rdma2_send_write_payload_awready,
        axi_rdma2_send_write_payload_wready,
        axi_rdma2_send_write_payload_bid,
        axi_rdma2_send_write_payload_bresp,
        axi_rdma2_send_write_payload_bvalid,
        axi_rdma2_send_write_payload_arready,
        axi_rdma2_send_write_payload_rid,
        axi_rdma2_send_write_payload_rdata,
        axi_rdma2_send_write_payload_rresp,
        axi_rdma2_send_write_payload_rlast,
        axi_rdma2_send_write_payload_rvalid
    );

    // get_axi_rdma_rsp_payload_1(
    //   dummy,
    //   dummy,
    //   dummy,  //replace awqos
    //   dummy,
    //   dummy,
    //   dummy,
    //   dummy,
    //   dummy,
    //   dummy,
    //   dummy,
    //   dummy,
    //   dummy,
    //   dummy,
    //   dummy,
    //   dummy,
    //   dummy,
    //   dummy,
    //   dummy,
    //   dummy,
    //   dummy,
    //   dummy,
    //   m_axi_rdma_rsp_payload_arvalid,
    //   m_axi_rdma_rsp_payload_arlock,
    //   dummy    //replace arqos
    // );

    get_axi_rdma_rsp_payload_2(
      m_axi_rdma_rsp_payload_awready,
      m_axi_rdma_rsp_payload_wready,
      m_axi_rdma_rsp_payload_bid,
      m_axi_rdma_rsp_payload_bresp,
      m_axi_rdma_rsp_payload_bvalid,
      m_axi_rdma_rsp_payload_arready,
      m_axi_rdma_rsp_payload_rid,
      m_axi_rdma_rsp_payload_rdata,
      m_axi_rdma_rsp_payload_rresp,
      m_axi_rdma_rsp_payload_rlast,
      m_axi_rdma_rsp_payload_rvalid
    );

    // get_axi_rdma_get_wqe_1(
    //   m_axi_rdma_get_wqe_awid,
    //   m_axi_rdma_get_wqe_awaddr,
    //   dummy,  //replace awqos
    //   m_axi_rdma_get_wqe_awlen,
    //   m_axi_rdma_get_wqe_awsize,
    //   m_axi_rdma_get_wqe_awburst,
    //   m_axi_rdma_get_wqe_awcache,
    //   m_axi_rdma_get_wqe_awprot,
    //   m_axi_rdma_get_wqe_awvalid,
    //   m_axi_rdma_get_wqe_wdata,
    //   m_axi_rdma_get_wqe_wstrb,
    //   m_axi_rdma_get_wqe_wlast,
    //   m_axi_rdma_get_wqe_wvalid,
    //   m_axi_rdma_get_wqe_awlock,
    //   m_axi_rdma_get_wqe_arid,
    //   m_axi_rdma_get_wqe_araddr,
    //   m_axi_rdma_get_wqe_arlen,
    //   m_axi_rdma_get_wqe_arsize,
    //   m_axi_rdma_get_wqe_arburst,
    //   m_axi_rdma_get_wqe_arcache,
    //   m_axi_rdma_get_wqe_arprot,
    //   m_axi_rdma_get_wqe_arvalid,
    //   m_axi_rdma_get_wqe_arlock,
    //   dummy    //replace arqos
    // );

    get_axi_rdma_get_wqe_2(
      m_axi_rdma_get_wqe_awready,
      m_axi_rdma_get_wqe_wready,
      m_axi_rdma_get_wqe_bid,
      m_axi_rdma_get_wqe_bresp,
      m_axi_rdma_get_wqe_bvalid,
      m_axi_rdma_get_wqe_arready,
      m_axi_rdma_get_wqe_rid,
      m_axi_rdma_get_wqe_rdata,
      m_axi_rdma_get_wqe_rresp,
      m_axi_rdma_get_wqe_rlast,
      m_axi_rdma_get_wqe_rvalid
    );

    set_axi_rdma2_get_payload_1(
      m_axi_rdma2_get_payload_awid,
      m_axi_rdma2_get_payload_awaddr,
      dummy,  //replace awqos
      m_axi_rdma2_get_payload_awlen,
      m_axi_rdma2_get_payload_awsize,
      m_axi_rdma2_get_payload_awburst,
      m_axi_rdma2_get_payload_awcache,
      m_axi_rdma2_get_payload_awprot,
      m_axi_rdma2_get_payload_awvalid,
      m_axi_rdma2_get_payload_wdata,
      m_axi_rdma2_get_payload_wstrb,
      m_axi_rdma2_get_payload_wlast,
      m_axi_rdma2_get_payload_wvalid,
      m_axi_rdma2_get_payload_awlock,
      m_axi_rdma2_get_payload_arid,
      m_axi_rdma2_get_payload_araddr,
      m_axi_rdma2_get_payload_arlen,
      m_axi_rdma2_get_payload_arsize,
      m_axi_rdma2_get_payload_arburst,
      m_axi_rdma2_get_payload_arcache,
      m_axi_rdma2_get_payload_arprot,
      m_axi_rdma2_get_payload_arvalid,
      m_axi_rdma2_get_payload_arlock,
      dummy    //replace arqos
    );

    get_axi_rdma2_get_payload_2(
      m_axi_rdma2_get_payload_awready,
      m_axi_rdma2_get_payload_wready,
      m_axi_rdma2_get_payload_bid,
      m_axi_rdma2_get_payload_bresp,
      m_axi_rdma2_get_payload_bvalid,
      m_axi_rdma2_get_payload_arready,
      m_axi_rdma2_get_payload_rid,
      m_axi_rdma2_get_payload_rdata,
      m_axi_rdma2_get_payload_rresp,
      m_axi_rdma2_get_payload_rlast,
      m_axi_rdma2_get_payload_rvalid
    );


    // get_axi_rdma_completion_1(
    //   m_axi_rdma_completion_awid,
    //   m_axi_rdma_completion_awaddr,
    //   dummy,  //replace awqos
    //   m_axi_rdma_completion_awlen,
    //   m_axi_rdma_completion_awsize,
    //   m_axi_rdma_completion_awburst,
    //   m_axi_rdma_completion_awcache,
    //   m_axi_rdma_completion_awprot,
    //   m_axi_rdma_completion_awvalid,
    //   m_axi_rdma_completion_wdata,
    //   m_axi_rdma_completion_wstrb,
    //   m_axi_rdma_completion_wlast,
    //   m_axi_rdma_completion_wvalid,
    //   m_axi_rdma_completion_awlock,
    //   m_axi_rdma_completion_arid,
    //   m_axi_rdma_completion_araddr,
    //   m_axi_rdma_completion_arlen,
    //   m_axi_rdma_completion_arsize,
    //   m_axi_rdma_completion_arburst,
    //   m_axi_rdma_completion_arcache,
    //   m_axi_rdma_completion_arprot,
    //   m_axi_rdma_completion_arvalid,
    //   m_axi_rdma_completion_arlock,
    //   dummy    //replace arqos
    // );

    get_axi_rdma_completion_2(
      m_axi_rdma_completion_awready,
      m_axi_rdma_completion_wready,
      m_axi_rdma_completion_bid,
      m_axi_rdma_completion_bresp,
      m_axi_rdma_completion_bvalid,
      m_axi_rdma_completion_arready,
      m_axi_rdma_completion_rid,
      m_axi_rdma_completion_rdata,
      m_axi_rdma_completion_rresp,
      m_axi_rdma_completion_rlast,
      m_axi_rdma_completion_rvalid
    );

    if (simbricks_is_exit()) begin
        $display("Got exit signal from SimBricks adapter.");
        $finish();
    end
end

// ====== SimBricks Adapter Code ======

// ====== Clock =====
// Adapted from rn_tb_driver.sv

localparam CLK_PERIOD = 10ns;
localparam CLK_PERIOD_75  = 12048ps;
localparam CLK_PERIOD_300 = 3012ps;
localparam CLK_PERIOD_400 = 2500ps;
localparam CLK_PERIOD_200 = 5000ps;

initial begin
  axil_rstn = 1'b0;
  axis_rstn = 1'b0;
  #500ns;

  #500ns;
  axil_rstn = 1'b1;
  axis_rstn = 1'b1;
end

initial begin
  axis_clk  = 1'b0;
  forever #(CLK_PERIOD_200/2) axis_clk = ~axis_clk;
end

initial begin
  axil_clk  = 1'b0;
  forever #(CLK_PERIOD/2) axil_clk = ~axil_clk;
end

always_comb
begin
  if(finish_rdma2_stat) begin
    $display("INFO: [rn_tb_2rdma_top_remote], time=%t, Simulation completed", $time);
    $finish;
  end
end

// Check RDMA packets generated by the local peer
logic [47:0] mac_dst;
logic [47:0] mac_src;
logic [3:0]  ip_ihl;
logic [15:0] ip_total_length;
logic [31:0] ip_src;
logic [31:0] ip_dst;
logic [15:0] udp_sport;
logic [15:0] udp_dport;
logic [15:0] udp_length;
logic [7:0]  bth_opcode;
logic [15:0] bth_partition_key;
logic [23:0] bth_dst_qp;
logic [23:0] bth_psn;
logic [31:0] reth_vir_addr_lsb;
logic [31:0] reth_vir_addr_msb;
logic [31:0] reth_rkey;
logic [31:0] reth_length; 

assign mac_dst = m_axis_cmac_tx_tvalid ? {m_axis_cmac_tx_tdata[7:0], m_axis_cmac_tx_tdata[15:8], m_axis_cmac_tx_tdata[23:16], m_axis_cmac_tx_tdata[31:24], m_axis_cmac_tx_tdata[39:32], m_axis_cmac_tx_tdata[47:40]} : 48'd0;
assign mac_src = m_axis_cmac_tx_tvalid ? {m_axis_cmac_tx_tdata[55:48], m_axis_cmac_tx_tdata[63:56], m_axis_cmac_tx_tdata[71:64], m_axis_cmac_tx_tdata[79:72], m_axis_cmac_tx_tdata[87:80], m_axis_cmac_tx_tdata[95:88]} : 48'd0;
assign ip_ihl = m_axis_cmac_tx_tvalid ? m_axis_cmac_tx_tdata[28*4+: 4] : 4'd0;
assign ip_total_length = m_axis_cmac_tx_tvalid ? {m_axis_cmac_tx_tdata[16*8+: 8], m_axis_cmac_tx_tdata[17*8+: 8]} : 16'd0;
assign ip_src = m_axis_cmac_tx_tvalid ? {m_axis_cmac_tx_tdata[26*8+: 8], m_axis_cmac_tx_tdata[27*8+: 8], m_axis_cmac_tx_tdata[28*8+: 8], m_axis_cmac_tx_tdata[29*8+: 8]} : 32'd0;
assign ip_dst = m_axis_cmac_tx_tvalid ? {m_axis_cmac_tx_tdata[30*8+: 8], m_axis_cmac_tx_tdata[31*8+: 8], m_axis_cmac_tx_tdata[32*8+: 8], m_axis_cmac_tx_tdata[33*8+: 8]} : 32'd0;
assign udp_sport = m_axis_cmac_tx_tvalid ? {m_axis_cmac_tx_tdata[34*8+: 8], m_axis_cmac_tx_tdata[35*8+: 16]} : 16'd0;
assign udp_dport = m_axis_cmac_tx_tvalid ? {m_axis_cmac_tx_tdata[36*8+: 8], m_axis_cmac_tx_tdata[37*8+: 8]} : 16'd0;
assign udp_length = m_axis_cmac_tx_tvalid ? {m_axis_cmac_tx_tdata[38*8+: 8], m_axis_cmac_tx_tdata[39*8+: 8]} : 16'd0;
assign bth_opcode = m_axis_cmac_tx_tvalid ? m_axis_cmac_tx_tdata[42*8+: 8] : 8'd0;
assign bth_partition_key = m_axis_cmac_tx_tvalid ? {m_axis_cmac_tx_tdata[44*8+: 8], m_axis_cmac_tx_tdata[45*8+: 8]} : 16'd0;
assign bth_dst_qp = m_axis_cmac_tx_tvalid ? {m_axis_cmac_tx_tdata[47*8+: 8], m_axis_cmac_tx_tdata[48*8+: 8], m_axis_cmac_tx_tdata[49*8+: 8]} : 24'd0;
assign bth_psn = m_axis_cmac_tx_tvalid ? {m_axis_cmac_tx_tdata[51*8+: 8], m_axis_cmac_tx_tdata[52*8+: 8], m_axis_cmac_tx_tdata[53*8+: 8]} : 24'd0;
assign reth_vir_addr_msb = m_axis_cmac_tx_tvalid ? {m_axis_cmac_tx_tdata[54*8+: 8], m_axis_cmac_tx_tdata[55*8+: 8], m_axis_cmac_tx_tdata[56*8+: 8], m_axis_cmac_tx_tdata[57*8+: 8]} : 32'd0;
assign reth_vir_addr_lsb = m_axis_cmac_tx_tvalid ? {m_axis_cmac_tx_tdata[58*8+: 8], m_axis_cmac_tx_tdata[59*8+: 8], m_axis_cmac_tx_tdata[60*8+: 8], m_axis_cmac_tx_tdata[61*8+: 8]} : 32'd0;;
assign reth_rkey = m_axis_cmac_tx_tvalid ? {m_axis_cmac_tx_tdata_delay[62*8+: 8], m_axis_cmac_tx_tdata_delay[63*8+: 8], m_axis_cmac_tx_tdata[0*8+: 8], m_axis_cmac_tx_tdata[1*8+: 8]} : 32'd0;
assign reth_length = m_axis_cmac_tx_tvalid ? {m_axis_cmac_tx_tdata[2*8+: 8], m_axis_cmac_tx_tdata[3*8+: 8], m_axis_cmac_tx_tdata[4*8+: 8], m_axis_cmac_tx_tdata[5*8+: 8]} : 32'd0;

logic [511:0] m_axis_cmac_tx_tdata_delay;
logic [63:0]  m_axis_cmac_tx_tkeep_delay;
logic         m_axis_cmac_tx_tvalid_delay;
logic         m_axis_cmac_tx_tlast_delay;

always_ff @(posedge axis_clk)
begin
  if(!axis_rstn) begin
    m_axis_cmac_tx_tdata_delay  <= 512'd0;
    m_axis_cmac_tx_tkeep_delay  <= 64'd0;
    m_axis_cmac_tx_tvalid_delay <= 1'b0;
    m_axis_cmac_tx_tlast_delay  <= 1'b0;
  end
  else begin
    m_axis_cmac_tx_tdata_delay  <= m_axis_cmac_tx_tdata;
    m_axis_cmac_tx_tkeep_delay  <= m_axis_cmac_tx_tkeep;
    m_axis_cmac_tx_tvalid_delay <= m_axis_cmac_tx_tvalid;
    m_axis_cmac_tx_tlast_delay  <= m_axis_cmac_tx_tlast;
  end
end

always_ff @(posedge axis_clk)
begin
  if(!axis_rstn) begin
    checking_recv_rdma2 <= 1'b0;
  end
  else begin
    if (m_axis_cmac_tx_tvalid && m_axis_cmac_tx_tready) begin
      // Detect whether it's a send operation
      if ((bth_opcode==8'h00) || (bth_opcode==8'h01) || (bth_opcode==8'h02) || (bth_opcode==8'h03) || (bth_opcode==8'h04) || (bth_opcode==8'h05)) begin
        checking_recv_rdma2 <= 1'b1;
      end
    end
  end
end

always_ff @(posedge axil_clk)
begin
  if(!axil_rstn) begin
    start_checking_recv_rdma2_cdc <= 2'd0;
  end
  else begin
    start_checking_recv_rdma2_cdc <= {start_checking_recv_rdma2_cdc[0], checking_recv_rdma2};
  end
end

assign start_checking_recv_rdma2 = start_checking_recv_rdma2_cdc[1];

// ====== Clock =====

logic dummy;

logic axil_clk;
logic axil_rstn;
logic axis_clk;
logic axis_rstn;

logic        axil_rdma2_awvalid;
logic [31:0] axil_rdma2_awaddr;
logic        axil_rdma2_awready;
logic        axil_rdma2_wvalid;
logic [31:0] axil_rdma2_wdata;
logic        axil_rdma2_wready;
logic        axil_rdma2_bvalid;
logic  [1:0] axil_rdma2_bresp;
logic        axil_rdma2_bready;
logic        axil_rdma2_arvalid;
logic [31:0] axil_rdma2_araddr;
logic        axil_rdma2_arready;
logic        axil_rdma2_rvalid;
logic [31:0] axil_rdma2_rdata;
logic  [1:0] axil_rdma2_rresp;
logic        axil_rdma2_rready;


// remote peer rdma to local peer rdma
logic [511:0] rp_rdma2lp_rdma_axis_tdata;
logic  [63:0] rp_rdma2lp_rdma_axis_tkeep;
logic         rp_rdma2lp_rdma_axis_tvalid;
logic         rp_rdma2lp_rdma_axis_tlast;
logic         rp_rdma2lp_rdma_axis_tready;


logic         m_axis_cmac_tx_tvalid;
logic [511:0] m_axis_cmac_tx_tdata;
logic  [63:0] m_axis_cmac_tx_tkeep;
logic         m_axis_cmac_tx_tlast;
logic  [15:0] m_axis_cmac_tx_tuser_size;
logic         m_axis_cmac_tx_tready;

// invalidate or immediate data from roce IETH/IMMDT header
logic  [63:0] rp_rdma2user_ieth_immdt_axis_tdata;
logic         rp_rdma2user_ieth_immdt_axis_tlast;
logic         rp_rdma2user_ieth_immdt_axis_tvalid;
logic         rp_rdma2user_ieth_immdt_axis_trdy;

assign rp_rdma2user_ieth_immdt_axis_trdy = 1'b1;

// RDMA AXI MM interface used to store payload from RDMA MAD, Send or Write operation
logic           axi_rdma2_send_write_payload_awid;
logic  [63 : 0] axi_rdma2_send_write_payload_awaddr;
logic  [31 : 0] axi_rdma2_send_write_payload_awuser;
logic   [3 : 0] axi_rdma2_send_write_payload_awqos;
logic   [7 : 0] axi_rdma2_send_write_payload_awlen;
logic   [2 : 0] axi_rdma2_send_write_payload_awsize;
logic   [1 : 0] axi_rdma2_send_write_payload_awburst;
logic   [3 : 0] axi_rdma2_send_write_payload_awcache;
logic   [2 : 0] axi_rdma2_send_write_payload_awprot;
logic           axi_rdma2_send_write_payload_awvalid;
logic           axi_rdma2_send_write_payload_awready;
logic [511 : 0] axi_rdma2_send_write_payload_wdata;
logic  [63 : 0] axi_rdma2_send_write_payload_wstrb;
logic           axi_rdma2_send_write_payload_wlast;
logic           axi_rdma2_send_write_payload_wvalid;
logic           axi_rdma2_send_write_payload_wready;
logic           axi_rdma2_send_write_payload_awlock;
logic           axi_rdma2_send_write_payload_bid;
logic   [1 : 0] axi_rdma2_send_write_payload_bresp;
logic           axi_rdma2_send_write_payload_bvalid;
logic           axi_rdma2_send_write_payload_bready;
logic           axi_rdma2_send_write_payload_arid;
logic  [63 : 0] axi_rdma2_send_write_payload_araddr;
logic   [7 : 0] axi_rdma2_send_write_payload_arlen;
logic   [2 : 0] axi_rdma2_send_write_payload_arsize;
logic   [1 : 0] axi_rdma2_send_write_payload_arburst;
logic   [3 : 0] axi_rdma2_send_write_payload_arcache;
logic   [2 : 0] axi_rdma2_send_write_payload_arprot;
logic           axi_rdma2_send_write_payload_arvalid;
logic           axi_rdma2_send_write_payload_arready;
logic           axi_rdma2_send_write_payload_rid;
logic [511 : 0] axi_rdma2_send_write_payload_rdata;
logic   [1 : 0] axi_rdma2_send_write_payload_rresp;
logic           axi_rdma2_send_write_payload_rlast;
logic           axi_rdma2_send_write_payload_rvalid;
logic           axi_rdma2_send_write_payload_rready;
logic           axi_rdma2_send_write_payload_arlock;
logic     [3:0] axi_rdma2_send_write_payload_arqos;

// RDMA AXI MM interface used to store payload from RDMA Read response operation
logic           m_axi_rdma_rsp_payload_awid;
logic  [63 : 0] m_axi_rdma_rsp_payload_awaddr;
logic   [7 : 0] m_axi_rdma_rsp_payload_awlen;
logic   [2 : 0] m_axi_rdma_rsp_payload_awsize;
logic   [1 : 0] m_axi_rdma_rsp_payload_awburst;
logic   [3 : 0] m_axi_rdma_rsp_payload_awcache;
logic   [2 : 0] m_axi_rdma_rsp_payload_awprot;
logic           m_axi_rdma_rsp_payload_awvalid;
logic           m_axi_rdma_rsp_payload_awready;
logic [511 : 0] m_axi_rdma_rsp_payload_wdata;
logic  [63 : 0] m_axi_rdma_rsp_payload_wstrb;
logic           m_axi_rdma_rsp_payload_wlast;
logic           m_axi_rdma_rsp_payload_wvalid;
logic           m_axi_rdma_rsp_payload_wready;
logic           m_axi_rdma_rsp_payload_awlock;
logic           m_axi_rdma_rsp_payload_bid;
logic   [1 : 0] m_axi_rdma_rsp_payload_bresp;
logic           m_axi_rdma_rsp_payload_bvalid;
logic           m_axi_rdma_rsp_payload_bready;
logic           m_axi_rdma_rsp_payload_arid;
logic  [63 : 0] m_axi_rdma_rsp_payload_araddr;
logic   [7 : 0] m_axi_rdma_rsp_payload_arlen;
logic   [2 : 0] m_axi_rdma_rsp_payload_arsize;
logic   [1 : 0] m_axi_rdma_rsp_payload_arburst;
logic   [3 : 0] m_axi_rdma_rsp_payload_arcache;
logic   [2 : 0] m_axi_rdma_rsp_payload_arprot;
logic           m_axi_rdma_rsp_payload_arvalid;
logic           m_axi_rdma_rsp_payload_arready;
logic           m_axi_rdma_rsp_payload_rid;
logic [511 : 0] m_axi_rdma_rsp_payload_rdata;
logic   [1 : 0] m_axi_rdma_rsp_payload_rresp;
logic           m_axi_rdma_rsp_payload_rlast;
logic           m_axi_rdma_rsp_payload_rvalid;
logic           m_axi_rdma_rsp_payload_rready;
logic           m_axi_rdma_rsp_payload_arlock;

// RDMA AXI MM interface used to fetch WQE entries in the senq queue from DDR by the QP manager
logic           m_axi_rdma_get_wqe_awid;
logic  [63 : 0] m_axi_rdma_get_wqe_awaddr;
logic   [7 : 0] m_axi_rdma_get_wqe_awlen;
logic   [2 : 0] m_axi_rdma_get_wqe_awsize;
logic   [1 : 0] m_axi_rdma_get_wqe_awburst;
logic   [3 : 0] m_axi_rdma_get_wqe_awcache;
logic   [2 : 0] m_axi_rdma_get_wqe_awprot;
logic           m_axi_rdma_get_wqe_awvalid;
logic           m_axi_rdma_get_wqe_awready;
logic [511 : 0] m_axi_rdma_get_wqe_wdata;
logic  [63 : 0] m_axi_rdma_get_wqe_wstrb;
logic           m_axi_rdma_get_wqe_wlast;
logic           m_axi_rdma_get_wqe_wvalid;
logic           m_axi_rdma_get_wqe_wready;
logic           m_axi_rdma_get_wqe_awlock;
logic           m_axi_rdma_get_wqe_bid;
logic   [1 : 0] m_axi_rdma_get_wqe_bresp;
logic           m_axi_rdma_get_wqe_bvalid;
logic           m_axi_rdma_get_wqe_bready;
logic           m_axi_rdma_get_wqe_arid;
logic  [63 : 0] m_axi_rdma_get_wqe_araddr;
logic   [7 : 0] m_axi_rdma_get_wqe_arlen;
logic   [2 : 0] m_axi_rdma_get_wqe_arsize;
logic   [1 : 0] m_axi_rdma_get_wqe_arburst;
logic   [3 : 0] m_axi_rdma_get_wqe_arcache;
logic   [2 : 0] m_axi_rdma_get_wqe_arprot;
logic           m_axi_rdma_get_wqe_arvalid;
logic           m_axi_rdma_get_wqe_arready;
logic           m_axi_rdma_get_wqe_rid;
logic [511 : 0] m_axi_rdma_get_wqe_rdata;
logic   [1 : 0] m_axi_rdma_get_wqe_rresp;
logic           m_axi_rdma_get_wqe_rlast;
logic           m_axi_rdma_get_wqe_rvalid;
logic           m_axi_rdma_get_wqe_rready;
logic           m_axi_rdma_get_wqe_arlock;

logic           m_axi_rdma2_get_payload_awid;
logic  [63 : 0] m_axi_rdma2_get_payload_awaddr;
logic   [3 : 0] m_axi_rdma2_get_payload_awqos;
logic   [7 : 0] m_axi_rdma2_get_payload_awlen;
logic   [2 : 0] m_axi_rdma2_get_payload_awsize;
logic   [1 : 0] m_axi_rdma2_get_payload_awburst;
logic   [3 : 0] m_axi_rdma2_get_payload_awcache;
logic   [2 : 0] m_axi_rdma2_get_payload_awprot;
logic           m_axi_rdma2_get_payload_awvalid;
logic           m_axi_rdma2_get_payload_awready;
logic [511 : 0] m_axi_rdma2_get_payload_wdata;
logic  [63 : 0] m_axi_rdma2_get_payload_wstrb;
logic           m_axi_rdma2_get_payload_wlast;
logic           m_axi_rdma2_get_payload_wvalid;
logic           m_axi_rdma2_get_payload_wready;
logic           m_axi_rdma2_get_payload_awlock;
logic           m_axi_rdma2_get_payload_bid;
logic   [1 : 0] m_axi_rdma2_get_payload_bresp;
logic           m_axi_rdma2_get_payload_bvalid;
logic           m_axi_rdma2_get_payload_bready;
logic           m_axi_rdma2_get_payload_arid;
logic  [63 : 0] m_axi_rdma2_get_payload_araddr;
logic   [7 : 0] m_axi_rdma2_get_payload_arlen;
logic   [2 : 0] m_axi_rdma2_get_payload_arsize;
logic   [1 : 0] m_axi_rdma2_get_payload_arburst;
logic   [3 : 0] m_axi_rdma2_get_payload_arcache;
logic   [2 : 0] m_axi_rdma2_get_payload_arprot;
logic           m_axi_rdma2_get_payload_arvalid;
logic           m_axi_rdma2_get_payload_arready;
logic           m_axi_rdma2_get_payload_rid;
logic [511 : 0] m_axi_rdma2_get_payload_rdata;
logic   [1 : 0] m_axi_rdma2_get_payload_rresp;
logic           m_axi_rdma2_get_payload_rlast;
logic           m_axi_rdma2_get_payload_rvalid;
logic           m_axi_rdma2_get_payload_rready;
logic           m_axi_rdma2_get_payload_arlock;
logic   [3 : 0] m_axi_rdma2_get_payload_arqos;

// RDMA AXI MM interface used to write completion entries to a completion queue in the DDR
logic           m_axi_rdma_completion_awid;
logic  [63 : 0] m_axi_rdma_completion_awaddr;
logic   [7 : 0] m_axi_rdma_completion_awlen;
logic   [2 : 0] m_axi_rdma_completion_awsize;
logic   [1 : 0] m_axi_rdma_completion_awburst;
logic   [3 : 0] m_axi_rdma_completion_awcache;
logic   [2 : 0] m_axi_rdma_completion_awprot;
logic           m_axi_rdma_completion_awvalid;
logic           m_axi_rdma_completion_awready;
logic [511 : 0] m_axi_rdma_completion_wdata;
logic  [63 : 0] m_axi_rdma_completion_wstrb;
logic           m_axi_rdma_completion_wlast;
logic           m_axi_rdma_completion_wvalid;
logic           m_axi_rdma_completion_wready;
logic           m_axi_rdma_completion_awlock;
logic           m_axi_rdma_completion_bid;
logic   [1 : 0] m_axi_rdma_completion_bresp;
logic           m_axi_rdma_completion_bvalid;
logic           m_axi_rdma_completion_bready;
logic           m_axi_rdma_completion_arid;
logic  [63 : 0] m_axi_rdma_completion_araddr;
logic   [7 : 0] m_axi_rdma_completion_arlen;
logic   [2 : 0] m_axi_rdma_completion_arsize;
logic   [1 : 0] m_axi_rdma_completion_arburst;
logic   [3 : 0] m_axi_rdma_completion_arcache;
logic   [2 : 0] m_axi_rdma_completion_arprot;
logic           m_axi_rdma_completion_arvalid;
logic           m_axi_rdma_completion_arready;
logic           m_axi_rdma_completion_rid;
logic [511 : 0] m_axi_rdma_completion_rdata;
logic   [1 : 0] m_axi_rdma_completion_rresp;
logic           m_axi_rdma_completion_rlast;
logic           m_axi_rdma_completion_rvalid;
logic           m_axi_rdma_completion_rready;
logic           m_axi_rdma_completion_arlock;

logic rdma2_rst_done;
logic rdma2_intr;

// RDMA-Send producer index doorbell
logic  [31:0] rx_pkt_hndler_o_rq_db_data;
logic   [9:0] rx_pkt_hndler_o_rq_db_addr;
logic         rx_pkt_hndler_o_rq_db_data_valid;
logic         rx_pkt_hndler_i_rq_db_rdy;

// RDMA-Send consumer index doorbell
logic  [15:0] i_qp_rq_cidb_hndshk;
logic  [31:0] i_qp_rq_cidb_wr_addr_hndshk;
logic         i_qp_rq_cidb_wr_valid_hndshk;
logic         o_qp_rq_cidb_wr_rdy;

// Send WQE producer index doorbell
logic  [15:0] i_qp_sq_pidb_hndshk;
logic  [31:0] i_qp_sq_pidb_wr_addr_hndshk;
logic         i_qp_sq_pidb_wr_valid_hndshk;
logic         o_qp_sq_pidb_wr_rdy;

// Send WQE completion queue doorbell
logic         resp_hndler_o_send_cq_db_cnt_valid;
logic   [9:0] resp_hndler_o_send_cq_db_addr;
logic  [31:0] resp_hndler_o_send_cq_db_cnt;
logic         resp_hndler_i_send_cq_db_rdy;

assign resp_hndler_i_send_cq_db_rdy = 1'b1;
assign i_qp_sq_pidb_hndshk = 16'd0;
assign i_qp_sq_pidb_wr_addr_hndshk = 32'd0;
assign i_qp_sq_pidb_wr_valid_hndshk = 1'b0;

assign i_qp_rq_cidb_hndshk = 16'd0;
assign i_qp_rq_cidb_wr_addr_hndshk = 32'd0;
assign i_qp_rq_cidb_wr_valid_hndshk = 1'b0;


rdma_subsystem_wrapper remote_peer_rdma_inst (
  // Note: OK
  // AXIL interface for RDMA control register
  .s_axil_awaddr    (axil_rdma2_awaddr),
  .s_axil_awvalid   (axil_rdma2_awvalid),
  .s_axil_awready   (axil_rdma2_awready),
  .s_axil_wdata     (axil_rdma2_wdata),
  .s_axil_wstrb     (4'hf),
  .s_axil_wvalid    (axil_rdma2_wvalid),
  .s_axil_wready    (axil_rdma2_wready),
  .s_axil_araddr    (axil_rdma2_araddr),
  .s_axil_arvalid   (axil_rdma2_arvalid),
  .s_axil_arready   (axil_rdma2_arready),
  .s_axil_rdata     (axil_rdma2_rdata),
  .s_axil_rvalid    (axil_rdma2_rvalid),
  .s_axil_rresp     (axil_rdma2_rresp),
  .s_axil_rready    (axil_rdma2_rready),
  .s_axil_bresp     (axil_rdma2_bresp),
  .s_axil_bvalid    (axil_rdma2_bvalid),
  .s_axil_bready    (axil_rdma2_bready),

  // Issue RDMA acknowledge packets back to the RDMA-1
  .m_rdma2cmac_axis_tdata  (rp_rdma2lp_rdma_axis_tdata),
  .m_rdma2cmac_axis_tkeep  (rp_rdma2lp_rdma_axis_tkeep),
  .m_rdma2cmac_axis_tvalid (rp_rdma2lp_rdma_axis_tvalid),
  .m_rdma2cmac_axis_tlast  (rp_rdma2lp_rdma_axis_tlast),    //outs
  .m_rdma2cmac_axis_tready (rp_rdma2lp_rdma_axis_tready),   //input

  // Do not receive any non-roce packets
  .s_qdma2rdma_non_roce_axis_tdata    (512'd0),
  .s_qdma2rdma_non_roce_axis_tkeep    (64'd0),
  .s_qdma2rdma_non_roce_axis_tvalid   (1'b0),
  .s_qdma2rdma_non_roce_axis_tlast    (1'b0),
  .s_qdma2rdma_non_roce_axis_tready   (),

  // Receive RoCEv2 packets from the local RDMA peer
  .s_cmac2rdma_roce_axis_tdata        (m_axis_cmac_tx_tdata),   //input
  .s_cmac2rdma_roce_axis_tkeep        (m_axis_cmac_tx_tkeep), 
  .s_cmac2rdma_roce_axis_tvalid       (m_axis_cmac_tx_tvalid),
  .s_cmac2rdma_roce_axis_tlast        (m_axis_cmac_tx_tlast),
  .s_cmac2rdma_roce_axis_tuser        (m_axis_cmac_tx_tvalid && m_axis_cmac_tx_tlast),

  // No non-RDMA packets from CMAC RX bypassing RDMA from the remote RDMA peer
  .s_cmac2rdma_non_roce_axis_tdata    (512'd0),
  .s_cmac2rdma_non_roce_axis_tkeep    (64'd0),
  .s_cmac2rdma_non_roce_axis_tvalid   (1'b0),
  .s_cmac2rdma_non_roce_axis_tlast    (1'b0),
  .s_cmac2rdma_non_roce_axis_tuser    (1'b0),

  // No non-RDMA packets bypassing RDMA to QDMA RX from the remote RDMA peer
  .m_rdma2qdma_non_roce_axis_tdata    (),
  .m_rdma2qdma_non_roce_axis_tkeep    (),
  .m_rdma2qdma_non_roce_axis_tvalid   (),
  .m_rdma2qdma_non_roce_axis_tlast    (),
  .m_rdma2qdma_non_roce_axis_tready   (1'b1),

  // invalidate or immediate data from roce IETH/IMMDT header
  .m_rdma2user_ieth_immdt_axis_tdata  (rp_rdma2user_ieth_immdt_axis_tdata),
  .m_rdma2user_ieth_immdt_axis_tlast  (rp_rdma2user_ieth_immdt_axis_tlast),
  .m_rdma2user_ieth_immdt_axis_tvalid (rp_rdma2user_ieth_immdt_axis_tvalid),
  .m_rdma2user_ieth_immdt_axis_trdy   (rp_rdma2user_ieth_immdt_axis_trdy),

  // NOTE: OK


  // RDMA AXI MM interface used to store payload from RDMA MAD, Send or Write operation
  .m_axi_rdma_send_write_payload_store_awid    (axi_rdma2_send_write_payload_awid),
  .m_axi_rdma_send_write_payload_store_awaddr  (axi_rdma2_send_write_payload_awaddr),
  .m_axi_rdma_send_write_payload_store_awuser  (axi_rdma2_send_write_payload_awuser),
  .m_axi_rdma_send_write_payload_store_awlen   (axi_rdma2_send_write_payload_awlen),
  .m_axi_rdma_send_write_payload_store_awsize  (axi_rdma2_send_write_payload_awsize),
  .m_axi_rdma_send_write_payload_store_awburst (axi_rdma2_send_write_payload_awburst),
  .m_axi_rdma_send_write_payload_store_awcache (axi_rdma2_send_write_payload_awcache),
  .m_axi_rdma_send_write_payload_store_awprot  (axi_rdma2_send_write_payload_awprot),
  .m_axi_rdma_send_write_payload_store_awvalid (axi_rdma2_send_write_payload_awvalid),
  .m_axi_rdma_send_write_payload_store_awready (axi_rdma2_send_write_payload_awready),
  .m_axi_rdma_send_write_payload_store_wdata   (axi_rdma2_send_write_payload_wdata),
  .m_axi_rdma_send_write_payload_store_wstrb   (axi_rdma2_send_write_payload_wstrb),
  .m_axi_rdma_send_write_payload_store_wlast   (axi_rdma2_send_write_payload_wlast),
  .m_axi_rdma_send_write_payload_store_wvalid  (axi_rdma2_send_write_payload_wvalid),
  .m_axi_rdma_send_write_payload_store_wready  (axi_rdma2_send_write_payload_wready),
  .m_axi_rdma_send_write_payload_store_awlock  (axi_rdma2_send_write_payload_awlock),
  .m_axi_rdma_send_write_payload_store_bid     (axi_rdma2_send_write_payload_bid),
  .m_axi_rdma_send_write_payload_store_bresp   (axi_rdma2_send_write_payload_bresp),
  .m_axi_rdma_send_write_payload_store_bvalid  (axi_rdma2_send_write_payload_bvalid),
  .m_axi_rdma_send_write_payload_store_bready  (axi_rdma2_send_write_payload_bready),
  .m_axi_rdma_send_write_payload_store_arid    (axi_rdma2_send_write_payload_arid),
  .m_axi_rdma_send_write_payload_store_araddr  (axi_rdma2_send_write_payload_araddr),
  .m_axi_rdma_send_write_payload_store_arlen   (axi_rdma2_send_write_payload_arlen),
  .m_axi_rdma_send_write_payload_store_arsize  (axi_rdma2_send_write_payload_arsize),
  .m_axi_rdma_send_write_payload_store_arburst (axi_rdma2_send_write_payload_arburst),
  .m_axi_rdma_send_write_payload_store_arcache (axi_rdma2_send_write_payload_arcache),
  .m_axi_rdma_send_write_payload_store_arprot  (axi_rdma2_send_write_payload_arprot),
  .m_axi_rdma_send_write_payload_store_arvalid (axi_rdma2_send_write_payload_arvalid),
  .m_axi_rdma_send_write_payload_store_arready (axi_rdma2_send_write_payload_arready),
  .m_axi_rdma_send_write_payload_store_rid     (axi_rdma2_send_write_payload_rid),
  .m_axi_rdma_send_write_payload_store_rdata   (axi_rdma2_send_write_payload_rdata),
  .m_axi_rdma_send_write_payload_store_rresp   (axi_rdma2_send_write_payload_rresp),
  .m_axi_rdma_send_write_payload_store_rlast   (axi_rdma2_send_write_payload_rlast),
  .m_axi_rdma_send_write_payload_store_rvalid  (axi_rdma2_send_write_payload_rvalid),
  .m_axi_rdma_send_write_payload_store_rready  (axi_rdma2_send_write_payload_rready),
  .m_axi_rdma_send_write_payload_store_arlock  (axi_rdma2_send_write_payload_arlock),

  // RDMA AXI MM interface used to store payload from RDMA Read response operation
  .m_axi_rdma_rsp_payload_awid          (m_axi_rdma_rsp_payload_awid),
  .m_axi_rdma_rsp_payload_awaddr        (m_axi_rdma_rsp_payload_awaddr),
  .m_axi_rdma_rsp_payload_awlen         (m_axi_rdma_rsp_payload_awlen),
  .m_axi_rdma_rsp_payload_awsize        (m_axi_rdma_rsp_payload_awsize),
  .m_axi_rdma_rsp_payload_awburst       (m_axi_rdma_rsp_payload_awburst),
  .m_axi_rdma_rsp_payload_awcache       (m_axi_rdma_rsp_payload_awcache),
  .m_axi_rdma_rsp_payload_awprot        (m_axi_rdma_rsp_payload_awprot),
  .m_axi_rdma_rsp_payload_awvalid       (m_axi_rdma_rsp_payload_awvalid),
  .m_axi_rdma_rsp_payload_awready       (m_axi_rdma_rsp_payload_awready),
  .m_axi_rdma_rsp_payload_wdata         (m_axi_rdma_rsp_payload_wdata),
  .m_axi_rdma_rsp_payload_wstrb         (m_axi_rdma_rsp_payload_wstrb),
  .m_axi_rdma_rsp_payload_wlast         (m_axi_rdma_rsp_payload_wlast),
  .m_axi_rdma_rsp_payload_wvalid        (m_axi_rdma_rsp_payload_wvalid),
  .m_axi_rdma_rsp_payload_wready        (m_axi_rdma_rsp_payload_wready),
  .m_axi_rdma_rsp_payload_awlock        (m_axi_rdma_rsp_payload_awlock),
  .m_axi_rdma_rsp_payload_bid           (m_axi_rdma_rsp_payload_bid),
  .m_axi_rdma_rsp_payload_bresp         (m_axi_rdma_rsp_payload_bresp),
  .m_axi_rdma_rsp_payload_bvalid        (m_axi_rdma_rsp_payload_bvalid),
  .m_axi_rdma_rsp_payload_bready        (m_axi_rdma_rsp_payload_bready),
  .m_axi_rdma_rsp_payload_arid          (m_axi_rdma_rsp_payload_arid),
  .m_axi_rdma_rsp_payload_araddr        (m_axi_rdma_rsp_payload_araddr),
  .m_axi_rdma_rsp_payload_arlen         (m_axi_rdma_rsp_payload_arlen),
  .m_axi_rdma_rsp_payload_arsize        (m_axi_rdma_rsp_payload_arsize),
  .m_axi_rdma_rsp_payload_arburst       (m_axi_rdma_rsp_payload_arburst),
  .m_axi_rdma_rsp_payload_arcache       (m_axi_rdma_rsp_payload_arcache),
  .m_axi_rdma_rsp_payload_arprot        (m_axi_rdma_rsp_payload_arprot),
  .m_axi_rdma_rsp_payload_arvalid       (m_axi_rdma_rsp_payload_arvalid),
  .m_axi_rdma_rsp_payload_arready       (m_axi_rdma_rsp_payload_arready),
  .m_axi_rdma_rsp_payload_rid           (m_axi_rdma_rsp_payload_rid),
  .m_axi_rdma_rsp_payload_rdata         (m_axi_rdma_rsp_payload_rdata),
  .m_axi_rdma_rsp_payload_rresp         (m_axi_rdma_rsp_payload_rresp),
  .m_axi_rdma_rsp_payload_rlast         (m_axi_rdma_rsp_payload_rlast),
  .m_axi_rdma_rsp_payload_rvalid        (m_axi_rdma_rsp_payload_rvalid),
  .m_axi_rdma_rsp_payload_rready        (m_axi_rdma_rsp_payload_rready),
  .m_axi_rdma_rsp_payload_arlock        (m_axi_rdma_rsp_payload_arlock),

  // RDMA AXI MM interface used to fetch WQE entries in the senq queue from DDR by the QP manager
  .m_axi_qp_get_wqe_awid                (m_axi_rdma_get_wqe_awid),      //output
  .m_axi_qp_get_wqe_awaddr              (m_axi_rdma_get_wqe_awaddr),
  .m_axi_qp_get_wqe_awlen               (m_axi_rdma_get_wqe_awlen),
  .m_axi_qp_get_wqe_awsize              (m_axi_rdma_get_wqe_awsize),
  .m_axi_qp_get_wqe_awburst             (m_axi_rdma_get_wqe_awburst),
  .m_axi_qp_get_wqe_awcache             (m_axi_rdma_get_wqe_awcache),
  .m_axi_qp_get_wqe_awprot              (m_axi_rdma_get_wqe_awprot),
  .m_axi_qp_get_wqe_awvalid             (m_axi_rdma_get_wqe_awvalid),
  .m_axi_qp_get_wqe_awready             (m_axi_rdma_get_wqe_awready),
  .m_axi_qp_get_wqe_wdata               (m_axi_rdma_get_wqe_wdata),
  .m_axi_qp_get_wqe_wstrb               (m_axi_rdma_get_wqe_wstrb),
  .m_axi_qp_get_wqe_wlast               (m_axi_rdma_get_wqe_wlast),
  .m_axi_qp_get_wqe_wvalid              (m_axi_rdma_get_wqe_wvalid),
  .m_axi_qp_get_wqe_wready              (m_axi_rdma_get_wqe_wready),
  .m_axi_qp_get_wqe_awlock              (m_axi_rdma_get_wqe_awlock),
  .m_axi_qp_get_wqe_bid                 (m_axi_rdma_get_wqe_bid),
  .m_axi_qp_get_wqe_bresp               (m_axi_rdma_get_wqe_bresp),
  .m_axi_qp_get_wqe_bvalid              (m_axi_rdma_get_wqe_bvalid),
  .m_axi_qp_get_wqe_bready              (m_axi_rdma_get_wqe_bready),
  .m_axi_qp_get_wqe_arid                (m_axi_rdma_get_wqe_arid),
  .m_axi_qp_get_wqe_araddr              (m_axi_rdma_get_wqe_araddr),
  .m_axi_qp_get_wqe_arlen               (m_axi_rdma_get_wqe_arlen),
  .m_axi_qp_get_wqe_arsize              (m_axi_rdma_get_wqe_arsize),
  .m_axi_qp_get_wqe_arburst             (m_axi_rdma_get_wqe_arburst),
  .m_axi_qp_get_wqe_arcache             (m_axi_rdma_get_wqe_arcache),
  .m_axi_qp_get_wqe_arprot              (m_axi_rdma_get_wqe_arprot),
  .m_axi_qp_get_wqe_arvalid             (m_axi_rdma_get_wqe_arvalid),
  .m_axi_qp_get_wqe_arready             (m_axi_rdma_get_wqe_arready),
  .m_axi_qp_get_wqe_rid                 (m_axi_rdma_get_wqe_rid),
  .m_axi_qp_get_wqe_rdata               (m_axi_rdma_get_wqe_rdata),
  .m_axi_qp_get_wqe_rresp               (m_axi_rdma_get_wqe_rresp),
  .m_axi_qp_get_wqe_rlast               (m_axi_rdma_get_wqe_rlast),
  .m_axi_qp_get_wqe_rvalid              (m_axi_rdma_get_wqe_rvalid),
  .m_axi_qp_get_wqe_rready              (m_axi_rdma_get_wqe_rready),
  .m_axi_qp_get_wqe_arlock              (m_axi_rdma_get_wqe_arlock),

  // TODO: In the current implementation, we do not consider retry buffer
  // RDMA AXI MM interface used to store payload of an outgoing RDMA write packet to a retry buffer
  .m_axi_payload_to_retry_buf_awid     (),
  .m_axi_payload_to_retry_buf_awaddr   (),
  .m_axi_payload_to_retry_buf_awlen    (),
  .m_axi_payload_to_retry_buf_awsize   (),
  .m_axi_payload_to_retry_buf_awburst  (),
  .m_axi_payload_to_retry_buf_awcache  (),
  .m_axi_payload_to_retry_buf_awprot   (),
  .m_axi_payload_to_retry_buf_awvalid  (),
  .m_axi_payload_to_retry_buf_awready  (1'b1),
  .m_axi_payload_to_retry_buf_wdata    (),
  .m_axi_payload_to_retry_buf_wstrb    (),
  .m_axi_payload_to_retry_buf_wlast    (),
  .m_axi_payload_to_retry_buf_wvalid   (),
  .m_axi_payload_to_retry_buf_wready   (1'b1),
  .m_axi_payload_to_retry_buf_awlock   (),
  .m_axi_payload_to_retry_buf_bid      (1'b0),
  .m_axi_payload_to_retry_buf_bresp    (2'd0),
  .m_axi_payload_to_retry_buf_bvalid   (1'b0),
  .m_axi_payload_to_retry_buf_bready   (),
  .m_axi_payload_to_retry_buf_arid     (),
  .m_axi_payload_to_retry_buf_araddr   (),
  .m_axi_payload_to_retry_buf_arlen    (),
  .m_axi_payload_to_retry_buf_arsize   (),
  .m_axi_payload_to_retry_buf_arburst  (),
  .m_axi_payload_to_retry_buf_arcache  (),
  .m_axi_payload_to_retry_buf_arprot   (),
  .m_axi_payload_to_retry_buf_arvalid  (),
  .m_axi_payload_to_retry_buf_arready  (1'b1),
  .m_axi_payload_to_retry_buf_rid      (1'b0),
  .m_axi_payload_to_retry_buf_rdata    (512'd0),
  .m_axi_payload_to_retry_buf_rresp    (2'd0),
  .m_axi_payload_to_retry_buf_rlast    (1'b0),
  .m_axi_payload_to_retry_buf_rvalid   (1'b0),
  .m_axi_payload_to_retry_buf_rready   (),
  .m_axi_payload_to_retry_buf_arlock   (),

  // RDMA AXI MM interface used to get payload of an outgoing RDMA send/write and read response packets
  .m_axi_pktgen_get_payload_awid       (m_axi_rdma2_get_payload_awid),
  .m_axi_pktgen_get_payload_awaddr     (m_axi_rdma2_get_payload_awaddr),
  .m_axi_pktgen_get_payload_awlen      (m_axi_rdma2_get_payload_awlen),
  .m_axi_pktgen_get_payload_awsize     (m_axi_rdma2_get_payload_awsize),
  .m_axi_pktgen_get_payload_awburst    (m_axi_rdma2_get_payload_awburst),
  .m_axi_pktgen_get_payload_awcache    (m_axi_rdma2_get_payload_awcache),
  .m_axi_pktgen_get_payload_awprot     (m_axi_rdma2_get_payload_awprot),
  .m_axi_pktgen_get_payload_awvalid    (m_axi_rdma2_get_payload_awvalid),
  .m_axi_pktgen_get_payload_awready    (m_axi_rdma2_get_payload_awready),
  .m_axi_pktgen_get_payload_wdata      (m_axi_rdma2_get_payload_wdata),
  .m_axi_pktgen_get_payload_wstrb      (m_axi_rdma2_get_payload_wstrb),
  .m_axi_pktgen_get_payload_wlast      (m_axi_rdma2_get_payload_wlast),
  .m_axi_pktgen_get_payload_wvalid     (m_axi_rdma2_get_payload_wvalid),
  .m_axi_pktgen_get_payload_wready     (m_axi_rdma2_get_payload_wready),
  .m_axi_pktgen_get_payload_awlock     (m_axi_rdma2_get_payload_awlock),
  .m_axi_pktgen_get_payload_bid        (m_axi_rdma2_get_payload_bid),
  .m_axi_pktgen_get_payload_bresp      (m_axi_rdma2_get_payload_bresp),
  .m_axi_pktgen_get_payload_bvalid     (m_axi_rdma2_get_payload_bvalid),
  .m_axi_pktgen_get_payload_bready     (m_axi_rdma2_get_payload_bready),
  .m_axi_pktgen_get_payload_arid       (m_axi_rdma2_get_payload_arid),
  .m_axi_pktgen_get_payload_araddr     (m_axi_rdma2_get_payload_araddr),
  .m_axi_pktgen_get_payload_arlen      (m_axi_rdma2_get_payload_arlen),
  .m_axi_pktgen_get_payload_arsize     (m_axi_rdma2_get_payload_arsize),
  .m_axi_pktgen_get_payload_arburst    (m_axi_rdma2_get_payload_arburst),
  .m_axi_pktgen_get_payload_arcache    (m_axi_rdma2_get_payload_arcache),
  .m_axi_pktgen_get_payload_arprot     (m_axi_rdma2_get_payload_arprot),
  .m_axi_pktgen_get_payload_arvalid    (m_axi_rdma2_get_payload_arvalid),
  .m_axi_pktgen_get_payload_arready    (m_axi_rdma2_get_payload_arready),
  .m_axi_pktgen_get_payload_rid        (m_axi_rdma2_get_payload_rid),
  .m_axi_pktgen_get_payload_rdata      (m_axi_rdma2_get_payload_rdata),
  .m_axi_pktgen_get_payload_rresp      (m_axi_rdma2_get_payload_rresp),
  .m_axi_pktgen_get_payload_rlast      (m_axi_rdma2_get_payload_rlast),
  .m_axi_pktgen_get_payload_rvalid     (m_axi_rdma2_get_payload_rvalid),
  .m_axi_pktgen_get_payload_rready     (m_axi_rdma2_get_payload_rready),
  .m_axi_pktgen_get_payload_arlock     (m_axi_rdma2_get_payload_arlock),

  // RDMA AXI MM interface used to write completion entries to a completion queue in the DDR
  .m_axi_write_completion_awid         (m_axi_rdma_completion_awid),
  .m_axi_write_completion_awaddr       (m_axi_rdma_completion_awaddr),
  .m_axi_write_completion_awlen        (m_axi_rdma_completion_awlen),
  .m_axi_write_completion_awsize       (m_axi_rdma_completion_awsize),
  .m_axi_write_completion_awburst      (m_axi_rdma_completion_awburst),
  .m_axi_write_completion_awcache      (m_axi_rdma_completion_awcache),
  .m_axi_write_completion_awprot       (m_axi_rdma_completion_awprot),
  .m_axi_write_completion_awvalid      (m_axi_rdma_completion_awvalid),
  .m_axi_write_completion_awready      (m_axi_rdma_completion_awready),
  .m_axi_write_completion_wdata        (m_axi_rdma_completion_wdata),
  .m_axi_write_completion_wstrb        (m_axi_rdma_completion_wstrb),
  .m_axi_write_completion_wlast        (m_axi_rdma_completion_wlast),
  .m_axi_write_completion_wvalid       (m_axi_rdma_completion_wvalid),
  .m_axi_write_completion_wready       (m_axi_rdma_completion_wready),
  .m_axi_write_completion_awlock       (m_axi_rdma_completion_awlock),
  .m_axi_write_completion_bid          (m_axi_rdma_completion_bid),
  .m_axi_write_completion_bresp        (m_axi_rdma_completion_bresp),
  .m_axi_write_completion_bvalid       (m_axi_rdma_completion_bvalid),
  .m_axi_write_completion_bready       (m_axi_rdma_completion_bready),
  .m_axi_write_completion_arid         (m_axi_rdma_completion_arid),
  .m_axi_write_completion_araddr       (m_axi_rdma_completion_araddr),
  .m_axi_write_completion_arlen        (m_axi_rdma_completion_arlen),
  .m_axi_write_completion_arsize       (m_axi_rdma_completion_arsize),
  .m_axi_write_completion_arburst      (m_axi_rdma_completion_arburst),
  .m_axi_write_completion_arcache      (m_axi_rdma_completion_arcache),
  .m_axi_write_completion_arprot       (m_axi_rdma_completion_arprot),
  .m_axi_write_completion_arvalid      (m_axi_rdma_completion_arvalid),
  .m_axi_write_completion_arready      (m_axi_rdma_completion_arready),
  .m_axi_write_completion_rid          (m_axi_rdma_completion_rid),
  .m_axi_write_completion_rdata        (m_axi_rdma_completion_rdata),
  .m_axi_write_completion_rresp        (m_axi_rdma_completion_rresp),
  .m_axi_write_completion_rlast        (m_axi_rdma_completion_rlast),
  .m_axi_write_completion_rvalid       (m_axi_rdma_completion_rvalid),
  .m_axi_write_completion_rready       (m_axi_rdma_completion_rready),
  .m_axi_write_completion_arlock       (m_axi_rdma_completion_arlock),

  // TODO: In the current implementation, we do not consider hardware handshaking from user logic
  // HW handshaking from user logic: Send WQE completion queue doorbell
  .resp_hndler_o_send_cq_db_cnt_valid(resp_hndler_o_send_cq_db_cnt_valid),
  .resp_hndler_o_send_cq_db_addr     (resp_hndler_o_send_cq_db_addr),
  .resp_hndler_o_send_cq_db_cnt      (resp_hndler_o_send_cq_db_cnt),
  .resp_hndler_i_send_cq_db_rdy      (resp_hndler_i_send_cq_db_rdy),

  // HW handshaking from user logic: Send WQE producer index doorbell
  .i_qp_sq_pidb_hndshk               (i_qp_sq_pidb_hndshk),
  .i_qp_sq_pidb_wr_addr_hndshk       (i_qp_sq_pidb_wr_addr_hndshk),
  .i_qp_sq_pidb_wr_valid_hndshk      (i_qp_sq_pidb_wr_valid_hndshk),
  .o_qp_sq_pidb_wr_rdy               (o_qp_sq_pidb_wr_rdy),

  // HW handshaking from user logic: RDMA-Send consumer index doorbell
  .i_qp_rq_cidb_hndshk               (i_qp_rq_cidb_hndshk),
  .i_qp_rq_cidb_wr_addr_hndshk       (i_qp_rq_cidb_wr_addr_hndshk),
  .i_qp_rq_cidb_wr_valid_hndshk      (i_qp_rq_cidb_wr_valid_hndshk),
  .o_qp_rq_cidb_wr_rdy               (o_qp_rq_cidb_wr_rdy),

  // HW handshaking from user logic: RDMA-Send producer index doorbell
  .rx_pkt_hndler_o_rq_db_data        (rx_pkt_hndler_o_rq_db_data),
  .rx_pkt_hndler_o_rq_db_addr        (rx_pkt_hndler_o_rq_db_addr),
  .rx_pkt_hndler_o_rq_db_data_valid  (rx_pkt_hndler_o_rq_db_data_valid),
  .rx_pkt_hndler_i_rq_db_rdy         (rx_pkt_hndler_i_rq_db_rdy),

  .rnic_intr    (rdma2_intr),

  .mod_rstn     (axil_rstn),
  .mod_rst_done (rdma2_rst_done),
  //.rdma_resetn_done (rdma_resetn_done),
  .axil_clk     (axil_clk),
  .axis_clk     (axis_clk)
);


// =========== axil_reg_control ==============

string traffic_filename            = "";
string table_filename              = "";
string rsp_table_filename          = "";
string golden_resp_filename        = "";
string get_req_feedback_filename   = "";
string axi_read_info_filename      = "";
string axi_dev_mem_filename        = "rdma_dev_mem";
string axi_sys_mem_filename        = "rdma_sys_mem";
string rdma_combined_cfg_filename  = "rdma_combined_config";
string rdma1_stat_filename         = "rdma1_stat_reg_config";
string rdma2_combined_cfg_filename = "rdma2_combined_config";
string rdma2_stat_reg_cfg_filename = "rdma2_stat_reg_config";
string rdma2_recv_cfg_filename     = "rdma2_per_q_recv_config";

/* Declaration of remote RDMA peer */
logic start_config_rdma2;
logic finish_config_rdma2;
logic start_rdma2_stat;
logic finish_rdma2_stat;
logic start_checking_recv_rdma2;
logic checking_recv_rdma2;
logic [1:0] start_checking_recv_rdma2_cdc;



logic init_sys_mem_done;
logic init_dev_mem_done;
assign start_config_rdma2 = init_sys_mem_done && init_dev_mem_done;

// RDMA AXI4-Lite register configuration channel for the remote RDMA peer
logic        s_axil_rdma2_reg_awvalid;
logic [31:0] s_axil_rdma2_reg_awaddr;
logic        s_axil_rdma2_reg_awready;
logic        s_axil_rdma2_reg_wvalid;
logic [31:0] s_axil_rdma2_reg_wdata;
logic        s_axil_rdma2_reg_wready;
logic        s_axil_rdma2_reg_bvalid;
logic  [1:0] s_axil_rdma2_reg_bresp;
logic        s_axil_rdma2_reg_bready;
logic        s_axil_rdma2_reg_arvalid;
logic [31:0] s_axil_rdma2_reg_araddr;
logic        s_axil_rdma2_reg_arready;
logic        s_axil_rdma2_reg_rvalid;
logic [31:0] s_axil_rdma2_reg_rdata;
logic  [1:0] s_axil_rdma2_reg_rresp;
logic        s_axil_rdma2_reg_rready;

// Configure the remote RDMA
axil_reg_control config_reg_config_rdma2 (
  .which_rdma        ("rdma2"),
  .rdma_cfg_filename (rdma2_combined_cfg_filename),
  .rdma_recv_cfg_filename(""),
  .rdma_stat_filename(""),
  .start_config_rdma (start_config_rdma2),    //handled by init_mems
  .finish_config_rdma(finish_config_rdma2),
  .start_checking_recv(1'b0),
  .start_rdma_stat   (1'b0),
  .finish_rdma_stat  (),
  .m_axil_reg_awvalid(s_axil_rdma2_reg_awvalid),
  .m_axil_reg_awaddr (s_axil_rdma2_reg_awaddr),
  .m_axil_reg_awready(s_axil_rdma2_reg_awready),
  .m_axil_reg_wvalid (s_axil_rdma2_reg_wvalid),
  .m_axil_reg_wdata  (s_axil_rdma2_reg_wdata),
  .m_axil_reg_wready (s_axil_rdma2_reg_wready),
  .m_axil_reg_bvalid (s_axil_rdma2_reg_bvalid),
  .m_axil_reg_bresp  (s_axil_rdma2_reg_bresp),
  .m_axil_reg_bready (s_axil_rdma2_reg_bready),
  .m_axil_reg_arvalid(s_axil_rdma2_reg_arvalid),
  .m_axil_reg_araddr (s_axil_rdma2_reg_araddr),
  .m_axil_reg_arready(s_axil_rdma2_reg_arready),
  .m_axil_reg_rvalid (s_axil_rdma2_reg_rvalid),
  .m_axil_reg_rdata  (s_axil_rdma2_reg_rdata),
  .m_axil_reg_rresp  (s_axil_rdma2_reg_rresp),
  .m_axil_reg_rready (s_axil_rdma2_reg_rready),
  .axil_clk          (axil_clk),
  .axil_rstn         (axil_rstn)
);

// RDMA AXI4-Lite status register channel for the remote RDMA peer
logic        s_axil_rdma2_stat_awvalid;
logic [31:0] s_axil_rdma2_stat_awaddr;
logic        s_axil_rdma2_stat_awready;
logic        s_axil_rdma2_stat_wvalid;
logic [31:0] s_axil_rdma2_stat_wdata;
logic        s_axil_rdma2_stat_wready;
logic        s_axil_rdma2_stat_bvalid;
logic  [1:0] s_axil_rdma2_stat_bresp;
logic        s_axil_rdma2_stat_bready;
logic        s_axil_rdma2_stat_arvalid;
logic [31:0] s_axil_rdma2_stat_araddr;
logic        s_axil_rdma2_stat_arready;
logic        s_axil_rdma2_stat_rvalid;
logic [31:0] s_axil_rdma2_stat_rdata;
logic  [1:0] s_axil_rdma2_stat_rresp;
logic        s_axil_rdma2_stat_rready;

// Configure the remote RDMA
axil_reg_control read_rdma2_stat_reg (
  .which_rdma        ("rdma2"),
  .rdma_cfg_filename (""),
  .rdma_recv_cfg_filename(""),
  .rdma_stat_filename(rdma2_stat_reg_cfg_filename),
  .start_config_rdma (1'b0),
  .finish_config_rdma(),
  .start_checking_recv(1'b0),
  .start_rdma_stat   (start_rdma2_stat),    // input by top
  .finish_rdma_stat  (finish_rdma2_stat),   // ends simulation
  .m_axil_reg_awvalid(s_axil_rdma2_stat_awvalid),
  .m_axil_reg_awaddr (s_axil_rdma2_stat_awaddr),
  .m_axil_reg_awready(s_axil_rdma2_stat_awready),
  .m_axil_reg_wvalid (s_axil_rdma2_stat_wvalid),
  .m_axil_reg_wdata  (s_axil_rdma2_stat_wdata),
  .m_axil_reg_wready (s_axil_rdma2_stat_wready),
  .m_axil_reg_bvalid (s_axil_rdma2_stat_bvalid),
  .m_axil_reg_bresp  (s_axil_rdma2_stat_bresp),
  .m_axil_reg_bready (s_axil_rdma2_stat_bready),
  .m_axil_reg_arvalid(s_axil_rdma2_stat_arvalid),
  .m_axil_reg_araddr (s_axil_rdma2_stat_araddr),
  .m_axil_reg_arready(s_axil_rdma2_stat_arready),
  .m_axil_reg_rvalid (s_axil_rdma2_stat_rvalid),
  .m_axil_reg_rdata  (s_axil_rdma2_stat_rdata),
  .m_axil_reg_rresp  (s_axil_rdma2_stat_rresp),
  .m_axil_reg_rready (s_axil_rdma2_stat_rready),
  .axil_clk          (axil_clk),
  .axil_rstn         (axil_rstn)
);

// RDMA AXI4-Lite polling register channel for receive operations of the remote RDMA peer
logic        s_axil_rdma2_recv_awvalid;
logic [31:0] s_axil_rdma2_recv_awaddr;
logic        s_axil_rdma2_recv_awready;
logic        s_axil_rdma2_recv_wvalid;
logic [31:0] s_axil_rdma2_recv_wdata;
logic        s_axil_rdma2_recv_wready;
logic        s_axil_rdma2_recv_bvalid;
logic  [1:0] s_axil_rdma2_recv_bresp;
logic        s_axil_rdma2_recv_bready;
logic        s_axil_rdma2_recv_arvalid;
logic [31:0] s_axil_rdma2_recv_araddr;
logic        s_axil_rdma2_recv_arready;
logic        s_axil_rdma2_recv_rvalid;
logic [31:0] s_axil_rdma2_recv_rdata;
logic  [1:0] s_axil_rdma2_recv_rresp;
logic        s_axil_rdma2_recv_rready;

// Polling for receive operations
axil_reg_control read_rdma2_recv_reg (
  .which_rdma        ("rdma2"),
  .rdma_cfg_filename (""),
  .rdma_recv_cfg_filename(rdma2_recv_cfg_filename),
  .rdma_stat_filename(""),
  .start_config_rdma (1'b0),
  .finish_config_rdma(),
  .start_checking_recv(start_checking_recv_rdma2),
  .start_rdma_stat   (1'b0),
  .finish_rdma_stat  (),
  .m_axil_reg_awvalid(s_axil_rdma2_recv_awvalid),
  .m_axil_reg_awaddr (s_axil_rdma2_recv_awaddr),
  .m_axil_reg_awready(s_axil_rdma2_recv_awready),
  .m_axil_reg_wvalid (s_axil_rdma2_recv_wvalid),
  .m_axil_reg_wdata  (s_axil_rdma2_recv_wdata),
  .m_axil_reg_wready (s_axil_rdma2_recv_wready),
  .m_axil_reg_bvalid (s_axil_rdma2_recv_bvalid),
  .m_axil_reg_bresp  (s_axil_rdma2_recv_bresp),
  .m_axil_reg_bready (s_axil_rdma2_recv_bready),
  .m_axil_reg_arvalid(s_axil_rdma2_recv_arvalid),
  .m_axil_reg_araddr (s_axil_rdma2_recv_araddr),
  .m_axil_reg_arready(s_axil_rdma2_recv_arready),
  .m_axil_reg_rvalid (s_axil_rdma2_recv_rvalid),
  .m_axil_reg_rdata  (s_axil_rdma2_recv_rdata),
  .m_axil_reg_rresp  (s_axil_rdma2_recv_rresp),
  .m_axil_reg_rready (s_axil_rdma2_recv_rready),
  .axil_clk          (axil_clk),
  .axil_rstn         (axil_rstn)
);

// =========== axil_reg_control ==============


axil_3to1_crossbar_wrapper axil_3to1_wrapper (
  // RDMA2 register interface for configuration
  .s_axil_reg_awvalid  (s_axil_rdma2_reg_awvalid),
  .s_axil_reg_awaddr   (s_axil_rdma2_reg_awaddr ),
  .s_axil_reg_awready  (s_axil_rdma2_reg_awready),
  .s_axil_reg_wvalid   (s_axil_rdma2_reg_wvalid ),
  .s_axil_reg_wdata    (s_axil_rdma2_reg_wdata  ),
  .s_axil_reg_wready   (s_axil_rdma2_reg_wready ),
  .s_axil_reg_bvalid   (s_axil_rdma2_reg_bvalid ),
  .s_axil_reg_bresp    (s_axil_rdma2_reg_bresp  ),
  .s_axil_reg_bready   (s_axil_rdma2_reg_bready ),
  .s_axil_reg_arvalid  (s_axil_rdma2_reg_arvalid),
  .s_axil_reg_araddr   (s_axil_rdma2_reg_araddr ),
  .s_axil_reg_arready  (s_axil_rdma2_reg_arready),
  .s_axil_reg_rvalid   (s_axil_rdma2_reg_rvalid ),
  .s_axil_reg_rdata    (s_axil_rdma2_reg_rdata  ),
  .s_axil_reg_rresp    (s_axil_rdma2_reg_rresp  ),
  .s_axil_reg_rready   (s_axil_rdma2_reg_rready ),

  // RDMA2 stat register interface for debug purpose
  .s_axil_stat_awvalid  (s_axil_rdma2_stat_awvalid),
  .s_axil_stat_awaddr   (s_axil_rdma2_stat_awaddr ),
  .s_axil_stat_awready  (s_axil_rdma2_stat_awready),
  .s_axil_stat_wvalid   (s_axil_rdma2_stat_wvalid ),
  .s_axil_stat_wdata    (s_axil_rdma2_stat_wdata  ),
  .s_axil_stat_wready   (s_axil_rdma2_stat_wready ),
  .s_axil_stat_bvalid   (s_axil_rdma2_stat_bvalid ),
  .s_axil_stat_bresp    (s_axil_rdma2_stat_bresp  ),
  .s_axil_stat_bready   (s_axil_rdma2_stat_bready ),
  .s_axil_stat_arvalid  (s_axil_rdma2_stat_arvalid),
  .s_axil_stat_araddr   (s_axil_rdma2_stat_araddr ),
  .s_axil_stat_arready  (s_axil_rdma2_stat_arready),
  .s_axil_stat_rvalid   (s_axil_rdma2_stat_rvalid ),
  .s_axil_stat_rdata    (s_axil_rdma2_stat_rdata  ),
  .s_axil_stat_rresp    (s_axil_rdma2_stat_rresp  ),
  .s_axil_stat_rready   (s_axil_rdma2_stat_rready ),

  // RDMA2 polling interface for receive operations
  .s_axil_recv_awvalid  (s_axil_rdma2_recv_awvalid),
  .s_axil_recv_awaddr   (s_axil_rdma2_recv_awaddr ),
  .s_axil_recv_awready  (s_axil_rdma2_recv_awready),
  .s_axil_recv_wvalid   (s_axil_rdma2_recv_wvalid ),
  .s_axil_recv_wdata    (s_axil_rdma2_recv_wdata  ),
  .s_axil_recv_wready   (s_axil_rdma2_recv_wready ),
  .s_axil_recv_bvalid   (s_axil_rdma2_recv_bvalid ),
  .s_axil_recv_bresp    (s_axil_rdma2_recv_bresp  ),
  .s_axil_recv_bready   (s_axil_rdma2_recv_bready ),
  .s_axil_recv_arvalid  (s_axil_rdma2_recv_arvalid),
  .s_axil_recv_araddr   (s_axil_rdma2_recv_araddr ),
  .s_axil_recv_arready  (s_axil_rdma2_recv_arready),
  .s_axil_recv_rvalid   (s_axil_rdma2_recv_rvalid ),
  .s_axil_recv_rdata    (s_axil_rdma2_recv_rdata  ),
  .s_axil_recv_rresp    (s_axil_rdma2_recv_rresp  ),
  .s_axil_recv_rready   (s_axil_rdma2_recv_rready ),

  .m_axil_awvalid  (axil_rdma2_awvalid),
  .m_axil_awaddr   (axil_rdma2_awaddr ),
  .m_axil_awready  (axil_rdma2_awready),
  .m_axil_wvalid   (axil_rdma2_wvalid ),
  .m_axil_wdata    (axil_rdma2_wdata  ),
  .m_axil_wready   (axil_rdma2_wready ),
  .m_axil_bvalid   (axil_rdma2_bvalid ),
  .m_axil_bresp    (axil_rdma2_bresp  ),
  .m_axil_bready   (axil_rdma2_bready ),
  .m_axil_arvalid  (axil_rdma2_arvalid),
  .m_axil_araddr   (axil_rdma2_araddr ),
  .m_axil_arready  (axil_rdma2_arready),
  .m_axil_rvalid   (axil_rdma2_rvalid ),
  .m_axil_rdata    (axil_rdma2_rdata  ),
  .m_axil_rresp    (axil_rdma2_rresp  ),
  .m_axil_rready   (axil_rdma2_rready ),  

  .axil_clk (axil_clk),
  .axil_rstn(axil_rstn)
);

endmodule: rn_tb_2rdma_top_remote
