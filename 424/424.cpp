#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>

class BigDecimal
{
public:
    BigDecimal() : data(), s(), updated(true)
    {
        this->data.push_back(0);
        this->str();
    }
    void add(const std::string& addend)
    {
        if (addend == "0") return;

        auto it = addend.cend();
        int len, i = 0;
        uint64_t block, carry = 0;

        while ((len = it - addend.cbegin()) > 0)
        {
            if (i >= this->data.size()) this->data.push_back(0);
            if (len > block_size_len) len = block_size_len;

            block = std::stoull(std::string(it - len, it)) + this->data[i] + carry;
            carry = block / block_size;
            block %= block_size;
            this->data[i] = block;

            it -= len;
            ++i;
        }
        if (carry)
        {
            if (i >= this->data.size()) this->data.push_back(carry);
            else this->data[i] += carry;
        }

        this->updated = true;
    }
    // const std::string& str() const { return this->s; }
    std::string str()
    {
        if (this->updated)
        {
            std::ostringstream stream;
            int i = this->data.size() - 1;
            stream  << this->data[i--]
                    << std::setw(block_size_len)
                    << std::setfill('0');
            while (i >= 0) stream << this->data[i--];
            this->s = stream.str();
            this->updated = false;
        }
        return this->s;
    }
private:
    std::vector<uint64_t> data;
    std::string s;
    bool updated;
    // log(2^64)=19
    static const constexpr uint64_t block_size = 1000000000000000000;
    static const constexpr int block_size_len = 18;
};

int main(int argc, char** argv)
{
    BigDecimal bd;
    std::string tmp;

    while (std::cin >> tmp && tmp != "0")
    {
        bd.add(tmp);
    }
    std::cout << bd.str() << std::endl;

    return 0;
}
