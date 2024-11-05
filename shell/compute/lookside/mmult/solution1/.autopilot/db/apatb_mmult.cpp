#include <systemc>
#include <iostream>
#include <cstdlib>
#include <cstddef>
#include <stdint.h>
#include "SysCFileHandler.h"
#include "ap_int.h"
#include "ap_fixed.h"
#include <complex>
#include <stdbool.h>
#include "autopilot_cbe.h"
#include "hls_stream.h"
#include "hls_half.h"
#include "hls_signal_handler.h"

using namespace std;
using namespace sc_core;
using namespace sc_dt;

// wrapc file define:
#define AUTOTB_TVIN_systolic "../tv/cdatafile/c.mmult.autotvin_systolic.dat"
#define AUTOTB_TVOUT_systolic "../tv/cdatafile/c.mmult.autotvout_systolic.dat"
// wrapc file define:
#define AUTOTB_TVIN_work_id_out_stream "../tv/cdatafile/c.mmult.autotvin_work_id_out_stream.dat"
#define AUTOTB_TVOUT_work_id_out_stream "../tv/cdatafile/c.mmult.autotvout_work_id_out_stream.dat"
#define WRAPC_STREAM_SIZE_OUT_work_id_out_stream "../tv/stream_size/stream_size_out_work_id_out_stream.dat"
#define WRAPC_STREAM_EGRESS_STATUS_work_id_out_stream "../tv/stream_size/stream_egress_status_work_id_out_stream.dat"
// wrapc file define:
#define AUTOTB_TVIN_a "../tv/cdatafile/c.mmult.autotvin_a.dat"
#define AUTOTB_TVOUT_a "../tv/cdatafile/c.mmult.autotvout_a.dat"
// wrapc file define:
#define AUTOTB_TVIN_b "../tv/cdatafile/c.mmult.autotvin_b.dat"
#define AUTOTB_TVOUT_b "../tv/cdatafile/c.mmult.autotvout_b.dat"
// wrapc file define:
#define AUTOTB_TVIN_c "../tv/cdatafile/c.mmult.autotvin_c.dat"
#define AUTOTB_TVOUT_c "../tv/cdatafile/c.mmult.autotvout_c.dat"
// wrapc file define:
#define AUTOTB_TVIN_a_row "../tv/cdatafile/c.mmult.autotvin_a_row.dat"
#define AUTOTB_TVOUT_a_row "../tv/cdatafile/c.mmult.autotvout_a_row.dat"
// wrapc file define:
#define AUTOTB_TVIN_a_col "../tv/cdatafile/c.mmult.autotvin_a_col.dat"
#define AUTOTB_TVOUT_a_col "../tv/cdatafile/c.mmult.autotvout_a_col.dat"
// wrapc file define:
#define AUTOTB_TVIN_b_col "../tv/cdatafile/c.mmult.autotvin_b_col.dat"
#define AUTOTB_TVOUT_b_col "../tv/cdatafile/c.mmult.autotvout_b_col.dat"
// wrapc file define:
#define AUTOTB_TVIN_work_id "../tv/cdatafile/c.mmult.autotvin_work_id.dat"
#define AUTOTB_TVOUT_work_id "../tv/cdatafile/c.mmult.autotvout_work_id.dat"

#define INTER_TCL "../tv/cdatafile/ref.tcl"

// tvout file define:
#define AUTOTB_TVOUT_PC_systolic "../tv/rtldatafile/rtl.mmult.autotvout_systolic.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_work_id_out_stream "../tv/rtldatafile/rtl.mmult.autotvout_work_id_out_stream.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_a "../tv/rtldatafile/rtl.mmult.autotvout_a.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_b "../tv/rtldatafile/rtl.mmult.autotvout_b.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_c "../tv/rtldatafile/rtl.mmult.autotvout_c.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_a_row "../tv/rtldatafile/rtl.mmult.autotvout_a_row.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_a_col "../tv/rtldatafile/rtl.mmult.autotvout_a_col.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_b_col "../tv/rtldatafile/rtl.mmult.autotvout_b_col.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_work_id "../tv/rtldatafile/rtl.mmult.autotvout_work_id.dat"


inline void rev_endian(char* p, size_t nbytes)
{
  std::reverse(p, p+nbytes);
}

template<size_t bit_width>
struct transaction {
  typedef uint64_t depth_t;
  static const size_t wbytes = (bit_width+7)>>3;
  static const size_t dbytes = sizeof(depth_t);
  const depth_t depth;
  const size_t vbytes;
  const size_t tbytes;
  char * const p;
  typedef char (*p_dat)[wbytes];
  p_dat vp;

  void reorder() {
    rev_endian(p, dbytes);
    p_dat vp = (p_dat) (p+dbytes);
    for (depth_t i = 0; i < depth; ++i) {
      rev_endian(vp[i], wbytes);
    }
  }

  transaction(depth_t depth)
    : depth(depth), vbytes(wbytes*depth), tbytes(dbytes+vbytes),
      p(new char[tbytes]) {
    *(depth_t*)p = depth;
    vp = (p_dat) (p+dbytes);
  }

  template<size_t psize>
  void import(char* param, depth_t num, int64_t offset) {
    param -= offset*psize;
    for (depth_t i = 0; i < num; ++i) {
      memcpy(vp[i], param, wbytes);
      param += psize;
    }
    vp += num;
  }

  template<size_t psize>
  void send(char* param, depth_t num) {
    for (depth_t i = 0; i < num; ++i) {
      memcpy(param, vp[i], wbytes);
      param += psize;
    }
    vp += num;
  }

  template<size_t psize>
  void send(char* param, depth_t num, int64_t skip) {
    for (depth_t i = 0; i < num; ++i) {
      memcpy(param, vp[skip+i], wbytes);
      param += psize;
    }
  }

  ~transaction() { if (p) { delete[] p; } }
};
      

inline const std::string begin_str(int num)
{
  return std::string("[[transaction]] ")
         .append(std::to_string(num))
         .append("\n");
}

inline const std::string end_str()
{
  return std::string("[[/transaction]] \n");
}
      
class INTER_TCL_FILE {
  public:
INTER_TCL_FILE(const char* name) {
  mName = name; 
  systolic_depth = 0;
  work_id_out_stream_depth = 0;
  a_depth = 0;
  b_depth = 0;
  c_depth = 0;
  a_row_depth = 0;
  a_col_depth = 0;
  b_col_depth = 0;
  work_id_depth = 0;
  trans_num =0;
}
~INTER_TCL_FILE() {
  mFile.open(mName);
  if (!mFile.good()) {
    cout << "Failed to open file ref.tcl" << endl;
    exit (1); 
  }
  string total_list = get_depth_list();
  mFile << "set depth_list {\n";
  mFile << total_list;
  mFile << "}\n";
  mFile << "set trans_num "<<trans_num<<endl;
  mFile.close();
}
string get_depth_list () {
  stringstream total_list;
  total_list << "{systolic " << systolic_depth << "}\n";
  total_list << "{work_id_out_stream " << work_id_out_stream_depth << "}\n";
  total_list << "{a " << a_depth << "}\n";
  total_list << "{b " << b_depth << "}\n";
  total_list << "{c " << c_depth << "}\n";
  total_list << "{a_row " << a_row_depth << "}\n";
  total_list << "{a_col " << a_col_depth << "}\n";
  total_list << "{b_col " << b_col_depth << "}\n";
  total_list << "{work_id " << work_id_depth << "}\n";
  return total_list.str();
}
void set_num (int num , int* class_num) {
  (*class_num) = (*class_num) > num ? (*class_num) : num;
}
void set_string(std::string list, std::string* class_list) {
  (*class_list) = list;
}
  public:
    int systolic_depth;
    int work_id_out_stream_depth;
    int a_depth;
    int b_depth;
    int c_depth;
    int a_row_depth;
    int a_col_depth;
    int b_col_depth;
    int work_id_depth;
    int trans_num;
  private:
    ofstream mFile;
    const char* mName;
};

static bool RTLOutputCheckAndReplacement(std::string &AESL_token, std::string PortName) {
  bool err = false;
  size_t x_found;

  // search and replace 'X' with '0' from the 3rd char of token
  while ((x_found = AESL_token.find('X', 0)) != string::npos)
    err = true, AESL_token.replace(x_found, 1, "0");
  
  // search and replace 'x' with '0' from the 3rd char of token
  while ((x_found = AESL_token.find('x', 2)) != string::npos)
    err = true, AESL_token.replace(x_found, 1, "0");
  
  return err;}
struct __cosim_s40__ { char data[64]; };
extern "C" void mmult_hw_stub_wrapper(volatile void *, volatile void *, volatile void *, volatile void *, int, int, int, int);

extern "C" void apatb_mmult_hw(volatile void * __xlx_apatb_param_work_id_out_stream, volatile void * __xlx_apatb_param_a, volatile void * __xlx_apatb_param_b, volatile void * __xlx_apatb_param_c, int __xlx_apatb_param_a_row, int __xlx_apatb_param_a_col, int __xlx_apatb_param_b_col, int __xlx_apatb_param_work_id) {
  refine_signal_handler();
  fstream wrapc_switch_file_token;
  wrapc_switch_file_token.open(".hls_cosim_wrapc_switch.log");
static AESL_FILE_HANDLER aesl_fh;
  int AESL_i;
  if (wrapc_switch_file_token.good())
  {

    CodeState = ENTER_WRAPC_PC;
    static unsigned AESL_transaction_pc = 0;
    string AESL_token;
    string AESL_num;
#ifdef USE_BINARY_TV_FILE
{
transaction<512> tr(3);
aesl_fh.read(AUTOTB_TVOUT_PC_systolic, tr.p, tr.tbytes);
tr.reorder();
tr.send<64>((char*)__xlx_apatb_param_a, 1);
tr.send<64>((char*)__xlx_apatb_param_b, 1);
tr.send<64>((char*)__xlx_apatb_param_c, 1);
}
#else
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_systolic);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<512> > systolic_pc_buffer(3);
          int i = 0;
          bool has_unknown_value = false;
          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            has_unknown_value |= RTLOutputCheckAndReplacement(AESL_token, "systolic");
  
            // push token into output port buffer
            if (AESL_token != "") {
              systolic_pc_buffer[i] = AESL_token.c_str();;
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (has_unknown_value) {
            cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'x' or 'X' on port " 
                 << "systolic" << ", possible cause: There are uninitialized variables in the C design."
                 << endl; 
          }
  
          if (i > 0) {{
            int i = 0;
            for (int j = 0, e = 1; j < e; j += 1, ++i) {((long long*)__xlx_apatb_param_a)[j*8+0] = systolic_pc_buffer[i].range(63,0).to_int64();
((long long*)__xlx_apatb_param_a)[j*8+1] = systolic_pc_buffer[i].range(127,64).to_int64();
((long long*)__xlx_apatb_param_a)[j*8+2] = systolic_pc_buffer[i].range(191,128).to_int64();
((long long*)__xlx_apatb_param_a)[j*8+3] = systolic_pc_buffer[i].range(255,192).to_int64();
((long long*)__xlx_apatb_param_a)[j*8+4] = systolic_pc_buffer[i].range(319,256).to_int64();
((long long*)__xlx_apatb_param_a)[j*8+5] = systolic_pc_buffer[i].range(383,320).to_int64();
((long long*)__xlx_apatb_param_a)[j*8+6] = systolic_pc_buffer[i].range(447,384).to_int64();
((long long*)__xlx_apatb_param_a)[j*8+7] = systolic_pc_buffer[i].range(511,448).to_int64();
}
            for (int j = 0, e = 1; j < e; j += 1, ++i) {((long long*)__xlx_apatb_param_b)[j*8+0] = systolic_pc_buffer[i].range(63,0).to_int64();
((long long*)__xlx_apatb_param_b)[j*8+1] = systolic_pc_buffer[i].range(127,64).to_int64();
((long long*)__xlx_apatb_param_b)[j*8+2] = systolic_pc_buffer[i].range(191,128).to_int64();
((long long*)__xlx_apatb_param_b)[j*8+3] = systolic_pc_buffer[i].range(255,192).to_int64();
((long long*)__xlx_apatb_param_b)[j*8+4] = systolic_pc_buffer[i].range(319,256).to_int64();
((long long*)__xlx_apatb_param_b)[j*8+5] = systolic_pc_buffer[i].range(383,320).to_int64();
((long long*)__xlx_apatb_param_b)[j*8+6] = systolic_pc_buffer[i].range(447,384).to_int64();
((long long*)__xlx_apatb_param_b)[j*8+7] = systolic_pc_buffer[i].range(511,448).to_int64();
}
            for (int j = 0, e = 1; j < e; j += 1, ++i) {((long long*)__xlx_apatb_param_c)[j*8+0] = systolic_pc_buffer[i].range(63,0).to_int64();
((long long*)__xlx_apatb_param_c)[j*8+1] = systolic_pc_buffer[i].range(127,64).to_int64();
((long long*)__xlx_apatb_param_c)[j*8+2] = systolic_pc_buffer[i].range(191,128).to_int64();
((long long*)__xlx_apatb_param_c)[j*8+3] = systolic_pc_buffer[i].range(255,192).to_int64();
((long long*)__xlx_apatb_param_c)[j*8+4] = systolic_pc_buffer[i].range(319,256).to_int64();
((long long*)__xlx_apatb_param_c)[j*8+5] = systolic_pc_buffer[i].range(383,320).to_int64();
((long long*)__xlx_apatb_param_c)[j*8+6] = systolic_pc_buffer[i].range(447,384).to_int64();
((long long*)__xlx_apatb_param_c)[j*8+7] = systolic_pc_buffer[i].range(511,448).to_int64();
}}}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  #endif
long __xlx_apatb_param_work_id_out_stream_stream_buf_final_size;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(WRAPC_STREAM_SIZE_OUT_work_id_out_stream);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){__xlx_apatb_param_work_id_out_stream_stream_buf_final_size = atoi(AESL_token.c_str());

            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  {
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_work_id_out_stream);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<32> > work_id_out_stream_pc_buffer;
          int i = 0;
          bool has_unknown_value = false;
          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            has_unknown_value |= RTLOutputCheckAndReplacement(AESL_token, "work_id_out_stream");
  
            // push token into output port buffer
            if (AESL_token != "") {
              work_id_out_stream_pc_buffer.push_back(AESL_token.c_str());
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (has_unknown_value) {
            cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'x' or 'X' on port " 
                 << "work_id_out_stream" << ", possible cause: There are uninitialized variables in the C design."
                 << endl; 
          }
  
          if (i > 0) {for (int j = 0, e = i; j != e; ++j) {
int xlx_stream_elt;
((char*)&xlx_stream_elt)[0*4+0] = work_id_out_stream_pc_buffer[j].range(7, 0).to_int64();
((char*)&xlx_stream_elt)[0*4+1] = work_id_out_stream_pc_buffer[j].range(15, 8).to_int64();
((char*)&xlx_stream_elt)[0*4+2] = work_id_out_stream_pc_buffer[j].range(23, 16).to_int64();
((char*)&xlx_stream_elt)[0*4+3] = work_id_out_stream_pc_buffer[j].range(31, 24).to_int64();
((hls::stream<int>*)__xlx_apatb_param_work_id_out_stream)->write(xlx_stream_elt);
}
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  
    AESL_transaction_pc++;
    return ;
  }
static unsigned AESL_transaction;
static INTER_TCL_FILE tcl_file(INTER_TCL);
std::vector<char> __xlx_sprintf_buffer(1024);
CodeState = ENTER_WRAPC;
aesl_fh.touch(WRAPC_STREAM_SIZE_OUT_work_id_out_stream);
aesl_fh.touch(WRAPC_STREAM_EGRESS_STATUS_work_id_out_stream);
CodeState = DUMP_INPUTS;
unsigned __xlx_offset_byte_param_a = 0;
unsigned __xlx_offset_byte_param_b = 0;
unsigned __xlx_offset_byte_param_c = 0;
#ifdef USE_BINARY_TV_FILE
{
aesl_fh.touch(AUTOTB_TVIN_systolic, 'b');
transaction<512> tr(3);
  __xlx_offset_byte_param_a = 0*64;
  if (__xlx_apatb_param_a) {
tr.import<64>((char*)__xlx_apatb_param_a, 1, 0);
  }
  __xlx_offset_byte_param_b = 1*64;
  if (__xlx_apatb_param_b) {
tr.import<64>((char*)__xlx_apatb_param_b, 1, 0);
  }
  __xlx_offset_byte_param_c = 2*64;
  if (__xlx_apatb_param_c) {
tr.import<64>((char*)__xlx_apatb_param_c, 1, 0);
  }
tr.reorder();
aesl_fh.write(AUTOTB_TVIN_systolic, tr.p, tr.tbytes);
}

  tcl_file.set_num(3, &tcl_file.systolic_depth);
#else
// print systolic Transactions
{
aesl_fh.write(AUTOTB_TVIN_systolic, begin_str(AESL_transaction));
{
  __xlx_offset_byte_param_a = 0*64;
  if (__xlx_apatb_param_a) {
    for (int j = 0  - 0, e = 1 - 0; j != e; ++j) {
sc_bv<512> __xlx_tmp_lv;
__xlx_tmp_lv.range(63,0) = ((long long*)__xlx_apatb_param_a)[j*8+0];
__xlx_tmp_lv.range(127,64) = ((long long*)__xlx_apatb_param_a)[j*8+1];
__xlx_tmp_lv.range(191,128) = ((long long*)__xlx_apatb_param_a)[j*8+2];
__xlx_tmp_lv.range(255,192) = ((long long*)__xlx_apatb_param_a)[j*8+3];
__xlx_tmp_lv.range(319,256) = ((long long*)__xlx_apatb_param_a)[j*8+4];
__xlx_tmp_lv.range(383,320) = ((long long*)__xlx_apatb_param_a)[j*8+5];
__xlx_tmp_lv.range(447,384) = ((long long*)__xlx_apatb_param_a)[j*8+6];
__xlx_tmp_lv.range(511,448) = ((long long*)__xlx_apatb_param_a)[j*8+7];
aesl_fh.write(AUTOTB_TVIN_systolic, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
    }
  }
  __xlx_offset_byte_param_b = 1*64;
  if (__xlx_apatb_param_b) {
    for (int j = 0  - 0, e = 1 - 0; j != e; ++j) {
sc_bv<512> __xlx_tmp_lv;
__xlx_tmp_lv.range(63,0) = ((long long*)__xlx_apatb_param_b)[j*8+0];
__xlx_tmp_lv.range(127,64) = ((long long*)__xlx_apatb_param_b)[j*8+1];
__xlx_tmp_lv.range(191,128) = ((long long*)__xlx_apatb_param_b)[j*8+2];
__xlx_tmp_lv.range(255,192) = ((long long*)__xlx_apatb_param_b)[j*8+3];
__xlx_tmp_lv.range(319,256) = ((long long*)__xlx_apatb_param_b)[j*8+4];
__xlx_tmp_lv.range(383,320) = ((long long*)__xlx_apatb_param_b)[j*8+5];
__xlx_tmp_lv.range(447,384) = ((long long*)__xlx_apatb_param_b)[j*8+6];
__xlx_tmp_lv.range(511,448) = ((long long*)__xlx_apatb_param_b)[j*8+7];
aesl_fh.write(AUTOTB_TVIN_systolic, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
    }
  }
  __xlx_offset_byte_param_c = 2*64;
  if (__xlx_apatb_param_c) {
    for (int j = 0  - 0, e = 1 - 0; j != e; ++j) {
sc_bv<512> __xlx_tmp_lv;
__xlx_tmp_lv.range(63,0) = ((long long*)__xlx_apatb_param_c)[j*8+0];
__xlx_tmp_lv.range(127,64) = ((long long*)__xlx_apatb_param_c)[j*8+1];
__xlx_tmp_lv.range(191,128) = ((long long*)__xlx_apatb_param_c)[j*8+2];
__xlx_tmp_lv.range(255,192) = ((long long*)__xlx_apatb_param_c)[j*8+3];
__xlx_tmp_lv.range(319,256) = ((long long*)__xlx_apatb_param_c)[j*8+4];
__xlx_tmp_lv.range(383,320) = ((long long*)__xlx_apatb_param_c)[j*8+5];
__xlx_tmp_lv.range(447,384) = ((long long*)__xlx_apatb_param_c)[j*8+6];
__xlx_tmp_lv.range(511,448) = ((long long*)__xlx_apatb_param_c)[j*8+7];
aesl_fh.write(AUTOTB_TVIN_systolic, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
    }
  }
}

  tcl_file.set_num(3, &tcl_file.systolic_depth);
aesl_fh.write(AUTOTB_TVIN_systolic, end_str());
}

#endif
std::vector<int> __xlx_apatb_param_work_id_out_stream_stream_buf;
long __xlx_apatb_param_work_id_out_stream_stream_buf_size = ((hls::stream<int>*)__xlx_apatb_param_work_id_out_stream)->size();
// print a Transactions
{
aesl_fh.write(AUTOTB_TVIN_a, begin_str(AESL_transaction));
{
    sc_bv<64> __xlx_tmp_lv = __xlx_offset_byte_param_a;
aesl_fh.write(AUTOTB_TVIN_a, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.a_depth);
aesl_fh.write(AUTOTB_TVIN_a, end_str());
}

// print b Transactions
{
aesl_fh.write(AUTOTB_TVIN_b, begin_str(AESL_transaction));
{
    sc_bv<64> __xlx_tmp_lv = __xlx_offset_byte_param_b;
aesl_fh.write(AUTOTB_TVIN_b, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.b_depth);
aesl_fh.write(AUTOTB_TVIN_b, end_str());
}

// print c Transactions
{
aesl_fh.write(AUTOTB_TVIN_c, begin_str(AESL_transaction));
{
    sc_bv<64> __xlx_tmp_lv = __xlx_offset_byte_param_c;
aesl_fh.write(AUTOTB_TVIN_c, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.c_depth);
aesl_fh.write(AUTOTB_TVIN_c, end_str());
}

// print a_row Transactions
{
aesl_fh.write(AUTOTB_TVIN_a_row, begin_str(AESL_transaction));
{
    sc_bv<32> __xlx_tmp_lv = *((int*)&__xlx_apatb_param_a_row);
aesl_fh.write(AUTOTB_TVIN_a_row, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.a_row_depth);
aesl_fh.write(AUTOTB_TVIN_a_row, end_str());
}

// print a_col Transactions
{
aesl_fh.write(AUTOTB_TVIN_a_col, begin_str(AESL_transaction));
{
    sc_bv<32> __xlx_tmp_lv = *((int*)&__xlx_apatb_param_a_col);
aesl_fh.write(AUTOTB_TVIN_a_col, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.a_col_depth);
aesl_fh.write(AUTOTB_TVIN_a_col, end_str());
}

// print b_col Transactions
{
aesl_fh.write(AUTOTB_TVIN_b_col, begin_str(AESL_transaction));
{
    sc_bv<32> __xlx_tmp_lv = *((int*)&__xlx_apatb_param_b_col);
aesl_fh.write(AUTOTB_TVIN_b_col, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.b_col_depth);
aesl_fh.write(AUTOTB_TVIN_b_col, end_str());
}

// print work_id Transactions
{
aesl_fh.write(AUTOTB_TVIN_work_id, begin_str(AESL_transaction));
{
    sc_bv<32> __xlx_tmp_lv = *((int*)&__xlx_apatb_param_work_id);
aesl_fh.write(AUTOTB_TVIN_work_id, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.work_id_depth);
aesl_fh.write(AUTOTB_TVIN_work_id, end_str());
}

CodeState = CALL_C_DUT;
mmult_hw_stub_wrapper(__xlx_apatb_param_work_id_out_stream, __xlx_apatb_param_a, __xlx_apatb_param_b, __xlx_apatb_param_c, __xlx_apatb_param_a_row, __xlx_apatb_param_a_col, __xlx_apatb_param_b_col, __xlx_apatb_param_work_id);
CodeState = DUMP_OUTPUTS;
#ifdef USE_BINARY_TV_FILE
{
aesl_fh.touch(AUTOTB_TVOUT_systolic, 'b');
transaction<512> tr(3);
  __xlx_offset_byte_param_a = 0*64;
  if (__xlx_apatb_param_a) {
tr.import<64>((char*)__xlx_apatb_param_a, 1, 0);
  }
  __xlx_offset_byte_param_b = 1*64;
  if (__xlx_apatb_param_b) {
tr.import<64>((char*)__xlx_apatb_param_b, 1, 0);
  }
  __xlx_offset_byte_param_c = 2*64;
  if (__xlx_apatb_param_c) {
tr.import<64>((char*)__xlx_apatb_param_c, 1, 0);
  }
tr.reorder();
aesl_fh.write(AUTOTB_TVOUT_systolic, tr.p, tr.tbytes);
}

  tcl_file.set_num(3, &tcl_file.systolic_depth);
#else
// print systolic Transactions
{
aesl_fh.write(AUTOTB_TVOUT_systolic, begin_str(AESL_transaction));
{
  __xlx_offset_byte_param_a = 0*64;
  if (__xlx_apatb_param_a) {
    for (int j = 0  - 0, e = 1 - 0; j != e; ++j) {
sc_bv<512> __xlx_tmp_lv;
__xlx_tmp_lv.range(63,0) = ((long long*)__xlx_apatb_param_a)[j*8+0];
__xlx_tmp_lv.range(127,64) = ((long long*)__xlx_apatb_param_a)[j*8+1];
__xlx_tmp_lv.range(191,128) = ((long long*)__xlx_apatb_param_a)[j*8+2];
__xlx_tmp_lv.range(255,192) = ((long long*)__xlx_apatb_param_a)[j*8+3];
__xlx_tmp_lv.range(319,256) = ((long long*)__xlx_apatb_param_a)[j*8+4];
__xlx_tmp_lv.range(383,320) = ((long long*)__xlx_apatb_param_a)[j*8+5];
__xlx_tmp_lv.range(447,384) = ((long long*)__xlx_apatb_param_a)[j*8+6];
__xlx_tmp_lv.range(511,448) = ((long long*)__xlx_apatb_param_a)[j*8+7];
aesl_fh.write(AUTOTB_TVOUT_systolic, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
    }
  }
  __xlx_offset_byte_param_b = 1*64;
  if (__xlx_apatb_param_b) {
    for (int j = 0  - 0, e = 1 - 0; j != e; ++j) {
sc_bv<512> __xlx_tmp_lv;
__xlx_tmp_lv.range(63,0) = ((long long*)__xlx_apatb_param_b)[j*8+0];
__xlx_tmp_lv.range(127,64) = ((long long*)__xlx_apatb_param_b)[j*8+1];
__xlx_tmp_lv.range(191,128) = ((long long*)__xlx_apatb_param_b)[j*8+2];
__xlx_tmp_lv.range(255,192) = ((long long*)__xlx_apatb_param_b)[j*8+3];
__xlx_tmp_lv.range(319,256) = ((long long*)__xlx_apatb_param_b)[j*8+4];
__xlx_tmp_lv.range(383,320) = ((long long*)__xlx_apatb_param_b)[j*8+5];
__xlx_tmp_lv.range(447,384) = ((long long*)__xlx_apatb_param_b)[j*8+6];
__xlx_tmp_lv.range(511,448) = ((long long*)__xlx_apatb_param_b)[j*8+7];
aesl_fh.write(AUTOTB_TVOUT_systolic, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
    }
  }
  __xlx_offset_byte_param_c = 2*64;
  if (__xlx_apatb_param_c) {
    for (int j = 0  - 0, e = 1 - 0; j != e; ++j) {
sc_bv<512> __xlx_tmp_lv;
__xlx_tmp_lv.range(63,0) = ((long long*)__xlx_apatb_param_c)[j*8+0];
__xlx_tmp_lv.range(127,64) = ((long long*)__xlx_apatb_param_c)[j*8+1];
__xlx_tmp_lv.range(191,128) = ((long long*)__xlx_apatb_param_c)[j*8+2];
__xlx_tmp_lv.range(255,192) = ((long long*)__xlx_apatb_param_c)[j*8+3];
__xlx_tmp_lv.range(319,256) = ((long long*)__xlx_apatb_param_c)[j*8+4];
__xlx_tmp_lv.range(383,320) = ((long long*)__xlx_apatb_param_c)[j*8+5];
__xlx_tmp_lv.range(447,384) = ((long long*)__xlx_apatb_param_c)[j*8+6];
__xlx_tmp_lv.range(511,448) = ((long long*)__xlx_apatb_param_c)[j*8+7];
aesl_fh.write(AUTOTB_TVOUT_systolic, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
    }
  }
}

  tcl_file.set_num(3, &tcl_file.systolic_depth);
aesl_fh.write(AUTOTB_TVOUT_systolic, end_str());
}

#endif
long __xlx_apatb_param_work_id_out_stream_stream_buf_final_size = ((hls::stream<int>*)__xlx_apatb_param_work_id_out_stream)->size() - __xlx_apatb_param_work_id_out_stream_stream_buf_size;
{
  while (!((hls::stream<int>*)__xlx_apatb_param_work_id_out_stream)->empty())
    __xlx_apatb_param_work_id_out_stream_stream_buf.push_back(((hls::stream<int>*)__xlx_apatb_param_work_id_out_stream)->read());
  for (int i = 0; i < __xlx_apatb_param_work_id_out_stream_stream_buf.size(); ++i)
    ((hls::stream<int>*)__xlx_apatb_param_work_id_out_stream)->write(__xlx_apatb_param_work_id_out_stream_stream_buf[i]);
  }
// print work_id_out_stream Transactions
{
aesl_fh.write(AUTOTB_TVOUT_work_id_out_stream, begin_str(AESL_transaction));
for (int j = 0, e = __xlx_apatb_param_work_id_out_stream_stream_buf_final_size; j != e; ++j) {
sc_bv<32> __xlx_tmp_lv = ((int*)&__xlx_apatb_param_work_id_out_stream_stream_buf[__xlx_apatb_param_work_id_out_stream_stream_buf_size+j])[0];
aesl_fh.write(AUTOTB_TVOUT_work_id_out_stream, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}

  tcl_file.set_num(__xlx_apatb_param_work_id_out_stream_stream_buf_final_size, &tcl_file.work_id_out_stream_depth);
aesl_fh.write(AUTOTB_TVOUT_work_id_out_stream, end_str());
}

{
aesl_fh.write(WRAPC_STREAM_SIZE_OUT_work_id_out_stream, begin_str(AESL_transaction));
sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_work_id_out_stream_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_OUT_work_id_out_stream, __xlx_sprintf_buffer.data());
aesl_fh.write(WRAPC_STREAM_SIZE_OUT_work_id_out_stream, end_str());
}
CodeState = DELETE_CHAR_BUFFERS;
AESL_transaction++;
tcl_file.set_num(AESL_transaction , &tcl_file.trans_num);
}
