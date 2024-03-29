#include <entity.h>

#include <math3d.h>
#include <cmath>

namespace raytracer {
    Sphere::Sphere(const Transform& transform, const float& radius, const Material& material) :
        Entity(transform, material), _radius(radius) {
    }

    bool Sphere::rayIntersects(const Ray& ray) const {
        vec3f to = ray.origin - transform.getPosition();

        float a = vec3f::dot(ray.direction, ray.direction);
        float b = 2.0 * vec3f::dot(to, ray.direction);
        float c = vec3f::dot(to, to) - _radius*_radius;

        float discriminant = b*b - 4*a*c;

        if(discriminant > EPSILON) {
            float sqrtDiscriminant = std::sqrt(discriminant);
            float numerator = -b - sqrtDiscriminant;

            if(numerator > EPSILON) {
                return true;
            }

            numerator = -b + sqrtDiscriminant;

            if(numerator > EPSILON) {
                return true;
            }
        }

        return false;
    }

    bool Sphere::rayIntersects(const Ray& ray, RayHit& hit) const {
        vec3f to = ray.origin - transform.getPosition();

        float a = vec3f::dot(ray.direction, ray.direction);
        float b = 2.0 * vec3f::dot(to, ray.direction);
        float c = vec3f::dot(to, to) - _radius*_radius;

        float discriminant = b*b - 4*a*c;

        if(discriminant > EPSILON) {
            float sqrtDiscriminant = std::sqrt(discriminant);
            float numerator = -b - sqrtDiscriminant;

            if(numerator > EPSILON) {
                hit.t = numerator / 2.0 * a;
                hit.entity = this;
                return true;
            }

            numerator = -b + sqrtDiscriminant;

            if(numerator > EPSILON) {
                hit.t = numerator / 2.0 * a;
                hit.entity = this;
                return true;
            }
        }
        return false;
    }

    vec3f Sphere::normalAtPoint(const vec3f& point) const {
        return (point - transform.getPosition()) / _radius;
    }
};
