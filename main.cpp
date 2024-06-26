#include <iostream>
#include <cmath> // Dla stałej M_PI
#include <stdexcept>

// Abstrakcyjna klasa Figure
class Figure {
public:
    // Czysta wirtualna metoda area()
    virtual double area() const = 0;

    // Czysta wirtualna metoda show()
    virtual void show() const = 0;

    // Wirtualny destruktor
    virtual ~Figure() = default;
};

// Klasa Circle dziedzicząca po Figure
class Circle : public Figure {
private:
    double radius;

public:
    Circle(double r) : radius(r) {}

    // Implementacja metody area()
    double area() const override {
        return M_PI * radius * radius;
    }

    // Implementacja metody show()
    void show() const override {
        std::cout << "Circle with radius: " << radius << " and area: " << area() << std::endl;
    }
};

// Klasa Rectangle dziedzicząca po Figure
class Rectangle : public Figure {
private:
    double width, height;

public:
    Rectangle(double w, double h) : width(w), height(h) {}

    // Implementacja metody area()
    double area() const override {
        return width * height;
    }

    // Implementacja metody show()
    void show() const override {
        std::cout << "Rectangle with width: " << width << ", height: " << height << " and area: " << area()
                  << std::endl;
    }
};

// Klasa TriangleError dziedzicząca po Figure
class TriangleError : public std::runtime_error {
public:
    explicit TriangleError(const std::string& message)
            : std::runtime_error(message) {}
};

class Triangle : public Figure {
private:
    double side1, side2, side3;

    void validate_triangle(double s1, double s2, double s3) {
        if (!(s1 + s2 > s3 && s1 + s3 > s2 && s2 + s3 > s1)) {
            throw TriangleError("The sides do not form a valid triangle");
        }
    }

public:
    Triangle(double s1, double s2, double s3) {
        try {
            validate_triangle(s1, s2, s3);
            side1 = s1;
            side2 = s2;
            side3 = s3;
        } catch (const TriangleError& e) {
            std::cerr << e.what() << ". Created default triangle with sides 3, 4, 5." << std::endl;
            side1 = 3;
            side2 = 4;
            side3 = 5;
        }
    }

    double area() const override {
        double s = (side1 + side2 + side3) / 2;
        return sqrt(s * (s - side1) * (s - side2) * (s - side3));
    }

    void show() const override {
        std::cout << "Triangle with sides: " << side1 << ", " << side2 << ", " << side3 << " and area: " << area() << std::endl;
    }
};

int main() {
    // Tablica wskaźników na obiekty klasy Figure
    Figure* figures[6];

    // Tworzenie obiektów i przypisywanie wskaźników do tablicy
    figures[0] = new Circle(5.0);
    figures[1] = new Rectangle(4.0, 6.0);
    figures[2] = new Circle(3.0);
    figures[3] = new Rectangle(2.5, 5.5);
    figures[4] = new Triangle(1.0, 1.0, 10.0); // Zły trójkąt
    figures[5] = new Triangle(2.5, 5.5, 6.5);

    // Iteracja przez tablicę i wyświetlanie informacji o obiektach
    for (int i = 0; i < 6; ++i) {
        figures[i]->show();
    }

    // Zwolnienie pamięci
    for (int i = 0; i < 6; ++i) {
        delete figures[i];
    }

    return 0;
}
