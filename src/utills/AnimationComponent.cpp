#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Vector2i frame_size)
    : sprite(sprite), frameSize(frame_size), isPaused(false)
{
}

AnimationComponent::~AnimationComponent()
{
    for (auto& p : animations)
        delete p.second;
}

void AnimationComponent::AddAnimation(std::string animation_name, unsigned frames_y, unsigned frames, unsigned frame_duration)
{
    delete animations[animation_name];
    animations[animation_name] = new Animation(sprite, {{0, frames_y * frameSize.y}, frameSize}, frames, frame_duration);
}

void AnimationComponent::AddAnimation(std::string animation_name, unsigned frames_y, unsigned frames, std::vector<unsigned> frame_durations)
{
    delete animations[animation_name];
    animations[animation_name] = new Animation(sprite, {{0, frames_y * frameSize.y}, frameSize}, frames, frame_durations);
}

void AnimationComponent::Play(std::string animation_name, float dt)
{
    if (lastAnimation != animation_name)
    {
        if (lastAnimation != "")
            animations[lastAnimation]->ResetAnimation();
        animations[animation_name]->ResetAnimation();
        lastAnimation = animation_name;
    }

    if (!isPaused)
        animations[animation_name]->Play(dt);
}

void AnimationComponent::Pause()
{
    isPaused = true;
}

void AnimationComponent::Unpause()
{
    isPaused = false;
}

bool AnimationComponent::IsPaused()
{
    return isPaused;
}
