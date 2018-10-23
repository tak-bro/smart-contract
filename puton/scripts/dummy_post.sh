#!/bin/bash

while [ : ]
do
    cleos push action puton addimages '["curl", "curl_post", ["http://curl_url","https://curl_url2"]]' -p curl
    sleep 0.7
    cleos push action puton addimages '["tak", "tak_post", ["http://tak_url","https://tak_url2","https://taktak"]]' -p tak
    sleep 0.7
done
