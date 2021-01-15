#include <iostream>
#include "utility/vec3.h"
#include "utility/color.h"
#include "utility/ray.h"
#include "utility/sphere.h"
#include "utility/hittable.h"

color ray_color(const ray& ray) {
	auto center = point3(0.0, 0.0, -1.0);

	hit_record rec;
	sphere sphere(center, 0.5);
	auto check = sphere.hit(ray, 0.001, double(INFINITY), rec);

	if (check == true) {
		auto norm = normalize(rec.normal);
		return 0.5 * color(norm.x() + 1, norm.y() + 1, norm.z() + 1);
	}

	vec3 unit_dir = normalize(ray.direction());
	auto q = 0.5 * (unit_dir.y() + 1.0);
	return (1.0 - q) * color(1.0, 1.0, 1.0) + q * color(0.3, 0.7, 1.0);
}

int main(){
	
	// Image
	const double aspect_ratio = 16.0 / 9.0;
	const int img_width = 400;
	const int img_height = static_cast<int>(img_width / aspect_ratio);

	// Camera
	double viewport_height = 2.0;
	double viewport_width = aspect_ratio * viewport_height;
	double focal_length = 1.0;

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
			auto u = double(i) / (img_width - 1);
			auto v = double(j) / (img_height - 1);

			// Initialise ray
			ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);

			// Store and write color values
			color pixel_color = ray_color(r);
			write_color(std::cout, pixel_color);
		}
	}
	std::cerr << "\nDone.\n";
}