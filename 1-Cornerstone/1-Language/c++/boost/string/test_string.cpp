#include <exception>
#include <iostream>
#include <boost/lexical_cast.hpp>

using boost::lexical_cast;

int boost_a2i()
{
    int a = boost::lexical_cast<int>("123456");
    std::cout << a << std::endl;
    double b = boost::lexical_cast<double>("123.12");
    std::cout << b << std::endl;
    long double c = lexical_cast<long double>("123.11");
    std::cout << c << std::endl;
    return 0;
}

int boost_i2a()
{
    using std::string;
    const double d = 123.12;
    string s = boost::lexical_cast<string>(d);
    std::cout << s << std::endl;
    return 0;
}

int boost_except()
{
    int i;
    try{
        i = boost::lexical_cast<int>("abc");
    }
    catch(boost::bad_lexical_cast & e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }

    std::cout << i << std::endl;
    return 0;
}

int boost_except2()
{
    int i;
    i = boost::lexical_cast<int>("abc");

    std::cout << "except happen!" << std::endl;
    return 0;
}


int main(int argc, char ** argv)
{
    if (argc != 2) {
        std::cout << "less params" << std::endl;
        return -1;
    }
    
    int index = atoi(argv[1]);

    switch(index) {
        case 0:
            boost_a2i();
            break;
        case 1:
            boost_i2a();
            break;
        case 2:
            boost_except();
            break;
        case 3:
            try {
                boost_except2();
            } catch (const std::exception &exc) {
                std::cout << "catch it!" << std::endl;
                std::cout << exc.what() << std::endl;
            }
            break;
        default:
            std::cout << "default" << std::endl;
            break;
            
    }

    return 0;
}
