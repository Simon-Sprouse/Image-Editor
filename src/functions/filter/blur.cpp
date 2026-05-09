#include "blur.hpp"
#include "../math/kernel.hpp"

using namespace image;



namespace filter::blur { 


    void gaussianBlur(Image<RGBA>& src, Image<RGBA>& dest, Size kernel_size, double blur_sigma) {
        const int width = src.getWidth();
        const int height = src.getHeight();
    
        if (kernel_size.width % 2 == 0 || kernel_size.height % 2 == 0) {
            throw std::invalid_argument("Kernel size must be odd.");
        }
    
        int radiusX = kernel_size.width / 2;
        int radiusY = kernel_size.height / 2;
    
        std::vector<double> kernelX = math::kernel::generateGaussianKernel1D(radiusX, blur_sigma);
        std::vector<double> kernelY = math::kernel::generateGaussianKernel1D(radiusY, blur_sigma);
    
        Image<RGBA> temp(width, height);  // Intermediate buffer
    
        // Horizontal pass
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                double r = 0, g = 0, b = 0, a = 0;
                for (int k = -radiusX; k <= radiusX; ++k) {
                    int sx = std::clamp(x + k, 0, width - 1);
                    RGBA sample = src.at(sx, y);
                    double w = kernelX[k + radiusX];
                    r += sample.r * w;
                    g += sample.g * w;
                    b += sample.b * w;
                    a += sample.a * w;
                }
                temp.at(x, y) = RGBA(
                    static_cast<uint8_t>(r),
                    static_cast<uint8_t>(g),
                    static_cast<uint8_t>(b),
                    static_cast<uint8_t>(a)
                );
            }
        }
    
        dest = Image<RGBA>(width, height);  // Allocate output
    
        // Vertical pass
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                double r = 0, g = 0, b = 0, a = 0;
                for (int k = -radiusY; k <= radiusY; ++k) {
                    int sy = std::clamp(y + k, 0, height - 1);
                    RGBA sample = temp.at(x, sy);
                    double w = kernelY[k + radiusY];
                    r += sample.r * w;
                    g += sample.g * w;
                    b += sample.b * w;
                    a += sample.a * w;
                }
                dest.at(x, y) = RGBA(
                    static_cast<uint8_t>(r),
                    static_cast<uint8_t>(g),
                    static_cast<uint8_t>(b),
                    static_cast<uint8_t>(a)
                );
            }
        }
    }

    void gaussianBlur(Image<RGBA>& src, Image<RGBA>& dest, int kernel_size, double blur_sigma) {
        Size kernel(kernel_size, kernel_size);
        gaussianBlur(src, dest, kernel, blur_sigma);
    }



}