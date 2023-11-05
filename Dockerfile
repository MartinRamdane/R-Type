FROM adamelm/r-type-compiler:latest
WORKDIR /rtype
COPY src/ src/
COPY CMakeLists.txt .
COPY conanfile.py .
COPY config/ config/
COPY assets/ assets/
COPY font/ font/
COPY sounds/ sounds/
RUN pip3 install conan && conan profile detect --force && conan install . --output-folder=build --build=missing
RUN cd build && cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release && cmake --build .
RUN cd build && cpack