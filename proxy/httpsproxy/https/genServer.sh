#!/bin/bash

openssl genrsa -out server.key 2048

openssl req -new -key server.key -subj "/CN=localhost" -out server.csr

openssl x509 -req -in server.csr -CA ca.crt -CAkey ca.key -CAcreateserial -out server.crt -days 5000