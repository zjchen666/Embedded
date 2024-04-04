### filtering the web traffic  
```
http.request or tls.handshake.type eq 1
```

| Button Label	| Filter Expression |
----------------| --------------------
| basic	| (http.request or tls.handshake.type eq 1) and !(ssdp)
| basic+	| (http.request or tls.handshake.type eq 1 or (tcp.flags.syn eq 1 and tcp.flags.ack eq 0)) and !(ssdp)
| basic+dns	| (http.request or tls.handshake.type eq 1 or (tcp.flags.syn eq 1 and tcp.flags.ack eq 0) or dns) and !(ssdp)

reference: https://unit42.paloaltonetworks.com/using-wireshark-display-filter-expressions/ 
