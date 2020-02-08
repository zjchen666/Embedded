
remote server ---- clone/fetch -----> repository ---> checkout ---> local
remote server <---- push ----- repository <--- add & commit --- local
remote server ------------------- pull -----------------------> local

## Clone 
git clone url 第一次初始化git

## Fetch
1. git remote -v : check remote repository
2. git fetch [remote repository_name] [branch_name]:tmp : checkout remote branch to local tmp branch    
3. git diff tmp : diff current local branch and tmp branch
4. git merge tmp: merge [optional]

## Push 
git push origin HEAD:refs/for/master  

## Checkout
You need to create a local branch that tracks a remote branch. The following command will create a local branch named daves_branch, tracking the remote branch origin/daves_branch. When you push your changes the remote branch will be updated.

For most recent versions of git:

git checkout --track origin/daves_branch
--track is shorthand for git checkout -b [branch] [remotename]/[branch] where [remotename] is origin in this case and [branch] is twice the same, daves_branch in this case.

For git 1.5.6.5 you needed this:

git checkout --track -b daves_branch origin/daves_branch
For git 1.7.2.3 and higher this is enough (might have started earlier but this is the earliest confirmation I could find quickly):

git checkout daves_branch  

## Submit Steps
1. After change, you should update your branch first:  
git fetch  
git rebase origin/master  

2. Check how many files you changed:  
git status  

3. add wanted file one by one:  
git add <wanted file>  

4. Commit your change:  
git commit -m "to realize the login model"  

5. Push your new code to gerrit for review:  
git push origin HEAD:refs/for/master 

## local command 
git add # 将工作区的修改提交到暂存区  
git commit # 将暂存区的修改提交到当前分支  
git status # 查看当前仓库的状态  
git log # 查看提交历史  
git reset --hard # 回退到某一个版本  
git reflog # 查看历史命令，类似与Linux中的history  
git checkout -- <file> 丢掉当前workspace的改动 - 没有add到stage的文件   
git checkout coomit_id <file> revert当前workspace的文件到指定版本  
git reset HEAD <file>可以把已经added到staged的文件reset  
git show COMMIT
 
## diff 
git diff --cached # 查看 staged 修改     
git diff # 查看 local unstaged 修改    

## remote  
git push branch master  
git pull 从远程抓取分支，使用 . 
git remote -v 

## branch  
git branch # 查看所有本地分支  
git checkout <branch> # 切换到指定分支  
git branch <new-branch> # 创建一个新的分支  
git branch -d <branch> # 删除一个分支  
git merge <branch> # 将指定的分支合并到当前分支  

git branch -vv ## 显示 local branch 和 remote branch的 联系  
git checkout -b local_branch remote_branch 建立 local branch 和 remote branch 的关系。
 
## remove  
git rm -r --cached myFolder # 保留本地  
git rm -r myFolder # 不保留本地

## add  
git add -A .来一次添加所有改变的文件  
git add . 表示添加新文件和编辑过的文件不包括删除的文件  
git add -u 表示添加编辑或者删除的文件，不包括新添加的文件  

## Rebase - 用来解决多个pending CL update
```
   git rebase -i HEAD~n
   change the CL to 'edit'
   git commit --amend
   git rebase --continue
```

https://git-scm.com/book/zh/v2/Git-%E5%B7%A5%E5%85%B7-%E9%87%8D%E5%86%99%E5%8E%86%E5%8F%B2

## Patch  - solve merge conflict between branch and master
### 用于已提交的版本
1. Branch: git format-patch HEAD^  有几个^就会打几个patch，从最近一次打起  
   以下代码作用同上  
   git format-patch -1 
2. repo sync  
3. git am patch patch_name  
4. commit to master

### local change
    git diff > patch_name
    patch -p1 < patch_name


