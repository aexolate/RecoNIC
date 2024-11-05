#include <systemc>
#include <vector>
#include <iostream>
#include "hls_stream.h"
#include "ap_int.h"
#include "ap_fixed.h"
using namespace std;
using namespace sc_dt;
class AESL_RUNTIME_BC {
  public:
    AESL_RUNTIME_BC(const char* name) {
      file_token.open( name);
      if (!file_token.good()) {
        cout << "Failed to open tv file " << name << endl;
        exit (1);
      }
      file_token >> mName;//[[[runtime]]]
    }
    ~AESL_RUNTIME_BC() {
      file_token.close();
    }
    int read_size () {
      int size = 0;
      file_token >> mName;//[[transaction]]
      file_token >> mName;//transaction number
      file_token >> mName;//pop_size
      size = atoi(mName.c_str());
      file_token >> mName;//[[/transaction]]
      return size;
    }
  public:
    fstream file_token;
    string mName;
};
unsigned int ap_apatb_ctl_cmd_stream_cap_bc;
static AESL_RUNTIME_BC __xlx_ctl_cmd_stream_V_size_Reader("../tv/stream_size/stream_size_in_ctl_cmd_stream.dat");
extern "C" void cl_box(int*, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *);
extern "C" void apatb_cl_box_hw(volatile void * __xlx_apatb_param_ctl_cmd_stream, volatile void * __xlx_apatb_param_a_baseaddr, volatile void * __xlx_apatb_param_b_baseaddr, volatile void * __xlx_apatb_param_c_baseaddr, volatile void * __xlx_apatb_param_a_row, volatile void * __xlx_apatb_param_a_col, volatile void * __xlx_apatb_param_b_col, volatile void * __xlx_apatb_param_work_id) {
  // collect __xlx_ctl_cmd_stream_tmp_vec
  unsigned __xlx_ctl_cmd_stream_V_tmp_Count = 0;
  unsigned __xlx_ctl_cmd_stream_V_read_Size = __xlx_ctl_cmd_stream_V_size_Reader.read_size();
  vector<int> __xlx_ctl_cmd_stream_tmp_vec;
  while (!((hls::stream<int>*)__xlx_apatb_param_ctl_cmd_stream)->empty() && __xlx_ctl_cmd_stream_V_tmp_Count < __xlx_ctl_cmd_stream_V_read_Size) {
    __xlx_ctl_cmd_stream_tmp_vec.push_back(((hls::stream<int>*)__xlx_apatb_param_ctl_cmd_stream)->read());
    __xlx_ctl_cmd_stream_V_tmp_Count++;
  }
  ap_apatb_ctl_cmd_stream_cap_bc = __xlx_ctl_cmd_stream_tmp_vec.size();
  // store input buffer
  int* __xlx_ctl_cmd_stream_input_buffer= new int[__xlx_ctl_cmd_stream_tmp_vec.size()];
  for (int i = 0; i < __xlx_ctl_cmd_stream_tmp_vec.size(); ++i) {
    __xlx_ctl_cmd_stream_input_buffer[i] = __xlx_ctl_cmd_stream_tmp_vec[i];
  }
  // DUT call
  cl_box(__xlx_ctl_cmd_stream_input_buffer, __xlx_apatb_param_a_baseaddr, __xlx_apatb_param_b_baseaddr, __xlx_apatb_param_c_baseaddr, __xlx_apatb_param_a_row, __xlx_apatb_param_a_col, __xlx_apatb_param_b_col, __xlx_apatb_param_work_id);
}
