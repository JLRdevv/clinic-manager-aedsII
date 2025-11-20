FROM ubuntu:22.04 AS builder

RUN apt update && apt install -y \
    g++ \
    cmake \
    git \
    build-essential \
    python3 \
    libasio-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . .

RUN cmake -B build -DCMAKE_BUILD_TYPE=Release .
RUN cmake --build build --target app -- -j$(nproc)

FROM ubuntu:22.04 AS runtime
RUN apt update && apt install -y libstdc++6 && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY --from=builder /app/build/app /app/app

CMD ["./app"]
