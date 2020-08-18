### AES encryption/Decryption
```
# openssl enc -d -nopad -nosalt  -aes-128-ecb -K 00000000000000000000000000000000 -in ./out.bin -out ./data.bin
Key:  in Hex String
file: Binary data

/* convert text string into binary data */
# xxd -r -p ./input.txt out.bin

/* Conver binary file into hex string file */
 xxd -p test.in > test.txt
```

### check RSA pub key
```
openssl rsa -in ./data/K0_REE.rsa.pub.pem -noout -text -pubin
```

### Signature
```
openssl dgst -sha256 -sign sign_key.rsa.priv.pem -out signature.bin data.bin
```
