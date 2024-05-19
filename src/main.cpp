#include <SFML/Graphics.hpp>
#include <Link.hpp>
#include <VerletObject.hpp>
#include <Solver.hpp>
#include <string>
#include <vector>
#include <iostream>

sf::Color rope = sf::Color(141, 81, 24);
sf::Color white = sf::Color(255, 255, 255);

int main () {
    float fps = 0.0f;
    uint32_t object_count = 0;
    std::string titleStr = "Verlet Physics Engine | Object count: " + std::to_string(object_count) + " | FPS: " + std::to_string(fps);
    sf::RenderWindow window(sf::VideoMode(1200, 800), titleStr);
    sf::Clock simClock;

    std::vector<std::shared_ptr<VerletObject>> verletObjects;
    // pendulum
    verletObjects.push_back(std::make_shared<VerletObject>(sf::Vector2f(500, 200), rope, true));
    verletObjects.push_back(std::make_shared<VerletObject>(sf::Vector2f(510, 200), rope));
    verletObjects.push_back(std::make_shared<VerletObject>(sf::Vector2f(520, 200), rope));
    verletObjects.push_back(std::make_shared<VerletObject>(sf::Vector2f(530, 200), rope));
    verletObjects.push_back(std::make_shared<VerletObject>(sf::Vector2f(540, 200), rope));
    verletObjects.push_back(std::make_shared<VerletObject>(sf::Vector2f(550, 200), rope));
    verletObjects.push_back(std::make_shared<VerletObject>(sf::Vector2f(560, 200), rope));
    verletObjects.push_back(std::make_shared<VerletObject>(sf::Vector2f(570, 200), rope));
    verletObjects.push_back(std::make_shared<VerletObject>(sf::Vector2f(580, 200), rope));
    verletObjects.push_back(std::make_shared<VerletObject>(sf::Vector2f(590, 200), rope));
    verletObjects.push_back(std::make_shared<VerletObject>(sf::Vector2f(600, 200), rope));
    verletObjects.push_back(std::make_shared<VerletObject>(sf::Vector2f(610, 200), rope));

    // net
    verletObjects.push_back(std::make_shared<VerletObject>(sf::Vector2f(800, 350), rope, true));
    verletObjects.push_back(std::make_shared<VerletObject>(sf::Vector2f(810, 360), rope));
    verletObjects.push_back(std::make_shared<VerletObject>(sf::Vector2f(820, 370), rope));
    verletObjects.push_back(std::make_shared<VerletObject>(sf::Vector2f(830, 380), rope));
    verletObjects.push_back(std::make_shared<VerletObject>(sf::Vector2f(840, 390), rope));
    verletObjects.push_back(std::make_shared<VerletObject>(sf::Vector2f(850, 400), rope));
    verletObjects.push_back(std::make_shared<VerletObject>(sf::Vector2f(860, 400), rope));
    verletObjects.push_back(std::make_shared<VerletObject>(sf::Vector2f(870, 400), rope));
    verletObjects.push_back(std::make_shared<VerletObject>(sf::Vector2f(880, 400), rope));
    verletObjects.push_back(std::make_shared<VerletObject>(sf::Vector2f(890, 400), rope));
    verletObjects.push_back(std::make_shared<VerletObject>(sf::Vector2f(910, 400), rope));
    verletObjects.push_back(std::make_shared<VerletObject>(sf::Vector2f(920, 400), rope));
    verletObjects.push_back(std::make_shared<VerletObject>(sf::Vector2f(930, 400), rope));
    verletObjects.push_back(std::make_shared<VerletObject>(sf::Vector2f(940, 400), rope));
    verletObjects.push_back(std::make_shared<VerletObject>(sf::Vector2f(950, 400), rope));
    verletObjects.push_back(std::make_shared<VerletObject>(sf::Vector2f(960, 390), rope));
    verletObjects.push_back(std::make_shared<VerletObject>(sf::Vector2f(970, 380), rope));
    verletObjects.push_back(std::make_shared<VerletObject>(sf::Vector2f(980, 370), rope));
    verletObjects.push_back(std::make_shared<VerletObject>(sf::Vector2f(990, 360), rope));
    verletObjects.push_back(std::make_shared<VerletObject>(sf::Vector2f(1000, 350), rope, true));

    Solver solver(verletObjects);

    // pendulum 0-11
    solver.addLink(verletObjects[0], verletObjects[1], 20.0f);
    solver.addLink(verletObjects[1], verletObjects[2], 20.0f);
    solver.addLink(verletObjects[2], verletObjects[3], 20.0f);
    solver.addLink(verletObjects[3], verletObjects[4], 20.0f);
    solver.addLink(verletObjects[4], verletObjects[5], 20.0f);
    solver.addLink(verletObjects[5], verletObjects[6], 20.0f);
    solver.addLink(verletObjects[6], verletObjects[7], 20.0f);
    solver.addLink(verletObjects[7], verletObjects[8], 20.0f);
    solver.addLink(verletObjects[8], verletObjects[9], 20.0f);
    solver.addLink(verletObjects[9], verletObjects[10], 20.0f);
    solver.addLink(verletObjects[10], verletObjects[11], 20.0f);

    // net 12-31
    solver.addLink(verletObjects[12], verletObjects[13], 20.0f);
    solver.addLink(verletObjects[13], verletObjects[14], 20.0f);
    solver.addLink(verletObjects[14], verletObjects[15], 20.0f);
    solver.addLink(verletObjects[15], verletObjects[16], 20.0f);
    solver.addLink(verletObjects[16], verletObjects[17], 20.0f);
    solver.addLink(verletObjects[17], verletObjects[18], 20.0f);
    solver.addLink(verletObjects[18], verletObjects[19], 20.0f);
    solver.addLink(verletObjects[19], verletObjects[20], 20.0f);
    solver.addLink(verletObjects[20], verletObjects[21], 20.0f);
    solver.addLink(verletObjects[21], verletObjects[22], 20.0f);
    solver.addLink(verletObjects[22], verletObjects[23], 20.0f);
    solver.addLink(verletObjects[23], verletObjects[24], 20.0f);
    solver.addLink(verletObjects[24], verletObjects[25], 20.0f);
    solver.addLink(verletObjects[25], verletObjects[26], 20.0f);
    solver.addLink(verletObjects[26], verletObjects[27], 20.0f);
    solver.addLink(verletObjects[27], verletObjects[28], 20.0f);
    solver.addLink(verletObjects[28], verletObjects[29], 20.0f);
    solver.addLink(verletObjects[29], verletObjects[30], 20.0f);
    solver.addLink(verletObjects[30], verletObjects[31], 20.0f);

    while (window.isOpen()) {
        std::string titleStr = "Verlet Physics Engine | Object count: " + std::to_string(object_count) + " | FPS: " + std::to_string(fps);
        window.setTitle(titleStr);
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseMoved) {
                //std::cout << "x: " << event.mouseMove.x << " y: " << event.mouseMove.y << std::endl;
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                auto newVerlet = std::make_shared<VerletObject>(sf::Vector2f(event.mouseButton.x, event.mouseButton.y), white);
                solver.addVerletObject(newVerlet);
            }
        }
        float dt = simClock.restart().asSeconds();
        fps = 1.0f / dt;
        object_count = solver.objects.size();
        solver.update(dt);
        window.clear();

        // render particles
        for (const auto& verlObj : solver.objects) {
            sf::CircleShape shape(10);
            shape.setPosition(verlObj->getPosition());
            shape.setFillColor(verlObj->color);
            window.draw(shape);
        }
        window.display();
    }
    return 0;
}