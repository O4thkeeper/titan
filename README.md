# AegonKV: A High Bandwidth, Low Tail Latency, and Low Storage Cost KV-Separated LSM Store with SmartSSD-based GC Offloading

## Build
AegonKV is built on Titan.

Follow three steps to build AegonKV: build RocksDB dependency (required by Titan), build AegonKV software side target, and build AegonKV FPGA hardware side target.

*Before building hardware target, make sure the SmartSSD environment is configured correctly. Some useful test commands are in `./hardware/host/test_commands.sh`.*

```shell
mkdir -p build
cd build
cmake -DROCKSDB_DIR=$(pwd)/../lib/rocksdb-6.29.tikv -DREAL_COMPILE=1 -DCMAKE_BUILD_TYPE=Debug ..
# build RocksDB
make -j rocksdb
# build software
make -j titan

# build hardware (it may takes several hours)
cd ..
nohup cmake --build $(pwd)/build --target gc_kernel -- -j 8 > hw_compile.log 2>&1 &
```
