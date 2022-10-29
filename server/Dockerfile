FROM kitware/cmake:ci-fedora36-x86_64-2022-10-04

WORKDIR /app
COPY . .

# RUN cd ./bin
RUN cmake .
RUN make my_server

ENTRYPOINT [ "./my_server" ]