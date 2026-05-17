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
        for (int i = 0; i < linear_size; i += 16) { 
            HSV2RGBA_simd(original.data() + i, rgba.data() + i);
        }
        for (int i = 0; i < tail_ops; i++) { 
            rgba.setPixel(i, original.at(i).toRgba());
        }
        return rgba;
    }



    void RGBA2HSV_simd(RGBA* src, HSV* dest) { 

        // LOAD
        uint8x16x3_t load = vld3q_u8(reinterpret_cast<uint8_t*>(src));
        uint8x16_t r = load.val[0];
        uint8x16_t g = load.val[1];
        uint8x16_t b = load.val[2];

        // SET VARS
        uint8x16_t cmax = vmaxq_u8(r, vmaxq_u8(g, b));
        uint8x16_t cmin = vminq_u8(r, vminq_u8(g, b));
        uint8x16_t delta = vsubq_u8(cmax, cmin);

        uint8x16_t r_g = vsubq_u8(r, g);
        uint8x16_t r_b = vsubq_u8(r, b);
        uint8x16_t g_b = vsubq_u8(g, b);
        uint8x16_t g_r = vsubq_u8(g, r);
        uint8x16_t b_r = vsubq_u8(b, r);
        uint8x16_t b_g = vsubq_u8(b, g);


        // MASKS
        uint8x16_t r_cmax = vceqq_u8(r, cmax);
        uint8x16_t g_cmax = vceqq_u8(g, cmax);
        uint8x16_t b_cmax = vceqq_u8(b, cmax);

        uint8x16_t r_cmin = vceqq_u8(r, cmin);
        uint8x16_t g_cmin = vceqq_u8(g, cmin);
        uint8x16_t b_cmin = vceqq_u8(b, cmin);

        uint8x16_t m5 = vandq_u8(r_cmax, g_cmin);
        uint8x16_t m0 = vandq_u8(r_cmax, b_cmin);
        uint8x16_t m1 = vandq_u8(g_cmax, b_cmin);
        uint8x16_t m2 = vandq_u8(g_cmax, r_cmin);
        uint8x16_t m3 = vandq_u8(b_cmax, r_cmin);
        uint8x16_t m4 = vandq_u8(b_cmax, g_cmin);

        // SET VARS
        uint8x16_t diff = vdupq_n_u8(0);
        diff = vbslq_u8(m5, b_g, diff);
        diff = vbslq_u8(m0, g_b, diff);
        diff = vbslq_u8(m1, r_b, diff);
        diff = vbslq_u8(m2, b_r, diff);
        diff = vbslq_u8(m3, g_r, diff);
        diff = vbslq_u8(m4, r_g, diff);

        uint8x16_t odd = vdupq_n_u8(0);
        odd = vorrq_u8(m1, vorrq_u8(m3, m5));

        uint8x16_t seg = vdupq_n_u8(0);
        seg = vbslq_u8(m1, vdupq_n_u8(1), seg);
        seg = vbslq_u8(m2, vdupq_n_u8(2), seg);
        seg = vbslq_u8(m3, vdupq_n_u8(3), seg);
        seg = vbslq_u8(m4, vdupq_n_u8(4), seg);
        seg = vbslq_u8(m5, vdupq_n_u8(5), seg);

        // SPLIT

        uint8x8_t delta_0 = vget_low_u8(delta);
        uint8x8_t diff_0 = vget_low_u8(diff);
        uint8x8_t odd_0 = vget_low_u8(odd);
        uint8x8_t seg_0 = vget_low_u8(seg);

        uint8x8_t cmax_0 = vget_low_u8(cmax);


        uint8x8_t delta_1 = vget_high_u8(delta);
        uint8x8_t diff_1 = vget_high_u8(diff);
        uint8x8_t odd_1 = vget_high_u8(odd);
        uint8x8_t seg_1 = vget_high_u8(seg);

        uint8x8_t cmax_1 = vget_high_u8(cmax);

        // WIDEN

        uint16x8_t delta_0_w = vmovl_u8(delta_0);
        uint16x8_t diff_0_w = vmovl_u8(diff_0);
        uint16x8_t odd_0_w = vmovl_u8(odd_0);
        uint16x8_t seg_0_w = vmovl_u8(seg_0);

        uint16x8_t cmax_0_w = vmovl_u8(cmax_0);


        uint16x8_t delta_1_w = vmovl_u8(delta_1);
        uint16x8_t diff_1_w = vmovl_u8(diff_1);
        uint16x8_t odd_1_w = vmovl_u8(odd_1);
        uint16x8_t seg_1_w = vmovl_u8(seg_1);

        uint16x8_t cmax_1_w = vmovl_u8(cmax_1);

        // RECIPROCALS

        uint16_t d_0_w_0 = vgetq_lane_u16(delta_0_w, 0);
        uint16_t d_0_w_1 = vgetq_lane_u16(delta_0_w, 1);
        uint16_t d_0_w_2 = vgetq_lane_u16(delta_0_w, 2);
        uint16_t d_0_w_3 = vgetq_lane_u16(delta_0_w, 3);
        uint16_t d_0_w_4 = vgetq_lane_u16(delta_0_w, 4);
        uint16_t d_0_w_5 = vgetq_lane_u16(delta_0_w, 5);
        uint16_t d_0_w_6 = vgetq_lane_u16(delta_0_w, 6);
        uint16_t d_0_w_7 = vgetq_lane_u16(delta_0_w, 7);

        uint16x8_t recip_delta_0_w = {
            RECIP[d_0_w_0],
            RECIP[d_0_w_1],
            RECIP[d_0_w_2],
            RECIP[d_0_w_3],
            RECIP[d_0_w_4],
            RECIP[d_0_w_5],
            RECIP[d_0_w_6],
            RECIP[d_0_w_7]
        };

        uint16_t d_1_w_0 = vgetq_lane_u16(delta_1_w, 0);
        uint16_t d_1_w_1 = vgetq_lane_u16(delta_1_w, 1);
        uint16_t d_1_w_2 = vgetq_lane_u16(delta_1_w, 2);
        uint16_t d_1_w_3 = vgetq_lane_u16(delta_1_w, 3);
        uint16_t d_1_w_4 = vgetq_lane_u16(delta_1_w, 4);
        uint16_t d_1_w_5 = vgetq_lane_u16(delta_1_w, 5);
        uint16_t d_1_w_6 = vgetq_lane_u16(delta_1_w, 6);
        uint16_t d_1_w_7 = vgetq_lane_u16(delta_1_w, 7);

        uint16x8_t recip_delta_1_w = {
            RECIP[d_1_w_0],
            RECIP[d_1_w_1],
            RECIP[d_1_w_2],
            RECIP[d_1_w_3],
            RECIP[d_1_w_4],
            RECIP[d_1_w_5],
            RECIP[d_1_w_6],
            RECIP[d_1_w_7]
        };

        uint16_t c_0_w_0 = vgetq_lane_u16(cmax_0_w, 0);
        uint16_t c_0_w_1 = vgetq_lane_u16(cmax_0_w, 1);
        uint16_t c_0_w_2 = vgetq_lane_u16(cmax_0_w, 2);
        uint16_t c_0_w_3 = vgetq_lane_u16(cmax_0_w, 3);
        uint16_t c_0_w_4 = vgetq_lane_u16(cmax_0_w, 4);
        uint16_t c_0_w_5 = vgetq_lane_u16(cmax_0_w, 5);
        uint16_t c_0_w_6 = vgetq_lane_u16(cmax_0_w, 6);
        uint16_t c_0_w_7 = vgetq_lane_u16(cmax_0_w, 7);

        uint16x8_t recip_cmax_0_w = {
            RECIP[c_0_w_0],
            RECIP[c_0_w_1],
            RECIP[c_0_w_2],
            RECIP[c_0_w_3],
            RECIP[c_0_w_4],
            RECIP[c_0_w_5],
            RECIP[c_0_w_6],
            RECIP[c_0_w_7]
        };

        uint16_t c_1_w_0 = vgetq_lane_u16(cmax_1_w, 0);
        uint16_t c_1_w_1 = vgetq_lane_u16(cmax_1_w, 1);
        uint16_t c_1_w_2 = vgetq_lane_u16(cmax_1_w, 2);
        uint16_t c_1_w_3 = vgetq_lane_u16(cmax_1_w, 3);
        uint16_t c_1_w_4 = vgetq_lane_u16(cmax_1_w, 4);
        uint16_t c_1_w_5 = vgetq_lane_u16(cmax_1_w, 5);
        uint16_t c_1_w_6 = vgetq_lane_u16(cmax_1_w, 6);
        uint16_t c_1_w_7 = vgetq_lane_u16(cmax_1_w, 7);

        uint16x8_t recip_cmax_1_w = {
            RECIP[c_1_w_0],
            RECIP[c_1_w_1],
            RECIP[c_1_w_2],
            RECIP[c_1_w_3],
            RECIP[c_1_w_4],
            RECIP[c_1_w_5],
            RECIP[c_1_w_6],
            RECIP[c_1_w_7]
        };


        // SPLIT + WIDEN FOR MULTIPLY
        uint16x4_t diff_0_w_0 = vget_low_u16(diff_0_w);
        uint32x4_t diff_0_w_0_w = vmovl_u16(diff_0_w_0);

        uint16x4_t diff_0_w_1 = vget_high_u16(diff_0_w);
        uint32x4_t diff_0_w_1_w = vmovl_u16(diff_0_w_1);

        uint16x4_t recip_delta_0_w_0 = vget_low_u16(recip_delta_0_w);
        uint32x4_t recip_delta_0_w_0_w = vmovl_u16(recip_delta_0_w_0);

        uint16x4_t recip_delta_0_w_1 = vget_high_u16(recip_delta_0_w);
        uint32x4_t recip_delta_0_w_1_w = vmovl_u16(recip_delta_0_w_1);

        uint16x4_t diff_1_w_0 = vget_low_u16(diff_1_w);
        uint32x4_t diff_1_w_0_w = vmovl_u16(diff_1_w_0);

        uint16x4_t diff_1_w_1 = vget_high_u16(diff_1_w);
        uint32x4_t diff_1_w_1_w = vmovl_u16(diff_1_w_1);

        uint16x4_t recip_delta_1_w_0 = vget_low_u16(recip_delta_1_w);
        uint32x4_t recip_delta_1_w_0_w = vmovl_u16(recip_delta_1_w_0);

        uint16x4_t recip_delta_1_w_1 = vget_high_u16(recip_delta_1_w);
        uint32x4_t recip_delta_1_w_1_w = vmovl_u16(recip_delta_1_w_1);





        uint16x4_t delta_0_w_0 = vget_low_u16(delta_0_w);
        uint32x4_t delta_0_w_0_w = vmovl_u16(delta_0_w_0);

        uint16x4_t recip_cmax_0_w_0 = vget_low_u16(recip_cmax_0_w);
        uint32x4_t recip_cmax_0_w_0_w = vmovl_u16(recip_cmax_0_w_0);

        uint16x4_t delta_0_w_1 = vget_high_u16(delta_0_w);
        uint32x4_t delta_0_w_1_w = vmovl_u16(delta_0_w_1);

        uint16x4_t recip_cmax_0_w_1 = vget_high_u16(recip_cmax_0_w);
        uint32x4_t recip_cmax_0_w_1_w = vmovl_u16(recip_cmax_0_w_1);

        uint16x4_t delta_1_w_0 = vget_low_u16(delta_1_w);
        uint32x4_t delta_1_w_0_w = vmovl_u16(delta_1_w_0);

        uint16x4_t recip_cmax_1_w_0 = vget_low_u16(recip_cmax_1_w);
        uint32x4_t recip_cmax_1_w_0_w = vmovl_u16(recip_cmax_1_w_0);

        uint16x4_t delta_1_w_1 = vget_high_u16(delta_1_w);
        uint32x4_t delta_1_w_1_w = vmovl_u16(delta_1_w_1);

        uint16x4_t recip_cmax_1_w_1 = vget_high_u16(recip_cmax_1_w);
        uint32x4_t recip_cmax_1_w_1_w = vmovl_u16(recip_cmax_1_w_1);

        // MULTIPLY

        // for hue
        uint32x4_t diff_0_w_0_w_pre = vshlq_n_u32(diff_0_w_0_w, 8); // diff * 256
        uint32x4_t x_product_0_0 = vmulq_u32(diff_0_w_0_w_pre, recip_delta_0_w_0_w);
        uint16x4_t x_0_0 = vget_high_u32(x_product_0_0); // >>16 and static_cast<uint16_t>

        uint32x4_t diff_0_w_1_w_pre = vshlq_n_u32(diff_0_w_1_w, 8);
        uint32x4_t x_product_0_1 = vmulq_u32(diff_0_w_1_w_pre, recip_delta_0_w_1_w);
        uint16x4_t x_0_1 = vget_high_u32(x_product_0_1); // >>16

        uint32x4_t diff_1_w_0_w_pre = vshlq_n_u32(diff_1_w_0_w, 8); // diff * 256
        uint32x4_t x_product_1_0 = vmulq_u32(diff_1_w_0_w_pre, recip_delta_1_w_0_w);
        uint16x4_t x_1_0 = vget_high_u32(x_product_1_0); // >>16 and static_cast<uint16_t>

        uint32x4_t diff_1_w_1_w_pre = vshlq_n_u32(diff_1_w_1_w, 8);
        uint32x4_t x_product_1_1 = vmulq_u32(diff_1_w_1_w_pre, recip_delta_1_w_1_w);
        uint16x4_t x_1_1 = vget_high_u32(x_product_1_1); // >>16


        // for saturation
        uint32x4_t const_255 = vdupq_n_u32(255);

        uint32x4_t delta_0_w_0_w_pre = vmulq_u32(delta_0_w_0_w, const_255);
        uint32x4_t s_product_0_0 = vmulq_u32(delta_0_w_0_w_pre, recip_cmax_0_w_0_w);
        uint16x4_t s_product_0_0_n = vget_high_u32(s_product_0_0); // >> 16

        uint32x4_t delta_0_w_1_w_pre = vmulq_u32(delta_0_w_1_w, const_255); // todo can do this before split
        uint32x4_t s_product_0_1 = vmulq_u32(delta_0_w_1_w_pre, recip_cmax_0_w_1_w);
        uint16x4_t s_product_0_1_n = vget_high_u32(s_product_0_1); // >> 16

        uint32x4_t delta_1_w_0_w_pre = vmulq_u32(delta_1_w_0_w, const_255);
        uint32x4_t s_product_1_0 = vmulq_u32(delta_1_w_0_w_pre, recip_cmax_1_w_0_w);
        uint16x4_t s_product_1_0_n = vget_high_u32(s_product_1_0); // >> 16

        uint32x4_t delta_1_w_1_w_pre = vmulq_u32(delta_1_w_1_w, const_255); // todo can do this before split
        uint32x4_t s_product_1_1 = vmulq_u32(delta_1_w_1_w_pre, recip_cmax_1_w_1_w);
        uint16x4_t s_product_1_1_n = vget_high_u32(s_product_1_1); // >> 16





        // CALCULATE S

        uint16x8_t s_0 = vcombine_u16(s_product_0_0_n, s_product_0_1_n);
        uint16x8_t s_1 = vcombine_u16(s_product_1_0_n, s_product_1_1_n);
        uint8x8_t s_0_n = vmovn_u16(s_0);
        uint8x8_t s_1_n = vmovn_u16(s_1);
        uint8x16_t s = vcombine_u8(s_0_n, s_1_n);

        // CALCULATE H

        uint16x8_t x_0 = vcombine_u16(x_0_0, x_0_1);
        uint16x8_t x_1 = vcombine_u16(x_1_0, x_0_1);

        uint16x8_t const_256 = vdupq_n_u16(256);

        uint16x8_t inv_x_0 = vsubq_u16(const_256, x_0);
        uint16x8_t x_0_post_inv = vbslq_u16(odd_0_w, inv_x_0, x_0);
        uint16x8_t add_0 = vshlq_n_u16(seg_0_w, 8);
        uint16x8_t h_0 = vaddq_u16(x_0_post_inv, add_0);

        uint16x8_t inv_x_1 = vsubq_u16(const_256, x_1);
        uint16x8_t x_1_post_inv = vbslq_u16(odd_1_w, inv_x_1, x_1);
        uint16x8_t add_1 = vshlq_n_u16(seg_1_w, 8);
        uint16x8_t h_1 = vaddq_u16(x_1_post_inv, add_1);


        uint8x8_t h_0_lo = vmovn_u16(h_0);
        uint8x8_t h_1_lo = vmovn_u16(h_1);
        uint8x8_t h_0_hi = vshrn_n_u16(h_0, 8);
        uint8x8_t h_1_hi = vshrn_n_u16(h_1, 8);

        uint8x16_t h_lo = vcombine_u8(h_0_lo, h_1_lo);
        uint8x16_t h_hi = vcombine_u8(h_1_lo, h_1_hi);


        // STORE
        uint8x16x4_t out;
        out.val[0] = h_lo;
        out.val[1] = h_hi;
        out.val[2] = s;
        out.val[3] = cmax;

        vst4q_u8(reinterpret_cast<uint8_t*>(dest), out);



    }




















































}