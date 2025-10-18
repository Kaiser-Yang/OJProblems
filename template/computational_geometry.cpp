#include <array>
#include <vector>

class computational_geometry {
public:
    template <typename T, typename R = T>
    static R polygon_area(const std::vector<std::array<T, 2>> &points) {
        R area = 0;
        for (int i = 0; i < points.size(); i++) {
            int j = (i + 1) % points.size();
            area += (R)points[i][0] * points[j][1];
            area -= (R)points[i][1] * points[j][0];
        }
        return std::abs(area) / 2;
    }
};
