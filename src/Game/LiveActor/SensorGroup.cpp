#include "LiveActor/SensorGroup.hpp"
#include "LiveActor/HitSensor.hpp"

SensorGroup::SensorGroup(int capacity, const char*) : mCapacity(capacity), mSensorCount(0), mSensors(nullptr) {
    mSensors = new HitSensor*[capacity];
    for (s32 i = 0; i < mCapacity; ++i) mSensors[i] = nullptr;
}

void SensorGroup::add(HitSensor* sensor) {
    mSensors[mSensorCount] = sensor;
    ++mSensorCount;
    sensor->mSensorGroup = this;
}

void SensorGroup::remove(HitSensor* sensor) {
    for (s32 i = 0; i < mSensorCount; ++i) {
        if (mSensors[i] == sensor) {
            const u32 last = mSensorCount - 1;
            mSensors[i] = mSensors[last];
            --mSensorCount;
            return;
        }
    }
}

void SensorGroup::clear() const {
    for (s32 i = 0; i < mSensorCount; ++i) mSensors[i]->mSensorCount = 0;
}
