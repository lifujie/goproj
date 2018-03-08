#!/bin/bash

openssl genrsa -out client.key 2048
openssl req -new -key client.key -subj "/CN=tuya_cn" -out client.csr

openssl x509 -req -in client.csr -CA ca.crt -CAkey ca.key -CAcreateserial -extfile client.ext -out client.crt -days 5000