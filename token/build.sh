#!/bin/bash

# unlock wallet
cleos wallet unlock --password PW5KRyUSVq3Ytht2mwHNx5ZQWYWginSJkiEhU5n6LWL6ehattytK2
cleos wallet unlock -n tak --password PW5KBvksXaoDgkQcCCnkFLbfxMUW5e5TK3hYZi5MhsW5duzzexdnV

# create eos account
cleos create account eosio tak EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8 EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8
cleos create account eosio curl EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8 EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8

# 토큰 발행 위한 계정 생성
cleos create account eosio puton.token EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8 EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8

# set contract
cleos set contract puton.token ~/workspace/failnicely/eos/build/contracts/eosio.token -p puton.token
