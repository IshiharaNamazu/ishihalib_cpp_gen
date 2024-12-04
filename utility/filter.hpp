#pragma once

#include <algorithm>
#include <cmath>
#include <vector>
namespace ishihalib {
class LowPassFilter {
  float K;
  float prev;

public:
  LowPassFilter(float Gain) : K(Gain), prev(0.) {}
  LowPassFilter(float time_constant, float filter_interval) : K(0), prev(0.) {
    set_time_constant(time_constant, filter_interval);
  }

  float calc(float data) { // O(1)
    return prev = data * K + (1 - K) * prev;
  }

  void set_Gain(float gain) { K = gain; }
  void set_time_constant(float time_constant, float filter_interval) {
    if ((time_constant <= 0) || (filter_interval <= 0)) // フィルタなし
      K = 1;
    else
      K = 1 - exp(-filter_interval / time_constant);
  }
};

class AverageFilter {
  const int n_sample;
  std::vector<double> data;
  double sum;
  int cnt;

public:
  AverageFilter(const int num_of_sampling = -1)
      : n_sample(num_of_sampling), data(0, 0), sum(0), cnt(0) { // 平均値フィルタ n<=0でデータ数無限
    if (n_sample > 0)
      data.resize(n_sample, 0);
  }

  double calc(double new_data) {
    if (n_sample > 0) { // 移動平均 O(1)
      sum -= data[cnt];
      sum += new_data;

      data[cnt] = new_data;
      cnt++;
      cnt %= n_sample;

      return (sum / n_sample);
    } else {                     // 平均
      if (cnt < __INT32_MAX__) { // オーバーフローさせない
        cnt++;
        sum += new_data;
      }
      return sum / cnt;
    }
  }

  double get() {
    if (n_sample > 0) {
      return sum / n_sample;
    } else {
      if (cnt == 0)
        return 0;
      else
        return (sum / cnt);
    }
  }

  void reset() {
    sum = 0;
    cnt = 0;
    if (n_sample > 0) {
      data.resize(n_sample, 0);
    }
  }
};

class MedianFilter {
  int n_sample;
  std::vector<float> data;
  int cnt = 0;

public:
  MedianFilter(int num_of_sampling) : n_sample(num_of_sampling), data(num_of_sampling, 0.0) {}

  float calc(float new_data) { // O(NlogN)
    data[cnt] = new_data;

    cnt++;
    cnt %= n_sample;

    std::vector<float> sorted_data(n_sample);
    for (int i = 0; i < n_sample; i++)
      sorted_data[i] = data[i];                        // copy
    std::sort(sorted_data.begin(), sorted_data.end()); // sort
    return sorted_data[(n_sample + 1) / 2];            // median
  }
};
} // namespace ishihalib