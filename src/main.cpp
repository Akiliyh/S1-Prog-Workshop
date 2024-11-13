#include <sil/sil.hpp>

void keep_green_only(sil::Image& image) // Prend l'image par référence pour pouvoir la modifier
{
    for (glm::vec3& color : image.pixels())
    {
        color.r = 0.f;
        color.b = 0.f;
    }
}

int main()
{
    {
        sil::Image image{"images/logo.png"};
        keep_green_only(image); 
        image.save("output/keep_green_only.png"); 
    }
}