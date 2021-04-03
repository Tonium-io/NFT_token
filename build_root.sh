#!/bin/bash
clang++ -target tvm --sysroot=$TVM_INCLUDE_PATH -export-json-abi -o RootTokenContractNF.abi.json RootTokenContractNF.cpp
sudo /opt/work/llvm/install/bin/tvm-build++.py --abi RootTokenContractNF.abi RootTokenContractNF.cpp --include $TVM_INCLUDE_PATH --linkerflags="--genkey key -o RootTokenContract.tvc"
