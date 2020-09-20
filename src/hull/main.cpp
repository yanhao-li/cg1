////////////////////////////////////////////////////////////////////////////////
#include <algorithm>
#include <complex>
#include <fstream>
#include <iostream>
#include <numeric>
#include <vector>
#include <limits.h>
#include <math.h>
////////////////////////////////////////////////////////////////////////////////

#define PI 3.14159265
typedef std::complex<double> Point;
typedef std::vector<Point> Polygon;

double inline det(const Point &u, const Point &v) {
	// TODO
	return 0;
} 

// p0 = (115.976, 432.047)
// p = (250.358, 432.033)
// xy = (134.382, 0.014)
// y / x = 0.000104

// get point's polar angle with P0
double inline getAngle(const Point p0, const Point p) {
	double y = abs(p.imag() - p0.imag());
	double x = abs(p.real() - p0.real());
	double angle = p0 == p ? 0 : atan(y / x);
	angle = angle < 0 ? angle + PI : angle;

	return angle;
}

struct Compare {
	Point p0; // Leftmost point of the poly
	bool operator ()(const Point p1, const Point p2) {
		double angle1 = getAngle(p0, p1);
		double angle2 = getAngle(p0, p2);
		return angle1 < angle2;
	}
};

bool inline salientAngle(Point &a, Point &b, Point &c) {
	// TODO
	return false;
}

////////////////////////////////////////////////////////////////////////////////

Polygon convex_hull(std::vector<Point> &points) {
	Compare order;
	Point p0 = points[0];
	for (Point point : points) {
		if (point.real() < p0.real()) {
			p0 = point;
		} else if (point.real() == p0.real() && point.imag() < p0.imag()) {
			p0 = point;
		}
	}

	order.p0 = p0;
	std::sort(points.begin(), points.end(), order);
	for (Point point : points) {
		std::cout << getAngle(p0, point) << " ";
	}

	std::cout << std::endl;
	Polygon hull;
	// TODO
	// use salientAngle(a, b, c) here
	return hull;
}

////////////////////////////////////////////////////////////////////////////////

std::vector<Point> load_xyz(const std::string &filename) {
	std::vector<Point> points;
	std::ifstream in(filename);

	std::string line;

	std::getline(in, line);
	int total_points = stoi(line);

	double x, y;
	while (std::getline(in, line))
	{
		in >> x >> y;
		points.push_back(Point(x, y));
	}

	return points;
}

void save_obj(const std::string &filename, Polygon &poly) {
	std::ofstream out(filename);
	if (!out.is_open()) {
		throw std::runtime_error("failed to open file " + filename);
	}
	out << std::fixed;
	for (const auto &v : poly) {
		out << "v " << v.real() << ' ' << v.imag() << " 0\n";
	}
	for (size_t i = 0; i < poly.size(); ++i) {
		out << "l " << i+1 << ' ' << 1+(i+1)%poly.size() << "\n";
	}
	out << std::endl;
}

////////////////////////////////////////////////////////////////////////////////

int main(int argc, char * argv[]) {
	if (argc <= 2) {
		std::cerr << "Usage: " << argv[0] << " points.xyz output.obj" << std::endl;
	}

	std::string input_file = argv[1];
	std::string output_file = argv[2];

	std::vector<Point> points = load_xyz(input_file);

	Polygon hull = convex_hull(points);
	save_obj(output_file, hull);
	return 0;
}
