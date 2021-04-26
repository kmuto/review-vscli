FROM vvakame/review:latest
RUN npm install -g npm && npm install -g @vivliostyle/cli
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
      libatk-bridge2.0-0 libgtk-3-0 libasound2 && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*
# Patch for Linux+Docker+tmpfs issue
COPY patches/ /tmp
RUN cd /var/lib/gems/2.5.0/gems/review-5.1.1 && patch -p1 < /tmp/01preserve.patch && rm -r /tmp/*.patch
WORKDIR /work
