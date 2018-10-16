# style_service

## how to use

```sh
# Create account for server
$ cleos create account eosio styleserver EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8 EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8

# create account for user
$ cleos create account eosio tak EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8 EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8
$ cleos create account eosio curl EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8 EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8

# Build contract
$ ./build.sh styleserver style

# Create new buzzler user
$ cleos push action styleserver createuser '["tak"]' -p styleserver
$ cleos push action styleserver createuser '["curl"]' -p styleserver

# Get Random number
$ cleos push action styleserver getrandom '["tak"]' -p styleserver

# Check DB
$ cleos get table styleserver styleserver users
{
  "rows": [{
      "account": "tak",
      "created_at": 1537758563
    }
  ],
  "more": false
}
```

> **기존 테이블에 데이터가 있는 상태에서 multi_index를 새로 추가하게되면 이전 데이터는 인덱싱이 되지 않음**
