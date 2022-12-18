# update submodule for develop branch

BR=`git name-rev --name-only HEAD`
echo "Current branch : $BR"
git pull
git submodule update --init --recursive

cd dep/emblib
git checkout $BR
git pull


