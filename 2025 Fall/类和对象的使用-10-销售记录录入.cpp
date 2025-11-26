#include <iostream>

class Book_Sale {
private:
    char* isbn_ptr_;
    int sales_volume_;
    double original_price_;
    double real_price_;
    double discount_;
    double gross_sales_;

    int strLength(const char* str) {
        if (str == nullptr) return 0;
        int len = 0;
        while (str[len] != '\0') {
            len++;
        }
        return len;
    }

    void strCopy(char* dest, const char* src) {
        if (src == nullptr || dest == nullptr) return;
        int i = 0;
        while (src[i] != '\0') {
            dest[i] = src[i];
            i++;
        }
        dest[i] = '\0';
    }

    void strConcat(char* dest, const char* src) {
        if (src == nullptr || dest == nullptr) return;
        int dest_len = strLength(dest);
        int i = 0;
        while (src[i] != '\0') {
            dest[dest_len + i] = src[i];
            i++;
        }
        dest[dest_len + i] = '\0';
    }

    void intToStr(int num, char* str, int width = 0) {
        if (str == nullptr) return;

        if (num == 0) {
            str[0] = '0';
            str[1] = '\0';
            return;
        }

        char temp[20] = { 0 };
        int i = 0;
        int num_copy = num;

        while (num_copy > 0) {
            temp[i++] = '0' + (num_copy % 10);
            num_copy /= 10;
        }

        int start = 0;
        int end = i - 1;
        while (start < end) {
            char c = temp[start];
            temp[start] = temp[end];
            temp[end] = c;
            start++;
            end--;
        }

        temp[i] = '\0';

        int len = i;
        if (width > len) {
            int zeros = width - len;
            for (int j = 0; j < zeros; j++) {
                str[j] = '0';
            }
            strCopy(str + zeros, temp);
        }
        else {
            strCopy(str, temp);
        }
    }

    char calculateCheckDigit(const char* isbn_base) {
        if (isbn_base == nullptr) return '0';

        int sum = 0;
        int weight = 1;

        for (int i = 0; isbn_base[i] != '\0'; i++) {
            if (isbn_base[i] >= '0' && isbn_base[i] <= '9') {
                sum += (isbn_base[i] - '0') * weight;
                weight++;
            }
        }

        int remainder = sum % 11;
        if (remainder == 10) {
            return 'X';
        }
        else {
            return '0' + remainder;
        }
    }

    void buildIsbn(int fourth_part) {
        char fourth_str[6] = { 0 };
        intToStr(fourth_part, fourth_str, 5);

        char isbn_base[13] = { 0 };
        strCopy(isbn_base, "9787121");
        strConcat(isbn_base, fourth_str);

        char check_digit = calculateCheckDigit(isbn_base);

        char full_isbn[20] = { 0 };
        strCopy(full_isbn, "978-7-121-");
        strConcat(full_isbn, fourth_str);
        strConcat(full_isbn, "-");

        int len = strLength(full_isbn);
        full_isbn[len] = check_digit;
        full_isbn[len + 1] = '\0';

        if (isbn_ptr_ != nullptr) {
            delete[] isbn_ptr_;
        }

        int new_len = strLength(full_isbn);
        isbn_ptr_ = new char[new_len + 1];
        strCopy(isbn_ptr_, full_isbn);
    }

public:
    Book_Sale(std::istream& is) : isbn_ptr_(nullptr) {
        readFromStream(is);
    }

    Book_Sale() : isbn_ptr_(nullptr), sales_volume_(0), original_price_(0),
        real_price_(0), discount_(0), gross_sales_(0) {
    }

    Book_Sale(const Book_Sale& other) {
        if (other.isbn_ptr_ != nullptr) {
            int len = strLength(other.isbn_ptr_);
            isbn_ptr_ = new char[len + 1];
            strCopy(isbn_ptr_, other.isbn_ptr_);
        }
        else {
            isbn_ptr_ = nullptr;
        }
        sales_volume_ = other.sales_volume_;
        original_price_ = other.original_price_;
        real_price_ = other.real_price_;
        discount_ = other.discount_;
        gross_sales_ = other.gross_sales_;
    }

    Book_Sale& operator=(const Book_Sale& other) {
        if (this != &other) {
            delete[] isbn_ptr_;

            if (other.isbn_ptr_ != nullptr) {
                int len = strLength(other.isbn_ptr_);
                isbn_ptr_ = new char[len + 1];
                strCopy(isbn_ptr_, other.isbn_ptr_);
            }
            else {
                isbn_ptr_ = nullptr;
            }

            sales_volume_ = other.sales_volume_;
            original_price_ = other.original_price_;
            real_price_ = other.real_price_;
            discount_ = other.discount_;
            gross_sales_ = other.gross_sales_;
        }
        return *this;
    }

    ~Book_Sale() {
        delete[] isbn_ptr_;
    }

    void readFromStream(std::istream& is) {
        int fourth_part;
        is >> fourth_part;

        if (is.fail()) return;

        is >> sales_volume_ >> original_price_ >> discount_;

        if (is.fail()) return;

        buildIsbn(fourth_part);
        real_price_ = original_price_ * discount_;
        gross_sales_ = real_price_ * sales_volume_;
    }

    void formatDouble(double value) const {
        int int_part = static_cast<int>(value);
        std::cout << int_part << ".";

        double fractional = value - int_part;
        for (int i = 0; i < 3; i++) {
            fractional *= 10;
            int digit = static_cast<int>(fractional);
            std::cout << digit;
            fractional -= digit;
        }
    }

    void display() const {
        std::cout << "该书的ISBN号为:" << (isbn_ptr_ ? isbn_ptr_ : "") << std::endl;
        std::cout << "销量为:" << sales_volume_ << "本 ";
        std::cout << "原价为:";
        formatDouble(original_price_);
        std::cout << "元 ";
        std::cout << "折扣为:" << discount_ << " ";
        std::cout << "现价为:";
        formatDouble(real_price_);
        std::cout << "元 ";
        std::cout << "总销售额为:";
        formatDouble(gross_sales_);
        std::cout << "元" << std::endl;
    }
};

int main() {
    int fourth_part;

    std::cin >> fourth_part;
    if (fourth_part == -1) {
        return 0;
    }

    Book_Sale first_book(std::cin);
    first_book.display();

    while (true) {
        std::cin >> fourth_part;
        if (fourth_part == -1) {
            break;
        }

        Book_Sale book;
        book.readFromStream(std::cin);
        book.display();
    }

    return 0;
}