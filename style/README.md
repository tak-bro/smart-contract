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

# Add post
$ cleos push action styleserver addpost '["tak", "HASH_VALUE HASH_VALUE HASH_VALUE HASH_VALUE HASH_VALUE HASH_VALUE"]' -p styleserver
$ cleos push action styleserver addpost '["tak", "HASH_222222222222222"]' -p styleserver
$ cleos push action styleserver addpost '["curl", "CURL_CURL_HASH"]' -p styleserver

# Check DB
$ cleos get table styleserver styleserver users
{
  "rows": [{
      "account": "curl",
      "created_at": 1539666255
    },{
      "account": "tak",
      "created_at": 1539666133
    }
  ],
  "more": false
}

$ cleos get table styleserver styleserver posts
{
  "rows": [{
      "author": "curl",
      "last_id": 1,
      "post_rows": [{
          "id": 1,
          "post_hash": "CURL_CURL_HASH",
          "created_at": 1539666258
        }
      ]
    },{
      "author": "tak",
      "last_id": 2,
      "post_rows": [{
          "id": 1,
          "post_hash": "HASH_VALUE HASH_VALUE HASH_VALUE HASH_VALUE HASH_VALUE HASH_VALUE",
          "created_at": 1539666181
        },{
          "id": 2,
          "post_hash": "HASH_222222222222222",
          "created_at": 1539666458
        }
      ]
    }
  ],
  "more": false
}
```

> **기존 테이블에 데이터가 있는 상태에서 multi_index를 새로 추가하게되면 이전 데이터는 인덱싱이 되지 않음**