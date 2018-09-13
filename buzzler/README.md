# buzzler smart-contract

## how to use

```sh
# Create account
$ cleos create account eosio tak EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8 EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8

# Build contract
$ ./build.sh tak buzzler

# Push hello action
$ cleos push action tak hello '["world"]' -p tak

# Create new user
$ cleos push action tak create '["tak", "taktak", "ajou", "cs"]' -p tak

# Update user
$ cleos push action tak update '["tak", "taktak2", "ajou", "cs", 1000000]' -p tak

# Remove user
$ cleos push action tak remove '["tak"]' -p tak

# Get user(print)
$ cleos push action tak getuser '["tak"]' -p tak

# Get user by Token
$ cleos push action tak bytoken '["1000000"]' -p tak

# Check DB
$ cleos get table tak tak users
{
  "rows": [{
      "account": "tak",
      "nickname": "taktak",
      "univ": "ajou",
      "major": "cs",
      "token": 0,
      "created_at": 1536222472
    }
  ],
  "more": false
}
```
