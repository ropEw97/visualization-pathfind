FROM ubuntu:latest

RUN apt-get update 
RUN apt-get -y install unzip wget libdbus-1-3 libfontconfig1

ENV QT_VERSION_A=5.9
ENV QT_VERSION_B=5.9.4
ENV QT_VERSION_SCRIPT=594
ENV QT_GRAPHICSSYSTEM="native"
RUN wget https://download.qt.io/archive/qt/${QT_VERSION_A}/${QT_VERSION_B}/qt-opensource-linux-x64-${QT_VERSION_B}.run
RUN chmod +x qt-opensource-linux-x64-${QT_VERSION_B}.run 
COPY qt-noninteractive.qs /qt-noninteractive.qs
RUN ./qt-opensource-linux-x64-${QT_VERSION_B}.run --script qt-noninteractive.qs  -platform minimal

COPY ./src /usr/src/app
WORKDIR /usr/src/app
RUN sudo apt-get install qt5-qmake
RUN sudo apt-get install qtbase5-dev
RUN qmake
RUN make
CMD [./algorithms]