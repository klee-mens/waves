#include <SFML/Graphics.hpp>
#include <chrono>
#include <cmath>
#include <vector>

using namespace std;

int main() {
  int width = 600;
  int height = 600;

  float x_min = -1.0f;
  float x_max = 1.0f;

  size_t sample_count = 200;
  float dx = (x_max - x_min) / (sample_count - 1);
  float dt = 0.005f;
  float alpha = 0.0005f;

  vector<float> heat(sample_count, 0);
  heat[0] = 0.0f;

  // for (size_t i = 1; i < sample_count - 1; ++i) {
  //   const auto scale = float(i) / (sample_count - 1);
  //   const auto x = x_min * (1.0f - scale) + x_max * scale;
  //   heat[i] = exp(-x * x * 50.0f);
  // }

  sf::RenderWindow window(sf::VideoMode(width, height), "Haißes Tail");

  float view_x_min = 1.1f * x_min;
  float view_x_max = 1.1f * x_max;
  float view_y_min = 1.1f * x_min;
  float view_y_max = 1.1f * x_max;

  auto old_time = chrono::high_resolution_clock::now();
  while (window.isOpen()) {
    auto time = chrono::high_resolution_clock::now();
    auto delta = chrono::duration<float>(time - old_time).count();
    // if (delta >= dt) {
    //   old_time = time;
    for (size_t i = 1; i < sample_count - 1; ++i) {
      heat[i] += dt * (alpha / (dx * dx) *
                           (heat[i + 1] + heat[i - 1] - 2.0f * heat[i]) +
                       ((i == sample_count / 2) ? (0.1f) : (0.0f)));
    }
    heat[0] = heat[1];
    // heat[sample_count - 1] = heat[sample_count - 2];
    // }
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }

    window.clear();
    for (size_t i = 0; i < sample_count; ++i) {
      sf::CircleShape point(2);
      const auto scale = float(i) / (sample_count - 1);
      const auto x = x_min * (1.0f - scale) + x_max * scale;
      point.setPosition(
          (x - view_x_min) / (view_x_max - view_x_min) * width,
          (heat[i] - view_y_min) / (view_y_max - view_y_min) * height);
      window.draw(point);
    }
    window.display();
  }
}