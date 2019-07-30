#!/usr/bin/env bash

USER=geojsonspec2
CONTRACT=geojsonspec2
ENDPOINT=https://jungle.eosn.io

cleos -u $ENDPOINT push action $CONTRACT clean \
    "[]" \
    -p $USER

cleos -u $ENDPOINT push action $CONTRACT create \
    "{\"owner\":\"${USER}\",\"lat\": 10, \"lon\": 95, \"tags\":[{\"k\":\"foo\",\"v\":\"bar\"}, {\"k\":\"hello\",\"v\":\"world\"}]}" \
    -p $USER

cleos -u $ENDPOINT push action $CONTRACT create \
    "[${USER},45, 110, [{\"k\":\"second\",\"v\":\"value0\"}]]" \
    -p $USER

cleos -u $ENDPOINT push action $CONTRACT move \
    "[${USER},0, 20, 50]" \
    -p $USER

cleos -u $ENDPOINT push action $CONTRACT modify \
    "[${USER},1, [{\"k\":\"second\", \"v\": \"updated\"}]]" \
    -p $USER
