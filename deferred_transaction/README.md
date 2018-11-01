# Deferred Transaction with inline action
- deferred transaction

## How to use

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

### build

```sh
# sender
$ eosiocpp -g sender/sender.abi sender/sender.cpp
$ eosiocpp -o sender/sender.wasm sender/sender.cpp

# recipient
$ eosiocpp -g recipient/recipient.abi recipient/recipient.cpp
$ eosiocpp -o recipient/recipient.wasm recipient/recipient.cpp
```

### set account permission
- Need to authorize sender contract's eosio.code permission to sender contract's active permission,
- cleos set account permission <YOUR_ACCOUNT> active '{"threshold": 1,"keys": [{"key": "<YOUR_PUBLIC_KEY>","weight": 1}],"accounts": [{"permission":{"actor":"<CONTRACT_ACCOUNT>","permission":"eosio.code"},"weight":1}]}' owner -p <YOUR_ACCOUNT>

```sh
$ cleos set account permission sender active '{"threshold": 1,"keys": [{"key": "EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8","weight": 1}],"accounts": [{"permission":{"actor":"sender","permission":"eosio.code"},"weight":1}]}' owner -p sender
```

### set smart contract

```sh
$ cleos set contract sender sender
$ cleos set contract recipient recipient
```

### action

```sh
# inline action
$ cleos push action sender send '["my_message"]' -p sender

# deferrered transaction
# ["메세지", "interval sec", "index", "iterations"]
# 3초에 한번씩 액션 수행 -> 10번까지
$ cleos push action sender spam '["deferred message", "3", "0", "10"]' -p sender

# deferrered transaction with inline action
$ cleos push action sender defertx '["deferred message", "5", "0", "10"]' -p sender
```