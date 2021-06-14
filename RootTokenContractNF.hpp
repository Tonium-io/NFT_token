#pragma once

#include "TONTokenWalletNF.hpp"

namespace tvm { namespace schema {

// ===== Root Token Contract (Non-fungible) ===== //
__interface IRootTokenContract {

  // expected offchain constructor execution
  __attribute__((internal, external, dyn_chain_parse))
  void constructor(bytes name, bytes symbol, uint8 decimals, uint256 root_public_key, cell wallet_code) = 11;

  __attribute__((external, noaccept, dyn_chain_parse))
  lazy<MsgAddressInt> deployWallet(int8 workchain_id, uint256 pubkey, TokenId tokenId, WalletGramsType grams, lazy<MsgAddressInt> nonce) = 12;

  __attribute__((internal, noaccept, dyn_chain_parse, answer_id))
  lazy<MsgAddressInt> deployWallet_response(int8 workchain_id, uint256 pubkey, WalletGramsType grams, lazy<MsgAddressInt> nonce) = 13;

  __attribute__((external, noaccept, dyn_chain_parse))
  void grant(lazy<MsgAddressInt> dest, TokenId tokenId, WalletGramsType grams) = 14;

  __attribute__((external, noaccept, dyn_chain_parse))
  TokenId mint(TokenId tokenId, bytes name, bytes jsonMeta,lazy<MsgAddressInt> data) = 15;

  __attribute__((getter))
  bytes getName() = 16;

  __attribute__((getter))
  bytes getSymbol() = 17;

  __attribute__((getter))
  uint8 getDecimals() = 19;

  __attribute__((getter))
  uint256 getRootKey() = 20;

  __attribute__((getter))
  TokensType getTotalSupply() = 21;

  __attribute__((getter))
  TokensType getTotalGranted() = 22;

  __attribute__((getter))
  cell getWalletCode() = 23;

  __attribute__((getter))
  TokenId getLastMintedToken() = 24;

  __attribute__((getter))
  lazy<MsgAddressInt> getWalletAddress(int8 workchain_id, uint256 pubkey, lazy<MsgAddressInt> nonce) = 25;

    __attribute__((getter))
  bytes getJson(TokenId tokenId) = 26;

    __attribute__((getter))
  t_file getInfoToken(TokenId tokenId) = 28;
};

struct DRootTokenContract {
  bytes name_;
  bytes symbol_;
  uint8 decimals_;
  uint256 root_public_key_;
  TokensType total_supply_;
  TokensType total_granted_;
  cell wallet_code_;
  dict_set<TokenId> tokens_;
  dict_map<uint128,t_file> files_;
  
  // t_file files_;
  //dict_array<File> files_;
};



struct ERootTokenContract {
};

}} // namespace tvm::schema

