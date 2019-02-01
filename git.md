//download from server  
git clone url

## local  
git add # 将工作区的修改提交到暂存区  
git commit # 将暂存区的修改提交到当前分支  
git status # 查看当前仓库的状态  
git diff # 查看修改  
git log # 查看提交历史  
git reset --hard # 回退到某一个版本  
git reflog # 查看历史命令，类似与Linux中的history  
git checkout -- <file> 丢掉当前workspace的改动 - 没有 git add的文件
git reset HEAD <file>可以把暂存区的修改撤销掉（unstage）已经added的 但没有commit的文件 
git show COMMIT
 
## remote  
git push branch master  
git pull 从远程抓取分支，使用

## branch  
git branch # 查看所有本地分支  
git checkout <branch> # 切换到指定分支  
git branch <new-branch> # 创建一个新的分支  
git branch -d <branch> # 删除一个分支  
git merge <branch> # 将指定的分支合并到当前分支  

## remove  
git rm -r --cached myFolder # 保留本地  
git rm -r myFolder # 不保留本地

## add  
git add -A .来一次添加所有改变的文件  
git add . 表示添加新文件和编辑过的文件不包括删除的文件  
git add -u 表示添加编辑或者删除的文件，不包括新添加的文件  
