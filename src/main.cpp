#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <Link.hpp>
#include <VerletObject.hpp>
#include <Solver.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <thread>
#include <corecrt_math_defines.h>

sf::Color rope = sf::Color(141, 81, 24);
sf::Color white = sf::Color(255, 255, 255);
std::vector<VerletObject> verletObjects;

struct ObjectOptions {
    bool isStatic;
    float mass;
    float radius;
    float colour[3];
};

int main () {
    float fps = 0.0f;
    uint32_t object_count = 0;
    ObjectOptions obj_opt;
    obj_opt.isStatic = false;
    obj_opt.mass = 5.0f;
    obj_opt.radius = 5.0f;
    std::string titleStr = "Verlet Physics Engine | Object count: " + std::to_string(object_count) + " | FPS: " + std::to_string(fps);
    sf::RenderWindow window(sf::VideoMode(1200, 800), titleStr);
    ImGui::SFML::Init(window);
    sf::Clock simClock;

    Solver solver(verletObjects);

    while (window.isOpen()) {
        std::string titleStr = "Verlet Physics Engine | Object count: " + std::to_string(object_count) + " | FPS: " + std::to_string(fps);
        window.setTitle(titleStr);
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.y < 600) {
                    sf::Color color;
                    color.r = (uint8_t) obj_opt.colour[0] * 255;
                    color.g = (uint8_t) obj_opt.colour[1] * 255;
                    color.b = (uint8_t) obj_opt.colour[2] * 255;
                    auto newVerlet = VerletObject(sf::Vector2f(event.mouseButton.x, event.mouseButton.y), color, obj_opt.isStatic, obj_opt.mass, obj_opt.radius);
                    solver.addVerletObject(newVerlet);
                }
            }
        }
        float dt = simClock.restart().asSeconds();
        fps = 1.0f / dt;
        object_count = solver.getObjectCount();
        solver.update(dt);
        window.clear();
        ImGui::SFML::Update(window, sf::seconds(dt));
        if (ImGui::CollapsingHeader("Object options")) {
            ImGuiIO& io = ImGui::GetIO();
            ImGui::Checkbox("Static object", &obj_opt.isStatic);
            if (ImGui::SliderFloat("Object mass", &obj_opt.mass, 0.0f, 20.0f, "%.0f"));
            if (ImGui::SliderFloat("Object radius", &obj_opt.radius, 0.0f, 20.0f, "%.0f"));
            ImGui::SeparatorText("Color picker");
            ImGui::ColorPicker3("MyColor##4", (float*)&obj_opt.colour, NULL);
        };
        // TODO: fix collision behaviour of objects with variable radii
        // render particles
        for (const auto& verlObj : solver.objects) {
            sf::RectangleShape shape (sf::Vector2f(verlObj.getRadius() * 2, verlObj.getRadius() * 2));
            shape.setOrigin(verlObj.getRadius(), verlObj.getRadius());
            shape.setPosition(verlObj.getPosition());
            shape.setRotation(verlObj.getAngularPosition() * 180.0f / M_PI);
            shape.setFillColor(verlObj.getColor());
            window.draw(shape);
        }
        ImGui::SFML::Render(window);
        window.display();
    }
    ImGui::SFML::Shutdown();
    return 0;
}