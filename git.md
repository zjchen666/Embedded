//download from server
git clone url

// local
git add # 将工作区的修改提交到暂存区
git commit # 将暂存区的修改提交到当前分支

// to server
git push branch master

git status # 查看当前仓库的状态
git diff # 查看修改
git log # 查看提交历史
git reset # 回退到某一个版本
git reflog # 查看历史命令，类似与Linux中的history

// branch
git branch # 查看所有本地分支
git branch <new-branch> # 创建一个新的分支
git checkout <branch> # 切换到指定分支
git branch -d <branch> # 删除一个分支
git merge <branch> # 将指定的分支合并到当前分支
