FROM alpine:latest as builder
RUN apk add --no-cache \
	build-base \
	git \
	libressl-dev \
	libuv-dev \
	linux-headers \
	zlib-dev \
	cmake

WORKDIR /app
COPY . .
RUN cmake .
RUN make

FROM alpine:latest as app

RUN apk add --no-cache libstdc++

COPY --from=builder /app/cpphttpserver /app/cpphttpserver
COPY --from=builder /app/build/index.html /app/index.html

WORKDIR /app

ENTRYPOINT [ "./cpphttpserver" ]