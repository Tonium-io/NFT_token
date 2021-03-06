#pragma once

#include <tvm/schema/message.hpp>
#include <tvm/sequence.hpp>

#include <tvm/replay_attack_protection/timestamp.hpp>
#include <tvm/smart_switcher.hpp>
#include <tvm/dict_set.hpp>

namespace tvm { namespace schema {

using WalletGramsType = uint128;
using TokensType = uint128;
using TokenId = uint128;

struct t_file {
  bytes name;
  lazy<MsgAddressInt> data;
  bytes jsonMeta;
  uint64 time;
};

struct info_token {
  bytes name;
  uint8 type;
  bytes tokenUri;
  uint64 time;
  lazy<MsgAddressInt> data;
};


static constexpr unsigned TOKEN_WALLET_TIMESTAMP_DELAY = 5;
using wallet_replay_protection_t = replay_attack_protection::timestamp<TOKEN_WALLET_TIMESTAMP_DELAY>;

struct allowance_info {
  lazy<MsgAddressInt> spender;
  TokenId allowedToken;
};


// ===== TON Token wallet ===== //
__interface ITONTokenWallet {

  // expected offchain constructor execution
  __attribute__((internal, external, dyn_chain_parse))
  void constructor(bytes name, bytes symbol, uint8 decimals,
                   uint256 root_public_key, uint256 wallet_public_key,
                   lazy<MsgAddressInt> root_address, cell code) = 11;


  __attribute__((external,internal, noaccept, dyn_chain_parse))
  void transfer(lazy<MsgAddressInt> dest, TokenId tokenId, WalletGramsType grams) = 12;
  
       __attribute__ ((external,internal noaccept, dyn_chain_parse))
  void send_all_token_by_pubkey(uint256 pubkey, lazy<MsgAddressInt> nonce) = 13;


  // Receive tokens from root
  __attribute__((internal, noaccept))
  void accept(TokenId tokenId) = 14;

  // Receive tokens from other wallet
  __attribute__((internal,noaccept))
  void internalTransfer(TokenId tokenId, uint256 pubkey, lazy<MsgAddressInt> timestamp) = 15;

  // getters
  __attribute__((getter))
  bytes getName() = 16;

  __attribute__((getter))
  bytes getSymbol() = 17;

  __attribute__((getter))
  uint8 getDecimals() = 18;

  __attribute__((getter))
  TokensType getBalance() = 19;

  __attribute__((getter))
  uint256 getWalletKey() = 20;

  __attribute__((getter))
  lazy<MsgAddressInt> getRootAddress() = 21;

  __attribute__((getter))
  allowance_info allowance() = 22;

  __attribute__((getter))
  TokenId getTokenByIndex(TokensType index) = 23;

  __attribute__((getter))
  lazy<MsgAddressInt> getApproved(TokenId tokenId) = 24;
  
    __attribute__((getter))
  lazy<MsgAddressInt> getNonce() = 25;

  // allowance interface
  __attribute__((external, noaccept, dyn_chain_parse))
  void approve(lazy<MsgAddressInt> spender, TokenId tokenId) = 26;

  __attribute__((external, noaccept, dyn_chain_parse))
  void transferFrom(lazy<MsgAddressInt> dest, lazy<MsgAddressInt> to, TokenId tokenId, WalletGramsType grams) = 27;

  __attribute__((internal))
  void internalTransferFrom(lazy<MsgAddressInt> to, TokenId tokenId) = 28;

  __attribute__((external, noaccept))
  void disapprove() = 29;
};

struct DTONTokenWallet {
  bytes name_;
  bytes symbol_;
  uint8 decimals_;
  uint256 root_public_key_;
  uint256 wallet_public_key_;
  lazy<MsgAddressInt> root_address_;
  cell code_;
  lazy<MsgAddressInt> nonce_;
  std::optional<allowance_info> allowance_;
  dict_set<TokenId> tokens_;
  
};

struct ETONTokenWallet {
};

// Prepare Token Wallet StateInit structure and expected contract address (hash from StateInit)
inline
std::pair<StateInit, uint256> prepare_wallet_state_init_and_addr(DTONTokenWallet wallet_data) {
  cell wallet_data_cl =
    prepare_persistent_data<ITONTokenWallet, wallet_replay_protection_t, DTONTokenWallet>(
      wallet_replay_protection_t::init(), wallet_data);
  StateInit wallet_init {
    /*split_depth*/{}, /*special*/{},
    wallet_data.code_, wallet_data_cl, /*library*/{}
  };
  cell wallet_init_cl = build(wallet_init).make_cell();
  return { wallet_init, uint256(tvm_hash(wallet_init_cl)) };
}

}} // namespace tvm::schema

