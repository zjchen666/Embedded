__0, 1, 2__
```
0 (stdin) - input
1 (stdout) - output
2 - stderr
```

__$? &>__
```
echo $?   -- The special variable $? returns the exit status of the last executed command
&>file -- redirects both stdout and stderr to the file
```

__remove color code from text stream__
```
sed -e 's/\x1b\[[0-9;]*m//g'
```

__find_and_replace__
```
grep -rl "find_string" . | xargs sed -i 's/find_string/replace_string/g'
```
