"""
-----------------------------
The purpose of this script is to format rgb hex strings into usable c++ const code

This website has mathmatically derived color stops for a few cmaps: https://hauselin.github.io/colorpalettejs/

The script adapts this output
-----------------------------
"""


def rgb_to_hsv(rgb_px):

    r, g, b = rgb_px
    
    cmax = max(r, g, b)
    cmin = min(r, g, b)
    delta = cmax - cmin
    
    if cmax == 0:
        return [0, 0, 0]
    if delta == 0:
        return [0, 0, cmax]
    
    v = cmax
    s = (delta / cmax) * 256
    
    if (cmax == r) :
        h = (g - b)/delta * 256
        if (h < 0): 
            h += 1536
    elif (cmax == g) :
        h = (b - r)/delta * 256 + 512
    elif (cmax == b):
        h = (r - g)/delta * 256 + 1024
     
    return [int(h), int(s), int(v)]
    


def read_hex_strings(in_file_path, out_file_path):
    with open(in_file_path, 'r') as in_file, open(out_file_path, 'w') as out_file: 
        lines = str(in_file.read())
        print("lines: ", lines)
        print()

        strings_list = lines.split("\"")
        hex_strings_list = [x for x in strings_list if "#" in x]
        print("hex_strings_list: ", hex_strings_list)
        print()
        
        filtered_hex_strings_list = [x.replace("#", "") for x in hex_strings_list]
        pixel_string_sublist = [[x[0:2], x[2:4], x[4:6]] for x in filtered_hex_strings_list]
        print("pixel_string_sublist: ", pixel_string_sublist)
        print()
        
        pixel_int_sublist = [[int(x, 16) for x in pixel] for pixel in pixel_string_sublist]
        print("pixel_int_sublist: ", pixel_int_sublist)
        print()
        
        hsv_int_sublist = [rgb_to_hsv(x) for x in pixel_int_sublist]
        print("hsv_int_sublist: ", hsv_int_sublist)
        print()
        
        hsv_string_sublist = [f"HSV({h}, {s}, {v})" for h, s, v in hsv_int_sublist]
        print("hsv_string_sublist", hsv_string_sublist)
        print()
        
        num_colors = len(hsv_int_sublist)
        stops = [str(round((x) / (num_colors-1), 3)) + 'f' for x in range(num_colors)]
        print("stops :", stops)
        print()
        
        hsv_stop_zip = zip(hsv_string_sublist, stops)
        formatted_values_list = [f"\t\tColor_Stop({hsv}, {stop}),\n" for hsv, stop in hsv_stop_zip]
        print("formatted_values_list: ", formatted_values_list)
        print()
        
        print("writing to: ", out_file_path)
        for line in formatted_values_list: 
            out_file.write(line)
        print()
        



def main():
    print("hello world")
    print()
    
    print("Testing rgb->hsv conversion")
    rgb_px = [255, 255, 100]
    hsv_px = rgb_to_hsv(rgb_px)
    print(hsv_px)
    
    
    hex_strings_path = "data/viridis_10_hex_strings.txt"
    out_file_path = "data/viridis_output.txt"
    read_hex_strings(hex_strings_path, out_file_path)
    
if __name__ == "__main__":
    main()