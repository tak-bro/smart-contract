# style_service

## TODO
- [ ] post_rows를 user table에 넣어야할듯 
- [ ] post 테이블에 comment_rows 추가

## how to use성

```sh
# Create account for server
$ cleos create account eosio styleserver EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8 EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8

# Create account for user
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

# Update post
$ cleos push action styleserver updatepost '["tak", "1", "TAK_UPDATED"]' -p styleserver

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