__change PIN__  
Default PIV PIN: 123456  
Default PIV admin PIN: 12345678  
Default PIV unlock PIN: 12345678  
```
 # gpg --card-edit

> passwd
```

__export key from PC to yubikey__   

```
gpg2 --edit-key <Key ID>

> keytocard
> enter pgp key password
> enter Admin PIN
```

