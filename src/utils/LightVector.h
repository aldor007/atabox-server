#ifndef _H_LIGHT_VECTOR
#define _H_LIGHT_VECTOR 1 

#include <vector>
#include <utility>
#include <cstddef>
#include <cmath>

typedef std::vector<float> Vector;

namespace v {
    struct LightVector: public std::pair<float *, float *> {

        template <typename... Arg> LightVector(Arg&& ... arg): std::pair<float *, float *>(std::forward<Arg>(arg) ...) {}

        float *data() const { 
            return first; 
        }

        size_t size() const { 
            return std::distance(first, second); 
        }

        bool empty() const  { 
            return first == second; 
        }

        float& operator[](size_t i) {
            return *(first + i); 
        }

        float operator[](size_t i) const {
            return *(first + i); 
        }

    };

    template <class Vector1, class Vector2> inline float dot(const Vector1&x, const Vector2& y) { 
        int m = x.size();
        const float *xd = x.data(), *yd = y.data();
        float sum = 0.0;
        while (--m >= 0)
            sum += (*xd++) * (*yd++);
        return sum;
    }

    // saxpy: x = x + g * y; x = a * x + g * y
    inline void saxpy(Vector& x, float g, const Vector& y) {
        int m = x.size();
        float *xd = x.data();
        const float *yd = y.data();
        while (--m >= 0) 
            (*xd++) += g * (*yd++);
    }

    inline void saxpy(float a, Vector& x, float g, const Vector& y) {
        int m = x.size();
        float *xd = x.data();
        const float *yd = y.data();
        while (--m >= 0) {
            (*xd) = a * (*xd) + g * (*yd); ++xd; ++yd; 
        }
    }

    inline void saxpy2(Vector& x, float g, const Vector& y, float h, const Vector& z) {
        int m = x.size();
        float *xd = x.data();
        const float *yd = y.data();
        const float *zd = z.data();
        while (--m >= 0) {
            (*xd++) +=  (g * (*yd++)  + h * (*zd++)); 
        }
    }

    inline void scale(Vector& x, float g) {
        int m = x.size();
        float *xd = x.data();

        while (--m >= 0) 
            (*xd++) *= g;
    }


    inline void unit(Vector& x) {
        float len = std::sqrt(dot(x, x));
        if (len == 0) 
            return;

        int m = x.size();
        float *xd = x.data();
        while (--m >= 0) 
            (*xd++) /= len;
    }

    /**
     * @brief [brief description]
     * @details [long description]
     * 
     * @param x [description]
     * @return true or false
     */
    inline bool isfinite(const Vector& x) { 
        for(auto const& i: x) {
            if (!std::isfinite(i)) 
                return false; 
            }    
        return true;
    }

}

#endif