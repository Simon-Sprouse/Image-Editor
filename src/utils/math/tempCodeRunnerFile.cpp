int num_cols = ax.x_table.size();
        int num_rows = ax.y_table.size();

        vector<int> col_intervals;
        col_intervals.reserve(num_cols - 1); // eg 10 seperation indexes means 9 interval spaces between
        for (int i = 0; i < num_cols; i++) { 
            int current_col = ax.x_table[i];
            int next_col = ax.x_table[i+1];

            int dx = next_col - current_col;
            col_intervals.push_back(dx);
        }

        // todo handle both interval and index calculation together (likely both elsewhere)
        vector<int> row_intervals;
        row_intervals.reserve(num_rows - 1);
        for (int i = 0; i < num_rows; i++) {
            int current_row = ax.y_table[i];
            int next_row = ax.y_table[i+1];

            int dy = next_row - current_row;
            row_intervals.push_back(dy);
        }


        vector<Rect> rect_coords;
        for (int i = 0; i < num_cols - 1; i++) { 
            for (int j = 0; j < num_rows - 1; j++) { 
                Rect coord = Rect{Point(ax.x_table[i], ax.y_table[j]), col_intervals[i], row_intervals[j]};
                rect_coords.push_back(coord);
            }
        }


        return rect_coords;
