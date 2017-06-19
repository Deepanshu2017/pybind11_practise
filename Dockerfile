FROM ubuntu:16.04
MAINTAINER Deepanshu Thakur (deepanshu2017@gmail.com)
RUN apt-get update && apt-get -yq upgrade \
 && apt-get install -yq --no-install-recommends \
    apt-utils \
    python3-dev \
    python3 \
    python3-pip \
    wget \
    git \
    clang \
 && apt-get clean \
 && rm -rf /var/lib/apt/lists/*

RUN mkdir /home/deepanshu 
WORKDIR /home/deepanshu

RUN git clone "https://github.com/pybind/pybind11.git" \
 && wget -O make.common "https://raw.githubusercontent.com/Deepanshu2017/pybind11_practise/master/make.common" \
 && wget -O makefile "https://raw.githubusercontent.com/Deepanshu2017/pybind11_practise/master/makefile" \
 && wget -O bp_magic.py "https://raw.githubusercontent.com/Deepanshu2017/pybind11_practise/master/bp_magic.py" \
 && wget -O CPP.ipynb "https://raw.githubusercontent.com/Deepanshu2017/pybind11_practise/master/CPP.ipynb" \
 && wget -O Python.ipynb "https://raw.githubusercontent.com/Deepanshu2017/pybind11_practise/master/Python.ipynb" 

RUN pip3 install --upgrade pip
RUN pip install setuptools \
 && pip install ipython \
 && pip install jupyter

RUN mkdir ~/.jupyter/ \
 && echo "c.NotebookApp.token = ''" >> ~/.jupyter/jupyter_notebook_config.py \ 
 && echo "c.NotebookApp.password = ''" >> ~/.jupyter/jupyter_notebook_config.py

EXPOSE 8888
CMD jupyter-notebook --allow-root --ip 0.0.0.0 
