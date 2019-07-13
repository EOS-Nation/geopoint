#!/usr/bin/env bash

USER=geojsonspec2
CONTRACT=geojsonspec2
ENDPOINT=https://jungle.eosn.io

cleos -u $ENDPOINT push action $CONTRACT createnode \
    "{\"owner\":\"${USER}\",\"node\": {\"lat\":10, \"lon\": 110}, \"tags\":[{\"key\":\"foo\",\"value\":\"bar\"}, {\"key\":\"hello\",\"value\":\"world\"}]}" \
    -p $USER
