void api_putchar(int c);
void api_end(void);

int HariMain()
{
    char a[100];
    a[10] = 'A';
    api_putchar(a[10]);
    a[102] = 'B';
    api_putchar(a[102]);
    a[222] = 'C';
    api_putchar(a[222]);
    api_end();
}
