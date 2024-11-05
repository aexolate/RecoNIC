#!/bin/bash
#==============================================================================
# Copyright (C) 2023, Advanced Micro Devices, Inc. All rights reserved.
# SPDX-License-Identifier: MIT
#
#==============================================================================
set -Eeuo pipefail

echo -e "simulate.sh - RecoNIC simulation with RoCEv2 packets"

VIVADO_VERSION=2021.2
QUESTA_VERSION=2020.4

cur_dir=$(pwd)
sim_dir=$(dirname $cur_dir)
build_dir=${sim_dir}/build
root_dir=$(dirname $sim_dir)
sim_src_dir=${sim_dir}/src
sim_script_dir=${sim_dir}/scripts

sb_pcisocket=""
sb_shmpath=""
sb_syncperiod=""
sb_pcilat=""
sb_name=""
sb_side=0


# Vivado xsim main
run_xsim()
{
  echo "current director: $(pwd)"
  copy_test_data $1

  top_module_name="$3"
  top_module_opt="${top_module_name}_opt"

  # Compile
  source xsim_compile.do 2>&1 | tee -a xsim_compile.log

  # Elaborate reco
  if [[ "$3" == "cl_tb_top" ]]; then
      xelab --incr --relax --debug typical --mt auto \
          -L reco \
          -L ernic_v3_1_1 \
          -L xilinx_vip \
          -L xpm \
          -L cam_v2_2_2 \
          -L vitis_net_p4_v1_0_2 \
          -L axi_protocol_checker_v2_0_8 \
          -L unisims_ver \
          -L unimacro_ver \
          -L secureip \
          --snapshot $top_module_opt reco.cl_tb_top reco.glbl \
          -log xsim_elaborate.log
  elif [[ "$3" == "rn_tb_2rdma_top" ]]; then

      if [[ $sb_side -eq 0 ]]; then
        top_module_selected="reco.rn_tb_2rdma_top"
      else
        top_module_selected="reco.rn_tb_2rdma_top_remote"
      fi

      xelab --incr --relax --debug typical --mt auto \
          --sv_root /home/gexl/Desktop/reconic_adapter/simbricks \
          --sv_lib xsim_adapter \
          --generic_top SIMBRICKS_PCI_SOCKET=$sb_pcisocket \
          --generic_top SHM_PATH=$sb_shmpath \
          --generic_top SYNC_PERIOD=$sb_syncperiod \
          --generic_top PCI_LATENCY=$sb_pcilat \
          -L reco \
          -L ernic_v3_1_1 \
          -L xilinx_vip \
          -L xpm \
          -L cam_v2_2_2 \
          -L vitis_net_p4_v1_0_2 \
          -L axi_protocol_checker_v2_0_8 \
          -L unisims_ver \
          -L unimacro_ver \
          -L secureip \
          --snapshot "${top_module_opt}_${sb_name}" $top_module_selected reco.glbl \
          -log xsim_elaborate.log
  else 
      xelab --incr --relax --debug typical --mt auto \
          -L reco \
          -L ernic_v3_1_1 \
          -L xilinx_vip \
          -L xpm \
          -L cam_v2_2_2 \
          -L vitis_net_p4_v1_0_2 \
          -L axi_protocol_checker_v2_0_8 \
          -L unisims_ver \
          -L unimacro_ver \
          -L secureip \
          --snapshot $top_module_opt reco.rn_tb_top reco.glbl \
          -log xsim_elaborate.log
  fi

  # Simulate
  if [[ $2 == "off" ]]; then
    xsim "${top_module_opt}_${sb_name}" -key {Behavioral:sim_1:Functional:${top_module_name}} -tclbatch xsim_tb_top.tcl -log xsim_simulate.log
  else
    xsim -g $top_module_opt -key {Behavioral:sim_1:Functional:${top_module_name}} -tclbatch xsim_tb_top.tcl -log xsim_simulate.log
  fi
}

# Copy test data
copy_test_data()
{
  if [[ -f "$sim_script_dir/packets.txt" ]]; then
    # Remove old test data files
    rm ${sim_script_dir}/*.txt
  fi

  if [[ ($1 != "") ]]; then
    test_data_path=${sim_dir}/testcases/"$1"
  fi
  echo "INFO: testcase data path: $test_data_path"
  cp ${test_data_path}/*.txt ${sim_script_dir}
}

clean()
{
  if [[ -d "${build_dir}/questa_lib" ]]; then
    rm -rf ${build_dir}/questa_lib
    rm ${sim_dir}/scripts/modelsim.ini
    if [[ -f "${sim_dir}/scripts/transcript" ]]; then
      rm -rf ${sim_dir}/scripts/transcript
    fi   
  fi

  if [[ -d "${build_dir}/xsim.dir" ]]; then
    rm -rf ${build_dir}/xsim.dir

    if [[ -f "${sim_dir}/scripts/vivado.jou" ]]; then
      rm -rf ${sim_dir}/scripts/*.jou
    fi

    if compgen -G "${sim_dir}/scripts/*.jou" > /dev/null; then
      rm ${sim_dir}/scripts/*.jou
    fi

    if compgen -G "${sim_dir}/scripts/*.wdb" > /dev/null; then
      rm ${sim_dir}/scripts/*.wdb
    fi

    if compgen -G "${sim_dir}/scripts/*.debug" > /dev/null; then
      rm ${sim_dir}/scripts/*.debug
    fi

    files_to_remove=(${sim_dir}/scripts/rn_tb_top_opt.wdb ${sim_dir}/scripts/vsim.wlf ${sim_dir}/scripts/xelab.pb ${sim_dir}/scripts/.Xil ${sim_dir}/scripts/xsim.dir ${sim_dir}/scripts/xvhdl.pb ${sim_dir}/scripts/xvlog.pb)
    for ((i=0; i<${#files_to_remove[*]}; i++)); do
      file="${files_to_remove[i]}"
      if [[ -e $file ]]; then
        rm -rf $file
      fi
    done
  fi

  if compgen -G "${sim_dir}/scripts/*.log" > /dev/null; then
    rm ${sim_dir}/scripts/*.log
  fi

  if [[ -f "${sim_dir}/scripts/packets.txt" ]]; then
    rm ${sim_dir}/scripts/*.txt
  fi

  echo -e "INFO: Simulation files are deleted.\n"
  exit 0
}

# Script usage
usage()
{
  msg="Usage: simulate.sh [-h|--help]\n\
Usage: simulate.sh -top rn_tb_top -g on|off [-t <testcase folder name>] [-s xsim]\n\
[-h|--help]\n\
\t Print help information for this script\n\
[-top top_module]\n\
\t Top module name in testbenches
[-s|--simulator questasim|xsim]\n\
\t Use questa-sim or xsim for simulation. Default is questa-sim\n\
[-t|--testcase <testcase_folder_name>]\n\
\t Testcase folder name\n\
[-g|--gui on|off]\n\
\t Open questasim/xsim in gui or command-line mode\n\
[-c|--clean]\n\
\t Clean build folder\n\n\
Example: ./simulate -t get -s questasim -g on\n"
  echo -e $msg
  exit 1
}

while [[ $# -gt 0 ]]; do
  key="$1"

  case $key in
    -h|--help)
      usage
      ;;
    -top)
      top_module=$2
      shift
      shift
      ;;
    -g|--gui)
      gui="$2"
      shift
      shift
      ;;
    -s|--simulator)
      simulator="$2"
      shift
      shift
      ;;
    -t|--testcase)
      testcase="$2"
      shift
      shift
      ;;
    -c|--clean)
      clean
      shift 
      ;;
    -sb_pcisocket)
      sb_pcisocket="$2"
      shift
      shift
      ;;
    -sb_shmpath)
      sb_shmpath="$2"
      shift
      shift
      ;;
    -sb_syncperiod)
      sb_syncperiod="$2"
      shift
      shift
      ;;
    -sb_pcilat)
      sb_pcilat="$2"
      shift
      shift
      ;;
    -sb_name)
      sb_name="$2"
      shift
      shift
      ;;
    -sb_side)
      sb_side="$2"
      shift
      shift
      ;;
    *) # Invalid option
      echo "ERROR: Invalid option"
      usage
      ;;
  esac
done

if [[ $top_module == "" ]]; then
  echo "ERROR: Please provide top module name of the testbenches"
  usage
fi

echo "INFO: Using PCI Socket: $sb_pcisocket"
echo "INFO: Using SHM Path: $sb_shmpath"
echo "INFO: Using Sync Period: $sb_syncperiod"
echo "INFO: Using PCI Latency: $sb_pcilat"
echo "INFO: Using Name: $sb_name"

if [[ $simulator == "questasim" ]]; then
  echo "INFO: Start questasim simulation"
  run_questasim $testcase $gui $top_module
elif [[ $simulator == "xsim" ]]; then
  echo "INFO: Start xsim simulation"
  run_xsim $testcase $gui $top_module
else
  echo "ERROR: Simulator not supported. Please use either questasim or xsim"
  usage
fi