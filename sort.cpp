// sort.cpp (Sorting by Successive Selection)

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <random>
#include <iomanip>

template <typename T, class Compare>
void mergesort(std::vector<T> & v, size_t first, size_t last, const Compare & comp)

{
    size_t i = 2, j = 1;        // Verschmolzen werden Mengen der Größe j
    std::vector<T> w(0);

    while(j <= last)
    {
        w = v;
        v.clear();

        for (size_t k = first; k <= last; k += i)
        {
            size_t cur1 = k, cur2 = k+j;

            if (cur2 > last) //"Partner"-lose Menge wird übernommen
            {
                for (size_t l = cur1; l <= last; ++l)
                {
                    v.push_back(w[l]);
                }
            }
            while(cur1 < k+j and cur2 < k+2*j and cur2 <= last)
            {
                if (comp(w[cur2],w[cur1]))
                {
                    v.push_back(w[cur2]);
                    cur2 += 1;
                }
                else
                {
                    v.push_back(w[cur1]);
                    cur1 += 1;
                }

                if (cur1 == k+j)
                {
                    for (size_t l = cur2; l < k+2*j and l <= last; l++)
                    {
                        v.push_back(w[l]);
                    }
                }
                if (cur2 == k+2*j or cur2 > last)
                {
                    for (size_t l = cur1; l < k+j; l++)
                    {
                        v.push_back(w[l]);
                    }
                }
            }
        }
        i *= 2;
        j *= 2;
    }
}


struct Date {
    Date()                                     // random constructor
    {
        time_t rdate = distribution(generator);
        _time = *localtime(&rdate);
    }

    Date(time_t date): _time (*localtime(&date)) {}     // constructor

    static std::uniform_int_distribution<time_t> distribution;
    static std::default_random_engine generator;
    static time_t today;
    tm _time;
};

time_t Date::today = time(nullptr);
std::uniform_int_distribution<time_t> Date::distribution (1, Date::today);
std::default_random_engine Date::generator (Date::today);


std::ostream & operator<<(std::ostream & os, const Date & date)
{
    static const std::string monthname[12] =  {"Jan", "Feb", "Mar",
        "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    os << monthname[date._time.tm_mon] << " " << std::setw(2)
       << date._time.tm_mday << ", " << date._time.tm_year + 1900;
    return os;
}


class BirthdayComparison {
public:
    BirthdayComparison(const Date & today) : _today(today) {}
    bool operator()(const Date & b1, const Date & b2) const
    {
        return day_num (b1) < day_num (b2);
    }
private:
    int day_num(const Date & date) const
    {
        return (32 * (12 + date._time.tm_mon - _today._time.tm_mon) +
                date._time.tm_mday  - _today._time.tm_mday) % (12*32);
    }
    Date const & _today;
};


int main()
{
    std::cout << "Today is " << Date(Date::today) << ".\n"
              << "How many random birthdays do you want to sort? ";
    int n;
    std::cin >> n;
    std::vector<Date> dates(n);
    std::cout << "Here are " << n << " random dates:\n";
    for (auto d: dates) {
        std::cout << d << "    ";
    }
    std::cout << "\n\n";

    BirthdayComparison comparison((Date(Date::today)));
    std::cout << "Sorting..." << std::endl;
    clock_t timer = clock();
    mergesort(dates, 0, dates.size() - 1, comparison);
    timer = clock() - timer;

    std::cout << "The upcoming birthdays are, starting today:\n";
    for (auto d: dates) {
        std::cout << d << "    ";
    }
    std::cout << "\n\n" << "Sorting took "
              << static_cast<double>(timer)/CLOCKS_PER_SEC << " seconds.\n";
}
