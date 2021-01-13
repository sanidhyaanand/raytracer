#include<iostream>
#include "utility/vec3.h"
#include "utility/color.h"
#include "utility/ray.h"

float hit_sphere(const point3& center, float radius, const ray& r) {
	vec3 oc = r.origin() - center;
	auto a = dot(r.direction(), r.direction());
	auto b = 2.0f * dot(oc, r.direction());
	auto c = dot(oc, oc) - radius * radius;
	auto discriminant = b * b - 4.0f * a * c;
	if (discriminant < 0) return -1.0f;
	else return (-b - sqrt(discriminant)) / (2.0f * a);
}

color ray_color(const ray& ray) {
	auto centre = point3(0.0, 0.0, -1.0);
	auto t = hit_sphere(centre, 0.5, ray);

	if (t > 0.0f) {
		auto norm = normalize(ray.at(t) - vec3(centre));
		return 0.5 * color(norm.x() + 1, norm.y() + 1, norm.z() + 1);
	}

	vec3 unit_dir = normalize(ray.direction());
	auto q = 0.5 * (unit_dir.y() + 1.0);
	return (1.0 - q) * color(1.0, 1.0, 1.0) + q * color(1.0, 0.7, 0.3);
}

int main(){
	
	// Image
	const float aspect_ratio = 16.0 / 9.0;
	const int img_width = 400;
	const int img_height = static_cast<int>(img_width / aspect_ratio);

	// Camera
	float viewport_height = 2.0;
	float viewport_width = aspect_ratio * viewport_height;
	float focal_length = 1.0;

	auto origin = point3(0.0, 0.0, 0.0);
	auto horizontal = vec3(viewport_width, 0, 0);
	auto vertical = vec3(0, viewport_height, 0);
	auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0.0, 0.0, focal_length);

	// Render
	std::cout << "P3\n" << img_width << ' ' << img_height << "\n255\n";

	// Iterate through each pixel
	for (int j = img_height - 1; j >= 0; j--) {
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (int i = 0; i < img_width; i++) {

			// Pixel positions
			auto u = float(i) / (img_width - 1);
			auto v = float(j) / (img_height - 1);

			ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);

			color pixel_color = ray_color(r);
			write_color(std::cout, pixel_color);
		}
	}
	std::cerr << "\nDone.\n";
}