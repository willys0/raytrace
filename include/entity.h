#ifndef __ENTITY_H_
#define __ENTITY_H_

#include <math3d.h>
#include <transform.h>
#include <ray.h>
#include <color.h>
#include <material.h>
#include <ray_hit.h>

namespace raytracer {

    class Entity {
        public:
            Transform transform;

            Entity(const Transform& transform, const Material& material = Material());

            virtual Color getDiffuse() const { return _material.diffuse; }
            virtual Color getSpecular() const { return _material.specular; }
            virtual float getShininess() const { return _material.shininess; }
            virtual float getReflectivity() const { return _material.reflectivity; }

            virtual bool rayIntersects(const Ray& ray) const = 0;
            virtual bool rayIntersects(const Ray& ray, RayHit& hit) const = 0;

            virtual vec3f normalAtPoint(const vec3f& point) const = 0;

        protected:
            Material _material;

            static const float _eps;
    };

    class Plane : public Entity {
        public:
            Plane(const Transform& transform, const Material& material = Material());

            bool rayIntersects(const Ray& ray) const override;
            bool rayIntersects(const Ray& ray, RayHit& hit) const override;
            vec3f normalAtPoint(const vec3f& point) const override;

        protected:
            vec3f getNormal() const;
    };

    class Sphere : public Entity {
        public:
            Sphere(const Transform& transform, const float& radius, const Material& material = Material());

            bool rayIntersects(const Ray& ray) const override;
            bool rayIntersects(const Ray& ray, RayHit& hit) const override;
            vec3f normalAtPoint(const vec3f& point) const override;

        protected:
            float _radius;
    };
};


#endif // __ENTITY_H_
