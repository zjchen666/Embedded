
## Installation:
### vundle :  
install:  
git clone https://github.com/VundleVim/Vundle.vim.git ~/.vim/bundle/Vundle.vim

install plugin:  
:PluginInstall

replace:
:%s/pld_string/new_string/g

### ctags on MacOS . 
#you need to get new ctags, i recommend homebrew but anything will work . 
$ brew install ctags  

#alias ctags if you used homebrew . 
$ alias ctags="`brew --prefix`/bin/ctags" . 


## Operation:

多行缩进：  
V 选择你要缩进的行数
再按 < 或 > 做缩进或退缩

文件内变量查找：  
gd 
n

new window:  
:split

file switch:  
:bn  
:bp

## show tab and space  
:set list listchars=tab:>-,trail:-  

## 光标跳转  
Ctrl + O
Ctrl + I
## search and replace  
% 代表对整个文件有效  
:%s/foo/bar/g  
Find each occurrence of 'foo' (in all lines), and replace it with 'bar'.  
:s/foo/bar/g  
Find each occurrence of 'foo' (in the current line only), and replace it with 'bar'.  
:%s/foo/bar/gc  
Change each 'foo' to 'bar', but ask for confirmation first.  
:%s/\<foo\>/bar/gc  
Change only whole words exactly matching 'foo' to 'bar'; ask for confirmation.  
:%s/foo/bar/gci  
Change each 'foo' (case insensitive due to the i flag) to 'bar'; ask for confirmation.  
:%s/foo\c/bar/gc is the same because \c makes the search case insensitive.  
This may be wanted after using :set noignorecase to make searches case sensitive (the default).  
:%s/foo/bar/gcI  
Change each 'foo' (case sensitive due to the I flag) to 'bar'; ask for confirmation.  
:%s/foo\C/bar/gc is the same because \C makes the search case sensitive.  
This may be wanted after using :set ignorecase to make searches case insensitive.  

## cscope update database
:!cscope -Rbq  
:cs reset

显示版本及默认vimrc配置文件加载路径:scriptnames

## add space into multiple lines
1. Use Ctrl + V to enter visual block mode.  
2. Move Up / Down to select the columns of text in the lines you want to comment.  
3. Then hit Shift + i and type the text you want to insert.  
4. Then hit Esc , wait 1 second and the inserted text will appear on every line.  
