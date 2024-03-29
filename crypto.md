### AES encryption/Decryption
```
// decryption
# openssl enc -d -nopad -nosalt  -aes-128-ecb -K 00000000000000000000000000000000 -in ./out.bin -out ./data.bin
Key:  in Hex String
file: Binary data

// encryption
openssl enc -e -nopad -nosalt  -aes-128-cbc -K '2b7e151628aed2a6abf7158809cf4f3c'  -iv '000102030405060708090a0b0c0d0e0f'  -in ./data.bin -out ./out.bin
```

### text to binary conversion
```
$ cat ./data.txt 
6bc1bee22e409f96e93d7e117393172a1a2b

/* convert text string into binary data */
# xxd -r -p ./input.txt out.bin

/* Conver binary file into hex string file */
 xxd -p test.in > test.txt
```
### HMAC command 
```
// the data file is binary file rather than text file
openssl dgst  -sha256 -mac HMAC -macopt hexkey:9779d9120642797f1747025d5b22b7ac607cab08e1758f2f3a46c8be1e25c53b8c6a8f58ffefa176 ./data.bin
```

### check RSA pub key
```
openssl rsa -in ./data/K0_REE.rsa.pub.pem -noout -text -pubin
```

### Signature
```
openssl dgst -sha256 -sign sign_key.rsa.priv.pem -out signature.bin data.bin
```

### SHA256
```
openssl dgst -sha256 data.bin
```


### Check a certificate
Check a certificate and return information about it (signing authority, expiration date, etc.):

openssl x509 -in server.crt -text -noout

### Check a key
Check the SSL key and verify the consistency:

openssl rsa -in server.key -check

### Check a CSR
Verify the CSR and print CSR data filled in when generating the CSR:

openssl req -text -noout -verify -in server.csr

### Verify a certificate and key matches
These two commands print out md5 checksums of the certificate and key; the checksums can be compared to verify that the certificate and key match.

openssl x509 -noout -modulus -in server.crt| openssl md5
openssl rsa -noout -modulus -in server.key| openssl md5
