#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-slicing"
#pragma ide diagnostic ignored "modernize-use-nodiscard"

#include <iostream>
#include <utility>
#include <vector>
#include <windows.h>

void set_color(int text_color) {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); // Console descriptor
    SetConsoleTextAttribute(hStdOut, (WORD) (text_color));
}

enum NetworkTechnology {
    UMTS, EDGE, GPRS, HSPA, LTE, NSA5G, SA5G
};


enum ROM {
    MIUI, EMUI, OxygenOS, LineageOS,
    PixelExperience, ColorOS, OneUI
};


class Matrix {
private:
    int width;
    int height;

public:
    Matrix() : width(800), height(600) {
        std::cout << "Matrix -> Default constructor was called" << std::endl;
    }

    explicit Matrix(int dim) : width(dim), height(dim) {
        std::cout << "Matrix -> Constructor with dim parameter was called" << std::endl;
    }

    Matrix(int width, int height) : width(width), height(height) {
        std::cout << "Matrix -> Constructor with screen_width and screen_height parameters was called" << std::endl;
    }

    ~Matrix() {
        std::cout << "Matrix -> The destructor was called" << std::endl;
    }

    int get_width() const {
        return width;
    }

    int get_height() const {
        return height;
    }
};


class Screen : public Matrix {
private:
    void init_pixels() {
        pixels = new int *[get_height()];
        for (int i = 0; i < get_height(); ++i)
            pixels[i] = new int[get_width()]{0};
    }

protected:
    int **pixels{};

public:
    Screen() : Matrix() {
        init_pixels();
        std::cout << "Screen -> Default constructor was called" << std::endl;
    }

    explicit Screen(int dim) : Matrix(dim) {
        init_pixels();
        std::cout << "Screen -> Constructor with dim parameter was called" << std::endl;
    }

    Screen(int screen_width, int screen_height) : Matrix(screen_width, screen_height) {
        init_pixels();
        std::cout << "Screen -> Constructor with screen_width and screen_height parameters was called" << std::endl;
    }

    Screen(const Screen &screen) : Matrix(screen.get_width(), screen.get_height()),
                                   pixels(screen.pixels) {
        std::cout << "Screen -> The copy constructor was called" << std::endl;
    }

    ~Screen() {
        std::cout << "Screen -> The destructor was called" << std::endl;
    }

    void set_pixel(int width, int height, int color) {
        pixels[height][width] = color;
    }

    int get_pixel(int width, int height) {
        return pixels[height][width];
    }
};


class Phone {
private:
    std::vector<NetworkTechnology> mobile_network_technologies;
    Screen screen;
    bool working{false};

public:
    Phone() : screen(),
              mobile_network_technologies(std::vector<NetworkTechnology>{NetworkTechnology::EDGE}) {
        std::cout << "Phone -> Default constructor was called" << std::endl;
    }

    Phone(std::vector<NetworkTechnology> mobile_network_technologies,
          int screen_width,
          int screen_height) : screen(screen_width, screen_height),
                               mobile_network_technologies(mobile_network_technologies) {
        std::cout << "Phone -> Constructor with mnt, screen_width and screen_height parameters was called" << std::endl;
    }

    Phone(std::vector<NetworkTechnology> mobile_network_technologies,
          const Screen &screen) : screen(screen),
                                  mobile_network_technologies(mobile_network_technologies) {
        std::cout << "Phone -> Constructor with mnt, screen_width and screen_height parameters was called" << std::endl;
    }

    const std::vector<NetworkTechnology> &get_network_technologies() const { return mobile_network_technologies; };

    const Screen &get_screen() const { return screen; }

    bool is_working() const { return working; }

    void turn_on() { working = true; }

    void turn_off() { working = false; }

    ~Phone() { std::cout << "Phone -> The destructor was called" << std::endl; }
};


class Camera : public Matrix {
private:
    float pixel_size; // в дюймах
    bool ois;

public:
    Camera() : Matrix(800, 600), pixel_size(1), ois(false) {
        std::cout << "Camera -> Default contructor was called" << std::endl;
    }

    Camera(int matrix_width, int matrix_height,
           float pixel_size, bool ois) : Matrix(matrix_width, matrix_height),
                                         pixel_size(pixel_size),
                                         ois(ois) {
        std::cout << "Camera -> Constructor with args was called" << std::endl;
    }

    bool support_ois() const { return ois; }

    long get_matrix_size() {
        return pixel_size * pixel_size * get_width() * get_height();
    }

    ~Camera() { std::cout << "Camera -> The destructor was called" << std::endl; }

};


class TouchTone : public Phone {
private:
    int buttons_count;

public:
    TouchTone() : buttons_count(12), Phone() {
        std::cout << "TouchTone -> Default constructor was called" << std::endl;
    }

    explicit TouchTone(int buttons_count) : buttons_count(buttons_count), Phone() {
        std::cout << "TouchTone -> Constructor with buttons_count arg was called" << std::endl;
    }

    ~TouchTone() { std::cout << "TouchTone -> The destructor was called" << std::endl; }
};


class Smartphone : public Phone {
private:
    ROM rom;
    Camera camera;

public:
    Smartphone() : Phone(), rom(ROM::PixelExperience), camera() {
        std::cout << "Smartphone -> Default constructor was called" << std::endl;
    }

    Smartphone(std::vector<NetworkTechnology> mobile_network_technologies, int screen_width, int screen_height) : Phone(
            mobile_network_technologies, screen_width, screen_height), rom(ROM::PixelExperience), camera() {
        std::cout << "Smartphone -> Constructor with screen size & mnt was called" << std::endl;
    }

    Smartphone(std::vector<NetworkTechnology> mobile_network_technologies, int screen_width, int screen_height, ROM rom)
            : Phone(
            mobile_network_technologies, screen_width, screen_height), rom(rom), camera() {
        std::cout << "Smartphone -> Constructor with screen size, mnt & rom was called" << std::endl;
    }

    Smartphone(std::vector<NetworkTechnology> mobile_network_technologies, int screen_width, int screen_height, ROM rom,
               const Camera &camera) : Phone(
            mobile_network_technologies, screen_width, screen_height), rom(rom), camera(camera) {
        std::cout << "Smartphone -> Constructor with screen size, mnt, rom & camera was called" << std::endl;
    }

    Smartphone(const Smartphone &smartphone) : Phone(smartphone.get_network_technologies(), smartphone.get_screen()),
                                               rom(smartphone.rom),
                                               camera(smartphone.camera) {
        std::cout << "Smartphone -> The copy constructor was called" << std::endl;
    }

    ~Smartphone() { std::cout << "Smartphone -> The destructor was called" << std::endl; }

};


void print_headline(const std::string &text) {
    set_color(4);
    std::cout << text;
    set_color(7);
}

void dynamic_test() {
    print_headline("\nDynamic\n");
    Phone *phonesDynamic[2];
    print_headline("1) Setting smartphone\n");
    phonesDynamic[0] = new Smartphone();
    print_headline("2) Setting touchtone\n");
    phonesDynamic[1] = new TouchTone();

    print_headline("Check if phones are working (1):\n");
    for (auto item: phonesDynamic)
        std::cout << item->is_working() << std::endl;

    print_headline("Turning on phones:\n");
    for (auto item: phonesDynamic)
        item->turn_on();

    print_headline("Check if phones are working (2):\n");
    for (auto item: phonesDynamic)
        std::cout << item->is_working() << std::endl;

    print_headline("Deleting elements manually:\n");
    for (auto item: phonesDynamic)
        delete item;
}

void static_test() {
    print_headline("\nStatic\n");
    Phone phonesStatic[2];
    print_headline("1) Setting smartphone\n");
    phonesStatic[0] = Smartphone();
    print_headline("2) Setting touchtone\n");
    phonesStatic[1] = TouchTone();

    print_headline("Check if phones are working (1):\n");
    for (const auto &item: phonesStatic)
        std::cout << item.is_working() << std::endl;

    print_headline("Turning on phones:\n");
    for (auto &item: phonesStatic)
        item.turn_on();

    print_headline("Check if phones are working (2):\n");
    for (const auto &item: phonesStatic)
        std::cout << item.is_working() << std::endl;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    int n;
    print_headline("Выберите вариант:\n");
    std::cout << "1) Динамическая инициализация с наследованием" << std::endl
              << "2) Статическая инициализация с наследованием" << std::endl;
    std::cin >> n;
    if (n == 1)
        dynamic_test();
    else
        static_test();
    return 0;
}

#pragma clang diagnostic pop