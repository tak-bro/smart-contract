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

# Create new buzzler user
$ cleos push action buzzserver createuser '["tak"]' -p buzzserver
$ cleos push action buzzserver createuser '["curl"]' -p buzzserver

# Update token
$ cleos push action buzzserver updatetoken '["tak", 1000]' -p buzzserver

# Write post with hash
$ cleos push action buzzserver writepost '[1, "tak", "post hash value"]' -p buzzserver
$ cleos push action buzzserver writepost '[2, "tak", "post2222"]' -p buzzserver
$ cleos push action buzzserver writepost '[3, "curl", "curlpost333333"]' -p buzzserver
$ cleos push action buzzserver writepost '[4, "tak", "takpost44444"]' -p buzzserver
$ cleos push action buzzserver writepost '[5, "curl", "curl555555"]' -p buzzserver

# Update post with buzz_amount by post id
$ cleos push action buzzserver updatepost '[1, "tak", "post hash value", 100, 1]' -p buzzserver
$ cleos push action buzzserver updatepost '[2, "curl", "post hash value222222", 10000, 1000]' -p buzzserver

# Delete post by id
$ cleos push action buzzserver deletepost '[2]' -p buzzserver

# Print Post by id
$ cleos push action buzzserver postbyid '[3]' -p buzzserver

# Print Post by author
$ cleos push action buzzserver postsbyuser '["tak"]' -p buzzserver

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

$ cleos get table buzzserver buzzserver posts
{
  "rows": [{
      "id": 1,
      "author": "tak",
      "post_hash": "post hash value",
      "buzz_amount": 0,
      "created_at": 1537760228
    },{
      "id": 2,
      "author": "tak",
      "post_hash": "post2222",
      "buzz_amount": 0,
      "created_at": 1537760248
    }
  ],
  "more": false
}
```

> **기존 테이블에 데이터가 있는 상태에서 multi_index를 새로 추가하게되면 이전 데이터는 인덱싱이 되지 않음**
