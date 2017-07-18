apt-get update && apt-get -yq upgrade
apt-get install -y git python3 python3-dev python3-pip virtualenv cmake wget vim emacs
virtualenv hydra_env -p /usr/bin/python3 --no-site-package
source hydra_env/bin/activate
pip install numpy
pip install llvmlite
pip install numba

git clone https://github.com/Deepanshu2017/pybind11_practise.git
cd pybind11_practise/edu
git clone "https://github.com/pybind/pybind11.git"
cmake .
cmake --build . --target hello
python -c "import hello; hello.print()"

cd ../..
wget https://downloads.sourceforge.net/project/tclap/tclap-1.2.1.tar.gz
tar -xvf tclap-1.2.1.tar.gz
cd tclap-1.2.1
./configure
make
make install
cd ..

wget https://root.cern.ch/download/root_v6.08.06.Linux-ubuntu16-x86_64-gcc5.4.tar.gz
tar -xvf root_v6.08.06.Linux-ubuntu16-x86_64-gcc5.4.tar.gz
. root/bin/thisroot.sh

wget https://dl.bintray.com/boostorg/release/1.64.0/source/boost_1_64_0.tar.gz
tar -xvf boost_1_64_0.tar.gz
cd boost_1_64_0
./bootstrap.sh
./b2 -j16 install
cd ..

git clone https://github.com/MultithreadCorner/Hydra.git
cd Hydra
mkdir build
cd build
cmake ../
make
