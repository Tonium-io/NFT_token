#!/bin/bash
clang++ -target tvm --sysroot=$TVM_INCLUDE_PATH -export-json-abi -o TONTokenWalletNF.abi.json TONTokenWalletNF.cpp
sudo /opt/work/llvm/install/bin/tvm-build++.py --abi TONTokenWalletNF.abi.json TONTokenWalletNF.cpp --include $TVM_INCLUDE_PATH --linkerflags="--genkey key -o TONTokenWalletNF.tvc"
