#!/bin/bash

cleos push action puton addpost '["tak", "TAKTAKTAK"]' -p tak
sleep 0.6

cleos push action puton addpost '["curl", "CURL_CURL_HASH"]' -p curl
sleep 0.6

while [ : ]
do
    cleos push action puton addcmt '["camry", "1", "comment"]' -p camry
    sleep 0.6
    cleos push action puton addcmt '["jinny", "1", "comment"]' -p jinny
    sleep 0.6
done
