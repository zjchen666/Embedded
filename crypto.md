### AES encryption/Decryption
openssl enc -d -nopad -nosalt  -aes-128-ecb -K 00000000000000000000000000000000 -in ./out.bin -out ./data.bin
Key:  in Hex String
file: Binary data