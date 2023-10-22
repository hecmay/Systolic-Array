#include "kernel_host.hpp"
#include <assert.h>
#include <stdio.h>
#include "kernel.h"

int main(int argc, char **argv){
  data_t cin[R + K - 1][C + K - 1][I];
  data_t w[O][K][K][I];
  data_t cout[R][C][O];
  data_t cout_golden[R][C][O];

  // data initialization
  for (int i = 0 ; i < I; i++)
    for (int r = 0; r < R + K - 1; r++)
      for (int c = 0; c < C + K - 1; c++) {
        cin[r][c][i] = i;
      }

  for (int o = 0; o < O; o++)
    for (int i = 0; i < I; i++) 
      for (int p = 0; p < K; p++)
        for (int q = 0; q < K; q++) {
          w[o][p][q][i] = o;
        }
 
  {
    if (argc != 2) {
      std::cout << "Usage: " << argv[0] << " <XCLBIN File>" << std::endl;
      return EXIT_FAILURE;
    }

    cl_int err;
    std::vector<cl::Device> devices = get_devices();
    cl::Device device = devices[0];
    std::string device_name = device.getInfo<CL_DEVICE_NAME>();
    std::cout << "Found Device=" << device_name.c_str() << std::endl;
    // Creating Context and Command Queue for selected device
    cl::Context context(device);
    cl::CommandQueue q(context, device);
    // Import XCLBIN
    xclbin_file_name = argv[1];
    cl::Program::Binaries kernel_bins = import_binary_file();
    // Create Program and Kernel
    //devices.erase(devices.begin());
    devices.resize(1);
    cl::Program program(context, devices, kernel_bins);
    cl::Kernel krnl(program, "kernel0");

    // Allocate memory in host memory
    std::vector<float, aligned_allocator<float>> dev_cin_unserialized((258) * (258) * (16));
    std::vector<float, aligned_allocator<float>> dev_cin(4718592);
    std::vector<float, aligned_allocator<float>> dev_cout_unserialized((256) * (256) * (16));
    std::vector<float, aligned_allocator<float>> dev_cout(1048576);
    std::vector<float, aligned_allocator<float>> dev_w_unserialized((16) * (3) * (3) * (16));
    std::vector<float, aligned_allocator<float>> dev_w(2359296);

    // Initialize host buffers
    std::copy(reinterpret_cast<float *>(cin), reinterpret_cast<float *>(cin) + (258) * (258) * (16), dev_cin_unserialized.begin());
    std::copy(reinterpret_cast<float *>(cout), reinterpret_cast<float *>(cout) + (256) * (256) * (16), dev_cout_unserialized.begin());
    std::copy(reinterpret_cast<float *>(w), reinterpret_cast<float *>(w) + (16) * (3) * (3) * (16), dev_w_unserialized.begin());
    host_serialize_cin(dev_cin, dev_cin_unserialized);
    host_serialize_w(dev_w, dev_w_unserialized);

    // Allocate buffers in device memory
    // Buffers are allocated using CL_MEM_USE_HOST_PTR for efficient memory and
    // device-to-host communication
    std::vector<cl::Buffer> buffer_cin;
    std::vector<cl::Buffer> buffer_cout;
    std::vector<cl::Buffer> buffer_w;
    for (int i = 0; i < 1; i++) {
      OCL_CHECK(err,
                cl::Buffer buffer_cin_tmp(context,
                                          CL_MEM_USE_HOST_PTR | CL_MEM_READ_ONLY,
                                          (4718592) * sizeof(float),
                                          dev_cin.data(),
                                          &err));
      buffer_cin.push_back(std::move(buffer_cin_tmp));
    }
    for (int i = 0; i < 1; i++) {
      OCL_CHECK(err,
                cl::Buffer buffer_cout_tmp(context,
                                           CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE,
                                           (1048576) * sizeof(float),
                                           dev_cout.data(),
                                           &err));
      buffer_cout.push_back(std::move(buffer_cout_tmp));
    }
    for (int i = 0; i < 1; i++) {
      OCL_CHECK(err,
                cl::Buffer buffer_w_tmp(context,
                                        CL_MEM_USE_HOST_PTR | CL_MEM_READ_ONLY,
                                        (2359296) * sizeof(float),
                                        dev_w.data(),
                                        &err));
      buffer_w.push_back(std::move(buffer_w_tmp));
    }

    auto host_begin = std::chrono::high_resolution_clock::now();
    auto fpga_begin = std::chrono::high_resolution_clock::now();
    auto fpga_end = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 1; i++) {
      OCL_CHECK(err,
                err = q.enqueueMigrateMemObjects({buffer_cin[i]}, 0));
    }

    for (int i = 0; i < 1; i++) {
      OCL_CHECK(err,
                err = q.enqueueMigrateMemObjects({buffer_cout[i]}, 0));
    }

    for (int i = 0; i < 1; i++) {
      OCL_CHECK(err,
                err = q.enqueueMigrateMemObjects({buffer_w[i]}, 0));
    }

    {
      OCL_CHECK(err, err = krnl.setArg(0, buffer_cin[0]));
      OCL_CHECK(err, err = krnl.setArg(1, buffer_cout[0]));
      OCL_CHECK(err, err = krnl.setArg(2, buffer_w[0]));
      q.finish();

      // Warm up
      OCL_CHECK(err, err = q.enqueueTask(krnl));
      q.finish();

      fpga_begin = std::chrono::high_resolution_clock::now();

      // Launch the kernel
      for (int i = 0; i < 10; i++)
        OCL_CHECK(err, err = q.enqueueTask(krnl));

      q.finish();
      fpga_end = std::chrono::high_resolution_clock::now();
    }

    for (int i = 0; i < 1; i++) {
      OCL_CHECK(err,
                err = q.enqueueMigrateMemObjects({buffer_cout[i]}, CL_MIGRATE_MEM_OBJECT_HOST));
    }
    q.finish();
    auto host_end = std::chrono::high_resolution_clock::now();

    // Calculate time
    std::chrono::duration<double> fpga_duration = fpga_end - fpga_begin;
    std::cout << "FPGA Time: " << fpga_duration.count() / 10 << " s" << std::endl;
    std::chrono::duration<double> host_duration = host_end - host_begin;
    std::cout << "Host Time: " << host_duration.count() << " s" << std::endl;

    host_deserialize_cout(dev_cout_unserialized, dev_cout);
    // Restore data from host buffers
    std::copy(dev_cout_unserialized.begin(), dev_cout_unserialized.end(), reinterpret_cast<float *>(cout));
  }
 
  for (int o = 0; o < O; o++)
    for (int r = 0; r < R; r++)
      for (int c = 0; c < C; c++) {
        cout_golden[r][c][o] = 0;
        for (int i = 0; i < I; i++)
          for (int p = 0; p < K; p++)
            for (int q = 0; q < K; q++) {
              cout_golden[r][c][o] = cout_golden[r][c][o] + cin[r + p][c + q][i] * w[o][p][q][i];
            }
      }

  int err = 0;
  float thres = 0.001;
  for (int o = 0; o < O; o++)
    for (int r = 0; r < R; r++)
      for (int c = 0; c < C; c++) {
        if (fabs((float)cout_golden[r][c][o] - (float)cout[r][c][o]) > thres) {
          err++;
        }
      }

  //if (err) {
  //  printf("Test failed with %d errors!\n", err);
  //  return -1;
  //} else {
  //  printf("Test passed!\n");
  //  return 0;
  //}
}
