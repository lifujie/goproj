#!/bin/bash
# call this script with an email address (valid or not).
mkdir certs
rm certs/*
echo "Make CA:"
openssl genrsa -out ./certs/rootCA.key 2048
openssl req -x509 -new -nodes -key ./certs/rootCA.key -days 1024 -out ./certs/rootCA.pem
echo "Make cert:"
openssl genrsa -out ./certs/server.key 2048
openssl req -new -key ./certs/server.key -out ./certs/server.csr
openssl x509 -req -in ./certs/server.csr -CA ./certs/rootCA.pem -CAkey ./certs/rootCA.key -CAcreateserial -out ./certs/server.crt -days 500
