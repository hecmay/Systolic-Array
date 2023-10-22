#include <ap_int.h>
#include <hls_stream.h>

#define min(x,y) ((x < y) ? x : y)
#define max(x,y) ((x > y) ? x : y)

/* Data Type */
typedef float cin_t1;
typedef float cout_t1;
typedef float w_t1;
typedef ap_uint<512> cin_t16;
typedef ap_uint<256> cin_t8;
typedef ap_uint<512> cout_t16;
typedef ap_uint<128> cout_t4;
typedef ap_uint<512> w_t16;
typedef ap_uint<256> w_t8;
/* Data Type */

extern "C" {
void kernel0(cin_t16 *cin, cout_t16 *cout, w_t16 *w);
}
void cin_IO_L2_in_intra_trans(int idx, int c1, int c2, int c3, cin_t8 local_cin[3][6][1], hls::stream<cin_t8> &fifo_cin_local_out, bool intra_trans_en);
void cin_IO_L2_in_inter_trans(int idx, int c1, int c2, int c3, cin_t8 local_cin[3][6][1], hls::stream<cin_t8> &fifo_cin_in, hls::stream<cin_t8> &fifo_cin_out, bool inter_trans_en);
void cin_IO_L2_in_inter_trans_boundary(int idx, int c1, int c2, int c3, cin_t8 local_cin[3][6][1], hls::stream<cin_t8> &fifo_cin_in, bool inter_trans_en);
void w_IO_L2_in_intra_trans(int idx, int c1, int c2, int c3, w_t8 local_w[4][3][3][1], hls::stream<w_t8> &fifo_w_local_out, bool intra_trans_en);
void w_IO_L2_in_inter_trans(int idx, int c1, int c2, int c3, w_t8 local_w[4][3][3][1], hls::stream<w_t8> &fifo_w_in, hls::stream<w_t8> &fifo_w_out, bool inter_trans_en);
void w_IO_L2_in_inter_trans_boundary(int idx, int c1, int c2, int c3, w_t8 local_w[4][3][3][1], hls::stream<w_t8> &fifo_w_in, bool inter_trans_en);
void PE_wrapper(int idx, int idy, hls::stream<cin_t8> &fifo_cin_in, hls::stream<cin_t8> &fifo_cin_out, hls::stream<float> &fifo_cout_drain_out, hls::stream<w_t8> &fifo_w_in, hls::stream<w_t8> &fifo_w_out);
void cout_drain_IO_L1_out_intra_trans(int idx, int idy, int c1, int c2, cout_t4 local_cout[1][4][1], hls::stream<float> &fifo_cout_drain_local_in);
void cout_drain_IO_L1_out_inter_trans(int idx, int idy, int c1, int c2, cout_t4 local_cout[1][4][1], hls::stream<cout_t4> &fifo_cout_drain_in, hls::stream<cout_t4> &fifo_cout_drain_out);
void cout_drain_IO_L1_out_inter_trans_boundary(int idx, int idy, int c1, int c2, cout_t4 local_cout[1][4][1], hls::stream<cout_t4> &fifo_cout_drain_out);
void cout_drain_IO_L1_out_wrapper(int idx, int idy, hls::stream<cout_t4> &fifo_cout_drain_in, hls::stream<cout_t4> &fifo_cout_drain_out, hls::stream<float> &fifo_cout_drain_local_in);
void cout_drain_IO_L1_out_boundary_wrapper(int idx, int idy, hls::stream<cout_t4> &fifo_cout_drain_out, hls::stream<float> &fifo_cout_drain_local_in);

/* Module Definition */
void cin_IO_L3_in(hls::stream<cin_t8> &fifo_cin_in, hls::stream<cin_t8> &fifo_cin_local_out) {
#pragma HLS INLINE OFF
  /* Variable Declaration */
  /* Variable Declaration */

  for (ap_uint<5> c1 = 0; c1 <= 15; c1 += 1)
    for (ap_uint<7> c2 = 0; c2 <= 63; c2 += 1)
      for (ap_uint<2> c3 = 0; c3 <= 1; c3 += 1) {
        // array
        // io_L3
        for (ap_uint<5> c4 = 0; c4 <= 15; c4 += 1) {
          // io_L2
          for (ap_uint<3> c5 = 0; c5 <= 2; c5 += 1)
            for (ap_uint<4> c6 = 0; c6 <= 5; c6 += 1) {
            #pragma HLS PIPELINE II=1
              // access_coalesce
              // access_serialize
              {
                cin_t8 in_data;
                cin_t8 out_data;
                in_data = fifo_cin_in.read();
                out_data = in_data;
                fifo_cin_local_out.write(out_data);
              }
            }
        }
      }
}
/* Module Definition */

/* Module Definition */
void cin_IO_L3_in_serialize(cin_t16 *cin, hls::stream<cin_t8> &fifo_cin_local_out) {
#pragma HLS INLINE OFF
  /* Variable Declaration */
  /* Variable Declaration */

  cin_t8 fifo_data;
  cin_t16 mem_data;
  for (ap_uint<20> i = 0; i < 294912; i++) {
  #pragma HLS PIPELINE II=1
    mem_data = cin[i];
    for (ap_uint<2> p = 0; p < 2; p++) {
      fifo_data = mem_data(255, 0);
      mem_data = mem_data >> 256;
      fifo_cin_local_out.write(fifo_data);
    }
  }
}
/* Module Definition */

/* Module Definition */
void cin_IO_L2_in_intra_trans(int idx, int c1, int c2, int c3, cin_t8 local_cin[3][6][1], hls::stream<cin_t8> &fifo_cin_local_out, bool intra_trans_en) {
#pragma HLS INLINE OFF
  /* Variable Declaration */
  int p0 = idx; // module id
  /* Variable Declaration */

  if (!intra_trans_en) return;


  // io_L2
  // io_L1
  // pe
  for (ap_uint<2> c6 = 0; c6 <= 1; c6 += 1)
    for (ap_uint<3> c8 = 0; c8 <= 2; c8 += 1)
      for (ap_uint<3> c9 = 0; c9 <= 2; c9 += 1) {
        // latency
        for (ap_uint<3> c10 = 0; c10 <= 3; c10 += 1) {
          // latency
          for (ap_uint<2> c11 = 0; c11 <= 1; c11 += 1) {
          #pragma HLS PIPELINE II=1
            // simd
            {
              cin_t8 in_data;
              cin_t8 out_data;
              in_data = local_cin[c8][c11 + 2*c6 + c9][0];
              out_data = in_data;
              fifo_cin_local_out.write(out_data);
            }
          }
        }
      }
}
/* Module Definition */

/* Module Definition */
void cin_IO_L2_in_inter_trans(int idx, int c1, int c2, int c3, cin_t8 local_cin[3][6][1], hls::stream<cin_t8> &fifo_cin_in, hls::stream<cin_t8> &fifo_cin_out, bool inter_trans_en) {
#pragma HLS INLINE OFF
  /* Variable Declaration */
  int p0 = idx; // module id
  /* Variable Declaration */

  if (!inter_trans_en) return;

  for (ap_uint<5> c4 = p0; c4 <= 15; c4 += 1) {
    // io_L2
    if (c4 == p0) {
      for (ap_uint<3> c5 = 0; c5 <= 2; c5 += 1)
        for (ap_uint<4> c6 = 0; c6 <= 5; c6 += 1) {
        #pragma HLS PIPELINE II=1
          // access_coalesce
          {
            cin_t8 in_data;
            cin_t8 out_data;
            in_data = fifo_cin_in.read();
            out_data = in_data;
            local_cin[c5][c6][0] = out_data;
          }
        }
    } else {
      for (ap_uint<3> c5 = 0; c5 <= 2; c5 += 1)
        for (ap_uint<4> c6 = 0; c6 <= 5; c6 += 1) {
        #pragma HLS PIPELINE II=1
          // access_coalesce
          {
            cin_t8 in_data;
            cin_t8 out_data;
            in_data = fifo_cin_in.read();
            out_data = in_data;
            fifo_cin_out.write(out_data);
          }
        }
    }
  }
}
/* Module Definition */

/* Module Definition */
void cin_IO_L2_in_inter_trans_boundary(int idx, int c1, int c2, int c3, cin_t8 local_cin[3][6][1], hls::stream<cin_t8> &fifo_cin_in, bool inter_trans_en) {
#pragma HLS INLINE OFF
  /* Variable Declaration */
  int p0 = idx; // module id
  /* Variable Declaration */

  if (!inter_trans_en) return;

  for (ap_uint<5> c4 = p0; c4 <= 15; c4 += 1)
    if (c4 == p0) {
      // io_L2
      for (ap_uint<3> c5 = 0; c5 <= 2; c5 += 1)
        for (ap_uint<4> c6 = 0; c6 <= 5; c6 += 1) {
        #pragma HLS PIPELINE II=1
          // access_coalesce
          {
            cin_t8 in_data;
            cin_t8 out_data;
            in_data = fifo_cin_in.read();
            out_data = in_data;
            local_cin[c5][c6][0] = out_data;
          }
        }
    }
}
/* Module Definition */

/* Module Definition */
void cin_IO_L2_in(int idx, hls::stream<cin_t8> &fifo_cin_in, hls::stream<cin_t8> &fifo_cin_out, hls::stream<cin_t8> &fifo_cin_local_out) {
#pragma HLS INLINE OFF
  /* Variable Declaration */
  int p0 = idx; // module id
  cin_t8 local_cin_ping[3][6][1];
  #pragma HLS BIND_STORAGE variable=local_cin_ping core=RAM_1P_BRAM
  cin_t8 local_cin_pong[3][6][1];
  #pragma HLS BIND_STORAGE variable=local_cin_pong core=RAM_1P_BRAM
  bool arb = 0;
  bool inter_trans_en = 1;
  bool intra_trans_en = 0;
  int c1, c1_prev;
  int c2, c2_prev;
  int c3, c3_prev;
  /* Variable Declaration */

  {
    for (ap_uint<5> c1 = 0; c1 <= 15; c1 += 1)
      for (ap_uint<7> c2 = 0; c2 <= 63; c2 += 1)
        for (ap_uint<2> c3 = 0; c3 <= 1; c3 += 1) {
          // array
          // io_L3
          {
            if (arb == 0) {
              cin_IO_L2_in_inter_trans(
                /* module id */ idx, 
                /* host iter */ c1, 
                /* host iter */ c2, 
                /* host iter */ c3, 
                /* array */ local_cin_pong, 
                /* fifo */ fifo_cin_in, 
                /* fifo */ fifo_cin_out, 
                /* enable */ inter_trans_en
              );
              cin_IO_L2_in_intra_trans(
                /* module id */ idx, 
                /* host iter */ c1_prev, 
                /* host iter */ c2_prev, 
                /* host iter */ c3_prev, 
                /* array */ local_cin_ping, 
                /* fifo */ fifo_cin_local_out, 
                /* enable */ intra_trans_en
              );
            } else {
              cin_IO_L2_in_inter_trans(
                /* module id */ idx, 
                /* host iter */ c1, 
                /* host iter */ c2, 
                /* host iter */ c3, 
                /* array */ local_cin_ping, 
                /* fifo */ fifo_cin_in, 
                /* fifo */ fifo_cin_out, 
                /* enable */ inter_trans_en
              );
              cin_IO_L2_in_intra_trans(
                /* module id */ idx, 
                /* host iter */ c1_prev, 
                /* host iter */ c2_prev, 
                /* host iter */ c3_prev, 
                /* array */ local_cin_pong, 
                /* fifo */ fifo_cin_local_out, 
                /* enable */ intra_trans_en
              );
            }
            intra_trans_en = 1;
            arb = !arb;
            c1_prev = c1;
            c2_prev = c2;
            c3_prev = c3;
          }
        }
    if (arb == 0) {
      cin_IO_L2_in_intra_trans(
        /* module id */ idx, 
        /* host iter */ c1_prev, 
        /* host iter */ c2_prev, 
        /* host iter */ c3_prev, 
        /* array */ local_cin_ping, 
        /* fifo */ fifo_cin_local_out, 
        /* enable */ intra_trans_en
      );
    } else {
      cin_IO_L2_in_intra_trans(
        /* module id */ idx, 
        /* host iter */ c1_prev, 
        /* host iter */ c2_prev, 
        /* host iter */ c3_prev, 
        /* array */ local_cin_pong, 
        /* fifo */ fifo_cin_local_out, 
        /* enable */ intra_trans_en
      );
    }
  }
}
/* Module Definition */

/* Module Definition */
void cin_IO_L2_in_boundary(int idx, hls::stream<cin_t8> &fifo_cin_in, hls::stream<cin_t8> &fifo_cin_local_out) {
#pragma HLS INLINE OFF
  /* Variable Declaration */
  int p0 = idx; // module id
  cin_t8 local_cin_ping[3][6][1];
  #pragma HLS BIND_STORAGE variable=local_cin_ping core=RAM_1P_BRAM
  cin_t8 local_cin_pong[3][6][1];
  #pragma HLS BIND_STORAGE variable=local_cin_pong core=RAM_1P_BRAM
  bool arb = 0;
  bool inter_trans_en = 1;
  bool intra_trans_en = 0;
  int c1, c1_prev;
  int c2, c2_prev;
  int c3, c3_prev;
  /* Variable Declaration */

  {
    for (ap_uint<5> c1 = 0; c1 <= 15; c1 += 1)
      for (ap_uint<7> c2 = 0; c2 <= 63; c2 += 1)
        for (ap_uint<2> c3 = 0; c3 <= 1; c3 += 1) {
          // array
          // io_L3
          {
            if (arb == 0) {
              cin_IO_L2_in_inter_trans_boundary(
                /* module id */ idx, 
                /* host iter */ c1, 
                /* host iter */ c2, 
                /* host iter */ c3, 
                /* array */ local_cin_pong, 
                /* fifo */ fifo_cin_in, 
                /* enable */ inter_trans_en
              );
              cin_IO_L2_in_intra_trans(
                /* module id */ idx, 
                /* host iter */ c1_prev, 
                /* host iter */ c2_prev, 
                /* host iter */ c3_prev, 
                /* array */ local_cin_ping, 
                /* fifo */ fifo_cin_local_out, 
                /* enable */ intra_trans_en
              );
            } else {
              cin_IO_L2_in_inter_trans_boundary(
                /* module id */ idx, 
                /* host iter */ c1, 
                /* host iter */ c2, 
                /* host iter */ c3, 
                /* array */ local_cin_ping, 
                /* fifo */ fifo_cin_in, 
                /* enable */ inter_trans_en
              );
              cin_IO_L2_in_intra_trans(
                /* module id */ idx, 
                /* host iter */ c1_prev, 
                /* host iter */ c2_prev, 
                /* host iter */ c3_prev, 
                /* array */ local_cin_pong, 
                /* fifo */ fifo_cin_local_out, 
                /* enable */ intra_trans_en
              );
            }
            intra_trans_en = 1;
            arb = !arb;
            c1_prev = c1;
            c2_prev = c2;
            c3_prev = c3;
          }
        }
    if (arb == 0) {
      cin_IO_L2_in_intra_trans(
        /* module id */ idx, 
        /* host iter */ c1_prev, 
        /* host iter */ c2_prev, 
        /* host iter */ c3_prev, 
        /* array */ local_cin_ping, 
        /* fifo */ fifo_cin_local_out, 
        /* enable */ intra_trans_en
      );
    } else {
      cin_IO_L2_in_intra_trans(
        /* module id */ idx, 
        /* host iter */ c1_prev, 
        /* host iter */ c2_prev, 
        /* host iter */ c3_prev, 
        /* array */ local_cin_pong, 
        /* fifo */ fifo_cin_local_out, 
        /* enable */ intra_trans_en
      );
    }
  }
}
/* Module Definition */

/* Module Definition */
void w_IO_L3_in(hls::stream<w_t8> &fifo_w_in, hls::stream<w_t8> &fifo_w_local_out) {
#pragma HLS INLINE OFF
  /* Variable Declaration */
  /* Variable Declaration */

  for (ap_uint<5> c1 = 0; c1 <= 15; c1 += 1)
    for (ap_uint<7> c2 = 0; c2 <= 63; c2 += 1)
      for (ap_uint<2> c3 = 0; c3 <= 1; c3 += 1) {
        // array
        // io_L3
        for (ap_uint<3> c4 = 0; c4 <= 3; c4 += 1) {
          // io_L2
          for (ap_uint<3> c5 = 0; c5 <= 3; c5 += 1)
            for (ap_uint<3> c6 = 0; c6 <= 2; c6 += 1)
              for (ap_uint<3> c7 = 0; c7 <= 2; c7 += 1) {
              #pragma HLS PIPELINE II=1
                // access_coalesce
                // access_serialize
                {
                  w_t8 in_data;
                  w_t8 out_data;
                  in_data = fifo_w_in.read();
                  out_data = in_data;
                  fifo_w_local_out.write(out_data);
                }
              }
        }
      }
}
/* Module Definition */

/* Module Definition */
void w_IO_L3_in_serialize(w_t16 *w, hls::stream<w_t8> &fifo_w_local_out) {
#pragma HLS INLINE OFF
  /* Variable Declaration */
  /* Variable Declaration */

  w_t8 fifo_data;
  w_t16 mem_data;
  for (ap_uint<19> i = 0; i < 147456; i++) {
  #pragma HLS PIPELINE II=1
    mem_data = w[i];
    for (ap_uint<2> p = 0; p < 2; p++) {
      fifo_data = mem_data(255, 0);
      mem_data = mem_data >> 256;
      fifo_w_local_out.write(fifo_data);
    }
  }
}
/* Module Definition */

/* Module Definition */
void w_IO_L2_in_intra_trans(int idx, int c1, int c2, int c3, w_t8 local_w[4][3][3][1], hls::stream<w_t8> &fifo_w_local_out, bool intra_trans_en) {
#pragma HLS INLINE OFF
  /* Variable Declaration */
  int p0 = idx; // module id
  /* Variable Declaration */

  if (!intra_trans_en) return;


  // io_L2
  // io_L1
  // pe
  for (ap_uint<2> c6 = 0; c6 <= 1; c6 += 1)
    for (ap_uint<3> c8 = 0; c8 <= 2; c8 += 1)
      for (ap_uint<3> c9 = 0; c9 <= 2; c9 += 1) {
        // latency
        for (ap_uint<3> c10 = 0; c10 <= 3; c10 += 1) {
          // latency
          for (ap_uint<2> c11 = 0; c11 <= 1; c11 += 1) {
          #pragma HLS PIPELINE II=1
            // simd
            {
              w_t8 in_data;
              w_t8 out_data;
              in_data = local_w[c10][c8][c9][0];
              out_data = in_data;
              fifo_w_local_out.write(out_data);
            }
          }
        }
      }
}
/* Module Definition */

/* Module Definition */
void w_IO_L2_in_inter_trans(int idx, int c1, int c2, int c3, w_t8 local_w[4][3][3][1], hls::stream<w_t8> &fifo_w_in, hls::stream<w_t8> &fifo_w_out, bool inter_trans_en) {
#pragma HLS INLINE OFF
  /* Variable Declaration */
  int p0 = idx; // module id
  /* Variable Declaration */

  if (!inter_trans_en) return;

  for (ap_uint<3> c4 = p0; c4 <= 3; c4 += 1) {
    // io_L2
    if (c4 == p0) {
      for (ap_uint<3> c5 = 0; c5 <= 3; c5 += 1)
        for (ap_uint<3> c6 = 0; c6 <= 2; c6 += 1)
          for (ap_uint<3> c7 = 0; c7 <= 2; c7 += 1) {
          #pragma HLS PIPELINE II=1
            // access_coalesce
            {
              w_t8 in_data;
              w_t8 out_data;
              in_data = fifo_w_in.read();
              out_data = in_data;
              local_w[c5][c6][c7][0] = out_data;
            }
          }
    } else {
      for (ap_uint<3> c5 = 0; c5 <= 3; c5 += 1)
        for (ap_uint<3> c6 = 0; c6 <= 2; c6 += 1)
          for (ap_uint<3> c7 = 0; c7 <= 2; c7 += 1) {
          #pragma HLS PIPELINE II=1
            // access_coalesce
            {
              w_t8 in_data;
              w_t8 out_data;
              in_data = fifo_w_in.read();
              out_data = in_data;
              fifo_w_out.write(out_data);
            }
          }
    }
  }
}
/* Module Definition */

/* Module Definition */
void w_IO_L2_in_inter_trans_boundary(int idx, int c1, int c2, int c3, w_t8 local_w[4][3][3][1], hls::stream<w_t8> &fifo_w_in, bool inter_trans_en) {
#pragma HLS INLINE OFF
  /* Variable Declaration */
  int p0 = idx; // module id
  /* Variable Declaration */

  if (!inter_trans_en) return;

  for (ap_uint<3> c4 = p0; c4 <= 3; c4 += 1)
    if (c4 == p0) {
      // io_L2
      for (ap_uint<3> c5 = 0; c5 <= 3; c5 += 1)
        for (ap_uint<3> c6 = 0; c6 <= 2; c6 += 1)
          for (ap_uint<3> c7 = 0; c7 <= 2; c7 += 1) {
          #pragma HLS PIPELINE II=1
            // access_coalesce
            {
              w_t8 in_data;
              w_t8 out_data;
              in_data = fifo_w_in.read();
              out_data = in_data;
              local_w[c5][c6][c7][0] = out_data;
            }
          }
    }
}
/* Module Definition */

/* Module Definition */
void w_IO_L2_in(int idx, hls::stream<w_t8> &fifo_w_in, hls::stream<w_t8> &fifo_w_out, hls::stream<w_t8> &fifo_w_local_out) {
#pragma HLS INLINE OFF
  /* Variable Declaration */
  int p0 = idx; // module id
  w_t8 local_w_ping[4][3][3][1];
  #pragma HLS BIND_STORAGE variable=local_w_ping core=RAM_1P_BRAM
  w_t8 local_w_pong[4][3][3][1];
  #pragma HLS BIND_STORAGE variable=local_w_pong core=RAM_1P_BRAM
  bool arb = 0;
  bool inter_trans_en = 1;
  bool intra_trans_en = 0;
  int c1, c1_prev;
  int c2, c2_prev;
  int c3, c3_prev;
  /* Variable Declaration */

  {
    for (ap_uint<5> c1 = 0; c1 <= 15; c1 += 1)
      for (ap_uint<7> c2 = 0; c2 <= 63; c2 += 1)
        for (ap_uint<2> c3 = 0; c3 <= 1; c3 += 1) {
          // array
          // io_L3
          {
            if (arb == 0) {
              w_IO_L2_in_inter_trans(
                /* module id */ idx, 
                /* host iter */ c1, 
                /* host iter */ c2, 
                /* host iter */ c3, 
                /* array */ local_w_pong, 
                /* fifo */ fifo_w_in, 
                /* fifo */ fifo_w_out, 
                /* enable */ inter_trans_en
              );
              w_IO_L2_in_intra_trans(
                /* module id */ idx, 
                /* host iter */ c1_prev, 
                /* host iter */ c2_prev, 
                /* host iter */ c3_prev, 
                /* array */ local_w_ping, 
                /* fifo */ fifo_w_local_out, 
                /* enable */ intra_trans_en
              );
            } else {
              w_IO_L2_in_inter_trans(
                /* module id */ idx, 
                /* host iter */ c1, 
                /* host iter */ c2, 
                /* host iter */ c3, 
                /* array */ local_w_ping, 
                /* fifo */ fifo_w_in, 
                /* fifo */ fifo_w_out, 
                /* enable */ inter_trans_en
              );
              w_IO_L2_in_intra_trans(
                /* module id */ idx, 
                /* host iter */ c1_prev, 
                /* host iter */ c2_prev, 
                /* host iter */ c3_prev, 
                /* array */ local_w_pong, 
                /* fifo */ fifo_w_local_out, 
                /* enable */ intra_trans_en
              );
            }
            intra_trans_en = 1;
            arb = !arb;
            c1_prev = c1;
            c2_prev = c2;
            c3_prev = c3;
          }
        }
    if (arb == 0) {
      w_IO_L2_in_intra_trans(
        /* module id */ idx, 
        /* host iter */ c1_prev, 
        /* host iter */ c2_prev, 
        /* host iter */ c3_prev, 
        /* array */ local_w_ping, 
        /* fifo */ fifo_w_local_out, 
        /* enable */ intra_trans_en
      );
    } else {
      w_IO_L2_in_intra_trans(
        /* module id */ idx, 
        /* host iter */ c1_prev, 
        /* host iter */ c2_prev, 
        /* host iter */ c3_prev, 
        /* array */ local_w_pong, 
        /* fifo */ fifo_w_local_out, 
        /* enable */ intra_trans_en
      );
    }
  }
}
/* Module Definition */

/* Module Definition */
void w_IO_L2_in_boundary(int idx, hls::stream<w_t8> &fifo_w_in, hls::stream<w_t8> &fifo_w_local_out) {
#pragma HLS INLINE OFF
  /* Variable Declaration */
  int p0 = idx; // module id
  w_t8 local_w_ping[4][3][3][1];
  #pragma HLS BIND_STORAGE variable=local_w_ping core=RAM_1P_BRAM
  w_t8 local_w_pong[4][3][3][1];
  #pragma HLS BIND_STORAGE variable=local_w_pong core=RAM_1P_BRAM
  bool arb = 0;
  bool inter_trans_en = 1;
  bool intra_trans_en = 0;
  int c1, c1_prev;
  int c2, c2_prev;
  int c3, c3_prev;
  /* Variable Declaration */

  {
    for (ap_uint<5> c1 = 0; c1 <= 15; c1 += 1)
      for (ap_uint<7> c2 = 0; c2 <= 63; c2 += 1)
        for (ap_uint<2> c3 = 0; c3 <= 1; c3 += 1) {
          // array
          // io_L3
          {
            if (arb == 0) {
              w_IO_L2_in_inter_trans_boundary(
                /* module id */ idx, 
                /* host iter */ c1, 
                /* host iter */ c2, 
                /* host iter */ c3, 
                /* array */ local_w_pong, 
                /* fifo */ fifo_w_in, 
                /* enable */ inter_trans_en
              );
              w_IO_L2_in_intra_trans(
                /* module id */ idx, 
                /* host iter */ c1_prev, 
                /* host iter */ c2_prev, 
                /* host iter */ c3_prev, 
                /* array */ local_w_ping, 
                /* fifo */ fifo_w_local_out, 
                /* enable */ intra_trans_en
              );
            } else {
              w_IO_L2_in_inter_trans_boundary(
                /* module id */ idx, 
                /* host iter */ c1, 
                /* host iter */ c2, 
                /* host iter */ c3, 
                /* array */ local_w_ping, 
                /* fifo */ fifo_w_in, 
                /* enable */ inter_trans_en
              );
              w_IO_L2_in_intra_trans(
                /* module id */ idx, 
                /* host iter */ c1_prev, 
                /* host iter */ c2_prev, 
                /* host iter */ c3_prev, 
                /* array */ local_w_pong, 
                /* fifo */ fifo_w_local_out, 
                /* enable */ intra_trans_en
              );
            }
            intra_trans_en = 1;
            arb = !arb;
            c1_prev = c1;
            c2_prev = c2;
            c3_prev = c3;
          }
        }
    if (arb == 0) {
      w_IO_L2_in_intra_trans(
        /* module id */ idx, 
        /* host iter */ c1_prev, 
        /* host iter */ c2_prev, 
        /* host iter */ c3_prev, 
        /* array */ local_w_ping, 
        /* fifo */ fifo_w_local_out, 
        /* enable */ intra_trans_en
      );
    } else {
      w_IO_L2_in_intra_trans(
        /* module id */ idx, 
        /* host iter */ c1_prev, 
        /* host iter */ c2_prev, 
        /* host iter */ c3_prev, 
        /* array */ local_w_pong, 
        /* fifo */ fifo_w_local_out, 
        /* enable */ intra_trans_en
      );
    }
  }
}
/* Module Definition */

/* Module Definition */
void PE(int idx, int idy, hls::stream<cin_t8> &fifo_cin_in, hls::stream<cin_t8> &fifo_cin_out, hls::stream<float> &fifo_cout_drain_out, hls::stream<w_t8> &fifo_w_in, hls::stream<w_t8> &fifo_w_out) {
#pragma HLS INLINE OFF
  /* Variable Declaration */
  int p0 = idx, p1 = idy; // module id
  cin_t1 local_cin[1][1][8];
  #pragma HLS ARRAY_PARTITION variable=local_cin dim=0 complete
  cout_t1 local_cout[1][4][4];
  #pragma HLS BIND_STORAGE variable=local_cout type=RAM_2P impl=BRAM
  w_t1 local_w[1][1][1][8];
  #pragma HLS ARRAY_PARTITION variable=local_w dim=0 complete
  /* Variable Declaration */

  for (ap_uint<5> c1 = 0; c1 <= 15; c1 += 1)
    for (ap_uint<7> c2 = 0; c2 <= 63; c2 += 1)
      for (ap_uint<2> c3 = 0; c3 <= 1; c3 += 1) {
        // array
        // pe
        for (ap_uint<2> c6 = 0; c6 <= 1; c6 += 1)
          for (ap_uint<3> c8 = 0; c8 <= 2; c8 += 1)
            for (ap_uint<3> c9 = 0; c9 <= 2; c9 += 1) {
              // latency
              for (ap_uint<3> c10 = 0; c10 <= 3; c10 += 1) {
                // latency
                for (ap_uint<2> c11 = 0; c11 <= 1; c11 += 1) {
                #pragma HLS PIPELINE II=1
                  {
                    {
                      cin_t8 fifo_data;
                      fifo_data = fifo_cin_in.read();
                      for (ap_uint<4> n = 0; n < 8; n++) {
                      #pragma HLS UNROLL
                        union {unsigned int ui; float ut;} u;
                        u.ui = (unsigned int)fifo_data(31, 0);
                        local_cin[0][0][n] = u.ut;
                        fifo_data = fifo_data >> 32;
                      }
                    }
                    {
                      w_t8 fifo_data;
                      fifo_data = fifo_w_in.read();
                      for (ap_uint<4> n = 0; n < 8; n++) {
                      #pragma HLS UNROLL
                        union {unsigned int ui; float ut;} u;
                        u.ui = (unsigned int)fifo_data(31, 0);
                        local_w[0][0][0][n] = u.ut;
                        fifo_data = fifo_data >> 32;
                      }
                    }
                    // simd
                    for (ap_uint<4> c12 = 0; c12 <= 7; c12 += 1) {
                    #pragma HLS UNROLL
                      local_cout[0][c11 + 2*c6][c10] = (local_cout[0][c11 + 2*c6][c10] + (local_cin[0][0][c12] * local_w[0][0][0][c12]));
                    }
                    {
                      w_t8 fifo_data;
                      union {unsigned int ui; float ut;} u7, u6, u5, u4, u3, u2, u1, u0;
                      u7.ut = local_w[0][0][0][7];
                      u6.ut = local_w[0][0][0][6];
                      u5.ut = local_w[0][0][0][5];
                      u4.ut = local_w[0][0][0][4];
                      u3.ut = local_w[0][0][0][3];
                      u2.ut = local_w[0][0][0][2];
                      u1.ut = local_w[0][0][0][1];
                      u0.ut = local_w[0][0][0][0];
                      fifo_data = (ap_uint<32>(u7.ui), ap_uint<32>(u6.ui), ap_uint<32>(u5.ui), ap_uint<32>(u4.ui), ap_uint<32>(u3.ui), ap_uint<32>(u2.ui), ap_uint<32>(u1.ui), ap_uint<32>(u0.ui));
                      fifo_w_out.write(fifo_data);
                    }
                    if (c3 == 1 && c8 == 2 && c9 == 2)
                      fifo_cout_drain_out.write(local_cout[0][c11 + 2*c6][c10]);
                    {
                      cin_t8 fifo_data;
                      union {unsigned int ui; float ut;} u7, u6, u5, u4, u3, u2, u1, u0;
                      u7.ut = local_cin[0][0][7];
                      u6.ut = local_cin[0][0][6];
                      u5.ut = local_cin[0][0][5];
                      u4.ut = local_cin[0][0][4];
                      u3.ut = local_cin[0][0][3];
                      u2.ut = local_cin[0][0][2];
                      u1.ut = local_cin[0][0][1];
                      u0.ut = local_cin[0][0][0];
                      fifo_data = (ap_uint<32>(u7.ui), ap_uint<32>(u6.ui), ap_uint<32>(u5.ui), ap_uint<32>(u4.ui), ap_uint<32>(u3.ui), ap_uint<32>(u2.ui), ap_uint<32>(u1.ui), ap_uint<32>(u0.ui));
                      fifo_cin_out.write(fifo_data);
                    }
                  }
                }
              }
            }
      }
}
/* Module Definition */

/* Module Definition */
void PE_wrapper(int idx, int idy, hls::stream<cin_t8> &fifo_cin_in, hls::stream<cin_t8> &fifo_cin_out, hls::stream<float> &fifo_cout_drain_out, hls::stream<w_t8> &fifo_w_in, hls::stream<w_t8> &fifo_w_out)
 {
  PE(
    /* module id */ idx, 
    /* module id */ idy, 
    /* fifo */ fifo_cin_in, 
    /* fifo */ fifo_cin_out, 
    /* fifo */ fifo_cout_drain_out, 
    /* fifo */ fifo_w_in, 
    /* fifo */ fifo_w_out);
}
/* Module Definition */

/* Module Definition */
void cin_PE_dummy_in(int idx, int idy, hls::stream<cin_t8> &fifo_cin_in) {
  /* Variable Declaration */
  int p0 = idx, p1 = idy; // module id
  /* Variable Declaration */

  for (ap_uint<5> c1 = 0; c1 <= 15; c1 += 1)
    for (ap_uint<7> c2 = 0; c2 <= 63; c2 += 1)
      for (ap_uint<2> c3 = 0; c3 <= 1; c3 += 1) {
        // array
        // pe
        for (ap_uint<2> c6 = 0; c6 <= 1; c6 += 1)
          for (ap_uint<3> c8 = 0; c8 <= 2; c8 += 1)
            for (ap_uint<3> c9 = 0; c9 <= 2; c9 += 1) {
              // latency
              for (ap_uint<3> c10 = 0; c10 <= 3; c10 += 1) {
                // latency
                for (ap_uint<2> c11 = 0; c11 <= 1; c11 += 1) {
                #pragma HLS PIPELINE II=1
                  cin_t8 fifo_data;
                  fifo_data = fifo_cin_in.read();
                }
              }
            }
      }
}
/* Module Definition */

/* Module Definition */
void w_PE_dummy_in(int idx, int idy, hls::stream<w_t8> &fifo_w_in) {
  /* Variable Declaration */
  int p0 = idx, p1 = idy; // module id
  /* Variable Declaration */

  for (ap_uint<5> c1 = 0; c1 <= 15; c1 += 1)
    for (ap_uint<7> c2 = 0; c2 <= 63; c2 += 1)
      for (ap_uint<2> c3 = 0; c3 <= 1; c3 += 1) {
        // array
        // pe
        for (ap_uint<2> c6 = 0; c6 <= 1; c6 += 1)
          for (ap_uint<3> c8 = 0; c8 <= 2; c8 += 1)
            for (ap_uint<3> c9 = 0; c9 <= 2; c9 += 1) {
              // latency
              for (ap_uint<3> c10 = 0; c10 <= 3; c10 += 1) {
                // latency
                for (ap_uint<2> c11 = 0; c11 <= 1; c11 += 1) {
                #pragma HLS PIPELINE II=1
                  w_t8 fifo_data;
                  fifo_data = fifo_w_in.read();
                }
              }
            }
      }
}
/* Module Definition */

/* Module Definition */
void cout_drain_IO_L1_out_intra_trans(int idx, int idy, int c1, int c2, cout_t4 local_cout[1][4][1], hls::stream<float> &fifo_cout_drain_local_in) {
#pragma HLS INLINE
  /* Variable Declaration */
  int p0 = idx, p1 = idy; // module id
  ap_uint<32> data_split[4];
  #pragma HLS ARRAY_PARTITION variable=data_split complete
  /* Variable Declaration */


  // io_L1
  // pe
  for (ap_uint<2> c6 = 0; c6 <= 1; c6 += 1) {
    // latency
    for (ap_uint<3> c10 = 0; c10 <= 3; c10 += 1) {
      // latency
      for (ap_uint<2> c11 = 0; c11 <= 1; c11 += 1) {
      #pragma HLS PIPELINE II=1
        // simd
        {
          cout_t1 in_data;
          cout_t4 out_data;
          in_data = fifo_cout_drain_local_in.read();
          int split_idx = (c10) % 4;
          out_data = local_cout[0][c11 + 2*c6][c10 / 4];
          for (ap_uint<3> n = 0; n < 4; n++) {
          #pragma HLS UNROLL
            data_split[n] = out_data(31, 0);
            out_data = out_data >> 32;
          }
          union {unsigned int ui; float ut;} u;
          u.ut = in_data;
          data_split[split_idx] = ap_uint<32>(u.ui);
          out_data = (data_split[3], data_split[2], data_split[1], data_split[0]);          local_cout[0][c11 + 2*c6][c10 / 4] = out_data;
        }
      }
    }
  }
}
/* Module Definition */

/* Module Definition */
void cout_drain_IO_L1_out_inter_trans(int idx, int idy, int c1, int c2, cout_t4 local_cout[1][4][1], hls::stream<cout_t4> &fifo_cout_drain_in, hls::stream<cout_t4> &fifo_cout_drain_out) {
#pragma HLS INLINE
  /* Variable Declaration */
  int p0 = idx, p1 = idy; // module id
  /* Variable Declaration */

  for (ap_uint<3> c5 = p1; c5 <= 3; c5 += 1) {
    // io_L1
    if (c5 == p1) {
      for (ap_uint<3> c7 = 0; c7 <= 3; c7 += 1) {
      #pragma HLS PIPELINE II=1
        // access_coalesce
        {
          cout_t4 in_data;
          cout_t4 out_data;
          in_data = local_cout[0][c7][0];
          out_data = in_data;
          fifo_cout_drain_out.write(out_data);
        }
      }
    } else {
      for (ap_uint<3> c7 = 0; c7 <= 3; c7 += 1) {
      #pragma HLS PIPELINE II=1
        // access_coalesce
        {
          cout_t4 in_data;
          cout_t4 out_data;
          in_data = fifo_cout_drain_in.read();
          out_data = in_data;
          fifo_cout_drain_out.write(out_data);
        }
      }
    }
  }
}
/* Module Definition */

/* Module Definition */
void cout_drain_IO_L1_out_inter_trans_boundary(int idx, int idy, int c1, int c2, cout_t4 local_cout[1][4][1], hls::stream<cout_t4> &fifo_cout_drain_out) {
#pragma HLS INLINE
  /* Variable Declaration */
  int p0 = idx, p1 = idy; // module id
  /* Variable Declaration */

  for (ap_uint<3> c5 = p1; c5 <= 3; c5 += 1)
    if (c5 == p1) {
      // io_L1
      for (ap_uint<3> c7 = 0; c7 <= 3; c7 += 1) {
      #pragma HLS PIPELINE II=1
        // access_coalesce
        {
          cout_t4 in_data;
          cout_t4 out_data;
          in_data = local_cout[0][c7][0];
          out_data = in_data;
          fifo_cout_drain_out.write(out_data);
        }
      }
    }
}
/* Module Definition */

/* Module Definition */
void cout_drain_IO_L1_out(int idx, int idy, hls::stream<cout_t4> &fifo_cout_drain_in, hls::stream<cout_t4> &fifo_cout_drain_out, hls::stream<float> &fifo_cout_drain_local_in) {
#pragma HLS INLINE OFF
  /* Variable Declaration */
  int p0 = idx, p1 = idy; // module id
  cout_t4 local_cout[1][4][1];
  #pragma HLS BIND_STORAGE variable=local_cout type=RAM_2P impl=BRAM
  /* Variable Declaration */

  for (ap_uint<5> c1 = 0; c1 <= 15; c1 += 1)
    for (ap_uint<7> c2 = 0; c2 <= 63; c2 += 1) {
      // array
      // io_L3
      // io_L2
      cout_drain_IO_L1_out_intra_trans(
        /* module id */ idx, 
        /* module id */ idy, 
        /* host iter */ c1, 
        /* host iter */ c2, 
        /* array */ local_cout, 
        /* fifo */ fifo_cout_drain_local_in
      );
      cout_drain_IO_L1_out_inter_trans(
        /* module id */ idx, 
        /* module id */ idy, 
        /* host iter */ c1, 
        /* host iter */ c2, 
        /* array */ local_cout, 
        /* fifo */ fifo_cout_drain_in, 
        /* fifo */ fifo_cout_drain_out
      );
    }
}
/* Module Definition */

/* Module Definition */
void cout_drain_IO_L1_out_wrapper(int idx, int idy, hls::stream<cout_t4> &fifo_cout_drain_in, hls::stream<cout_t4> &fifo_cout_drain_out, hls::stream<float> &fifo_cout_drain_local_in)
 {
  cout_drain_IO_L1_out(
    /* module id */ idx, 
    /* module id */ idy, 
    /* fifo */ fifo_cout_drain_in, 
    /* fifo */ fifo_cout_drain_out, 
    /* fifo */ fifo_cout_drain_local_in);
}
/* Module Definition */

/* Module Definition */
void cout_drain_IO_L1_out_boundary(int idx, int idy, hls::stream<cout_t4> &fifo_cout_drain_out, hls::stream<float> &fifo_cout_drain_local_in) {
#pragma HLS INLINE
  /* Variable Declaration */
  int p0 = idx, p1 = idy; // module id
  cout_t4 local_cout[1][4][1];
  #pragma HLS BIND_STORAGE variable=local_cout type=RAM_2P impl=BRAM
  /* Variable Declaration */

  for (ap_uint<5> c1 = 0; c1 <= 15; c1 += 1)
    for (ap_uint<7> c2 = 0; c2 <= 63; c2 += 1) {
      // array
      // io_L3
      // io_L2
      cout_drain_IO_L1_out_intra_trans(
        /* module id */ idx, 
        /* module id */ idy, 
        /* host iter */ c1, 
        /* host iter */ c2, 
        /* array */ local_cout, 
        /* fifo */ fifo_cout_drain_local_in
      );
      cout_drain_IO_L1_out_inter_trans_boundary(
        /* module id */ idx, 
        /* module id */ idy, 
        /* host iter */ c1, 
        /* host iter */ c2, 
        /* array */ local_cout, 
        /* fifo */ fifo_cout_drain_out
      );
    }
}
/* Module Definition */

/* Module Definition */
void cout_drain_IO_L1_out_boundary_wrapper(int idx, int idy, hls::stream<cout_t4> &fifo_cout_drain_out, hls::stream<float> &fifo_cout_drain_local_in)
 {
  cout_drain_IO_L1_out_boundary(
    /* module id */ idx, 
    /* module id */ idy, 
    /* fifo */ fifo_cout_drain_out, 
    /* fifo */ fifo_cout_drain_local_in);
}
/* Module Definition */

/* Module Definition */
void cout_drain_IO_L2_out(int idx, hls::stream<cout_t4> &fifo_cout_drain_in, hls::stream<cout_t4> &fifo_cout_drain_out, hls::stream<cout_t4> &fifo_cout_drain_local_in) {
#pragma HLS INLINE OFF
  /* Variable Declaration */
  int p0 = idx; // module id
  /* Variable Declaration */

  for (ap_uint<5> c1 = 0; c1 <= 15; c1 += 1)
    for (ap_uint<7> c2 = 0; c2 <= 63; c2 += 1) {
      // array
      // io_L3
      for (ap_uint<5> c4 = p0; c4 <= 15; c4 += 1) {
        // io_L2
        if (c4 == p0) {
          for (ap_uint<3> c5 = 0; c5 <= 3; c5 += 1) {
            // io_L1
            for (ap_uint<3> c7 = 0; c7 <= 3; c7 += 1) {
            #pragma HLS PIPELINE II=1
              // access_coalesce
              {
                cout_t4 in_data;
                cout_t4 out_data;
                in_data = fifo_cout_drain_local_in.read();
                out_data = in_data;
                fifo_cout_drain_out.write(out_data);
              }
            }
          }
        } else {
          for (ap_uint<3> c5 = 0; c5 <= 3; c5 += 1) {
            // io_L1
            for (ap_uint<3> c7 = 0; c7 <= 3; c7 += 1) {
            #pragma HLS PIPELINE II=1
              // access_coalesce
              {
                cout_t4 in_data;
                cout_t4 out_data;
                in_data = fifo_cout_drain_in.read();
                out_data = in_data;
                fifo_cout_drain_out.write(out_data);
              }
            }
          }
        }
      }
    }
}
/* Module Definition */

/* Module Definition */
void cout_drain_IO_L2_out_boundary(int idx, hls::stream<cout_t4> &fifo_cout_drain_out, hls::stream<cout_t4> &fifo_cout_drain_local_in) {
#pragma HLS INLINE OFF
  /* Variable Declaration */
  int p0 = idx; // module id
  /* Variable Declaration */

  for (ap_uint<5> c1 = 0; c1 <= 15; c1 += 1)
    for (ap_uint<7> c2 = 0; c2 <= 63; c2 += 1) {
      // array
      // io_L3
      for (ap_uint<5> c4 = p0; c4 <= 15; c4 += 1)
        if (c4 == p0) {
          // io_L2
          for (ap_uint<3> c5 = 0; c5 <= 3; c5 += 1) {
            // io_L1
            for (ap_uint<3> c7 = 0; c7 <= 3; c7 += 1) {
            #pragma HLS PIPELINE II=1
              // access_coalesce
              {
                cout_t4 in_data;
                cout_t4 out_data;
                in_data = fifo_cout_drain_local_in.read();
                out_data = in_data;
                fifo_cout_drain_out.write(out_data);
              }
            }
          }
        }
    }
}
/* Module Definition */

/* Module Definition */
void cout_drain_IO_L3_out(hls::stream<cout_t4> &fifo_cout_drain_out, hls::stream<cout_t4> &fifo_cout_drain_local_in) {
#pragma HLS INLINE OFF
  /* Variable Declaration */
  /* Variable Declaration */

  for (ap_uint<5> c1 = 0; c1 <= 15; c1 += 1)
    for (ap_uint<7> c2 = 0; c2 <= 63; c2 += 1) {
      // array
      // io_L3
      for (ap_uint<5> c4 = 0; c4 <= 15; c4 += 1) {
        // io_L2
        for (ap_uint<3> c5 = 0; c5 <= 3; c5 += 1) {
          // io_L1
          for (ap_uint<3> c7 = 0; c7 <= 3; c7 += 1) {
          #pragma HLS PIPELINE II=1
            // access_coalesce
            // access_serialize
            {
              cout_t4 in_data;
              cout_t4 out_data;
              in_data = fifo_cout_drain_local_in.read();
              out_data = in_data;
              fifo_cout_drain_out.write(out_data);
            }
          }
        }
      }
    }
}
/* Module Definition */

/* Module Definition */
void cout_drain_IO_L3_out_serialize(cout_t16 *cout, hls::stream<cout_t4> &fifo_cout_drain_local_in) {
#pragma HLS INLINE OFF
  /* Variable Declaration */
  /* Variable Declaration */

  for (ap_uint<17> i = 0; i < 65536; i++) {
  #pragma HLS PIPELINE II=1
    cout_t4 fifo_data;
    cout_t16 mem_data;
    cout_t4 mem_data_split[4];
    #pragma HLS ARRAY_PARTITION variable=mem_data_split complete
    for (ap_uint<3> p = 0; p < 4; p++) {
      fifo_data = fifo_cout_drain_local_in.read();
      mem_data_split[p] = fifo_data;
    }
    mem_data = (mem_data_split[3], mem_data_split[2], mem_data_split[1], mem_data_split[0]);
    cout[i] = mem_data;
  }
}
/* Module Definition */

extern "C" {
void kernel0(cin_t16 *cin, cout_t16 *cout, w_t16 *w)
{
#pragma HLS INTERFACE m_axi port=cin offset=slave bundle=gmem_cin
#pragma HLS INTERFACE m_axi port=cout offset=slave bundle=gmem_cout
#pragma HLS INTERFACE m_axi port=w offset=slave bundle=gmem_w
#pragma HLS INTERFACE s_axilite port=cin bundle=control
#pragma HLS INTERFACE s_axilite port=cout bundle=control
#pragma HLS INTERFACE s_axilite port=w bundle=control
#pragma HLS INTERFACE s_axilite port=return bundle=control

#pragma HLS DATAFLOW

  /* FIFO Declaration */
  /* cin_IO_L3_in_serialize fifo */ hls::stream<cin_t8> fifo_cin_cin_IO_L3_in_serialize;
  #pragma HLS STREAM variable=fifo_cin_cin_IO_L3_in_serialize depth=2
  /* w_IO_L3_in_serialize fifo */ hls::stream<w_t8> fifo_w_w_IO_L3_in_serialize;
  #pragma HLS STREAM variable=fifo_w_w_IO_L3_in_serialize depth=2
  /* cout_drain_IO_L3_out_serialize fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L3_out_serialize;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L3_out_serialize depth=2
  /* cin_IO_L2_in fifo */ hls::stream<cin_t8> fifo_cin_cin_IO_L2_in_0;
  #pragma HLS STREAM variable=fifo_cin_cin_IO_L2_in_0 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_cin_IO_L2_in_0 type=FIFO impl=SRL
  /* cin_IO_L2_in fifo */ hls::stream<cin_t8> fifo_cin_cin_IO_L2_in_1;
  #pragma HLS STREAM variable=fifo_cin_cin_IO_L2_in_1 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_cin_IO_L2_in_1 type=FIFO impl=SRL
  /* cin_IO_L2_in fifo */ hls::stream<cin_t8> fifo_cin_cin_IO_L2_in_2;
  #pragma HLS STREAM variable=fifo_cin_cin_IO_L2_in_2 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_cin_IO_L2_in_2 type=FIFO impl=SRL
  /* cin_IO_L2_in fifo */ hls::stream<cin_t8> fifo_cin_cin_IO_L2_in_3;
  #pragma HLS STREAM variable=fifo_cin_cin_IO_L2_in_3 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_cin_IO_L2_in_3 type=FIFO impl=SRL
  /* cin_IO_L2_in fifo */ hls::stream<cin_t8> fifo_cin_cin_IO_L2_in_4;
  #pragma HLS STREAM variable=fifo_cin_cin_IO_L2_in_4 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_cin_IO_L2_in_4 type=FIFO impl=SRL
  /* cin_IO_L2_in fifo */ hls::stream<cin_t8> fifo_cin_cin_IO_L2_in_5;
  #pragma HLS STREAM variable=fifo_cin_cin_IO_L2_in_5 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_cin_IO_L2_in_5 type=FIFO impl=SRL
  /* cin_IO_L2_in fifo */ hls::stream<cin_t8> fifo_cin_cin_IO_L2_in_6;
  #pragma HLS STREAM variable=fifo_cin_cin_IO_L2_in_6 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_cin_IO_L2_in_6 type=FIFO impl=SRL
  /* cin_IO_L2_in fifo */ hls::stream<cin_t8> fifo_cin_cin_IO_L2_in_7;
  #pragma HLS STREAM variable=fifo_cin_cin_IO_L2_in_7 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_cin_IO_L2_in_7 type=FIFO impl=SRL
  /* cin_IO_L2_in fifo */ hls::stream<cin_t8> fifo_cin_cin_IO_L2_in_8;
  #pragma HLS STREAM variable=fifo_cin_cin_IO_L2_in_8 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_cin_IO_L2_in_8 type=FIFO impl=SRL
  /* cin_IO_L2_in fifo */ hls::stream<cin_t8> fifo_cin_cin_IO_L2_in_9;
  #pragma HLS STREAM variable=fifo_cin_cin_IO_L2_in_9 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_cin_IO_L2_in_9 type=FIFO impl=SRL
  /* cin_IO_L2_in fifo */ hls::stream<cin_t8> fifo_cin_cin_IO_L2_in_10;
  #pragma HLS STREAM variable=fifo_cin_cin_IO_L2_in_10 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_cin_IO_L2_in_10 type=FIFO impl=SRL
  /* cin_IO_L2_in fifo */ hls::stream<cin_t8> fifo_cin_cin_IO_L2_in_11;
  #pragma HLS STREAM variable=fifo_cin_cin_IO_L2_in_11 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_cin_IO_L2_in_11 type=FIFO impl=SRL
  /* cin_IO_L2_in fifo */ hls::stream<cin_t8> fifo_cin_cin_IO_L2_in_12;
  #pragma HLS STREAM variable=fifo_cin_cin_IO_L2_in_12 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_cin_IO_L2_in_12 type=FIFO impl=SRL
  /* cin_IO_L2_in fifo */ hls::stream<cin_t8> fifo_cin_cin_IO_L2_in_13;
  #pragma HLS STREAM variable=fifo_cin_cin_IO_L2_in_13 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_cin_IO_L2_in_13 type=FIFO impl=SRL
  /* cin_IO_L2_in fifo */ hls::stream<cin_t8> fifo_cin_cin_IO_L2_in_14;
  #pragma HLS STREAM variable=fifo_cin_cin_IO_L2_in_14 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_cin_IO_L2_in_14 type=FIFO impl=SRL
  /* cin_IO_L2_in fifo */ hls::stream<cin_t8> fifo_cin_cin_IO_L2_in_15;
  #pragma HLS STREAM variable=fifo_cin_cin_IO_L2_in_15 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_cin_IO_L2_in_15 type=FIFO impl=SRL
  /* cin_IO_L2_in fifo */ hls::stream<cin_t8> fifo_cin_cin_IO_L2_in_16;
  #pragma HLS STREAM variable=fifo_cin_cin_IO_L2_in_16 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_cin_IO_L2_in_16 type=FIFO impl=SRL
  /* w_IO_L2_in fifo */ hls::stream<w_t8> fifo_w_w_IO_L2_in_0;
  #pragma HLS STREAM variable=fifo_w_w_IO_L2_in_0 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_w_IO_L2_in_0 type=FIFO impl=SRL
  /* w_IO_L2_in fifo */ hls::stream<w_t8> fifo_w_w_IO_L2_in_1;
  #pragma HLS STREAM variable=fifo_w_w_IO_L2_in_1 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_w_IO_L2_in_1 type=FIFO impl=SRL
  /* w_IO_L2_in fifo */ hls::stream<w_t8> fifo_w_w_IO_L2_in_2;
  #pragma HLS STREAM variable=fifo_w_w_IO_L2_in_2 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_w_IO_L2_in_2 type=FIFO impl=SRL
  /* w_IO_L2_in fifo */ hls::stream<w_t8> fifo_w_w_IO_L2_in_3;
  #pragma HLS STREAM variable=fifo_w_w_IO_L2_in_3 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_w_IO_L2_in_3 type=FIFO impl=SRL
  /* w_IO_L2_in fifo */ hls::stream<w_t8> fifo_w_w_IO_L2_in_4;
  #pragma HLS STREAM variable=fifo_w_w_IO_L2_in_4 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_w_IO_L2_in_4 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_0_0;
  #pragma HLS STREAM variable=fifo_cin_PE_0_0 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_0_0 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_1_0;
  #pragma HLS STREAM variable=fifo_cin_PE_1_0 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_1_0 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_2_0;
  #pragma HLS STREAM variable=fifo_cin_PE_2_0 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_2_0 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_3_0;
  #pragma HLS STREAM variable=fifo_cin_PE_3_0 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_3_0 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_4_0;
  #pragma HLS STREAM variable=fifo_cin_PE_4_0 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_4_0 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_0_1;
  #pragma HLS STREAM variable=fifo_cin_PE_0_1 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_0_1 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_1_1;
  #pragma HLS STREAM variable=fifo_cin_PE_1_1 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_1_1 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_2_1;
  #pragma HLS STREAM variable=fifo_cin_PE_2_1 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_2_1 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_3_1;
  #pragma HLS STREAM variable=fifo_cin_PE_3_1 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_3_1 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_4_1;
  #pragma HLS STREAM variable=fifo_cin_PE_4_1 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_4_1 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_0_2;
  #pragma HLS STREAM variable=fifo_cin_PE_0_2 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_0_2 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_1_2;
  #pragma HLS STREAM variable=fifo_cin_PE_1_2 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_1_2 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_2_2;
  #pragma HLS STREAM variable=fifo_cin_PE_2_2 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_2_2 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_3_2;
  #pragma HLS STREAM variable=fifo_cin_PE_3_2 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_3_2 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_4_2;
  #pragma HLS STREAM variable=fifo_cin_PE_4_2 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_4_2 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_0_3;
  #pragma HLS STREAM variable=fifo_cin_PE_0_3 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_0_3 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_1_3;
  #pragma HLS STREAM variable=fifo_cin_PE_1_3 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_1_3 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_2_3;
  #pragma HLS STREAM variable=fifo_cin_PE_2_3 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_2_3 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_3_3;
  #pragma HLS STREAM variable=fifo_cin_PE_3_3 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_3_3 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_4_3;
  #pragma HLS STREAM variable=fifo_cin_PE_4_3 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_4_3 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_0_4;
  #pragma HLS STREAM variable=fifo_cin_PE_0_4 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_0_4 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_1_4;
  #pragma HLS STREAM variable=fifo_cin_PE_1_4 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_1_4 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_2_4;
  #pragma HLS STREAM variable=fifo_cin_PE_2_4 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_2_4 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_3_4;
  #pragma HLS STREAM variable=fifo_cin_PE_3_4 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_3_4 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_4_4;
  #pragma HLS STREAM variable=fifo_cin_PE_4_4 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_4_4 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_0_5;
  #pragma HLS STREAM variable=fifo_cin_PE_0_5 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_0_5 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_1_5;
  #pragma HLS STREAM variable=fifo_cin_PE_1_5 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_1_5 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_2_5;
  #pragma HLS STREAM variable=fifo_cin_PE_2_5 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_2_5 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_3_5;
  #pragma HLS STREAM variable=fifo_cin_PE_3_5 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_3_5 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_4_5;
  #pragma HLS STREAM variable=fifo_cin_PE_4_5 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_4_5 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_0_6;
  #pragma HLS STREAM variable=fifo_cin_PE_0_6 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_0_6 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_1_6;
  #pragma HLS STREAM variable=fifo_cin_PE_1_6 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_1_6 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_2_6;
  #pragma HLS STREAM variable=fifo_cin_PE_2_6 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_2_6 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_3_6;
  #pragma HLS STREAM variable=fifo_cin_PE_3_6 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_3_6 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_4_6;
  #pragma HLS STREAM variable=fifo_cin_PE_4_6 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_4_6 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_0_7;
  #pragma HLS STREAM variable=fifo_cin_PE_0_7 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_0_7 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_1_7;
  #pragma HLS STREAM variable=fifo_cin_PE_1_7 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_1_7 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_2_7;
  #pragma HLS STREAM variable=fifo_cin_PE_2_7 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_2_7 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_3_7;
  #pragma HLS STREAM variable=fifo_cin_PE_3_7 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_3_7 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_4_7;
  #pragma HLS STREAM variable=fifo_cin_PE_4_7 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_4_7 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_0_8;
  #pragma HLS STREAM variable=fifo_cin_PE_0_8 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_0_8 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_1_8;
  #pragma HLS STREAM variable=fifo_cin_PE_1_8 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_1_8 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_2_8;
  #pragma HLS STREAM variable=fifo_cin_PE_2_8 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_2_8 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_3_8;
  #pragma HLS STREAM variable=fifo_cin_PE_3_8 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_3_8 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_4_8;
  #pragma HLS STREAM variable=fifo_cin_PE_4_8 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_4_8 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_0_9;
  #pragma HLS STREAM variable=fifo_cin_PE_0_9 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_0_9 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_1_9;
  #pragma HLS STREAM variable=fifo_cin_PE_1_9 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_1_9 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_2_9;
  #pragma HLS STREAM variable=fifo_cin_PE_2_9 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_2_9 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_3_9;
  #pragma HLS STREAM variable=fifo_cin_PE_3_9 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_3_9 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_4_9;
  #pragma HLS STREAM variable=fifo_cin_PE_4_9 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_4_9 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_0_10;
  #pragma HLS STREAM variable=fifo_cin_PE_0_10 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_0_10 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_1_10;
  #pragma HLS STREAM variable=fifo_cin_PE_1_10 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_1_10 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_2_10;
  #pragma HLS STREAM variable=fifo_cin_PE_2_10 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_2_10 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_3_10;
  #pragma HLS STREAM variable=fifo_cin_PE_3_10 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_3_10 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_4_10;
  #pragma HLS STREAM variable=fifo_cin_PE_4_10 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_4_10 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_0_11;
  #pragma HLS STREAM variable=fifo_cin_PE_0_11 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_0_11 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_1_11;
  #pragma HLS STREAM variable=fifo_cin_PE_1_11 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_1_11 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_2_11;
  #pragma HLS STREAM variable=fifo_cin_PE_2_11 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_2_11 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_3_11;
  #pragma HLS STREAM variable=fifo_cin_PE_3_11 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_3_11 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_4_11;
  #pragma HLS STREAM variable=fifo_cin_PE_4_11 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_4_11 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_0_12;
  #pragma HLS STREAM variable=fifo_cin_PE_0_12 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_0_12 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_1_12;
  #pragma HLS STREAM variable=fifo_cin_PE_1_12 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_1_12 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_2_12;
  #pragma HLS STREAM variable=fifo_cin_PE_2_12 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_2_12 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_3_12;
  #pragma HLS STREAM variable=fifo_cin_PE_3_12 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_3_12 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_4_12;
  #pragma HLS STREAM variable=fifo_cin_PE_4_12 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_4_12 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_0_13;
  #pragma HLS STREAM variable=fifo_cin_PE_0_13 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_0_13 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_1_13;
  #pragma HLS STREAM variable=fifo_cin_PE_1_13 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_1_13 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_2_13;
  #pragma HLS STREAM variable=fifo_cin_PE_2_13 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_2_13 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_3_13;
  #pragma HLS STREAM variable=fifo_cin_PE_3_13 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_3_13 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_4_13;
  #pragma HLS STREAM variable=fifo_cin_PE_4_13 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_4_13 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_0_14;
  #pragma HLS STREAM variable=fifo_cin_PE_0_14 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_0_14 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_1_14;
  #pragma HLS STREAM variable=fifo_cin_PE_1_14 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_1_14 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_2_14;
  #pragma HLS STREAM variable=fifo_cin_PE_2_14 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_2_14 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_3_14;
  #pragma HLS STREAM variable=fifo_cin_PE_3_14 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_3_14 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_4_14;
  #pragma HLS STREAM variable=fifo_cin_PE_4_14 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_4_14 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_0_15;
  #pragma HLS STREAM variable=fifo_cin_PE_0_15 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_0_15 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_1_15;
  #pragma HLS STREAM variable=fifo_cin_PE_1_15 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_1_15 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_2_15;
  #pragma HLS STREAM variable=fifo_cin_PE_2_15 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_2_15 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_3_15;
  #pragma HLS STREAM variable=fifo_cin_PE_3_15 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_3_15 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<cin_t8> fifo_cin_PE_4_15;
  #pragma HLS STREAM variable=fifo_cin_PE_4_15 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cin_PE_4_15 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_0_0;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_0_0 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_0_0 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_1_0;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_1_0 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_1_0 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_2_0;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_2_0 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_2_0 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_3_0;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_3_0 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_3_0 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_0_1;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_0_1 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_0_1 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_1_1;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_1_1 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_1_1 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_2_1;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_2_1 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_2_1 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_3_1;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_3_1 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_3_1 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_0_2;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_0_2 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_0_2 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_1_2;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_1_2 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_1_2 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_2_2;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_2_2 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_2_2 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_3_2;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_3_2 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_3_2 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_0_3;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_0_3 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_0_3 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_1_3;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_1_3 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_1_3 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_2_3;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_2_3 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_2_3 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_3_3;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_3_3 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_3_3 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_0_4;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_0_4 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_0_4 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_1_4;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_1_4 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_1_4 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_2_4;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_2_4 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_2_4 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_3_4;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_3_4 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_3_4 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_0_5;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_0_5 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_0_5 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_1_5;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_1_5 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_1_5 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_2_5;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_2_5 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_2_5 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_3_5;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_3_5 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_3_5 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_0_6;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_0_6 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_0_6 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_1_6;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_1_6 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_1_6 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_2_6;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_2_6 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_2_6 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_3_6;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_3_6 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_3_6 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_0_7;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_0_7 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_0_7 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_1_7;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_1_7 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_1_7 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_2_7;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_2_7 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_2_7 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_3_7;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_3_7 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_3_7 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_0_8;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_0_8 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_0_8 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_1_8;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_1_8 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_1_8 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_2_8;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_2_8 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_2_8 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_3_8;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_3_8 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_3_8 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_0_9;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_0_9 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_0_9 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_1_9;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_1_9 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_1_9 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_2_9;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_2_9 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_2_9 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_3_9;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_3_9 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_3_9 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_0_10;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_0_10 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_0_10 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_1_10;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_1_10 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_1_10 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_2_10;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_2_10 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_2_10 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_3_10;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_3_10 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_3_10 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_0_11;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_0_11 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_0_11 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_1_11;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_1_11 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_1_11 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_2_11;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_2_11 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_2_11 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_3_11;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_3_11 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_3_11 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_0_12;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_0_12 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_0_12 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_1_12;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_1_12 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_1_12 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_2_12;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_2_12 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_2_12 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_3_12;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_3_12 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_3_12 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_0_13;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_0_13 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_0_13 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_1_13;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_1_13 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_1_13 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_2_13;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_2_13 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_2_13 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_3_13;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_3_13 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_3_13 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_0_14;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_0_14 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_0_14 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_1_14;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_1_14 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_1_14 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_2_14;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_2_14 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_2_14 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_3_14;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_3_14 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_3_14 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_0_15;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_0_15 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_0_15 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_1_15;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_1_15 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_1_15 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_2_15;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_2_15 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_2_15 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<float> fifo_cout_drain_PE_3_15;
  #pragma HLS STREAM variable=fifo_cout_drain_PE_3_15 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_PE_3_15 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_0_0;
  #pragma HLS STREAM variable=fifo_w_PE_0_0 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_0_0 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_0_1;
  #pragma HLS STREAM variable=fifo_w_PE_0_1 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_0_1 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_0_2;
  #pragma HLS STREAM variable=fifo_w_PE_0_2 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_0_2 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_0_3;
  #pragma HLS STREAM variable=fifo_w_PE_0_3 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_0_3 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_0_4;
  #pragma HLS STREAM variable=fifo_w_PE_0_4 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_0_4 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_0_5;
  #pragma HLS STREAM variable=fifo_w_PE_0_5 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_0_5 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_0_6;
  #pragma HLS STREAM variable=fifo_w_PE_0_6 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_0_6 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_0_7;
  #pragma HLS STREAM variable=fifo_w_PE_0_7 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_0_7 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_0_8;
  #pragma HLS STREAM variable=fifo_w_PE_0_8 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_0_8 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_0_9;
  #pragma HLS STREAM variable=fifo_w_PE_0_9 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_0_9 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_0_10;
  #pragma HLS STREAM variable=fifo_w_PE_0_10 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_0_10 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_0_11;
  #pragma HLS STREAM variable=fifo_w_PE_0_11 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_0_11 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_0_12;
  #pragma HLS STREAM variable=fifo_w_PE_0_12 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_0_12 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_0_13;
  #pragma HLS STREAM variable=fifo_w_PE_0_13 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_0_13 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_0_14;
  #pragma HLS STREAM variable=fifo_w_PE_0_14 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_0_14 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_0_15;
  #pragma HLS STREAM variable=fifo_w_PE_0_15 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_0_15 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_0_16;
  #pragma HLS STREAM variable=fifo_w_PE_0_16 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_0_16 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_1_0;
  #pragma HLS STREAM variable=fifo_w_PE_1_0 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_1_0 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_1_1;
  #pragma HLS STREAM variable=fifo_w_PE_1_1 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_1_1 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_1_2;
  #pragma HLS STREAM variable=fifo_w_PE_1_2 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_1_2 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_1_3;
  #pragma HLS STREAM variable=fifo_w_PE_1_3 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_1_3 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_1_4;
  #pragma HLS STREAM variable=fifo_w_PE_1_4 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_1_4 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_1_5;
  #pragma HLS STREAM variable=fifo_w_PE_1_5 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_1_5 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_1_6;
  #pragma HLS STREAM variable=fifo_w_PE_1_6 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_1_6 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_1_7;
  #pragma HLS STREAM variable=fifo_w_PE_1_7 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_1_7 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_1_8;
  #pragma HLS STREAM variable=fifo_w_PE_1_8 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_1_8 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_1_9;
  #pragma HLS STREAM variable=fifo_w_PE_1_9 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_1_9 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_1_10;
  #pragma HLS STREAM variable=fifo_w_PE_1_10 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_1_10 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_1_11;
  #pragma HLS STREAM variable=fifo_w_PE_1_11 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_1_11 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_1_12;
  #pragma HLS STREAM variable=fifo_w_PE_1_12 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_1_12 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_1_13;
  #pragma HLS STREAM variable=fifo_w_PE_1_13 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_1_13 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_1_14;
  #pragma HLS STREAM variable=fifo_w_PE_1_14 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_1_14 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_1_15;
  #pragma HLS STREAM variable=fifo_w_PE_1_15 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_1_15 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_1_16;
  #pragma HLS STREAM variable=fifo_w_PE_1_16 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_1_16 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_2_0;
  #pragma HLS STREAM variable=fifo_w_PE_2_0 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_2_0 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_2_1;
  #pragma HLS STREAM variable=fifo_w_PE_2_1 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_2_1 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_2_2;
  #pragma HLS STREAM variable=fifo_w_PE_2_2 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_2_2 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_2_3;
  #pragma HLS STREAM variable=fifo_w_PE_2_3 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_2_3 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_2_4;
  #pragma HLS STREAM variable=fifo_w_PE_2_4 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_2_4 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_2_5;
  #pragma HLS STREAM variable=fifo_w_PE_2_5 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_2_5 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_2_6;
  #pragma HLS STREAM variable=fifo_w_PE_2_6 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_2_6 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_2_7;
  #pragma HLS STREAM variable=fifo_w_PE_2_7 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_2_7 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_2_8;
  #pragma HLS STREAM variable=fifo_w_PE_2_8 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_2_8 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_2_9;
  #pragma HLS STREAM variable=fifo_w_PE_2_9 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_2_9 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_2_10;
  #pragma HLS STREAM variable=fifo_w_PE_2_10 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_2_10 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_2_11;
  #pragma HLS STREAM variable=fifo_w_PE_2_11 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_2_11 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_2_12;
  #pragma HLS STREAM variable=fifo_w_PE_2_12 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_2_12 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_2_13;
  #pragma HLS STREAM variable=fifo_w_PE_2_13 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_2_13 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_2_14;
  #pragma HLS STREAM variable=fifo_w_PE_2_14 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_2_14 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_2_15;
  #pragma HLS STREAM variable=fifo_w_PE_2_15 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_2_15 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_2_16;
  #pragma HLS STREAM variable=fifo_w_PE_2_16 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_2_16 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_3_0;
  #pragma HLS STREAM variable=fifo_w_PE_3_0 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_3_0 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_3_1;
  #pragma HLS STREAM variable=fifo_w_PE_3_1 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_3_1 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_3_2;
  #pragma HLS STREAM variable=fifo_w_PE_3_2 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_3_2 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_3_3;
  #pragma HLS STREAM variable=fifo_w_PE_3_3 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_3_3 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_3_4;
  #pragma HLS STREAM variable=fifo_w_PE_3_4 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_3_4 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_3_5;
  #pragma HLS STREAM variable=fifo_w_PE_3_5 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_3_5 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_3_6;
  #pragma HLS STREAM variable=fifo_w_PE_3_6 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_3_6 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_3_7;
  #pragma HLS STREAM variable=fifo_w_PE_3_7 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_3_7 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_3_8;
  #pragma HLS STREAM variable=fifo_w_PE_3_8 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_3_8 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_3_9;
  #pragma HLS STREAM variable=fifo_w_PE_3_9 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_3_9 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_3_10;
  #pragma HLS STREAM variable=fifo_w_PE_3_10 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_3_10 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_3_11;
  #pragma HLS STREAM variable=fifo_w_PE_3_11 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_3_11 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_3_12;
  #pragma HLS STREAM variable=fifo_w_PE_3_12 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_3_12 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_3_13;
  #pragma HLS STREAM variable=fifo_w_PE_3_13 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_3_13 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_3_14;
  #pragma HLS STREAM variable=fifo_w_PE_3_14 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_3_14 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_3_15;
  #pragma HLS STREAM variable=fifo_w_PE_3_15 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_3_15 type=FIFO impl=SRL
  /* PE fifo */ hls::stream<w_t8> fifo_w_PE_3_16;
  #pragma HLS STREAM variable=fifo_w_PE_3_16 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_w_PE_3_16 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_0_0;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_0_0 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_0_0 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_0_1;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_0_1 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_0_1 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_0_2;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_0_2 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_0_2 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_0_3;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_0_3 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_0_3 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_0_4;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_0_4 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_0_4 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_1_0;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_1_0 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_1_0 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_1_1;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_1_1 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_1_1 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_1_2;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_1_2 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_1_2 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_1_3;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_1_3 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_1_3 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_1_4;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_1_4 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_1_4 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_2_0;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_2_0 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_2_0 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_2_1;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_2_1 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_2_1 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_2_2;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_2_2 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_2_2 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_2_3;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_2_3 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_2_3 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_2_4;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_2_4 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_2_4 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_3_0;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_3_0 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_3_0 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_3_1;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_3_1 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_3_1 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_3_2;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_3_2 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_3_2 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_3_3;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_3_3 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_3_3 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_3_4;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_3_4 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_3_4 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_4_0;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_4_0 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_4_0 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_4_1;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_4_1 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_4_1 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_4_2;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_4_2 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_4_2 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_4_3;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_4_3 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_4_3 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_4_4;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_4_4 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_4_4 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_5_0;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_5_0 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_5_0 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_5_1;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_5_1 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_5_1 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_5_2;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_5_2 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_5_2 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_5_3;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_5_3 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_5_3 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_5_4;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_5_4 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_5_4 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_6_0;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_6_0 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_6_0 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_6_1;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_6_1 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_6_1 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_6_2;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_6_2 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_6_2 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_6_3;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_6_3 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_6_3 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_6_4;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_6_4 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_6_4 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_7_0;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_7_0 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_7_0 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_7_1;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_7_1 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_7_1 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_7_2;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_7_2 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_7_2 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_7_3;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_7_3 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_7_3 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_7_4;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_7_4 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_7_4 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_8_0;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_8_0 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_8_0 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_8_1;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_8_1 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_8_1 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_8_2;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_8_2 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_8_2 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_8_3;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_8_3 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_8_3 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_8_4;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_8_4 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_8_4 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_9_0;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_9_0 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_9_0 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_9_1;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_9_1 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_9_1 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_9_2;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_9_2 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_9_2 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_9_3;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_9_3 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_9_3 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_9_4;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_9_4 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_9_4 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_10_0;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_10_0 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_10_0 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_10_1;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_10_1 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_10_1 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_10_2;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_10_2 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_10_2 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_10_3;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_10_3 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_10_3 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_10_4;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_10_4 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_10_4 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_11_0;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_11_0 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_11_0 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_11_1;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_11_1 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_11_1 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_11_2;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_11_2 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_11_2 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_11_3;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_11_3 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_11_3 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_11_4;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_11_4 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_11_4 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_12_0;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_12_0 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_12_0 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_12_1;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_12_1 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_12_1 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_12_2;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_12_2 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_12_2 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_12_3;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_12_3 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_12_3 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_12_4;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_12_4 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_12_4 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_13_0;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_13_0 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_13_0 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_13_1;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_13_1 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_13_1 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_13_2;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_13_2 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_13_2 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_13_3;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_13_3 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_13_3 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_13_4;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_13_4 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_13_4 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_14_0;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_14_0 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_14_0 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_14_1;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_14_1 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_14_1 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_14_2;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_14_2 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_14_2 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_14_3;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_14_3 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_14_3 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_14_4;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_14_4 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_14_4 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_15_0;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_15_0 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_15_0 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_15_1;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_15_1 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_15_1 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_15_2;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_15_2 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_15_2 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_15_3;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_15_3 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_15_3 type=FIFO impl=SRL
  /* cout_drain_IO_L1_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L1_out_15_4;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L1_out_15_4 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L1_out_15_4 type=FIFO impl=SRL
  /* cout_drain_IO_L2_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L2_out_0;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L2_out_0 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L2_out_0 type=FIFO impl=SRL
  /* cout_drain_IO_L2_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L2_out_1;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L2_out_1 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L2_out_1 type=FIFO impl=SRL
  /* cout_drain_IO_L2_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L2_out_2;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L2_out_2 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L2_out_2 type=FIFO impl=SRL
  /* cout_drain_IO_L2_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L2_out_3;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L2_out_3 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L2_out_3 type=FIFO impl=SRL
  /* cout_drain_IO_L2_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L2_out_4;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L2_out_4 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L2_out_4 type=FIFO impl=SRL
  /* cout_drain_IO_L2_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L2_out_5;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L2_out_5 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L2_out_5 type=FIFO impl=SRL
  /* cout_drain_IO_L2_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L2_out_6;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L2_out_6 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L2_out_6 type=FIFO impl=SRL
  /* cout_drain_IO_L2_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L2_out_7;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L2_out_7 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L2_out_7 type=FIFO impl=SRL
  /* cout_drain_IO_L2_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L2_out_8;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L2_out_8 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L2_out_8 type=FIFO impl=SRL
  /* cout_drain_IO_L2_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L2_out_9;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L2_out_9 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L2_out_9 type=FIFO impl=SRL
  /* cout_drain_IO_L2_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L2_out_10;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L2_out_10 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L2_out_10 type=FIFO impl=SRL
  /* cout_drain_IO_L2_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L2_out_11;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L2_out_11 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L2_out_11 type=FIFO impl=SRL
  /* cout_drain_IO_L2_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L2_out_12;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L2_out_12 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L2_out_12 type=FIFO impl=SRL
  /* cout_drain_IO_L2_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L2_out_13;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L2_out_13 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L2_out_13 type=FIFO impl=SRL
  /* cout_drain_IO_L2_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L2_out_14;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L2_out_14 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L2_out_14 type=FIFO impl=SRL
  /* cout_drain_IO_L2_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L2_out_15;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L2_out_15 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L2_out_15 type=FIFO impl=SRL
  /* cout_drain_IO_L2_out fifo */ hls::stream<cout_t4> fifo_cout_drain_cout_drain_IO_L2_out_16;
  #pragma HLS STREAM variable=fifo_cout_drain_cout_drain_IO_L2_out_16 depth=2
  #pragma HLS BIND_STORAGE variable=fifo_cout_drain_cout_drain_IO_L2_out_16 type=FIFO impl=SRL
  /* FIFO Declaration */

  /* Module Call */
  cin_IO_L3_in_serialize(
    /* array */ cin,
    /* fifo */ fifo_cin_cin_IO_L3_in_serialize
  );
  /* Module Call */

  /* Module Call */
  cin_IO_L3_in(
    /* fifo */ fifo_cin_cin_IO_L3_in_serialize,
    /* fifo */ fifo_cin_cin_IO_L2_in_0
  );
  /* Module Call */

  /* Module Call */
  cin_IO_L2_in(
    /* module id */ 0,
    /* fifo */ fifo_cin_cin_IO_L2_in_0,
    /* fifo */ fifo_cin_cin_IO_L2_in_1,
    /* fifo */ fifo_cin_PE_0_0
  );
  /* Module Call */

  /* Module Call */
  cin_IO_L2_in(
    /* module id */ 1,
    /* fifo */ fifo_cin_cin_IO_L2_in_1,
    /* fifo */ fifo_cin_cin_IO_L2_in_2,
    /* fifo */ fifo_cin_PE_0_1
  );
  /* Module Call */

  /* Module Call */
  cin_IO_L2_in(
    /* module id */ 2,
    /* fifo */ fifo_cin_cin_IO_L2_in_2,
    /* fifo */ fifo_cin_cin_IO_L2_in_3,
    /* fifo */ fifo_cin_PE_0_2
  );
  /* Module Call */

  /* Module Call */
  cin_IO_L2_in(
    /* module id */ 3,
    /* fifo */ fifo_cin_cin_IO_L2_in_3,
    /* fifo */ fifo_cin_cin_IO_L2_in_4,
    /* fifo */ fifo_cin_PE_0_3
  );
  /* Module Call */

  /* Module Call */
  cin_IO_L2_in(
    /* module id */ 4,
    /* fifo */ fifo_cin_cin_IO_L2_in_4,
    /* fifo */ fifo_cin_cin_IO_L2_in_5,
    /* fifo */ fifo_cin_PE_0_4
  );
  /* Module Call */

  /* Module Call */
  cin_IO_L2_in(
    /* module id */ 5,
    /* fifo */ fifo_cin_cin_IO_L2_in_5,
    /* fifo */ fifo_cin_cin_IO_L2_in_6,
    /* fifo */ fifo_cin_PE_0_5
  );
  /* Module Call */

  /* Module Call */
  cin_IO_L2_in(
    /* module id */ 6,
    /* fifo */ fifo_cin_cin_IO_L2_in_6,
    /* fifo */ fifo_cin_cin_IO_L2_in_7,
    /* fifo */ fifo_cin_PE_0_6
  );
  /* Module Call */

  /* Module Call */
  cin_IO_L2_in(
    /* module id */ 7,
    /* fifo */ fifo_cin_cin_IO_L2_in_7,
    /* fifo */ fifo_cin_cin_IO_L2_in_8,
    /* fifo */ fifo_cin_PE_0_7
  );
  /* Module Call */

  /* Module Call */
  cin_IO_L2_in(
    /* module id */ 8,
    /* fifo */ fifo_cin_cin_IO_L2_in_8,
    /* fifo */ fifo_cin_cin_IO_L2_in_9,
    /* fifo */ fifo_cin_PE_0_8
  );
  /* Module Call */

  /* Module Call */
  cin_IO_L2_in(
    /* module id */ 9,
    /* fifo */ fifo_cin_cin_IO_L2_in_9,
    /* fifo */ fifo_cin_cin_IO_L2_in_10,
    /* fifo */ fifo_cin_PE_0_9
  );
  /* Module Call */

  /* Module Call */
  cin_IO_L2_in(
    /* module id */ 10,
    /* fifo */ fifo_cin_cin_IO_L2_in_10,
    /* fifo */ fifo_cin_cin_IO_L2_in_11,
    /* fifo */ fifo_cin_PE_0_10
  );
  /* Module Call */

  /* Module Call */
  cin_IO_L2_in(
    /* module id */ 11,
    /* fifo */ fifo_cin_cin_IO_L2_in_11,
    /* fifo */ fifo_cin_cin_IO_L2_in_12,
    /* fifo */ fifo_cin_PE_0_11
  );
  /* Module Call */

  /* Module Call */
  cin_IO_L2_in(
    /* module id */ 12,
    /* fifo */ fifo_cin_cin_IO_L2_in_12,
    /* fifo */ fifo_cin_cin_IO_L2_in_13,
    /* fifo */ fifo_cin_PE_0_12
  );
  /* Module Call */

  /* Module Call */
  cin_IO_L2_in(
    /* module id */ 13,
    /* fifo */ fifo_cin_cin_IO_L2_in_13,
    /* fifo */ fifo_cin_cin_IO_L2_in_14,
    /* fifo */ fifo_cin_PE_0_13
  );
  /* Module Call */

  /* Module Call */
  cin_IO_L2_in(
    /* module id */ 14,
    /* fifo */ fifo_cin_cin_IO_L2_in_14,
    /* fifo */ fifo_cin_cin_IO_L2_in_15,
    /* fifo */ fifo_cin_PE_0_14
  );
  /* Module Call */

  /* Module Call */
  cin_IO_L2_in_boundary(
    /* module id */ 15,
    /* fifo */ fifo_cin_cin_IO_L2_in_15,
    /* fifo */ fifo_cin_PE_0_15
  );
  /* Module Call */

  /* Module Call */
  w_IO_L3_in_serialize(
    /* array */ w,
    /* fifo */ fifo_w_w_IO_L3_in_serialize
  );
  /* Module Call */

  /* Module Call */
  w_IO_L3_in(
    /* fifo */ fifo_w_w_IO_L3_in_serialize,
    /* fifo */ fifo_w_w_IO_L2_in_0
  );
  /* Module Call */

  /* Module Call */
  w_IO_L2_in(
    /* module id */ 0,
    /* fifo */ fifo_w_w_IO_L2_in_0,
    /* fifo */ fifo_w_w_IO_L2_in_1,
    /* fifo */ fifo_w_PE_0_0
  );
  /* Module Call */

  /* Module Call */
  w_IO_L2_in(
    /* module id */ 1,
    /* fifo */ fifo_w_w_IO_L2_in_1,
    /* fifo */ fifo_w_w_IO_L2_in_2,
    /* fifo */ fifo_w_PE_1_0
  );
  /* Module Call */

  /* Module Call */
  w_IO_L2_in(
    /* module id */ 2,
    /* fifo */ fifo_w_w_IO_L2_in_2,
    /* fifo */ fifo_w_w_IO_L2_in_3,
    /* fifo */ fifo_w_PE_2_0
  );
  /* Module Call */

  /* Module Call */
  w_IO_L2_in_boundary(
    /* module id */ 3,
    /* fifo */ fifo_w_w_IO_L2_in_3,
    /* fifo */ fifo_w_PE_3_0
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 0,
    /* module id */ 0,
    /* fifo */ fifo_cin_PE_0_0,
    /* fifo */ fifo_cin_PE_1_0,
    /* fifo */ fifo_cout_drain_PE_0_0,
    /* fifo */ fifo_w_PE_0_0,
    /* fifo */ fifo_w_PE_0_1
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 0,
    /* module id */ 1,
    /* fifo */ fifo_cin_PE_0_1,
    /* fifo */ fifo_cin_PE_1_1,
    /* fifo */ fifo_cout_drain_PE_0_1,
    /* fifo */ fifo_w_PE_0_1,
    /* fifo */ fifo_w_PE_0_2
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 0,
    /* module id */ 2,
    /* fifo */ fifo_cin_PE_0_2,
    /* fifo */ fifo_cin_PE_1_2,
    /* fifo */ fifo_cout_drain_PE_0_2,
    /* fifo */ fifo_w_PE_0_2,
    /* fifo */ fifo_w_PE_0_3
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 0,
    /* module id */ 3,
    /* fifo */ fifo_cin_PE_0_3,
    /* fifo */ fifo_cin_PE_1_3,
    /* fifo */ fifo_cout_drain_PE_0_3,
    /* fifo */ fifo_w_PE_0_3,
    /* fifo */ fifo_w_PE_0_4
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 0,
    /* module id */ 4,
    /* fifo */ fifo_cin_PE_0_4,
    /* fifo */ fifo_cin_PE_1_4,
    /* fifo */ fifo_cout_drain_PE_0_4,
    /* fifo */ fifo_w_PE_0_4,
    /* fifo */ fifo_w_PE_0_5
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 0,
    /* module id */ 5,
    /* fifo */ fifo_cin_PE_0_5,
    /* fifo */ fifo_cin_PE_1_5,
    /* fifo */ fifo_cout_drain_PE_0_5,
    /* fifo */ fifo_w_PE_0_5,
    /* fifo */ fifo_w_PE_0_6
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 0,
    /* module id */ 6,
    /* fifo */ fifo_cin_PE_0_6,
    /* fifo */ fifo_cin_PE_1_6,
    /* fifo */ fifo_cout_drain_PE_0_6,
    /* fifo */ fifo_w_PE_0_6,
    /* fifo */ fifo_w_PE_0_7
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 0,
    /* module id */ 7,
    /* fifo */ fifo_cin_PE_0_7,
    /* fifo */ fifo_cin_PE_1_7,
    /* fifo */ fifo_cout_drain_PE_0_7,
    /* fifo */ fifo_w_PE_0_7,
    /* fifo */ fifo_w_PE_0_8
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 0,
    /* module id */ 8,
    /* fifo */ fifo_cin_PE_0_8,
    /* fifo */ fifo_cin_PE_1_8,
    /* fifo */ fifo_cout_drain_PE_0_8,
    /* fifo */ fifo_w_PE_0_8,
    /* fifo */ fifo_w_PE_0_9
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 0,
    /* module id */ 9,
    /* fifo */ fifo_cin_PE_0_9,
    /* fifo */ fifo_cin_PE_1_9,
    /* fifo */ fifo_cout_drain_PE_0_9,
    /* fifo */ fifo_w_PE_0_9,
    /* fifo */ fifo_w_PE_0_10
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 0,
    /* module id */ 10,
    /* fifo */ fifo_cin_PE_0_10,
    /* fifo */ fifo_cin_PE_1_10,
    /* fifo */ fifo_cout_drain_PE_0_10,
    /* fifo */ fifo_w_PE_0_10,
    /* fifo */ fifo_w_PE_0_11
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 0,
    /* module id */ 11,
    /* fifo */ fifo_cin_PE_0_11,
    /* fifo */ fifo_cin_PE_1_11,
    /* fifo */ fifo_cout_drain_PE_0_11,
    /* fifo */ fifo_w_PE_0_11,
    /* fifo */ fifo_w_PE_0_12
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 0,
    /* module id */ 12,
    /* fifo */ fifo_cin_PE_0_12,
    /* fifo */ fifo_cin_PE_1_12,
    /* fifo */ fifo_cout_drain_PE_0_12,
    /* fifo */ fifo_w_PE_0_12,
    /* fifo */ fifo_w_PE_0_13
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 0,
    /* module id */ 13,
    /* fifo */ fifo_cin_PE_0_13,
    /* fifo */ fifo_cin_PE_1_13,
    /* fifo */ fifo_cout_drain_PE_0_13,
    /* fifo */ fifo_w_PE_0_13,
    /* fifo */ fifo_w_PE_0_14
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 0,
    /* module id */ 14,
    /* fifo */ fifo_cin_PE_0_14,
    /* fifo */ fifo_cin_PE_1_14,
    /* fifo */ fifo_cout_drain_PE_0_14,
    /* fifo */ fifo_w_PE_0_14,
    /* fifo */ fifo_w_PE_0_15
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 0,
    /* module id */ 15,
    /* fifo */ fifo_cin_PE_0_15,
    /* fifo */ fifo_cin_PE_1_15,
    /* fifo */ fifo_cout_drain_PE_0_15,
    /* fifo */ fifo_w_PE_0_15,
    /* fifo */ fifo_w_PE_0_16
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 1,
    /* module id */ 0,
    /* fifo */ fifo_cin_PE_1_0,
    /* fifo */ fifo_cin_PE_2_0,
    /* fifo */ fifo_cout_drain_PE_1_0,
    /* fifo */ fifo_w_PE_1_0,
    /* fifo */ fifo_w_PE_1_1
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 1,
    /* module id */ 1,
    /* fifo */ fifo_cin_PE_1_1,
    /* fifo */ fifo_cin_PE_2_1,
    /* fifo */ fifo_cout_drain_PE_1_1,
    /* fifo */ fifo_w_PE_1_1,
    /* fifo */ fifo_w_PE_1_2
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 1,
    /* module id */ 2,
    /* fifo */ fifo_cin_PE_1_2,
    /* fifo */ fifo_cin_PE_2_2,
    /* fifo */ fifo_cout_drain_PE_1_2,
    /* fifo */ fifo_w_PE_1_2,
    /* fifo */ fifo_w_PE_1_3
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 1,
    /* module id */ 3,
    /* fifo */ fifo_cin_PE_1_3,
    /* fifo */ fifo_cin_PE_2_3,
    /* fifo */ fifo_cout_drain_PE_1_3,
    /* fifo */ fifo_w_PE_1_3,
    /* fifo */ fifo_w_PE_1_4
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 1,
    /* module id */ 4,
    /* fifo */ fifo_cin_PE_1_4,
    /* fifo */ fifo_cin_PE_2_4,
    /* fifo */ fifo_cout_drain_PE_1_4,
    /* fifo */ fifo_w_PE_1_4,
    /* fifo */ fifo_w_PE_1_5
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 1,
    /* module id */ 5,
    /* fifo */ fifo_cin_PE_1_5,
    /* fifo */ fifo_cin_PE_2_5,
    /* fifo */ fifo_cout_drain_PE_1_5,
    /* fifo */ fifo_w_PE_1_5,
    /* fifo */ fifo_w_PE_1_6
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 1,
    /* module id */ 6,
    /* fifo */ fifo_cin_PE_1_6,
    /* fifo */ fifo_cin_PE_2_6,
    /* fifo */ fifo_cout_drain_PE_1_6,
    /* fifo */ fifo_w_PE_1_6,
    /* fifo */ fifo_w_PE_1_7
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 1,
    /* module id */ 7,
    /* fifo */ fifo_cin_PE_1_7,
    /* fifo */ fifo_cin_PE_2_7,
    /* fifo */ fifo_cout_drain_PE_1_7,
    /* fifo */ fifo_w_PE_1_7,
    /* fifo */ fifo_w_PE_1_8
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 1,
    /* module id */ 8,
    /* fifo */ fifo_cin_PE_1_8,
    /* fifo */ fifo_cin_PE_2_8,
    /* fifo */ fifo_cout_drain_PE_1_8,
    /* fifo */ fifo_w_PE_1_8,
    /* fifo */ fifo_w_PE_1_9
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 1,
    /* module id */ 9,
    /* fifo */ fifo_cin_PE_1_9,
    /* fifo */ fifo_cin_PE_2_9,
    /* fifo */ fifo_cout_drain_PE_1_9,
    /* fifo */ fifo_w_PE_1_9,
    /* fifo */ fifo_w_PE_1_10
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 1,
    /* module id */ 10,
    /* fifo */ fifo_cin_PE_1_10,
    /* fifo */ fifo_cin_PE_2_10,
    /* fifo */ fifo_cout_drain_PE_1_10,
    /* fifo */ fifo_w_PE_1_10,
    /* fifo */ fifo_w_PE_1_11
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 1,
    /* module id */ 11,
    /* fifo */ fifo_cin_PE_1_11,
    /* fifo */ fifo_cin_PE_2_11,
    /* fifo */ fifo_cout_drain_PE_1_11,
    /* fifo */ fifo_w_PE_1_11,
    /* fifo */ fifo_w_PE_1_12
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 1,
    /* module id */ 12,
    /* fifo */ fifo_cin_PE_1_12,
    /* fifo */ fifo_cin_PE_2_12,
    /* fifo */ fifo_cout_drain_PE_1_12,
    /* fifo */ fifo_w_PE_1_12,
    /* fifo */ fifo_w_PE_1_13
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 1,
    /* module id */ 13,
    /* fifo */ fifo_cin_PE_1_13,
    /* fifo */ fifo_cin_PE_2_13,
    /* fifo */ fifo_cout_drain_PE_1_13,
    /* fifo */ fifo_w_PE_1_13,
    /* fifo */ fifo_w_PE_1_14
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 1,
    /* module id */ 14,
    /* fifo */ fifo_cin_PE_1_14,
    /* fifo */ fifo_cin_PE_2_14,
    /* fifo */ fifo_cout_drain_PE_1_14,
    /* fifo */ fifo_w_PE_1_14,
    /* fifo */ fifo_w_PE_1_15
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 1,
    /* module id */ 15,
    /* fifo */ fifo_cin_PE_1_15,
    /* fifo */ fifo_cin_PE_2_15,
    /* fifo */ fifo_cout_drain_PE_1_15,
    /* fifo */ fifo_w_PE_1_15,
    /* fifo */ fifo_w_PE_1_16
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 2,
    /* module id */ 0,
    /* fifo */ fifo_cin_PE_2_0,
    /* fifo */ fifo_cin_PE_3_0,
    /* fifo */ fifo_cout_drain_PE_2_0,
    /* fifo */ fifo_w_PE_2_0,
    /* fifo */ fifo_w_PE_2_1
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 2,
    /* module id */ 1,
    /* fifo */ fifo_cin_PE_2_1,
    /* fifo */ fifo_cin_PE_3_1,
    /* fifo */ fifo_cout_drain_PE_2_1,
    /* fifo */ fifo_w_PE_2_1,
    /* fifo */ fifo_w_PE_2_2
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 2,
    /* module id */ 2,
    /* fifo */ fifo_cin_PE_2_2,
    /* fifo */ fifo_cin_PE_3_2,
    /* fifo */ fifo_cout_drain_PE_2_2,
    /* fifo */ fifo_w_PE_2_2,
    /* fifo */ fifo_w_PE_2_3
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 2,
    /* module id */ 3,
    /* fifo */ fifo_cin_PE_2_3,
    /* fifo */ fifo_cin_PE_3_3,
    /* fifo */ fifo_cout_drain_PE_2_3,
    /* fifo */ fifo_w_PE_2_3,
    /* fifo */ fifo_w_PE_2_4
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 2,
    /* module id */ 4,
    /* fifo */ fifo_cin_PE_2_4,
    /* fifo */ fifo_cin_PE_3_4,
    /* fifo */ fifo_cout_drain_PE_2_4,
    /* fifo */ fifo_w_PE_2_4,
    /* fifo */ fifo_w_PE_2_5
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 2,
    /* module id */ 5,
    /* fifo */ fifo_cin_PE_2_5,
    /* fifo */ fifo_cin_PE_3_5,
    /* fifo */ fifo_cout_drain_PE_2_5,
    /* fifo */ fifo_w_PE_2_5,
    /* fifo */ fifo_w_PE_2_6
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 2,
    /* module id */ 6,
    /* fifo */ fifo_cin_PE_2_6,
    /* fifo */ fifo_cin_PE_3_6,
    /* fifo */ fifo_cout_drain_PE_2_6,
    /* fifo */ fifo_w_PE_2_6,
    /* fifo */ fifo_w_PE_2_7
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 2,
    /* module id */ 7,
    /* fifo */ fifo_cin_PE_2_7,
    /* fifo */ fifo_cin_PE_3_7,
    /* fifo */ fifo_cout_drain_PE_2_7,
    /* fifo */ fifo_w_PE_2_7,
    /* fifo */ fifo_w_PE_2_8
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 2,
    /* module id */ 8,
    /* fifo */ fifo_cin_PE_2_8,
    /* fifo */ fifo_cin_PE_3_8,
    /* fifo */ fifo_cout_drain_PE_2_8,
    /* fifo */ fifo_w_PE_2_8,
    /* fifo */ fifo_w_PE_2_9
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 2,
    /* module id */ 9,
    /* fifo */ fifo_cin_PE_2_9,
    /* fifo */ fifo_cin_PE_3_9,
    /* fifo */ fifo_cout_drain_PE_2_9,
    /* fifo */ fifo_w_PE_2_9,
    /* fifo */ fifo_w_PE_2_10
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 2,
    /* module id */ 10,
    /* fifo */ fifo_cin_PE_2_10,
    /* fifo */ fifo_cin_PE_3_10,
    /* fifo */ fifo_cout_drain_PE_2_10,
    /* fifo */ fifo_w_PE_2_10,
    /* fifo */ fifo_w_PE_2_11
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 2,
    /* module id */ 11,
    /* fifo */ fifo_cin_PE_2_11,
    /* fifo */ fifo_cin_PE_3_11,
    /* fifo */ fifo_cout_drain_PE_2_11,
    /* fifo */ fifo_w_PE_2_11,
    /* fifo */ fifo_w_PE_2_12
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 2,
    /* module id */ 12,
    /* fifo */ fifo_cin_PE_2_12,
    /* fifo */ fifo_cin_PE_3_12,
    /* fifo */ fifo_cout_drain_PE_2_12,
    /* fifo */ fifo_w_PE_2_12,
    /* fifo */ fifo_w_PE_2_13
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 2,
    /* module id */ 13,
    /* fifo */ fifo_cin_PE_2_13,
    /* fifo */ fifo_cin_PE_3_13,
    /* fifo */ fifo_cout_drain_PE_2_13,
    /* fifo */ fifo_w_PE_2_13,
    /* fifo */ fifo_w_PE_2_14
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 2,
    /* module id */ 14,
    /* fifo */ fifo_cin_PE_2_14,
    /* fifo */ fifo_cin_PE_3_14,
    /* fifo */ fifo_cout_drain_PE_2_14,
    /* fifo */ fifo_w_PE_2_14,
    /* fifo */ fifo_w_PE_2_15
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 2,
    /* module id */ 15,
    /* fifo */ fifo_cin_PE_2_15,
    /* fifo */ fifo_cin_PE_3_15,
    /* fifo */ fifo_cout_drain_PE_2_15,
    /* fifo */ fifo_w_PE_2_15,
    /* fifo */ fifo_w_PE_2_16
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 3,
    /* module id */ 0,
    /* fifo */ fifo_cin_PE_3_0,
    /* fifo */ fifo_cin_PE_4_0,
    /* fifo */ fifo_cout_drain_PE_3_0,
    /* fifo */ fifo_w_PE_3_0,
    /* fifo */ fifo_w_PE_3_1
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 3,
    /* module id */ 1,
    /* fifo */ fifo_cin_PE_3_1,
    /* fifo */ fifo_cin_PE_4_1,
    /* fifo */ fifo_cout_drain_PE_3_1,
    /* fifo */ fifo_w_PE_3_1,
    /* fifo */ fifo_w_PE_3_2
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 3,
    /* module id */ 2,
    /* fifo */ fifo_cin_PE_3_2,
    /* fifo */ fifo_cin_PE_4_2,
    /* fifo */ fifo_cout_drain_PE_3_2,
    /* fifo */ fifo_w_PE_3_2,
    /* fifo */ fifo_w_PE_3_3
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 3,
    /* module id */ 3,
    /* fifo */ fifo_cin_PE_3_3,
    /* fifo */ fifo_cin_PE_4_3,
    /* fifo */ fifo_cout_drain_PE_3_3,
    /* fifo */ fifo_w_PE_3_3,
    /* fifo */ fifo_w_PE_3_4
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 3,
    /* module id */ 4,
    /* fifo */ fifo_cin_PE_3_4,
    /* fifo */ fifo_cin_PE_4_4,
    /* fifo */ fifo_cout_drain_PE_3_4,
    /* fifo */ fifo_w_PE_3_4,
    /* fifo */ fifo_w_PE_3_5
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 3,
    /* module id */ 5,
    /* fifo */ fifo_cin_PE_3_5,
    /* fifo */ fifo_cin_PE_4_5,
    /* fifo */ fifo_cout_drain_PE_3_5,
    /* fifo */ fifo_w_PE_3_5,
    /* fifo */ fifo_w_PE_3_6
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 3,
    /* module id */ 6,
    /* fifo */ fifo_cin_PE_3_6,
    /* fifo */ fifo_cin_PE_4_6,
    /* fifo */ fifo_cout_drain_PE_3_6,
    /* fifo */ fifo_w_PE_3_6,
    /* fifo */ fifo_w_PE_3_7
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 3,
    /* module id */ 7,
    /* fifo */ fifo_cin_PE_3_7,
    /* fifo */ fifo_cin_PE_4_7,
    /* fifo */ fifo_cout_drain_PE_3_7,
    /* fifo */ fifo_w_PE_3_7,
    /* fifo */ fifo_w_PE_3_8
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 3,
    /* module id */ 8,
    /* fifo */ fifo_cin_PE_3_8,
    /* fifo */ fifo_cin_PE_4_8,
    /* fifo */ fifo_cout_drain_PE_3_8,
    /* fifo */ fifo_w_PE_3_8,
    /* fifo */ fifo_w_PE_3_9
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 3,
    /* module id */ 9,
    /* fifo */ fifo_cin_PE_3_9,
    /* fifo */ fifo_cin_PE_4_9,
    /* fifo */ fifo_cout_drain_PE_3_9,
    /* fifo */ fifo_w_PE_3_9,
    /* fifo */ fifo_w_PE_3_10
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 3,
    /* module id */ 10,
    /* fifo */ fifo_cin_PE_3_10,
    /* fifo */ fifo_cin_PE_4_10,
    /* fifo */ fifo_cout_drain_PE_3_10,
    /* fifo */ fifo_w_PE_3_10,
    /* fifo */ fifo_w_PE_3_11
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 3,
    /* module id */ 11,
    /* fifo */ fifo_cin_PE_3_11,
    /* fifo */ fifo_cin_PE_4_11,
    /* fifo */ fifo_cout_drain_PE_3_11,
    /* fifo */ fifo_w_PE_3_11,
    /* fifo */ fifo_w_PE_3_12
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 3,
    /* module id */ 12,
    /* fifo */ fifo_cin_PE_3_12,
    /* fifo */ fifo_cin_PE_4_12,
    /* fifo */ fifo_cout_drain_PE_3_12,
    /* fifo */ fifo_w_PE_3_12,
    /* fifo */ fifo_w_PE_3_13
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 3,
    /* module id */ 13,
    /* fifo */ fifo_cin_PE_3_13,
    /* fifo */ fifo_cin_PE_4_13,
    /* fifo */ fifo_cout_drain_PE_3_13,
    /* fifo */ fifo_w_PE_3_13,
    /* fifo */ fifo_w_PE_3_14
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 3,
    /* module id */ 14,
    /* fifo */ fifo_cin_PE_3_14,
    /* fifo */ fifo_cin_PE_4_14,
    /* fifo */ fifo_cout_drain_PE_3_14,
    /* fifo */ fifo_w_PE_3_14,
    /* fifo */ fifo_w_PE_3_15
  );
  /* Module Call */

  /* Module Call */
  PE_wrapper(
    /* module id */ 3,
    /* module id */ 15,
    /* fifo */ fifo_cin_PE_3_15,
    /* fifo */ fifo_cin_PE_4_15,
    /* fifo */ fifo_cout_drain_PE_3_15,
    /* fifo */ fifo_w_PE_3_15,
    /* fifo */ fifo_w_PE_3_16
  );
  /* Module Call */

  /* Module Call */
  cin_PE_dummy_in(
    /* module id */ 3,
    /* module id */ 0,
    /* fifo */ fifo_cin_PE_4_0
  );
  /* Module Call */

  /* Module Call */
  cin_PE_dummy_in(
    /* module id */ 3,
    /* module id */ 1,
    /* fifo */ fifo_cin_PE_4_1
  );
  /* Module Call */

  /* Module Call */
  cin_PE_dummy_in(
    /* module id */ 3,
    /* module id */ 2,
    /* fifo */ fifo_cin_PE_4_2
  );
  /* Module Call */

  /* Module Call */
  cin_PE_dummy_in(
    /* module id */ 3,
    /* module id */ 3,
    /* fifo */ fifo_cin_PE_4_3
  );
  /* Module Call */

  /* Module Call */
  cin_PE_dummy_in(
    /* module id */ 3,
    /* module id */ 4,
    /* fifo */ fifo_cin_PE_4_4
  );
  /* Module Call */

  /* Module Call */
  cin_PE_dummy_in(
    /* module id */ 3,
    /* module id */ 5,
    /* fifo */ fifo_cin_PE_4_5
  );
  /* Module Call */

  /* Module Call */
  cin_PE_dummy_in(
    /* module id */ 3,
    /* module id */ 6,
    /* fifo */ fifo_cin_PE_4_6
  );
  /* Module Call */

  /* Module Call */
  cin_PE_dummy_in(
    /* module id */ 3,
    /* module id */ 7,
    /* fifo */ fifo_cin_PE_4_7
  );
  /* Module Call */

  /* Module Call */
  cin_PE_dummy_in(
    /* module id */ 3,
    /* module id */ 8,
    /* fifo */ fifo_cin_PE_4_8
  );
  /* Module Call */

  /* Module Call */
  cin_PE_dummy_in(
    /* module id */ 3,
    /* module id */ 9,
    /* fifo */ fifo_cin_PE_4_9
  );
  /* Module Call */

  /* Module Call */
  cin_PE_dummy_in(
    /* module id */ 3,
    /* module id */ 10,
    /* fifo */ fifo_cin_PE_4_10
  );
  /* Module Call */

  /* Module Call */
  cin_PE_dummy_in(
    /* module id */ 3,
    /* module id */ 11,
    /* fifo */ fifo_cin_PE_4_11
  );
  /* Module Call */

  /* Module Call */
  cin_PE_dummy_in(
    /* module id */ 3,
    /* module id */ 12,
    /* fifo */ fifo_cin_PE_4_12
  );
  /* Module Call */

  /* Module Call */
  cin_PE_dummy_in(
    /* module id */ 3,
    /* module id */ 13,
    /* fifo */ fifo_cin_PE_4_13
  );
  /* Module Call */

  /* Module Call */
  cin_PE_dummy_in(
    /* module id */ 3,
    /* module id */ 14,
    /* fifo */ fifo_cin_PE_4_14
  );
  /* Module Call */

  /* Module Call */
  cin_PE_dummy_in(
    /* module id */ 3,
    /* module id */ 15,
    /* fifo */ fifo_cin_PE_4_15
  );
  /* Module Call */

  /* Module Call */
  w_PE_dummy_in(
    /* module id */ 0,
    /* module id */ 15,
    /* fifo */ fifo_w_PE_0_16
  );
  /* Module Call */

  /* Module Call */
  w_PE_dummy_in(
    /* module id */ 1,
    /* module id */ 15,
    /* fifo */ fifo_w_PE_1_16
  );
  /* Module Call */

  /* Module Call */
  w_PE_dummy_in(
    /* module id */ 2,
    /* module id */ 15,
    /* fifo */ fifo_w_PE_2_16
  );
  /* Module Call */

  /* Module Call */
  w_PE_dummy_in(
    /* module id */ 3,
    /* module id */ 15,
    /* fifo */ fifo_w_PE_3_16
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_boundary_wrapper(
    /* module id */ 0,
    /* module id */ 3,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_0_3,
    /* fifo */ fifo_cout_drain_PE_3_0
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_wrapper(
    /* module id */ 0,
    /* module id */ 2,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_0_3,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_0_2,
    /* fifo */ fifo_cout_drain_PE_2_0
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_wrapper(
    /* module id */ 0,
    /* module id */ 1,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_0_2,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_0_1,
    /* fifo */ fifo_cout_drain_PE_1_0
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_wrapper(
    /* module id */ 0,
    /* module id */ 0,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_0_1,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_0_0,
    /* fifo */ fifo_cout_drain_PE_0_0
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_boundary_wrapper(
    /* module id */ 1,
    /* module id */ 3,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_1_3,
    /* fifo */ fifo_cout_drain_PE_3_1
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_wrapper(
    /* module id */ 1,
    /* module id */ 2,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_1_3,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_1_2,
    /* fifo */ fifo_cout_drain_PE_2_1
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_wrapper(
    /* module id */ 1,
    /* module id */ 1,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_1_2,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_1_1,
    /* fifo */ fifo_cout_drain_PE_1_1
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_wrapper(
    /* module id */ 1,
    /* module id */ 0,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_1_1,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_1_0,
    /* fifo */ fifo_cout_drain_PE_0_1
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_boundary_wrapper(
    /* module id */ 2,
    /* module id */ 3,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_2_3,
    /* fifo */ fifo_cout_drain_PE_3_2
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_wrapper(
    /* module id */ 2,
    /* module id */ 2,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_2_3,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_2_2,
    /* fifo */ fifo_cout_drain_PE_2_2
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_wrapper(
    /* module id */ 2,
    /* module id */ 1,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_2_2,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_2_1,
    /* fifo */ fifo_cout_drain_PE_1_2
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_wrapper(
    /* module id */ 2,
    /* module id */ 0,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_2_1,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_2_0,
    /* fifo */ fifo_cout_drain_PE_0_2
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_boundary_wrapper(
    /* module id */ 3,
    /* module id */ 3,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_3_3,
    /* fifo */ fifo_cout_drain_PE_3_3
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_wrapper(
    /* module id */ 3,
    /* module id */ 2,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_3_3,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_3_2,
    /* fifo */ fifo_cout_drain_PE_2_3
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_wrapper(
    /* module id */ 3,
    /* module id */ 1,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_3_2,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_3_1,
    /* fifo */ fifo_cout_drain_PE_1_3
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_wrapper(
    /* module id */ 3,
    /* module id */ 0,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_3_1,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_3_0,
    /* fifo */ fifo_cout_drain_PE_0_3
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_boundary_wrapper(
    /* module id */ 4,
    /* module id */ 3,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_4_3,
    /* fifo */ fifo_cout_drain_PE_3_4
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_wrapper(
    /* module id */ 4,
    /* module id */ 2,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_4_3,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_4_2,
    /* fifo */ fifo_cout_drain_PE_2_4
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_wrapper(
    /* module id */ 4,
    /* module id */ 1,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_4_2,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_4_1,
    /* fifo */ fifo_cout_drain_PE_1_4
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_wrapper(
    /* module id */ 4,
    /* module id */ 0,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_4_1,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_4_0,
    /* fifo */ fifo_cout_drain_PE_0_4
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_boundary_wrapper(
    /* module id */ 5,
    /* module id */ 3,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_5_3,
    /* fifo */ fifo_cout_drain_PE_3_5
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_wrapper(
    /* module id */ 5,
    /* module id */ 2,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_5_3,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_5_2,
    /* fifo */ fifo_cout_drain_PE_2_5
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_wrapper(
    /* module id */ 5,
    /* module id */ 1,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_5_2,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_5_1,
    /* fifo */ fifo_cout_drain_PE_1_5
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_wrapper(
    /* module id */ 5,
    /* module id */ 0,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_5_1,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_5_0,
    /* fifo */ fifo_cout_drain_PE_0_5
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_boundary_wrapper(
    /* module id */ 6,
    /* module id */ 3,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_6_3,
    /* fifo */ fifo_cout_drain_PE_3_6
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_wrapper(
    /* module id */ 6,
    /* module id */ 2,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_6_3,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_6_2,
    /* fifo */ fifo_cout_drain_PE_2_6
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_wrapper(
    /* module id */ 6,
    /* module id */ 1,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_6_2,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_6_1,
    /* fifo */ fifo_cout_drain_PE_1_6
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_wrapper(
    /* module id */ 6,
    /* module id */ 0,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_6_1,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_6_0,
    /* fifo */ fifo_cout_drain_PE_0_6
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_boundary_wrapper(
    /* module id */ 7,
    /* module id */ 3,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_7_3,
    /* fifo */ fifo_cout_drain_PE_3_7
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_wrapper(
    /* module id */ 7,
    /* module id */ 2,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_7_3,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_7_2,
    /* fifo */ fifo_cout_drain_PE_2_7
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_wrapper(
    /* module id */ 7,
    /* module id */ 1,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_7_2,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_7_1,
    /* fifo */ fifo_cout_drain_PE_1_7
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_wrapper(
    /* module id */ 7,
    /* module id */ 0,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_7_1,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_7_0,
    /* fifo */ fifo_cout_drain_PE_0_7
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_boundary_wrapper(
    /* module id */ 8,
    /* module id */ 3,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_8_3,
    /* fifo */ fifo_cout_drain_PE_3_8
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_wrapper(
    /* module id */ 8,
    /* module id */ 2,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_8_3,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_8_2,
    /* fifo */ fifo_cout_drain_PE_2_8
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_wrapper(
    /* module id */ 8,
    /* module id */ 1,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_8_2,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_8_1,
    /* fifo */ fifo_cout_drain_PE_1_8
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_wrapper(
    /* module id */ 8,
    /* module id */ 0,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_8_1,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_8_0,
    /* fifo */ fifo_cout_drain_PE_0_8
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_boundary_wrapper(
    /* module id */ 9,
    /* module id */ 3,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_9_3,
    /* fifo */ fifo_cout_drain_PE_3_9
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_wrapper(
    /* module id */ 9,
    /* module id */ 2,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_9_3,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_9_2,
    /* fifo */ fifo_cout_drain_PE_2_9
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_wrapper(
    /* module id */ 9,
    /* module id */ 1,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_9_2,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_9_1,
    /* fifo */ fifo_cout_drain_PE_1_9
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_wrapper(
    /* module id */ 9,
    /* module id */ 0,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_9_1,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_9_0,
    /* fifo */ fifo_cout_drain_PE_0_9
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_boundary_wrapper(
    /* module id */ 10,
    /* module id */ 3,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_10_3,
    /* fifo */ fifo_cout_drain_PE_3_10
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_wrapper(
    /* module id */ 10,
    /* module id */ 2,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_10_3,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_10_2,
    /* fifo */ fifo_cout_drain_PE_2_10
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_wrapper(
    /* module id */ 10,
    /* module id */ 1,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_10_2,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_10_1,
    /* fifo */ fifo_cout_drain_PE_1_10
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_wrapper(
    /* module id */ 10,
    /* module id */ 0,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_10_1,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_10_0,
    /* fifo */ fifo_cout_drain_PE_0_10
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_boundary_wrapper(
    /* module id */ 11,
    /* module id */ 3,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_11_3,
    /* fifo */ fifo_cout_drain_PE_3_11
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_wrapper(
    /* module id */ 11,
    /* module id */ 2,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_11_3,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_11_2,
    /* fifo */ fifo_cout_drain_PE_2_11
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_wrapper(
    /* module id */ 11,
    /* module id */ 1,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_11_2,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_11_1,
    /* fifo */ fifo_cout_drain_PE_1_11
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_wrapper(
    /* module id */ 11,
    /* module id */ 0,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_11_1,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_11_0,
    /* fifo */ fifo_cout_drain_PE_0_11
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_boundary_wrapper(
    /* module id */ 12,
    /* module id */ 3,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_12_3,
    /* fifo */ fifo_cout_drain_PE_3_12
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_wrapper(
    /* module id */ 12,
    /* module id */ 2,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_12_3,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_12_2,
    /* fifo */ fifo_cout_drain_PE_2_12
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_wrapper(
    /* module id */ 12,
    /* module id */ 1,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_12_2,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_12_1,
    /* fifo */ fifo_cout_drain_PE_1_12
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_wrapper(
    /* module id */ 12,
    /* module id */ 0,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_12_1,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_12_0,
    /* fifo */ fifo_cout_drain_PE_0_12
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_boundary_wrapper(
    /* module id */ 13,
    /* module id */ 3,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_13_3,
    /* fifo */ fifo_cout_drain_PE_3_13
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_wrapper(
    /* module id */ 13,
    /* module id */ 2,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_13_3,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_13_2,
    /* fifo */ fifo_cout_drain_PE_2_13
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_wrapper(
    /* module id */ 13,
    /* module id */ 1,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_13_2,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_13_1,
    /* fifo */ fifo_cout_drain_PE_1_13
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_wrapper(
    /* module id */ 13,
    /* module id */ 0,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_13_1,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_13_0,
    /* fifo */ fifo_cout_drain_PE_0_13
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_boundary_wrapper(
    /* module id */ 14,
    /* module id */ 3,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_14_3,
    /* fifo */ fifo_cout_drain_PE_3_14
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_wrapper(
    /* module id */ 14,
    /* module id */ 2,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_14_3,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_14_2,
    /* fifo */ fifo_cout_drain_PE_2_14
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_wrapper(
    /* module id */ 14,
    /* module id */ 1,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_14_2,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_14_1,
    /* fifo */ fifo_cout_drain_PE_1_14
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_wrapper(
    /* module id */ 14,
    /* module id */ 0,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_14_1,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_14_0,
    /* fifo */ fifo_cout_drain_PE_0_14
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_boundary_wrapper(
    /* module id */ 15,
    /* module id */ 3,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_15_3,
    /* fifo */ fifo_cout_drain_PE_3_15
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_wrapper(
    /* module id */ 15,
    /* module id */ 2,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_15_3,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_15_2,
    /* fifo */ fifo_cout_drain_PE_2_15
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_wrapper(
    /* module id */ 15,
    /* module id */ 1,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_15_2,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_15_1,
    /* fifo */ fifo_cout_drain_PE_1_15
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L1_out_wrapper(
    /* module id */ 15,
    /* module id */ 0,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_15_1,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_15_0,
    /* fifo */ fifo_cout_drain_PE_0_15
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L2_out_boundary(
    /* module id */ 15,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L2_out_15,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_15_0
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L2_out(
    /* module id */ 14,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L2_out_15,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L2_out_14,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_14_0
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L2_out(
    /* module id */ 13,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L2_out_14,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L2_out_13,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_13_0
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L2_out(
    /* module id */ 12,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L2_out_13,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L2_out_12,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_12_0
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L2_out(
    /* module id */ 11,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L2_out_12,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L2_out_11,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_11_0
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L2_out(
    /* module id */ 10,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L2_out_11,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L2_out_10,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_10_0
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L2_out(
    /* module id */ 9,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L2_out_10,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L2_out_9,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_9_0
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L2_out(
    /* module id */ 8,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L2_out_9,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L2_out_8,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_8_0
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L2_out(
    /* module id */ 7,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L2_out_8,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L2_out_7,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_7_0
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L2_out(
    /* module id */ 6,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L2_out_7,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L2_out_6,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_6_0
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L2_out(
    /* module id */ 5,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L2_out_6,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L2_out_5,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_5_0
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L2_out(
    /* module id */ 4,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L2_out_5,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L2_out_4,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_4_0
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L2_out(
    /* module id */ 3,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L2_out_4,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L2_out_3,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_3_0
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L2_out(
    /* module id */ 2,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L2_out_3,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L2_out_2,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_2_0
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L2_out(
    /* module id */ 1,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L2_out_2,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L2_out_1,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_1_0
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L2_out(
    /* module id */ 0,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L2_out_1,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L2_out_0,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L1_out_0_0
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L3_out(
    /* fifo */ fifo_cout_drain_cout_drain_IO_L3_out_serialize,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L2_out_0
  );
  /* Module Call */

  /* Module Call */
  cout_drain_IO_L3_out_serialize(
    /* array */ cout,
    /* fifo */ fifo_cout_drain_cout_drain_IO_L3_out_serialize
  );
  /* Module Call */

}
}
