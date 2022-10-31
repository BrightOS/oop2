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
        std::cout << "Matrix()" << std::endl;
    }

    explicit Matrix(int dim) : width(dim), height(dim) {
        std::cout << "Matrix(int dim)" << std::endl;
    }

    Matrix(int width, int height) : width(width), height(height) {
        std::cout << "Matrix(int width, int height)" << std::endl;
    }

    Matrix(const Matrix &matrix) : width(matrix.width), height(matrix.height) {
        std::cout << "Matrix(const Matrix &matrix)" << std::endl;
    }

    ~Matrix() {
        std::cout << "~Matrix()" << std::endl;
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
        std::cout << "Screen()" << std::endl;
    }

    explicit Screen(int dim) : Matrix(dim) {
        init_pixels();
        std::cout << "Screen(int dim)" << std::endl;
    }

    Screen(int screen_width, int screen_height) : Matrix(screen_width, screen_height) {
        init_pixels();
        std::cout << "Screen(int screen_width, int screen_height)" << std::endl;
    }

    Screen(const Screen &screen) : Matrix(screen.get_width(), screen.get_height()),
                                   pixels(screen.pixels) {
        std::cout << "Screen(const Screen &screen)" << std::endl;
    }

    ~Screen() {
        std::cout << "~Screen()" << std::endl;
    }

    void set_pixel(int width, int height, int color) {
        pixels[height][width] = color;
    }

    int get_pixel(int width, int height) {
        return pixels[height][width];
    }
};


class Camera : public Matrix {
private:
    float pixel_size; // в дюймах
    bool ois;

public:
    Camera() : Matrix(800, 600), pixel_size(1), ois(false) {
        std::cout << "Camera()" << std::endl;
    }

    Camera(int matrix_width, int matrix_height,
           float pixel_size, bool ois) : Matrix(matrix_width, matrix_height),
                                         pixel_size(pixel_size),
                                         ois(ois) {
        std::cout << "Camera(int matrix_width, int matrix_height, float pixel_size, bool ois)" << std::endl;
    }

    Camera(const Camera &camera) : Matrix(camera.get_width(), camera.get_height()),
                                   pixel_size(camera.pixel_size),
                                   ois(camera.ois) {
        std::cout << "Camera(const Camera &camera)" << std::endl;
    }

    bool support_ois() const { return ois; }

    double get_matrix_size() {
        return pixel_size * pixel_size * 1.0 * get_width() * get_height();
    }

    ~Camera() { std::cout << "~Camera()" << std::endl; }

};


class Phone {
private:
    std::vector<NetworkTechnology> mobile_network_technologies;
    Screen screen;
    bool working{false};

public:
    Phone() : screen(),
              mobile_network_technologies(std::vector<NetworkTechnology>{NetworkTechnology::EDGE}) {
        std::cout << "Phone()" << std::endl;
    }

    Phone(std::vector<NetworkTechnology> mobile_network_technologies)
            : screen(),
              mobile_network_technologies(std::move(mobile_network_technologies)) {
        std::cout << "Phone(std::vector<NetworkTechnology> mobile_network_technologies)" << std::endl;
    }

    Phone(std::vector<NetworkTechnology> mobile_network_technologies, int screen_width, int screen_height)
            : screen(screen_width, screen_height),
              mobile_network_technologies(std::move(mobile_network_technologies)) {
        std::cout
                << "Phone(std::vector<NetworkTechnology> mobile_network_technologies, int screen_width, int screen_height)"
                << std::endl;
    }

    Phone(const Phone &phone) : screen(phone.screen),
                                mobile_network_technologies(phone.mobile_network_technologies) {
        std::cout << "Phone(const Phone &phone)" << std::endl;
    }

    const std::vector<NetworkTechnology> &get_network_technologies() const { return mobile_network_technologies; };

    const Screen &get_screen() const { return screen; }

    bool is_working() const { return working; }

    void turn_on() { working = true; }

    void turn_off() { working = false; }

    ~Phone() { std::cout << "~Phone()" << std::endl; }
};


class TouchTone : public Phone {
private:
    int buttons_count;

public:
    TouchTone() : buttons_count(12), Phone() {
        std::cout << "TouchTone()" << std::endl;
    }

    explicit TouchTone(int buttons_count) : buttons_count(buttons_count), Phone() {
        std::cout << "TouchTone(int buttons_count)" << std::endl;
    }

    int get_buttons_count() const {
        return buttons_count;
    }

    ~TouchTone() { std::cout << "~TouchTone()" << std::endl; }
};


class Smartphone : public Phone {
private:
    ROM rom;
    Camera camera;

public:
    Smartphone() : Phone(
            std::vector<NetworkTechnology>{
                    NetworkTechnology::EDGE, NetworkTechnology::GPRS,
                    NetworkTechnology::HSPA, NetworkTechnology::UMTS
            }), rom(ROM::PixelExperience), camera() {
        std::cout << "Smartphone()" << std::endl;
    }

    Smartphone(std::vector<NetworkTechnology> mobile_network_technologies, int screen_width, int screen_height) : Phone(
            std::move(mobile_network_technologies), screen_width, screen_height), rom(ROM::PixelExperience), camera() {
        std::cout
                << "Smartphone(std::vector<NetworkTechnology> mobile_network_technologies, int screen_width, int screen_height)"
                << std::endl;
    }

    Smartphone(std::vector<NetworkTechnology> mobile_network_technologies, int screen_width, int screen_height, ROM rom)
            : Phone(
            std::move(mobile_network_technologies), screen_width, screen_height), rom(rom), camera() {
        std::cout
                << "Smartphone(std::vector<NetworkTechnology> mobile_network_technologies, int screen_width, int screen_height, ROM rom)"
                << std::endl;
    }

    Smartphone(std::vector<NetworkTechnology> mobile_network_technologies, int screen_width, int screen_height, ROM rom,
               const Camera &camera) : Phone(
            std::move(mobile_network_technologies), screen_width, screen_height), rom(rom), camera(camera) {
        std::cout
                << "Smartphone(std::vector<NetworkTechnology> mobile_network_technologies, int screen_width, int screen_height, ROM rom, Camera camera)"
                << std::endl;
    }

    Smartphone(const Smartphone &smartphone) : Phone(smartphone),
                                               rom(smartphone.rom),
                                               camera(smartphone.camera) {
        std::cout << "Smartphone(const Smartphone &smartphone)" << std::endl;
    }

    ~Smartphone() { std::cout << "~Smartphone()" << std::endl; }

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

    print_headline("Turning on phones...\n");
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

    print_headline("Turning on phones...\n");
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