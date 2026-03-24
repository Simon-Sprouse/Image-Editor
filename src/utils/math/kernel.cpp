#include "kernel.hpp"

namespace math::kernel {


    std::vector<double> generateGaussianKernel1D(int radius, double sigma) {

        // TODO maybe this belongs in a math library? 
        int size = 2 * radius + 1;
        std::vector<double> kernel(size);
        double sum = 0.0;
    
        const double coeff = 1.0 / (std::sqrt(2.0 * M_PI) * sigma);
        const double denom = 2.0 * sigma * sigma;
    
        for (int i = -radius; i <= radius; ++i) {
            double value = coeff * std::exp(-(i * i) / denom);
            kernel[i + radius] = value;
            sum += value;
        }
    
        // Normalize kernel
        for (double& value : kernel) {
            value /= sum;
        }
    
        return kernel;
    }
    
}