# puton_service(퓨턴)

## TODO
- [ ] post_rows를 user table에 넣어야할듯 
- [ ] post 테이블에 comment_rows 추가

## how to use

```sh
# Create account for server
$ cleos create account eosio puton EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8 EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8

# Create account for user
$ cleos create account eosio tak EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8 EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8
$ cleos create account eosio curl EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8 EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8

# Build contract
$ ./build.sh puton puton

# Create new buzzler user
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
$ cleos push action puton updateimages '["tak", "1", "TAK_UPDATED", ["xxxxxxxbbbb","aagggggggaaa","asd","asdasd","asdas"]]' -p tak

# Like post
$ cleos push action puton likepost '["tak", "1"]' -p tak
$ cleos push action puton likepost '["tak", "1"]' -p curl

# Delete post
$ cleos push action puton deletepost '["tak", "1"]' -p tak

# Add comment
$ cleos push action puton addcmt '["tak", "1", "comment"]' -p tak

# Update comment
$ cleos push action puton updatecmt '["tak", "1", "0", "updated comment"]' -p tak

# Delete comment
$ cleos push action puton deletecmt '["tak", "1", "0"]' -p tak



# Check DB
$ cleos get table puton puton users
$ cleos get table puton puton posts
$ cleos get table puton puton posts --lower "10" --upper "20"