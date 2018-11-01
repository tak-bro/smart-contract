# inline action
- communicate with smart contract

## how to use

### unlock wallet

```sh
$ cleos wallet unlock --password PW5KRyUSVq3Ytht2mwHNx5ZQWYWginSJkiEhU5n6LWL6ehattytK2
$ cleos wallet unlock -n tak --password PW5KBvksXaoDgkQcCCnkFLbfxMUW5e5TK3hYZi5MhsW5duzzexdnV
```

### create sender, recipient account

```sh
$ cleos create account eosio sender EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8 EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8
$ cleos create account eosio recipient EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8 EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8
```

# build

```sh
# sender
$ eosiocpp -g sender/sender.abi sender/sender.cpp
$ eosiocpp -o sender/sender.wasm sender/sender.cpp

# recipient
$ eosiocpp -g recipient/recipient.abi recipient/recipient.cpp
$ eosiocpp -o recipient/recipient.wasm recipient/recipient.cpp
```

# set account permission
- cleos set account permission <YOUR_ACCOUNT> active '{"threshold": 1,"keys": [{"key": "<YOUR_PUBLIC_KEY>","weight": 1}],"accounts": [{"permission":{"actor":"<CONTRACT_ACCOUNT>","permission":"eosio.code"},"weight":1}]}' owner -p <YOUR_ACCOUNT>

```sh
$ cleos set account permission sender active '{"threshold": 1,"keys": [{"key": "EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8","weight": 1}],"accounts": [{"permission":{"actor":"sender","permission":"eosio.code"},"weight":1}]}' owner -p sender
```

# set smart contract
```sh
$ cleos set contract sender sender
$ cleos set contract recipient recipient
```

# action
```sh
$ cleos push action sender send '["sender", "my_message"]' -p sender

# print message from recipient func
3480146ms thread-0   apply_context.cpp:28          print_debug          ]
[(recipient,receive)->recipient]: CONSOLE OUTPUT BEGIN =====================
sender, recipient, my_message
[(recipient,receive)->recipient]: CONSOLE OUTPUT END   =====================
```