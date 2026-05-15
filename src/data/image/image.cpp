#include "image.hpp"
#include <arm_neon.h>


namespace image { 





    // Conversions 
    // todo swap these out with SIMD optimizations
    

    Image<HSV> toHSV(const Image<RGBA>& original) { 
        Image<HSV> hsv(original.size());

        // --- FUTURE SIMD CODE ---
        // int n = 4; // batch size
        // int simd_ops = original.size() / n
        // for (int i = 0; i < simd_ops; i += n) { 
        //      RGBA2HSV_batch()
        // }
        // int remaining = original.size() - simd_ops * n;
        // for (int i = 0; i < remaining; i++) {
        //      RGBA2HSV();
        // }


        // todo police usage of original as var name
        for (int i = 0; i < original.linearSize(); i++) { 
            hsv.setPixel(i, original.at(i).toHsv());
        }
        return hsv;
    }

    Image<GRAY> toGRAY(const Image<RGBA>& original) { 
        Image<GRAY> gray(original.size());
        for (int i = 0; i < original.linearSize(); i++) { 
            gray.setPixel(i, original.at(i).toGray());
        }
        return gray;
    }

    // todo polymorphic toRGBA needs to handle all types eventually
    // todo should this function allocate memory?
    Image<RGBA> toRGBA(const Image<HSV>& original) { 
        Image<RGBA> rgba(original.size());
        for (int i = 0; i < original.linearSize(); i++) { 
            rgba.setPixel(i, original.at(i).toRgba());
        }
        return rgba;
    }






    void HSV2RGBA_simd(HSV* ptr, RGBA* dest) { 
        

        // LOAD
        uint8x16x4_t load = vld4q_u8(reinterpret_cast<uint8_t*>(ptr));
        uint8x16_t off = load.val[0];
        uint8x16_t seg = load.val[1]; // msb stored later do to little-end
        uint8x16_t s = load.val[2];
        uint8x16_t v = load.val[3];


        // SPLIT
        uint8x8_t off_0 = vget_low_u8(off);
        uint8x8_t s_0 = vget_low_u8(s);
        uint8x8_t v_0 = vget_low_u8(v);

        uint8x8_t off_1 = vget_high_u8(off);
        uint8x8_t s_1 = vget_high_u8(s);
        uint8x8_t v_1 = vget_high_u8(v);

        // WIDEN
        uint16x8_t off_0_w = vmovl_u8(off_0);
        uint16x8_t s_0_w = vmovl_u8(s_0);
        uint16x8_t v_0_w = vmovl_u8(v_0);

        uint16x8_t off_1_w = vmovl_u8(off_1);
        uint16x8_t s_1_w = vmovl_u8(s_1);
        uint16x8_t v_1_w = vmovl_u8(v_1);

        // MATH
        uint16x8_t delta_0_pre = vmulq_u16(v_0_w, s_0_w);       // v * s
        uint16x8_t delta_0 = vshrq_n_u16(delta_0_pre, 8);       // (v * s) >> 8
        uint16x8_t cmin_0 = vsubq_u16(v_0_w, delta_0);          // v - delta

        uint16x8_t delta_x_off_pre_0 = vmulq_u16(delta_0, off_0_w);     // delta * off
        uint16x8_t delta_x_off_0 = vshrq_n_u16(delta_x_off_pre_0, 8);      // (delta * off) >> 8
        uint16x8_t fall_0 = vsubq_u16(v_0_w, delta_x_off_0);  // cmax - (delta*off)>>8
        uint16x8_t rise_0 = vaddq_u16(cmin_0, delta_x_off_0); // cmin + (delta*off)>>8


        uint16x8_t delta_1_pre = vmulq_u16(v_1_w, s_1_w);
        uint16x8_t delta_1 = vshrq_n_u16(delta_1_pre, 8);
        uint16x8_t cmin_1 = vsubq_u16(v_1_w, delta_1);

        uint16x8_t delta_x_off_pre_1 = vmulq_u16(delta_1, off_1_w);
        uint16x8_t delta_x_off_1 = vshrq_n_u16(delta_x_off_pre_1, 8);
        uint16x8_t fall_1 = vsubq_u16(v_1_w, delta_x_off_1);
        uint16x8_t rise_1 = vaddq_u16(cmin_1, delta_x_off_1);

        // RESTRUCTURE
        uint8x8_t v_0_h = vmovn_u16(v_0_w);
        uint8x8_t v_1_h = vmovn_u16(v_1_w);
        uint8x16_t cmax = vcombine_u8(v_0_h, v_1_h);

        uint8x8_t cmin_0_h = vmovn_u16(cmin_0);
        uint8x8_t cmin_1_h = vmovn_u16(cmin_1);
        uint8x16_t cmin = vcombine_u8(cmin_0_h, cmin_1_h);

        uint8x8_t fall_0_h = vmovn_u16(fall_0);
        uint8x8_t fall_1_h = vmovn_u16(fall_1);
        uint8x16_t fall = vcombine_u8(fall_0_h, fall_1_h);

        uint8x8_t rise_0_h = vmovn_u16(rise_0);
        uint8x8_t rise_1_h = vmovn_u16(rise_1);
        uint8x16_t rise = vcombine_u8(rise_0_h, rise_1_h);

        // CREATE MASK
        uint8x16_t k_0 = vdupq_n_u8(0);
        uint8x16_t k_1 = vdupq_n_u8(1);
        uint8x16_t k_2 = vdupq_n_u8(2);
        uint8x16_t k_3 = vdupq_n_u8(3);
        uint8x16_t k_4 = vdupq_n_u8(4);
        uint8x16_t k_5 = vdupq_n_u8(5);

        uint8x16_t m_0 = vceqq_u8(seg, k_0);
        uint8x16_t m_1 = vceqq_u8(seg, k_1);
        uint8x16_t m_2 = vceqq_u8(seg, k_2);
        uint8x16_t m_3 = vceqq_u8(seg, k_3);
        uint8x16_t m_4 = vceqq_u8(seg, k_4);
        uint8x16_t m_5 = vceqq_u8(seg, k_5);

        // APPLY MASK
        uint8x16_t r = vdupq_n_u8(0);
        uint8x16_t g = vdupq_n_u8(0);
        uint8x16_t b = vdupq_n_u8(0);
        uint8x16_t a = vdupq_n_u8(255);

        // segment 0
        r = vbslq_u8(m_0, cmax, r);
        g = vbslq_u8(m_0, rise, g);
        b = vbslq_u8(m_0, cmin, b);

        // segment 1
        r = vbslq_u8(m_1, fall, r);
        g = vbslq_u8(m_1, cmax, g);
        b = vbslq_u8(m_1, cmin, b);

        // segment 2
        r = vbslq_u8(m_2, cmin, r);
        g = vbslq_u8(m_2, cmax, g);
        b = vbslq_u8(m_2, rise, b);

        // segment 3
        r = vbslq_u8(m_3, cmin, r);
        g = vbslq_u8(m_3, fall, g);
        b = vbslq_u8(m_3, cmax, b);

        // segment 4
        r = vbslq_u8(m_4, rise, r);
        g = vbslq_u8(m_4, cmin, g);
        b = vbslq_u8(m_4, cmax, b);

        // segment 5
        r = vbslq_u8(m_5, cmax, r);
        g = vbslq_u8(m_5, cmin, g);
        b = vbslq_u8(m_5, fall, b);
        

        // STORE
        uint8x16x4_t out;
        out.val[0] = r;
        out.val[1] = g;
        out.val[2] = b;
        out.val[3] = a;

        vst4q_u8(reinterpret_cast<uint8_t*>(dest), out);


    }

    Image<RGBA> toRGBA_simd(Image<HSV>& original) { 
        Image<RGBA> rgba(original.size());
        int linear_size = original.linearSize();
        int num_ops = linear_size / 16;
        int tail_ops = linear_size - (16 * num_ops);
        for (int i = 0; i < num_ops; i += 16) { 
            HSV2RGBA_simd(original.data() + i, rgba.data() + i);
        }
        for (int i = 0; i < tail_ops; i++) { 
            rgba.setPixel(i, original.at(i).toRgba());
        }
        return rgba;
    }


















}