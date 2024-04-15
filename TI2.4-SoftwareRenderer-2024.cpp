#define NOMINMAX
#include <iostream>
#include <math.h>
#include "stb_image_write.h"
#include "Vec3.h"
#include "Vec2.h"
#include "Matrix4.h"
#include "ObjModel.h"
#ifdef _WIN32
#include <Windows.h>
#endif

#define M_PI       3.14159265358979323846   // pi


const int width = 512;
const int height = 512;

void setPixel(char* imgData, int x, int y, const Vec3 &color)
{
    if (x < 0 || y < 0 || x >= width || y >= height)
        return;
    imgData[3 * (x + width * (height-1-y)) + 0] = (unsigned char)(color.x * 255);
    imgData[3 * (x + width * (height-1-y)) + 1] = (unsigned char)(color.y * 255);
    imgData[3 * (x + width * (height-1-y)) + 2] = (unsigned char)(color.z * 255);
}


Vec3 baryCentric(const Vec2& A, const Vec2& B, const Vec2& C, const Vec2& P)
{
    Vec3 X(C.x - A.x, B.x - A.x, A.x - P.x);
    Vec3 Y(C.y - A.y, B.y - A.y, A.y - P.y);
    Vec3 U = X.cross(Y);
    return Vec3(1 - (U.x + U.y) / U.z, U.y / U.z, U.x / U.z);
}


void drawTriangle(char* imgData, float* zBuffer, 
    const Vec3& p1, const Vec3& p2, const Vec3& p3, 
    const Vec3& n1, const Vec3& n2, const Vec3& n3, const Vec3& color)
{
    float minx = std::min(std::min(p1.x, p2.x), p3.x);
    float maxx = std::max(std::max(p1.x, p2.x), p3.x);
    float miny = std::min(std::min(p1.y, p2.y), p3.y);
    float maxy = std::max(std::max(p1.y, p2.y), p3.y);

    minx = std::max(0.0f, minx);
    miny = std::max(0.0f, miny);
    maxx = std::min(width-1.0f, maxx);
    maxy = std::min(height-1.0f, maxy);

    for (int x = floor(minx); x < ceil(maxx); x++)
    {
        for(int y = floor(miny); y < ceil(maxy); y++)
        {
            auto barry = baryCentric(Vec2(p1), Vec2(p2), Vec2(p3), Vec2(x,y));
            if (barry.x < 0 || barry.y < 0 || barry.z < 0)
                continue;

            float z = barry.x * p1.z + barry.y * p2.z + barry.z * p3.z;
            if (zBuffer[x + width * y] > z)
                continue;
            zBuffer[x + width * y] = z;

            Vec3 normal = n1 * barry.x + n2 * barry.y + n3 * barry.z;
            normal = normal.normalized();
            Vec3 lightDirection(1, 1, 1);
            lightDirection = lightDirection.normalized();

            float intensity = std::max(0.0f, normal.dot(lightDirection));


            setPixel(imgData, x, y, color * (0.2f + 0.8f * intensity));
        }
    }

}

int main()
{
    char* imgData = new char[width * height * 3];
    float* zBuffer = new float[width * height];

    ObjModel model("monkey.obj");


    for (int frame = 0; frame < 36; frame++)
    {
        for (int x = 0; x < width; x++)
            for (int y = 0; y < height; y++)
                setPixel(imgData, x, y, Vec3(0.95f, 0.34f, 0));

        for (int i = 0; i < width * height; i++)
            zBuffer[i] = -1929848038;

        Matrix4 matrix = Matrix4::rotate((float)(10*frame * (M_PI / 180)), Vec3(0, 1, 0));


        for (auto i = 0; i < model.faces.size(); i++)
        {
            auto& face = model.faces[i];

            auto a = matrix * model.vertices[face.vertex[0] - 1];
            auto b = matrix * model.vertices[face.vertex[1] - 1];
            auto c = matrix * model.vertices[face.vertex[2] - 1];

            auto na = matrix * model.normals[face.normal[0] - 1];
            auto nb = matrix * model.normals[face.normal[1] - 1];
            auto nc = matrix * model.normals[face.normal[2] - 1];

            drawTriangle(imgData, zBuffer,
                a * Vec3(width / 2, height / 2, 1) + Vec3(width / 2, height / 2, 0),
                b * Vec3(width / 2, height / 2, 1) + Vec3(width / 2, height / 2, 0),
                c * Vec3(width / 2, height / 2, 1) + Vec3(width / 2, height / 2, 0),
                na, nb, nc,
                //    Vec3(rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, rand() / (float)RAND_MAX)
                Vec3(1, 1, 1)
            );


        }

        std::string filename = "out" + std::to_string(frame) + ".png";
        stbi_write_png(filename.c_str(), width, height, 3, imgData, 0);
    }
#ifdef _WIN32
    ShellExecuteA(nullptr, nullptr, "out.png", nullptr, nullptr, SW_SHOW);
#endif
}
