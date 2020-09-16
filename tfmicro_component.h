#include "esphome.h"
#include <EloquentTinyML.h>
#include "model.h"

#define NUMBER_OF_INPUTS 1
#define NUMBER_OF_OUTPUTS 1
#define TENSOR_ARENA_SIZE 2*1024

class TFMicroComponent : public Component {
 public:
  Eloquent::TinyML::TfLite<NUMBER_OF_INPUTS, NUMBER_OF_OUTPUTS, TENSOR_ARENA_SIZE> ml;

  void setup() override {
      Serial.begin(115200);
      this->ml.begin(sine_model);
  }

  void loop() override {
      float x = 3.14 * random(100) / 100;
      float y = sin(x);
      float input[1] = { x };
      float predicted = this->ml.predict(input);

      Serial.print("sin(");
      Serial.print(x);
      Serial.print(") = ");
      Serial.print(y);
      Serial.print("\t predicted: ");
      Serial.println(predicted);
      delay(1000);
  }
};
