#pragma once

#include <vector>
#include <SFML/Graphics/Sprite.hpp>

class Animation
{
public:
    Animation(sf::Sprite& sprite, sf::IntRect frame_rect, unsigned frames, unsigned frames_duration);
    Animation(sf::Sprite& sprite, sf::IntRect frame_rect, unsigned frames, std::vector<unsigned> frame_durations);
    ~Animation();

    void Play(float dt);
    void ResetAnimation();

private:
    sf::Sprite& sprite;
    sf::IntRect frameRect;
    unsigned* frameDurations; // array
    unsigned frames;
    unsigned frame;
    float timer;
};
