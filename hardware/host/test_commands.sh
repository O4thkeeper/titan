



/usr/bin/cmake --build /home/hfeng/code/titan/cmake-build-debug-node25 --target gc_kernel -- -j 8
# !remember to change sw_emu/hw_emu in gc_driver_test.cc
/usr/bin/cmake --build /home/hfeng/code/titan/cmake-build-debug-node25 --target gc_host -- -j 8
/usr/bin/cmake --build /home/hfeng/code/titan/cmake-build-debug-node25 --target gc_host_test -- -j 8

export XCL_EMULATION_MODE=sw_emu
export XCL_EMULATION_MODE=hw_emu
export EMCONFIG_PATH=/home/hfeng/code/titan/cmake-build-debug-node25/hardware/kernel
rm /home/SmartSSD_Data/hfeng/titan/4.blob
/home/hfeng/code/titan/cmake-build-debug-node25/hardware/host/gc_host_test


/home/hfeng/tool/cmake/bin/cmake --build /home/hfeng/code/titan/cmake-build-debug-node27 --target gc_kernel -- -j 8
# !remember to change sw_emu/hw_emu in gc_driver_test.cc
/home/hfeng/tool/cmake/bin/cmake --build /home/hfeng/code/titan/cmake-build-debug-node27 --target gc_host_test -- -j 8
export XCL_EMULATION_MODE=sw_emu
export XCL_EMULATION_MODE=hw_emu
export EMCONFIG_PATH=/home/hfeng/code/titan/cmake-build-debug-node27/hardware/kernel
/home/hfeng/code/titan/cmake-build-debug-node27/hardware/host/gc_host_test

