# buzzer_service smart-contract

## how to use

```sh
# Create account for server
$ cleos create account eosio buzzserver EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8 EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8

# create account for user
$ cleos create account eosio tak EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8 EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8
$ cleos create account eosio curl EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8 EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8

# Build contract
$ ./build.sh buzzserver buzzler

# Create new user
$ cleos push action buzzserver createuser '["tak"]' -p buzzserver

# Update token
$ cleos push action buzzserver updatetoken '["tak", 1000]' -p buzzserver

# Check DB
$ cleos get table buzzserver buzzserver users
{
  "rows": [{
      "account": "tak",
      "buzz_token": 1000,
      "created_at": 1537758563
    }
  ],
  "more": false
}
```
