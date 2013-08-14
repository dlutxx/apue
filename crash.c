
static int a(int* p);

int main(int argc, char* argv[])
{
    int * p = (int*)0;
    return a(p);
}

int a(int* p)
{
    int y=*p;
    return y;
}


