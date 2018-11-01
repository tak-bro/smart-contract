#!/bin/bash

# unlock wallet
cleos wallet unlock --password PW5KRyUSVq3Ytht2mwHNx5ZQWYWginSJkiEhU5n6LWL6ehattytK2
cleos wallet unlock -n tak --password PW5KBvksXaoDgkQcCCnkFLbfxMUW5e5TK3hYZi5MhsW5duzzexdnV

# create eos account
cleos create account eosio sender EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8 EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8
sleep 0.6

cleos create account eosio recipient EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8 EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8
sleep 0.6

# build
eosiocpp -g sender/sender.abi sender/sender.cpp
eosiocpp -o sender/sender.wasm sender/sender.cpp

eosiocpp -g recipient/recipient.abi recipient/recipient.cpp
eosiocpp -o recipient/recipient.wasm recipient/recipient.cpp

# cleos set account permission <YOUR_ACCOUNT> active '{"threshold": 1,"keys": [{"key": "<YOUR_PUBLIC_KEY>","weight": 1}],"accounts": [{"permission":{"actor":"<CONTRACT_ACCOUNT>","permission":"eosio.code"},"weight":1}]}' owner -p <YOUR_ACCOUNT>
cleos set account permission sender active '{"threshold": 1,"keys": [{"key": "EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8","weight": 1}],"accounts": [{"permission":{"actor":"sender","permission":"eosio.code"},"weight":1}]}' owner -p sender
# cleos set account permission sender active 
# '{
#     "threshold": 1,
#     "keys": [{
#         "key": "EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8",
#         "weight": 1
#     }],
#     "accounts": [{
#         "permission":{
#             "actor":"sender",
#             "permission":"eosio.code"
#         },
#         "weight":1
#     }]
# }'
# owner -p sender

cleos set contract sender sender
cleos set contract recipient recipient