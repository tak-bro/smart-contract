# Token 

# create eos account
cleos create account eosio tak EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8 EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8
cleos create account eosio curl EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8 EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8

# 토큰 발행 위한 계정 생성
cleos create account eosio puton.token EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8 EOS8Txt52C9jUD4Pc5LFsceeBy9RKi9MSVEV4WvoaB2KpEjHwyPz8

# set contract
cleos set contract puton.token ~/workspace/failnicely/eos/build/contracts/eosio.token -p puton.token

# 토큰 생성
cleos push action puton.token create '["eosio","1000000000000.000 PTN"]' -p puton.token

# 토큰 발행
cleos push action puton.token issue '["tak","100.000 PTN","memo"]' -p eosio
cleos push action puton.token issue '["curl","100.000 PTN","memo"]' -p eosio

# 확인
cleos get currency balance puton.token tak
cleos get currency balance puton.token curl

# 보내기 
cleos push action puton.token transfer '{"from":"tak","to":"curl","quantity":"10.000 PTN","memo":"memo"}' -p tak