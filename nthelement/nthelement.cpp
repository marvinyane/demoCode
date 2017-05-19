#include <iostream>
#include <algorithm>
#include <vector>

bool test_func(int i, int j) 
{
    return i < j;
}

int main()
{
    std::vector<int> t;
    for (int i = 1; i <= 10; i++) 
        t.push_back(i);

    t.push_back(8);
    t.push_back(8);
    t.push_back(8);
    t.push_back(8);
    t.push_back(8);
    t.push_back(8);
    t.push_back(8);
    t.push_back(8);
    t.push_back(8);
    t.push_back(8);
    t.push_back(8);
    t.push_back(8);
    t.push_back(8);

    std::random_shuffle(t.begin(), t.end());

    std::nth_element(t.begin(), t.begin()+5, t.end(), test_func);

    for(int i = 0; i < t.size(); i++)
    {
        std::cout << t[i] << " ";
    }

    std::cout << "\n";

    return 0;
}
