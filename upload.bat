@echo off

git rm --cached -r *
git add -A
git commit -m "C++"
git push origin master
