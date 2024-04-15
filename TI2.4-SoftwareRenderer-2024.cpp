#include <iostream>
#include "stb_image_write.h"
#include "Vec3.h"
#include "Vec2.h"

const int width = 512;
const int height = 512;

void setPixel(char* imgData, int x, int y, const Vec3 &color)
{
    if (x < 0 || y < 0 || x >= width || y >= height)
        return;
    imgData[3 * (x + width * y) + 0] = (unsigned char)(color.x * 255);
    imgData[3 * (x + width * y) + 1] = (unsigned char)(color.y * 255);
    imgData[3 * (x + width * y) + 2] = (unsigned char)(color.z * 255);
}

void drawTriangle(const Vec2& p1, const Vec2& p2, const Vec2& p3, const Vec3& color)
{
    //code om een driehoek te tekenen
}

int main()
{
    char* imgData = new char[512 * 512 * 3];
    for (int x = 0; x < width; x++)
        for (int y = 0; y < height; y++)
            setPixel(imgData, x, y, Vec3(0.95f, 0.34f, 0));


    drawTriangle(Vec2(10, 10), Vec2(400, 30), Vec2(200, 300), Vec3(1,1,1));


    stbi_write_png("out.png", width, height, 3, imgData, 0);
}
