# puton_service(퓨턴)

## TODO
- [x] post_rows를 user table에 넣어야할듯 
- [x] post 테이블에 comment_rows 추가
- [ ] comment 작성하면 point 올라가게

## how to use

```sh
# Create account for server
$ cleos create account eosio puton EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8 EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8

# Create account for user
$ cleos create account eosio tak EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8 EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8
$ cleos create account eosio curl EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8 EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8

# Build contract
$ ./build.sh puton puton

# Create new puton user
$ cleos push action puton createuser '["tak"]' -p puton
$ cleos push action puton createuser '["curl"]' -p puton

# Get Random number
$ cleos push action puton getrandom '["tak"]' -p puton

# Add post
$ cleos push action puton addpost '["tak", "TEST1111"]' -p tak
$ cleos push action puton addpost '["tak", "TEST22222"]' -p tak
$ cleos push action puton addpost '["curl", "CURL_CURL_HASH"]' -p curl
$ cleos push action puton addpost '["curl", "CURL_CURL_HASH22"]' -p curl

# Add post with image urls
$ cleos push action puton addimages '["tak", "test2222", ["https://www.google.co.kr/imgres?imgurl=https%3A%2F%2Fblockgeeks.com%2Fwp-content%2Fuploads%2F2018%2F01%2FWhat-is-EOS-Blockchain_-Beginners-Guide.png&imgrefurl=https%3A%2F%2Fblockgeeks.com%2Fguides%2Feos-blockchain%2F&docid=GJUKsWa0TUo42M&tbnid=ZjzOVChgnxEeGM%3A&vet=10ahUKEwip07-S4ozeAhVMEHAKHcYoDXIQMwgwKAAwAA..i&w=1200&h=628&bih=888&biw=1879&q=eos%20blockchain&ved=0ahUKEwip07-S4ozeAhVMEHAKHcYoDXIQMwgwKAAwAA&iact=mrc&uact=8","https://www.google.co.kr/imgres?imgurl=https%3A%2F%2Fblockgeeks.com%2Fwp-content%2Fuploads%2F2018%2F01%2FWhat-is-EOS-Blockchain_-Beginners-Guide.png&imgrefurl=https%3A%2F%2Fblockgeeks.com%2Fguides%2Feos-blockchain%2F&docid=GJUKsWa0TUo42M&tbnid=ZjzOVChgnxEeGM%3A&vet=10ahUKEwip07-S4ozeAhVMEHAKHcYoDXIQMwgwKAAwAA..i&w=1200&h=628&bih=888&biw=1879&q=eos%20blockchain&ved=0ahUKEwip07-S4ozeAhVMEHAKHcYoDXIQMwgwKAAwAA&iact=mrc&uact=8"]]' -p tak
$ cleos push action puton addimages '["curl", "test33333", ["xxxxxxxbbbb","aagggggggaaa"]]' -p curl

# Update post
$ cleos push action puton updatepost '["tak", "1", "TAK_UPDATED"]' -p tak

# Update post with image urls
$ cleos push action puton updateimages '["tak", "1", "TAK_UPDATED_WITH_IMAGE", ["xxxxxxxbbbb","aagggggggaaa","asd","asdasd","asdas"]]' -p tak

# Like post
$ cleos push action puton likepost '["tak", "1"]' -p tak
$ cleos push action puton likepost '["tak", "4"]' -p tak
$ cleos push action puton likepost '["curl", "4"]' -p curl

# Cancel Like
$ cleos push action puton cancellike '["tak", "4"]' -p tak

# Delete post
$ cleos push action puton deletepost '["tak", "1"]' -p tak

# Add comment
$ cleos push action puton addcmt '["tak", "2", "comment"]' -p tak

# Update comment
$ cleos push action puton updatecmt '["camry", "1", "1", "updated comment"]' -p camry
$ cleos push action puton updatecmt '["tak", "2", "1", "updated comment"]' -p tak

# Delete comment
$ cleos push action puton deletecmt '["tak", "1", "2"]' -p tak

# Check DB
$ cleos get table puton puton users
{
  "rows": [{
      "account": "curl",
      "liked_rows": [{
          "post_id": 4
        }
      ]
    },{
      "account": "tak",
      "liked_rows": [{
          "post_id": 2
        }
      ]
    }
  ],
  "more": false
}

$ cleos get table puton puton posts
{
  "rows": [{
      "id": 0,
      "author": "tak",
      "post_hash": "TEST1111",
      "image_urls": [],
      "cmt_rows": [],
      "last_id": 0,
      "like_cnt": 0,
      "point": 0,
      "created_at": 1539932282
    },{
      "id": 2,
      "author": "curl",
      "post_hash": "CURL_CURL_HASH",
      "image_urls": [],
      "cmt_rows": [{
          "cmt_id": 1,
          "author": "tak",
          "cmt_hash": "updated comment",
          "created_at": 1539932472
        }
      ],
      "last_id": 2,
      "like_cnt": 1,
      "point": 1,
      "created_at": 1539932299
    },{
      "id": 3,
      "author": "curl",
      "post_hash": "CURL_CURL_HASH22",
      "image_urls": [],
      "cmt_rows": [],
      "last_id": 0,
      "like_cnt": 0,
      "point": 0,
      "created_at": 1539932302
    },{
      "id": 4,
      "author": "curl",
      "post_hash": "test33333",
      "image_urls": [
        "xxxxxxxbbbb",
        "aagggggggaaa"
      ],
      "cmt_rows": [],
      "last_id": 0,
      "like_cnt": 1,
      "point": 0,
      "created_at": 1539932307
    }
  ],
  "more": false
}
$ cleos get table puton puton posts --lower "10" --upper "20"