extern "C" 
{

extern int add(int a, int b);

int func(int a)
{
    return add(a, 1) ;
}

}
