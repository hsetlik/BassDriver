#include "BassDriver/Audio/RollingAverage.h"

RollingAverage::RollingAverage(int length) : buf(length) {
  denom = (float)length;
}

float RollingAverage::process(float input) {
  // 1. add the new value to the sum
  sum += input;
  // 2. subtract the oldest value
  sum -= buf.getOldest();
  // 3. overwrite that value with the new one
  buf.push(input);
  // 4. return the mean
  return (sum / denom);
}
