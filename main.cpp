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
  float dt = 0.001f;
  float c = 0.05f;
  float courant_square = c * c * dt * dt / (dx * dx);

  vector<float> wave(sample_count, 0);
  vector<float> vave(sample_count, 0);
  vector<float> bave(sample_count, 0);

  // initial Gaußpulse
  for (size_t i = 1; i < sample_count - 1; ++i) {
    const auto scale = float(i) / (sample_count - 1);
    const auto x = x_min * (1.0f - scale) + x_max * scale;
    wave[i] = exp(-x * x * 400.0f);
    wave[i] = (wave[i] < 0.001) ? (0) : (wave[i]);
  }
  for (size_t i = 0; i < sample_count; ++i) {
    bave[i] = wave[i];
  }

  sf::RenderWindow window(sf::VideoMode(width, height), "Swing dein Ding");

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
      vave[i] += dt * (c * c / (dx * dx) *
                           (wave[i + 1] + wave[i - 1] - 2.0f * wave[i]) -
                       0.05f * vave[i] - 0.5f * wave[i]);
      wave[i] += dt * vave[i];
    }

    // float tmp = 2 * wave[i] - bave[i] +
    //             courant_square * (wave[i + 1] + wave[i - 1] - 2 * wave[i]);
    // bave[i] = wave[i];
    // wave[i] = tmp;
    // }
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
          (wave[i] - view_y_min) / (view_y_max - view_y_min) * height);
      window.draw(point);
    }
    window.display();
  }
}