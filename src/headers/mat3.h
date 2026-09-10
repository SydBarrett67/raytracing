#pragma once

#include <cmath>
#include <string>

class mat3 {
public:

    float data[3][3];

    // Constructor
    mat3() = default;
    mat3(
        float a00, float a01, float a02,
        float a10, float a11, float a12,
        float a20, float a21, float a22
    ) {
        data[0][0] = a00;
        data[0][1] = a01;
        data[0][2] = a02;

        data[1][0] = a10;
        data[1][1] = a11;
        data[1][2] = a12;

        data[2][0] = a20;
        data[2][1] = a21;
        data[2][2] = a22;
    }

    std::string print() const { 
        std::string result = "";

        for (int i=0;i<3;i++) {
            for (int j=0;j<3;j++) {
                result += std::to_string(data[i][j]);
            }
        }
    }

    // Getter
    float get(int x, int y) const { return data[y][x]; }
    // Setter
    void set(int x, int y, float value) { data[y][x] = value; }
};
