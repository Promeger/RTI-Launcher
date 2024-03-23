#include <SFML/Graphics.hpp>

class GlobalFont
{
public:
    static GlobalFont* get();
    sf::Font* getFont();

protected:

    GlobalFont();

    static GlobalFont* s_instance;

    sf::Font* m_font;
};