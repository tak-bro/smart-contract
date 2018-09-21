# todo_service smart-contract

## how to use

```sh
# Create account for server
$ cleos create account eosio todoservice EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8 EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8

# create account for user
$ cleos create account eosio tak EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8 EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8
 && cleos create account eosio curl EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8 EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8

# Build contract
$ ./build.sh todoservice todo

# Create new todo item
$ cleos push action todoservice create '["todoservice", 1, "todo1"]' -p todoservice

# Check DB
$ cleos get table todoservice todoservice todos
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
