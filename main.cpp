#include <nlohmann/json.hpp>
#include "Nodes/Node/Node.h"
#include "Managers/FactoryManager/FactoryManager.h"
#include "Managers/DrawManager/DrawManager.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Test window");
    // sf::CircleShape shape(100.f);
    // shape.setFillColor(sf::Color::Green);
    std::vector<std::string> vec = {"/Users/mariolalov/repos/graphicsLib/Testfiles/test.json"};

    RssManager rssMgr;
    rssMgr.Load(vec);

    FactoryManager factoryMgr(rssMgr);
    auto root = factoryMgr.CreateNode("ROOT");

    auto sprite1 = factoryMgr.CreateSprite("Sprite1", "Sprite1_rss");
    auto sprite2 = factoryMgr.CreateSprite("Sprite2", "Sprite2_rss");
    auto sprite3 = factoryMgr.CreateSprite("Sprite3", "Sprite3_rss");

    sprite1->set_parent(root);
    sprite2->set_parent(root);
    sprite3->set_parent(sprite2);

    root->set_rotation(30);
    sprite2->set_rotation(60);
    sprite3->set_rotation(34);

    // sprite2->set_position({300, 400});

    DrawManager drawMgr;

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
        drawMgr.Draw(root, window);
        window.display();
    }

    return 0;
}