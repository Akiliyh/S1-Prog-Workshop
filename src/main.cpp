#include <sil/sil.hpp>
#include <random.hpp>
#include <iostream>
#include <math.h>

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

void gradient()
{
    sil::Image image{300, 200};
    for (int x{0}; x < image.width(); ++x)
    {
        for (int y{0}; y < image.height(); ++y)
        {
            image.pixel(x, y) = glm::vec3{static_cast<float>(x) / static_cast<float>(image.width() - 1)};
        }
    }
    image.save("output/gradient.png");
}

void mirror(sil::Image& image)
{
    sil::Image newImage{image};
    for (int x{0}; x < image.width(); ++x)
    {
        for (int y{0}; y < image.height(); ++y)
        {
            image.pixel(x, y) = newImage.pixel(image.width()-x-1, y);
        }
    }
}

void rgbSplit(sil::Image& image)
{
    sil::Image newImage{image};
    int newXRed {};
    int newXGreen {};
    int newXBlue {};
    int gap {30};
    for (int x{0}; x < newImage.width(); ++x)
    {
        for (int y{0}; y < newImage.height(); ++y)
        {
            if (x+gap < newImage.width()) newXRed = x + gap;
            newXGreen = x;
            if (x-gap < newImage.width() && x-gap > 0) newXBlue = x - gap;
            newImage.pixel(newXRed, y).r = image.pixel(x,y).r;
            newImage.pixel(newXGreen, y).g = image.pixel(x,y).g;
            newImage.pixel(newXBlue, y).b = image.pixel(x,y).b;
        }
    }
    image = newImage; 
}

void to90Degrees(sil::Image& image)
{
    sil::Image newImage{image.height(), image.width()}; /* change dimensions */
    for (int x{0}; x < newImage.width(); ++x)
    {
        for (int y{0}; y < newImage.height(); ++y)
        {

            newImage.pixel(x, y) = image.pixel(y,newImage.width()-x-1);
        }
    }
    image = newImage;  
}

void addNoise(sil::Image& image)
{
    for (glm::vec3& color : image.pixels())
    {
        if (true_with_probability(0.3f)) color = glm::vec3{random_float(0.f,1.f), random_float(0.f,1.f), random_float(0.f,1.f)};
    }
}

void changeLuminosity(sil::Image& image, float lumino)
{
    for (glm::vec3& color : image.pixels())
    {
        color.r = pow(color.r, lumino); 
        color.b = pow(color.b, lumino);
        color.g = pow(color.g, lumino);
        /*color.g = pow(color.g, 1/2); 
        color.b = pow(color.b, 1/2); */
        /*color.r = color.r + exp (color.r);
        color.g = color.g + exp (color.g);
        color.b = color.b + exp (color.b);*/
    }
}

int main()
{
    /*{
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
    {
        sil::Image image{"images/logo.png"};
        mirror(image); 
        image.save("output/mirror.png"); 
    }
    {
        sil::Image image{"images/logo.png"};
        rgbSplit(image); 
        image.save("output/rgb_split.png"); 
    }
    {
        sil::Image image{"images/logo.png"};
        to90Degrees(image); 
        image.save("output/90degrees.png"); 
    }
    {
        gradient();  
    }*/

    {
        sil::Image image{"images/logo.png"};
        addNoise(image); 
        image.save("output/noise.png"); 
    }

    {
        sil::Image image{"images/photo.jpg"};
        changeLuminosity(image, 0.5); /* change value here to change luminosity */
        image.save("output/changed-luminosity.png"); 
    }
}