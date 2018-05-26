#ifndef TOUCH_SENSOR_H_
#define TOUCH_SENSOR_H_

namespace Worms {
class TouchListener {
    public:
        virtual void touched();
};

class TouchSensor {
   public:
    TouchSensor();
    ~TouchSensor();
};
}  // namespace Worms

#endif
