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
#define AUTOTB_TVIN_ctl_cmd_stream "../tv/cdatafile/c.cl_box.autotvin_ctl_cmd_stream.dat"
#define AUTOTB_TVOUT_ctl_cmd_stream "../tv/cdatafile/c.cl_box.autotvout_ctl_cmd_stream.dat"
#define WRAPC_STREAM_SIZE_IN_ctl_cmd_stream "../tv/stream_size/stream_size_in_ctl_cmd_stream.dat"
#define WRAPC_STREAM_INGRESS_STATUS_ctl_cmd_stream "../tv/stream_size/stream_ingress_status_ctl_cmd_stream.dat"
// wrapc file define:
#define AUTOTB_TVIN_a_baseaddr "../tv/cdatafile/c.cl_box.autotvin_a_baseaddr.dat"
#define AUTOTB_TVOUT_a_baseaddr "../tv/cdatafile/c.cl_box.autotvout_a_baseaddr.dat"
// wrapc file define:
#define AUTOTB_TVIN_b_baseaddr "../tv/cdatafile/c.cl_box.autotvin_b_baseaddr.dat"
#define AUTOTB_TVOUT_b_baseaddr "../tv/cdatafile/c.cl_box.autotvout_b_baseaddr.dat"
// wrapc file define:
#define AUTOTB_TVIN_c_baseaddr "../tv/cdatafile/c.cl_box.autotvin_c_baseaddr.dat"
#define AUTOTB_TVOUT_c_baseaddr "../tv/cdatafile/c.cl_box.autotvout_c_baseaddr.dat"
// wrapc file define:
#define AUTOTB_TVIN_a_row "../tv/cdatafile/c.cl_box.autotvin_a_row.dat"
#define AUTOTB_TVOUT_a_row "../tv/cdatafile/c.cl_box.autotvout_a_row.dat"
// wrapc file define:
#define AUTOTB_TVIN_a_col "../tv/cdatafile/c.cl_box.autotvin_a_col.dat"
#define AUTOTB_TVOUT_a_col "../tv/cdatafile/c.cl_box.autotvout_a_col.dat"
// wrapc file define:
#define AUTOTB_TVIN_b_col "../tv/cdatafile/c.cl_box.autotvin_b_col.dat"
#define AUTOTB_TVOUT_b_col "../tv/cdatafile/c.cl_box.autotvout_b_col.dat"
// wrapc file define:
#define AUTOTB_TVIN_work_id "../tv/cdatafile/c.cl_box.autotvin_work_id.dat"
#define AUTOTB_TVOUT_work_id "../tv/cdatafile/c.cl_box.autotvout_work_id.dat"

#define INTER_TCL "../tv/cdatafile/ref.tcl"

// tvout file define:
#define AUTOTB_TVOUT_PC_ctl_cmd_stream "../tv/rtldatafile/rtl.cl_box.autotvout_ctl_cmd_stream.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_a_baseaddr "../tv/rtldatafile/rtl.cl_box.autotvout_a_baseaddr.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_b_baseaddr "../tv/rtldatafile/rtl.cl_box.autotvout_b_baseaddr.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_c_baseaddr "../tv/rtldatafile/rtl.cl_box.autotvout_c_baseaddr.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_a_row "../tv/rtldatafile/rtl.cl_box.autotvout_a_row.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_a_col "../tv/rtldatafile/rtl.cl_box.autotvout_a_col.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_b_col "../tv/rtldatafile/rtl.cl_box.autotvout_b_col.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_work_id "../tv/rtldatafile/rtl.cl_box.autotvout_work_id.dat"


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
  ctl_cmd_stream_depth = 0;
  a_baseaddr_depth = 0;
  b_baseaddr_depth = 0;
  c_baseaddr_depth = 0;
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
  total_list << "{ctl_cmd_stream " << ctl_cmd_stream_depth << "}\n";
  total_list << "{a_baseaddr " << a_baseaddr_depth << "}\n";
  total_list << "{b_baseaddr " << b_baseaddr_depth << "}\n";
  total_list << "{c_baseaddr " << c_baseaddr_depth << "}\n";
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
    int ctl_cmd_stream_depth;
    int a_baseaddr_depth;
    int b_baseaddr_depth;
    int c_baseaddr_depth;
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
extern "C" void cl_box_hw_stub_wrapper(volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *);

extern "C" void apatb_cl_box_hw(volatile void * __xlx_apatb_param_ctl_cmd_stream, volatile void * __xlx_apatb_param_a_baseaddr, volatile void * __xlx_apatb_param_b_baseaddr, volatile void * __xlx_apatb_param_c_baseaddr, volatile void * __xlx_apatb_param_a_row, volatile void * __xlx_apatb_param_a_col, volatile void * __xlx_apatb_param_b_col, volatile void * __xlx_apatb_param_work_id) {
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
long __xlx_apatb_param_ctl_cmd_stream_stream_buf_final_size;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(WRAPC_STREAM_SIZE_IN_ctl_cmd_stream);
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
          while (AESL_token != "[[/transaction]]"){__xlx_apatb_param_ctl_cmd_stream_stream_buf_final_size = atoi(AESL_token.c_str());

            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  for (long i = 0; i < __xlx_apatb_param_ctl_cmd_stream_stream_buf_final_size; ++i)((hls::stream<int>*)__xlx_apatb_param_ctl_cmd_stream)->read();
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_a_baseaddr);
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
          std::vector<sc_bv<32> > a_baseaddr_pc_buffer(1);
          int i = 0;
          bool has_unknown_value = false;
          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            has_unknown_value |= RTLOutputCheckAndReplacement(AESL_token, "a_baseaddr");
  
            // push token into output port buffer
            if (AESL_token != "") {
              a_baseaddr_pc_buffer[i] = AESL_token.c_str();;
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (has_unknown_value) {
            cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'x' or 'X' on port " 
                 << "a_baseaddr" << ", possible cause: There are uninitialized variables in the C design."
                 << endl; 
          }
  
          if (i > 0) {((char*)__xlx_apatb_param_a_baseaddr)[0*4+0] = a_baseaddr_pc_buffer[0].range(7, 0).to_int64();
((char*)__xlx_apatb_param_a_baseaddr)[0*4+1] = a_baseaddr_pc_buffer[0].range(15, 8).to_int64();
((char*)__xlx_apatb_param_a_baseaddr)[0*4+2] = a_baseaddr_pc_buffer[0].range(23, 16).to_int64();
((char*)__xlx_apatb_param_a_baseaddr)[0*4+3] = a_baseaddr_pc_buffer[0].range(31, 24).to_int64();
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  {
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_b_baseaddr);
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
          std::vector<sc_bv<32> > b_baseaddr_pc_buffer(1);
          int i = 0;
          bool has_unknown_value = false;
          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            has_unknown_value |= RTLOutputCheckAndReplacement(AESL_token, "b_baseaddr");
  
            // push token into output port buffer
            if (AESL_token != "") {
              b_baseaddr_pc_buffer[i] = AESL_token.c_str();;
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (has_unknown_value) {
            cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'x' or 'X' on port " 
                 << "b_baseaddr" << ", possible cause: There are uninitialized variables in the C design."
                 << endl; 
          }
  
          if (i > 0) {((char*)__xlx_apatb_param_b_baseaddr)[0*4+0] = b_baseaddr_pc_buffer[0].range(7, 0).to_int64();
((char*)__xlx_apatb_param_b_baseaddr)[0*4+1] = b_baseaddr_pc_buffer[0].range(15, 8).to_int64();
((char*)__xlx_apatb_param_b_baseaddr)[0*4+2] = b_baseaddr_pc_buffer[0].range(23, 16).to_int64();
((char*)__xlx_apatb_param_b_baseaddr)[0*4+3] = b_baseaddr_pc_buffer[0].range(31, 24).to_int64();
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  {
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_c_baseaddr);
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
          std::vector<sc_bv<32> > c_baseaddr_pc_buffer(1);
          int i = 0;
          bool has_unknown_value = false;
          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            has_unknown_value |= RTLOutputCheckAndReplacement(AESL_token, "c_baseaddr");
  
            // push token into output port buffer
            if (AESL_token != "") {
              c_baseaddr_pc_buffer[i] = AESL_token.c_str();;
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (has_unknown_value) {
            cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'x' or 'X' on port " 
                 << "c_baseaddr" << ", possible cause: There are uninitialized variables in the C design."
                 << endl; 
          }
  
          if (i > 0) {((char*)__xlx_apatb_param_c_baseaddr)[0*4+0] = c_baseaddr_pc_buffer[0].range(7, 0).to_int64();
((char*)__xlx_apatb_param_c_baseaddr)[0*4+1] = c_baseaddr_pc_buffer[0].range(15, 8).to_int64();
((char*)__xlx_apatb_param_c_baseaddr)[0*4+2] = c_baseaddr_pc_buffer[0].range(23, 16).to_int64();
((char*)__xlx_apatb_param_c_baseaddr)[0*4+3] = c_baseaddr_pc_buffer[0].range(31, 24).to_int64();
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  {
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_a_row);
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
          std::vector<sc_bv<32> > a_row_pc_buffer(1);
          int i = 0;
          bool has_unknown_value = false;
          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            has_unknown_value |= RTLOutputCheckAndReplacement(AESL_token, "a_row");
  
            // push token into output port buffer
            if (AESL_token != "") {
              a_row_pc_buffer[i] = AESL_token.c_str();;
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (has_unknown_value) {
            cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'x' or 'X' on port " 
                 << "a_row" << ", possible cause: There are uninitialized variables in the C design."
                 << endl; 
          }
  
          if (i > 0) {((char*)__xlx_apatb_param_a_row)[0*4+0] = a_row_pc_buffer[0].range(7, 0).to_int64();
((char*)__xlx_apatb_param_a_row)[0*4+1] = a_row_pc_buffer[0].range(15, 8).to_int64();
((char*)__xlx_apatb_param_a_row)[0*4+2] = a_row_pc_buffer[0].range(23, 16).to_int64();
((char*)__xlx_apatb_param_a_row)[0*4+3] = a_row_pc_buffer[0].range(31, 24).to_int64();
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  {
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_a_col);
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
          std::vector<sc_bv<32> > a_col_pc_buffer(1);
          int i = 0;
          bool has_unknown_value = false;
          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            has_unknown_value |= RTLOutputCheckAndReplacement(AESL_token, "a_col");
  
            // push token into output port buffer
            if (AESL_token != "") {
              a_col_pc_buffer[i] = AESL_token.c_str();;
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (has_unknown_value) {
            cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'x' or 'X' on port " 
                 << "a_col" << ", possible cause: There are uninitialized variables in the C design."
                 << endl; 
          }
  
          if (i > 0) {((char*)__xlx_apatb_param_a_col)[0*4+0] = a_col_pc_buffer[0].range(7, 0).to_int64();
((char*)__xlx_apatb_param_a_col)[0*4+1] = a_col_pc_buffer[0].range(15, 8).to_int64();
((char*)__xlx_apatb_param_a_col)[0*4+2] = a_col_pc_buffer[0].range(23, 16).to_int64();
((char*)__xlx_apatb_param_a_col)[0*4+3] = a_col_pc_buffer[0].range(31, 24).to_int64();
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  {
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_b_col);
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
          std::vector<sc_bv<32> > b_col_pc_buffer(1);
          int i = 0;
          bool has_unknown_value = false;
          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            has_unknown_value |= RTLOutputCheckAndReplacement(AESL_token, "b_col");
  
            // push token into output port buffer
            if (AESL_token != "") {
              b_col_pc_buffer[i] = AESL_token.c_str();;
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (has_unknown_value) {
            cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'x' or 'X' on port " 
                 << "b_col" << ", possible cause: There are uninitialized variables in the C design."
                 << endl; 
          }
  
          if (i > 0) {((char*)__xlx_apatb_param_b_col)[0*4+0] = b_col_pc_buffer[0].range(7, 0).to_int64();
((char*)__xlx_apatb_param_b_col)[0*4+1] = b_col_pc_buffer[0].range(15, 8).to_int64();
((char*)__xlx_apatb_param_b_col)[0*4+2] = b_col_pc_buffer[0].range(23, 16).to_int64();
((char*)__xlx_apatb_param_b_col)[0*4+3] = b_col_pc_buffer[0].range(31, 24).to_int64();
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  {
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_work_id);
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
          std::vector<sc_bv<32> > work_id_pc_buffer(1);
          int i = 0;
          bool has_unknown_value = false;
          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            has_unknown_value |= RTLOutputCheckAndReplacement(AESL_token, "work_id");
  
            // push token into output port buffer
            if (AESL_token != "") {
              work_id_pc_buffer[i] = AESL_token.c_str();;
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (has_unknown_value) {
            cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'x' or 'X' on port " 
                 << "work_id" << ", possible cause: There are uninitialized variables in the C design."
                 << endl; 
          }
  
          if (i > 0) {((char*)__xlx_apatb_param_work_id)[0*4+0] = work_id_pc_buffer[0].range(7, 0).to_int64();
((char*)__xlx_apatb_param_work_id)[0*4+1] = work_id_pc_buffer[0].range(15, 8).to_int64();
((char*)__xlx_apatb_param_work_id)[0*4+2] = work_id_pc_buffer[0].range(23, 16).to_int64();
((char*)__xlx_apatb_param_work_id)[0*4+3] = work_id_pc_buffer[0].range(31, 24).to_int64();
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
aesl_fh.touch(WRAPC_STREAM_SIZE_IN_ctl_cmd_stream);
aesl_fh.touch(WRAPC_STREAM_INGRESS_STATUS_ctl_cmd_stream);
CodeState = DUMP_INPUTS;
std::vector<int> __xlx_apatb_param_ctl_cmd_stream_stream_buf;
{
  while (!((hls::stream<int>*)__xlx_apatb_param_ctl_cmd_stream)->empty())
    __xlx_apatb_param_ctl_cmd_stream_stream_buf.push_back(((hls::stream<int>*)__xlx_apatb_param_ctl_cmd_stream)->read());
  for (int i = 0; i < __xlx_apatb_param_ctl_cmd_stream_stream_buf.size(); ++i)
    ((hls::stream<int>*)__xlx_apatb_param_ctl_cmd_stream)->write(__xlx_apatb_param_ctl_cmd_stream_stream_buf[i]);
  }
long __xlx_apatb_param_ctl_cmd_stream_stream_buf_size = ((hls::stream<int>*)__xlx_apatb_param_ctl_cmd_stream)->size();
// print a_baseaddr Transactions
{
aesl_fh.write(AUTOTB_TVIN_a_baseaddr, begin_str(AESL_transaction));
{
    sc_bv<32> __xlx_tmp_lv = *((int*)__xlx_apatb_param_a_baseaddr);
aesl_fh.write(AUTOTB_TVIN_a_baseaddr, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.a_baseaddr_depth);
aesl_fh.write(AUTOTB_TVIN_a_baseaddr, end_str());
}

// print b_baseaddr Transactions
{
aesl_fh.write(AUTOTB_TVIN_b_baseaddr, begin_str(AESL_transaction));
{
    sc_bv<32> __xlx_tmp_lv = *((int*)__xlx_apatb_param_b_baseaddr);
aesl_fh.write(AUTOTB_TVIN_b_baseaddr, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.b_baseaddr_depth);
aesl_fh.write(AUTOTB_TVIN_b_baseaddr, end_str());
}

// print c_baseaddr Transactions
{
aesl_fh.write(AUTOTB_TVIN_c_baseaddr, begin_str(AESL_transaction));
{
    sc_bv<32> __xlx_tmp_lv = *((int*)__xlx_apatb_param_c_baseaddr);
aesl_fh.write(AUTOTB_TVIN_c_baseaddr, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.c_baseaddr_depth);
aesl_fh.write(AUTOTB_TVIN_c_baseaddr, end_str());
}

// print a_row Transactions
{
aesl_fh.write(AUTOTB_TVIN_a_row, begin_str(AESL_transaction));
{
    sc_bv<32> __xlx_tmp_lv = *((int*)__xlx_apatb_param_a_row);
aesl_fh.write(AUTOTB_TVIN_a_row, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.a_row_depth);
aesl_fh.write(AUTOTB_TVIN_a_row, end_str());
}

// print a_col Transactions
{
aesl_fh.write(AUTOTB_TVIN_a_col, begin_str(AESL_transaction));
{
    sc_bv<32> __xlx_tmp_lv = *((int*)__xlx_apatb_param_a_col);
aesl_fh.write(AUTOTB_TVIN_a_col, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.a_col_depth);
aesl_fh.write(AUTOTB_TVIN_a_col, end_str());
}

// print b_col Transactions
{
aesl_fh.write(AUTOTB_TVIN_b_col, begin_str(AESL_transaction));
{
    sc_bv<32> __xlx_tmp_lv = *((int*)__xlx_apatb_param_b_col);
aesl_fh.write(AUTOTB_TVIN_b_col, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.b_col_depth);
aesl_fh.write(AUTOTB_TVIN_b_col, end_str());
}

// print work_id Transactions
{
aesl_fh.write(AUTOTB_TVIN_work_id, begin_str(AESL_transaction));
{
    sc_bv<32> __xlx_tmp_lv = *((int*)__xlx_apatb_param_work_id);
aesl_fh.write(AUTOTB_TVIN_work_id, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.work_id_depth);
aesl_fh.write(AUTOTB_TVIN_work_id, end_str());
}

CodeState = CALL_C_DUT;
cl_box_hw_stub_wrapper(__xlx_apatb_param_ctl_cmd_stream, __xlx_apatb_param_a_baseaddr, __xlx_apatb_param_b_baseaddr, __xlx_apatb_param_c_baseaddr, __xlx_apatb_param_a_row, __xlx_apatb_param_a_col, __xlx_apatb_param_b_col, __xlx_apatb_param_work_id);
CodeState = DUMP_OUTPUTS;
long __xlx_apatb_param_ctl_cmd_stream_stream_buf_final_size = __xlx_apatb_param_ctl_cmd_stream_stream_buf_size - ((hls::stream<int>*)__xlx_apatb_param_ctl_cmd_stream)->size();
// print ctl_cmd_stream Transactions
{
aesl_fh.write(AUTOTB_TVIN_ctl_cmd_stream, begin_str(AESL_transaction));
for (int j = 0, e = __xlx_apatb_param_ctl_cmd_stream_stream_buf_final_size; j != e; ++j) {
sc_bv<32> __xlx_tmp_lv_hw;
sc_bv<32> __xlx_tmp_lv;
__xlx_tmp_lv = ((int*)&__xlx_apatb_param_ctl_cmd_stream_stream_buf[j])[0];
__xlx_tmp_lv_hw = __xlx_tmp_lv;

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv_hw.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVIN_ctl_cmd_stream, __xlx_sprintf_buffer.data()); 
  }

  tcl_file.set_num(__xlx_apatb_param_ctl_cmd_stream_stream_buf_final_size, &tcl_file.ctl_cmd_stream_depth);
aesl_fh.write(AUTOTB_TVIN_ctl_cmd_stream, end_str());
}


// dump stream ingress status to file
{
aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_ctl_cmd_stream, begin_str(AESL_transaction));
if (__xlx_apatb_param_ctl_cmd_stream_stream_buf_final_size > 0) {
  long ctl_cmd_stream_stream_ingress_size = __xlx_apatb_param_ctl_cmd_stream_stream_buf_size;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", ctl_cmd_stream_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_ctl_cmd_stream, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_ctl_cmd_stream_stream_buf_final_size; j != e; j++) {
    ctl_cmd_stream_stream_ingress_size--;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", ctl_cmd_stream_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_ctl_cmd_stream, __xlx_sprintf_buffer.data());
  }
} else {
  long ctl_cmd_stream_stream_ingress_size = 0;
sprintf(__xlx_sprintf_buffer.data(), "%d\n", ctl_cmd_stream_stream_ingress_size);
 aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_ctl_cmd_stream, __xlx_sprintf_buffer.data());
}
aesl_fh.write(WRAPC_STREAM_INGRESS_STATUS_ctl_cmd_stream, end_str());
}
{
aesl_fh.write(WRAPC_STREAM_SIZE_IN_ctl_cmd_stream, begin_str(AESL_transaction));
sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_ctl_cmd_stream_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_IN_ctl_cmd_stream, __xlx_sprintf_buffer.data());
aesl_fh.write(WRAPC_STREAM_SIZE_IN_ctl_cmd_stream, end_str());
}
// print a_baseaddr Transactions
{
aesl_fh.write(AUTOTB_TVOUT_a_baseaddr, begin_str(AESL_transaction));
{
    sc_bv<32> __xlx_tmp_lv = *((int*)__xlx_apatb_param_a_baseaddr);
aesl_fh.write(AUTOTB_TVOUT_a_baseaddr, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.a_baseaddr_depth);
aesl_fh.write(AUTOTB_TVOUT_a_baseaddr, end_str());
}

// print b_baseaddr Transactions
{
aesl_fh.write(AUTOTB_TVOUT_b_baseaddr, begin_str(AESL_transaction));
{
    sc_bv<32> __xlx_tmp_lv = *((int*)__xlx_apatb_param_b_baseaddr);
aesl_fh.write(AUTOTB_TVOUT_b_baseaddr, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.b_baseaddr_depth);
aesl_fh.write(AUTOTB_TVOUT_b_baseaddr, end_str());
}

// print c_baseaddr Transactions
{
aesl_fh.write(AUTOTB_TVOUT_c_baseaddr, begin_str(AESL_transaction));
{
    sc_bv<32> __xlx_tmp_lv = *((int*)__xlx_apatb_param_c_baseaddr);
aesl_fh.write(AUTOTB_TVOUT_c_baseaddr, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.c_baseaddr_depth);
aesl_fh.write(AUTOTB_TVOUT_c_baseaddr, end_str());
}

// print a_row Transactions
{
aesl_fh.write(AUTOTB_TVOUT_a_row, begin_str(AESL_transaction));
{
    sc_bv<32> __xlx_tmp_lv = *((int*)__xlx_apatb_param_a_row);
aesl_fh.write(AUTOTB_TVOUT_a_row, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.a_row_depth);
aesl_fh.write(AUTOTB_TVOUT_a_row, end_str());
}

// print a_col Transactions
{
aesl_fh.write(AUTOTB_TVOUT_a_col, begin_str(AESL_transaction));
{
    sc_bv<32> __xlx_tmp_lv = *((int*)__xlx_apatb_param_a_col);
aesl_fh.write(AUTOTB_TVOUT_a_col, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.a_col_depth);
aesl_fh.write(AUTOTB_TVOUT_a_col, end_str());
}

// print b_col Transactions
{
aesl_fh.write(AUTOTB_TVOUT_b_col, begin_str(AESL_transaction));
{
    sc_bv<32> __xlx_tmp_lv = *((int*)__xlx_apatb_param_b_col);
aesl_fh.write(AUTOTB_TVOUT_b_col, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.b_col_depth);
aesl_fh.write(AUTOTB_TVOUT_b_col, end_str());
}

// print work_id Transactions
{
aesl_fh.write(AUTOTB_TVOUT_work_id, begin_str(AESL_transaction));
{
    sc_bv<32> __xlx_tmp_lv = *((int*)__xlx_apatb_param_work_id);
aesl_fh.write(AUTOTB_TVOUT_work_id, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.work_id_depth);
aesl_fh.write(AUTOTB_TVOUT_work_id, end_str());
}

CodeState = DELETE_CHAR_BUFFERS;
AESL_transaction++;
tcl_file.set_num(AESL_transaction , &tcl_file.trans_num);
}
