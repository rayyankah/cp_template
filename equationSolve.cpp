pi solveEq(int a1, int b1, int n1, int a2, int b2, int n2)
{
    // a1x + b1y = n1
    // a2x + b2y = n2
    int det = a1 * b2 - a2 * b1;
    if (det == 0)
    {
        // check if they are consistent
        if (a1 * n2 == a2 * n1)
        {
            // inf solutions
            return {0, 0};
        }
        else
        {
            // no solution
            return {-1, -1};
        }
    }
    else
    {
        if((n1*b2 - n2*b1) % det != 0 || (a1*n2 - a2*n1) % det != 0)
            return {-1,-1};
        int x = (n1 * b2 - n2 * b1) / det;
        int y = (a1 * n2 - a2 * n1) / det;
        if(x<0 || y<0)
            return {-1,-1};
        return {x, y};
    }
}
