#pragma once

#include "Animation.h"
#include <string>
#include <map>

class AnimationComponent
{
public:
    AnimationComponent(sf::Sprite& sprite, sf::Vector2i frame_size);
    ~AnimationComponent();

    void AddAnimation(std::string animation_name, unsigned frames_y, unsigned frames, unsigned frame_duration);
    void AddAnimation(std::string animation_name, unsigned frames_y, unsigned frames, std::vector<unsigned> frame_duration);
    void Play(std::string animation_name, float dt);
    void Pause();
    void Unpause();
    bool IsPaused();
    
private:
    sf::Sprite& sprite;
    sf::Vector2i frameSize;
    std::map<std::string, Animation*> animations;
    std::string lastAnimation;
    bool isPaused;
};
