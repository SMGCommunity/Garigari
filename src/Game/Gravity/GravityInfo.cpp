#include "Game/Gravity/GravityInfo.hpp"

GravityInfo::GravityInfo() : mGravityVector(0.0f, 0.0f, 0.0f), mLargestPriority(-1), mGravityInstance() {
}

void GravityInfo::init() {
    mGravityVector.zero();
    mLargestPriority = -1;
    mGravityInstance = nullptr;
}
