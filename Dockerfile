FROM vvakame/review:latest
RUN npm install -g @vivliostyle/cli
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
      libatk-bridge2.0-0 libgtk-3-0 libasound2 && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*
# Patch for Linux+Docker+tmpfs issue
COPY patches/ /tmp
RUN cd /var/lib/gems/3.1.0/gems/review-5.8.0 && patch -p1 < /tmp/01preserve.patch && rm -r /tmp/*.patch
WORKDIR /work
