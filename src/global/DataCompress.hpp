/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** DataCompress
*/

#ifndef DATACOMPRESS_HPP_
#define DATACOMPRESS_HPP_
#include "lz4.h"

class DataCompress {
    public:
        DataCompress(){};
        DataCompress(const char *src){
            Compress(src);
        }
        DataCompress(int compressed_size, int og_size) : compressed_size(compressed_size), original_size(og_size) {};
        ~DataCompress() = default;
        char *Compress(const char *src) {
            int src_size = static_cast<int>(strlen(src) + 1);
            original_size = src_size;
            int maxCompressedSize = LZ4_compressBound(src_size);
            compressed = new char[maxCompressedSize];
            if (compressed == NULL) {
                // Not enough memory
                throw std::runtime_error("Not enough memory");
            }
            compressed_size = LZ4_compress_default(src, compressed, src_size, maxCompressedSize);
            if (compressed_size <= 0) {
                // Compression failed
                throw std::runtime_error("Compression failed");
            }
            // if (compressed_size > 0) {
            //     std::cout << "compressed with a ratio : " << (float)src_size / compressed_size << std::endl;
            //     std::cout << "compressed size : " << compressed_size << std::endl;
            //     std::cout << "original size : " << src_size << std::endl;
            // }
            char *new_compressed = new char[compressed_size];
            if (new_compressed == NULL) {
                // Not enough memory
                throw std::runtime_error("Not enough memory");
            }
            memcpy(new_compressed, compressed, compressed_size);
            delete[] compressed;
            compressed = new_compressed;
            return compressed;
        }
        // Decompress data using LZ4
        char *Decompress(const char *src) {
            char *decompressed = new char[original_size];
            if (decompressed == NULL) {
                // Not enough memory
                throw std::runtime_error("Not enough memory");
            }
            const int decSize = LZ4_decompress_safe(src, decompressed, compressed_size, original_size);
            if (decSize < 0) {
                // Decompression failed
                throw std::runtime_error("Decompression failed");
            }
            return decompressed;

        }
        void setCompressedSize(int size) {
            compressed_size = size;
        }
        int getCompressedSize() {
            return compressed_size;
        }
        void setOriginalSize(int size) {
            original_size = size;
        }
        int getOriginalSize() {
            return original_size;
        }
        char *getCompressed() {
            return compressed;
        }
    protected:
    private:
        int compressed_size;
        int original_size;
        char *compressed;
};

#endif /* !DATACOMPRESS_HPP_ */
