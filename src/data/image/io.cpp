#include <iostream>
#include <fstream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"  // Put this in one .cpp file only!

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h" // Put this in one .cpp file only! 


#include "io.hpp"
#include "image.hpp"

#include <opencv2/imgproc.hpp>


using namespace std;


namespace image::io { 

    Image fromEncodedBuffer(const uint8_t* data, size_t size) {
        int width, height, channels;

        unsigned char* pixels = stbi_load_from_memory(data, size, &width, &height, &channels, 4); // Force RGBA

        if (!pixels) {
            throw std::runtime_error("Failed to load image from memory");
        }

        Image img(width, height);
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                int idx = (y * width + x) * 4;
                Color c;
                c.r = pixels[idx + 0];
                c.g = pixels[idx + 1];
                c.b = pixels[idx + 2];
                img.setPixel(x, y, c);
            }
        }

        stbi_image_free(pixels);
        return img;
    }

    Image loadImageFileSystem(const std::string& path) { 
        std::ifstream f(path, std::ios::binary);
        auto data = std::vector<uint8_t>((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
        return fromEncodedBuffer(data.data(), data.size());
    }

    void saveImageFileSystem(const Image& img, const std::string& save_path) {
        int width = img.getWidth();
        int height = img.getHeight();
        int channels = 4; // RGBA
    
        // Allocate flat buffer (row-major RGB)
        std::vector<uint8_t> buffer(width * height * channels);
    
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                Color c = img.at(x, y);
                int idx = (y * width + x) * channels;
                buffer[idx + 0] = c.r;
                buffer[idx + 1] = c.g;
                buffer[idx + 2] = c.b;
                buffer[idx + 3] = c.a;
            }
        }
    
        // Write as PNG (you can also use stbi_write_jpg or stbi_write_bmp)
        int success = stbi_write_jpg(save_path.c_str(), width, height, channels, buffer.data(), width * channels);
    
        if (!success) {
            throw std::runtime_error("Failed to save image to: " + save_path);
        }
    }
    

    cv::Mat imageToCvMat(const Image& source_image) { 
        cv::Mat dest_mat(source_image.getHeight(), source_image.getWidth(), CV_8UC4);
        std::memcpy(dest_mat.data, source_image.rawData(), source_image.rawDataBytesSize());
        cv::cvtColor(dest_mat, dest_mat, cv::COLOR_RGB2BGR);
        return dest_mat;
    }


}