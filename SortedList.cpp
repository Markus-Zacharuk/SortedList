#include <vector>
#include <functional>
#include <iostream>
#include <algorithm>
#include <string>

template <class T>
struct SortedList
{
private:
    std::vector<T> list;
    bool is_reversed;
    std::function<bool (const T&, const T&)> comparator;
    void sort() { std::sort(list.begin(), list.end(), comparator); } // Sorts thr list.
public:
    SortedList(bool is_reversed, std::function<bool(const T&, const T&)> comparator) :
        is_reversed{ is_reversed }, comparator{ comparator } {}
    SortedList(const std::vector<T>& list, bool is_reversed, std::function<bool (const T&, const T&)> comparator) :
        list{ list }, is_reversed{ is_reversed }, comparator(comparator) { sort(); /*Sort the list in case.*/ }
    void insert(const T& arg)
    {
        list.insert(upper_bound(list.begin(), list.end(), 
            [reverse, comparator](const T& left, const T& right) -> bool { 
                return is_reversed ? !comparator(left, right) : comparator(left, right);
            }
            ));
    }
    // You can get the list, but aren't allowed to modify it.
    const std::vector<T>& get_const_list() const { return list; }
    // You can get the comparator, but aren't allowed to modify it.
    const std::vector<T>& get_const_comparator() const { return comparator; }
    void set_comparator(std::function<bool(const T&, const T&)> new_comparator)
    {
        comparator = new_comparator;
        sort();
    }
    void reverse()
    {
        is_reversed = !is_reversed;
        // Assuming total order, this works.
        std::reverse(list.begin(), list.end());
    }

};

template <class T>
std::ostream& operator<< (std::ostream& stream, SortedList<T> rhs) {
    std::string seperator = "";
    stream << "[";
    const std::vector<T>& list = rhs.get_const_list();
    for (const T& element : list)
    {
        stream << seperator << element;
        seperator = ", ";
    }
    stream << "]";
    return stream;
}

void test1()
{
    std::cout << "Test 1\n\n";

    std::vector<int> arg {1, 3, 4, 5, 2, 6};
    SortedList<int> list( 
        arg, false, [](int left, int right) -> bool { return left < right;  }
    );
    std::cout << "Created with {1, 3, 4, 5, 2, 6}\n";
    std::cout << "-> " << list << std::endl;

    std::cout << "Reverse it!\n";
    list.reverse();
    std::cout << list << std::endl;

    std::cout << "Reverse it again!\n";
    list.reverse();
    std::cout << list << std::endl;

    std::cout << "Set a new comparator, which should reverse it again!\n";
    list.set_comparator([](int left, int right) -> bool { return left > right;  });
    std::cout << list << std::endl << std::endl;
}


void test2()
{
    std::cout << "Test 2\n\n";

    std::vector<int> arg{ 1, 3, 4, 5, 2, 6, 9, 7, 8, 15, 13, 14, 11, 10, 100, 200, 150, 999, 643, 1000};
    SortedList<int> list(
        arg, false, [](int left, int right) -> bool { return left < right;  }
    );
    std::cout << "Created with {1, 3, 4, 5, 2, 6, 9, 7, 8, 15, 13, 14, 11, 10, 100, 200, 150, 999, 643, 1000}\n";
    std::cout << "-> " << list << std::endl;

    std::cout << "Reverse it!\n";
    list.reverse();
    std::cout << list << std::endl;

    std::cout << "Reverse it again!\n";
    list.reverse();
    std::cout << list << std::endl;

    std::cout << "Set a new comparator, which should reverse it again!\n";
    list.set_comparator([](int left, int right) -> bool { return left > right;  });
    std::cout << list << std::endl << std::endl;
}

int main()
{
    test1();
    test2();
};
