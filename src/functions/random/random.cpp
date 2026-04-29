#include "random.hpp"

#include <chrono>


namespace random_gen { 


    


    


        
    double randomDouble(double min_val, double max_val) {
        static std::mt19937 rng(std::random_device{}());
        std::uniform_real_distribution<double> dist(min_val, max_val);
        return dist(rng);
    }

    Color randomColor() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<int> dist(0, 255);
    
        return Color{
            static_cast<uint8_t>(dist(gen)),  // red
            static_cast<uint8_t>(dist(gen)),  // green
            static_cast<uint8_t>(dist(gen))   // blue
        };
    }

    std::vector<Color> randomColors(int num_colors) { 
        std::vector<Color> colors;
        colors.reserve(num_colors);
        for (int i = 0; i < num_colors; i++) { 
            colors.push_back(randomColor());
        }   
        return colors;
    }

    



    Point randomPoint(int w, int h) { 
        static std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<int> dist_x(0, w - 1);
        std::uniform_int_distribution<int> dist_y(0, h - 1);
        int x = dist_x(rng);
        int y = dist_y(rng);
        return Point(x, y);
    }
    Point randomPoint(Size size) {
        return randomPoint(size.width, size.height);
    }

    std::vector<Point> randomPointsVector(int w, int h, int num_points) { 

        std::vector<Point> random_points;

        static std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<int> dist_x(0, w - 1);
        std::uniform_int_distribution<int> dist_y(0, h - 1);

        for (int i = 0; i < num_points; ++i) {
            int x = dist_x(rng);
            int y = dist_y(rng);
            random_points.emplace_back(x, y);
        }

        return random_points;
    }
    std::vector<Point> randomPointsVector(Size size, int num_points) { 
        return randomPointsVector(size.width, size.height, num_points);
    }


    std::vector<Point> gridPointsVector(int w, int h, int grid_size) {
        std::vector<Point> grid_points;


        for (int y = 0; y < h; y += grid_size) {
            for (int x = 0; x < w; x += grid_size) {
                grid_points.emplace_back(Point(x, y));
            }
        }

        return grid_points;
    }


    std::vector<Point> gridPointsVector(Size size, int grid_size) {
        return gridPointsVector(size.width, size.height, grid_size);
    }

    std::vector<Point> jitterPoints(const std::vector<Point>& input_points, int max_step, const Size& image_size) {
        std::vector<Point> jittered_points;

        if (max_step < 0 || input_points.empty()) {
            return input_points;  // No jittering needed
        }

        static std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<int> offset_dist(-max_step, max_step);

        for (const auto& pt : input_points) {
            int jitter_x = pt.x + offset_dist(rng);
            int jitter_y = pt.y + offset_dist(rng);

            // Clamp to image bounds
            jitter_x = std::clamp(jitter_x, 0, image_size.width - 1);
            jitter_y = std::clamp(jitter_y, 0, image_size.height - 1);

            jittered_points.emplace_back(jitter_x, jitter_y);
        }

        return jittered_points;
    }



    uint32_t lcg(uint32_t seed) { 
        // Real formula is: 
        // R0 = seed
        // Rn = (aRn + c) mod m
        // where: c and m are coprime, a-1 divisible by prime factors of m, 
        //        and if m is divisible then a-1 % 4 == 0
        //
        // but we cam set m = 2^32 and int_32 overflows gives a natural mod
        uint32_t a = 1664525u;
        uint32_t c = 1013904223u;
        return a * seed + c;
    }

    // credit chris wellons
    // https://github.com/skeeto/hash-prospector
    uint32_t triple32(uint32_t x) {
        x ^= x >> 17;
        x *= 0xed5ad4bb;
        x ^= x >> 11;
        x *= 0xac4c1b51;
        x ^= x >> 15;
        x *= 0x31848bab;
        x ^= x >> 14;
        return x;
    }

    // credit daniel lemire
    // https://github.com/lemire/fastrange
    uint32_t random_bounded(uint32_t x, uint32_t range) {
        return uint32_t((uint64_t(x) * range) >> 32);
    }

    uint32_t random_bounded(uint32_t x, int range) { 
        return random_bounded(x, static_cast<uint32_t>(range));
    }

    uint32_t seedFromClock() { 
        using clock = std::chrono::high_resolution_clock;
        auto now = clock::now();
        auto duration = now.time_since_epoch();
        return static_cast<uint32_t>(duration.count());
    }
   




}