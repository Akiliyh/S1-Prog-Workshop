#include <sil/sil.hpp>
#include <iostream>

void keep_green_only(sil::Image& image) 
{
    for (glm::vec3& color : image.pixels())
    {
        color.r = 0.f;
        color.b = 0.f;
    }
}

void swap(sil::Image& image) 
{
    for (glm::vec3& color : image.pixels())
    {
        std::swap(color.b,color.r);
    }
}

void grayscale(sil::Image& image) 
{
    for (glm::vec3& color : image.pixels())
    {
        float luminance {};
        luminance += 0.2126f * color.r;
        luminance += 0.7152f * color.g;
        luminance += 0.0722f * color.b;
        color.b = luminance;
        color.r = luminance;
        color.g = luminance;
    }
}

void negative(sil::Image& image)
{
    for (glm::vec3& color : image.pixels())
    {
        color.r = 1.f-color.r;
        color.b = 1.f-color.b;
        color.g = 1.f-color.g;
    }
}

int main()
{
    {
        sil::Image image{"images/logo.png"};
        keep_green_only(image); 
        image.save("output/keep_green_only.png"); 
    }
    {
        sil::Image image{"images/logo.png"};
        swap(image); 
        image.save("output/swap.png"); 
    }
    {
        sil::Image image{"images/logo.png"};
        grayscale(image); 
        image.save("output/grayscale.png"); 
    }
    {
        sil::Image image{"images/logo.png"};
        negative(image); 
        image.save("output/negative.png"); 
    }
}