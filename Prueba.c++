#include <iostream>
#include <map>
#include <vector>
#include <string>

int main()
{
    // Definimos un map donde la clave es una string (la categoría de la unidad de medida)
    // y el valor es un vector de strings (las unidades de medida)
    std::map<std::string, std::vector<std::string>> units;
    units["Longitud"] = {"m", "km", "cm", "mm", "µm", "nm", "mi", "yd", "ft", "in"};
    units["Masa"] = {"kg", "g", "mg", "µg", "t", "lb", "oz"};
    units["Volumen"] = {"m3", "L", "mL", "gal", "qt", "pt", "floz"};
    units["Tiempo"] = {"s", "min", "h", " d", "wk", "mo", "yr"};
    units["Temperatura"] = {"gC", "gF", "K"};
    units["Area"] = {"m2", "km2", "ha", "ac", "mi2", "yd2", "ft2", "in2"};
    units["Velocidad"] = {"ms", "kmh", "mph", "kt"};

    // Creamos un nuevo map donde la clave es una string (la unidad de medida)
    // y el valor es una string (la categoría de la unidad de medida)
    std::map<std::string, std::string> categories;
    for (const auto &category : units)
    {
        for (const auto &unit : category.second)
        {
            categories[unit] = category.first;
        }
    }

    // Ahora puedes buscar en el map por la unidad de medida
    std::string unidad = "m2";
    if (categories.count(unidad) > 0)
    {
        std::cout << "La categoría de la unidad \"" << unidad << "\" es: " << categories[unidad] << std::endl;
    }
    else
    {
        std::cout << "Unidad no encontrada." << std::endl;
    }

    return 0;
}